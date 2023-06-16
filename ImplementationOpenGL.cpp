//#include <string>
//#include <iostream>
//#include <sstream>  
//#include <fstream>
//#include <filesystem>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image.h"
//#include "stb_image_write.h"
//
//#include "Window.h"
//#include "Renderer.h"
//#include "Shader.h"
//#include "Texture.h"
//#include "IndexBuffer.h"
//#include "VertexBuffer.h"
//#include "VertexBufferLayout.h"
//#include "VertexArray.h"
//
//static const unsigned int SCREEN_WIDTH = 700;
//static const unsigned int SCREEN_HEIGHT = 700;
//
//static void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//static void storeRenderData(std::vector<unsigned char>* buffer)
//{
//	_glCall(glPixelStorei(GL_PACK_ALIGNMENT, 4));
//	_glCall(glReadBuffer(GL_FRONT));
//	_glCall(glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, buffer->data()));
//}
//
//static void saveImage(const char* filepath, std::vector<unsigned char>* buffer, unsigned int nrChannels, unsigned int stride)
//{
//	storeRenderData(buffer);
//	stbi_flip_vertically_on_write(true);
//	stbi_write_png(filepath, SCREEN_WIDTH, SCREEN_HEIGHT, nrChannels, buffer->data(), stride);
//}
//
//static void PushStyleCompact()
//{
//	ImGuiStyle& style = ImGui::GetStyle();
//	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
//	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));
//}
//
//static void PopStyleCompact()
//{
//	ImGui::PopStyleVar(2);
//}
//
//int main()
//{
//	Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Tesis Shaders y Autómatas");
//
//	float vertices[] = {
//		 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//		 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//		-1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//		-1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f
//	};
//
//	unsigned int indices[] = {
//		0,1,3,
//		1,2,3
//	};
//
//	VertexBuffer VertexBufferObject(vertices, 8 * 4 * sizeof(float));
//	IndexBuffer ElementBufferObject(indices, 6);
//	VertexArray VertexArrayObject;
//	VertexBufferLayout layout;
//	layout.Push<float>(3);
//	layout.Push<float>(3);
//	layout.Push<float>(2);
//	VertexArrayObject.AddBuffer(VertexBufferObject, layout);
//
//	Shader* shader = new Shader("Resources/Shaders/roomGenerator.shader");
//
//	VertexBufferObject.Unbind();
//	VertexArrayObject.Unbind();
//	ElementBufferObject.Unbind();
//	shader->Unbind();
//	Renderer renderer;
//
//	ImGui::CreateContext();
//	ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
//	ImGui_ImplOpenGL3_Init(window.GetVersion());
//	ImGui::StyleColorsDark();
//
//	ImVec4 colorA = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
//	unsigned int nrChannels = 3;
//	unsigned int stride = nrChannels * SCREEN_WIDTH;
//	stride += (stride % 4) ? (4 - stride % 4) : 0;
//	unsigned int bufferSize = stride * SCREEN_HEIGHT;
//	std::vector<unsigned char> buffer(bufferSize);
//	glm::mat4 model(1.0f);
//
//	float time = 0.0f;
//	double xpos = 0.0f;
//	double ypos = 0.0f;
//	static float intensity = 1.0f;
//	Texture texture("Resources/Textures/fruitBowl.jpg");
//
//	bool isSetupDone = false;
//
//	while (!glfwWindowShouldClose(window.GetWindow()))
//	{	
//		processInput(window.GetWindow());
//		//Render Setup
//		if (!isSetupDone)
//		{	//Scene setup
//			// Start the ImGui frame
//			ImGui_ImplOpenGL3_NewFrame();
//			ImGui_ImplGlfw_NewFrame();
//			ImGui::NewFrame();
//			//Background
//			renderer.Clear(0.154f, 0.164f, 0.174f, 1.0f);
//
//			{ //ImGui Uniform manager popup 
//				ImGui::Begin("Automata Setup");
//				if (ImGui::TreeNode("Start"))
//				{
//					ImGui::Text("Initialize Automata");
//					ImGui::Checkbox("Start", &isSetupDone);
//					ImGui::TreePop();
//				}
//				
//				//ImGui::Text("Affects the sharpness of edgeDetect.shader's edges");
//				//ImGui::SliderFloat("uIntensity", &intensity, 0.0f, 10.0f);
//				//ImGui::Text("Affects color of rainbowParty.shader's color multiplication");
//				//ImGui::ColorEdit3("uColor", (float*)&colorA);
//				//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//
//				if (ImGui::TreeNode("Pick Shader"))
//				{
//					std::string relativePath = "./Resources/Shaders";
//					std::size_t folderSize = std::distance(std::filesystem::directory_iterator(relativePath), std::filesystem::directory_iterator{});
//					if (ImGui::BeginTable("table1", 2, ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable))
//					{	
//						int row = 0;
//						for (const auto& entry : std::filesystem::directory_iterator(relativePath))
//						{
//							//Parse Filename and Path
//							std::stringstream buffer;
//							buffer << entry.path();							
//							const std::string& tmp = buffer.str();
//							std::string tmp_parse = tmp.substr(0, tmp.size() - 1);
//							tmp_parse = tmp_parse.erase(0, 3);
//							const char* currentFile = tmp_parse.c_str();
//							std::string baseFilename = tmp_parse.substr(tmp_parse.find_last_of("/\\") + 1);
//							const char* fileName = baseFilename.c_str();
//							ImGui::TableNextRow();
//
//							ImU32 row_bg_color = ImGui::GetColorU32(ImVec4(0.2f + row * 0.02f, 0.02f, 0.5f - row * 0.02f, 0.65f)); 
//							ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0 + 1, row_bg_color);
//							for (int column = 0; column < 2; column++)
//							{
//								ImGui::TableSetColumnIndex(column);
//								switch (column)
//								{
//								case 0:
//									if (ImGui::SmallButton(fileName))
//									{
//										std::cout << "Loading Shader on path: " << currentFile << "\n";
//										shader->~Shader();
//										shader = new Shader(currentFile);
//										shader->Unbind();
//									}
//									break;
//
//								case 1:  ImGui::Text(currentFile); break;
//								default: std::cout << "Shader Table exeeded columns\n";
//								}
//							}
//							row++;							
//						}
//						ImGui::EndTable();
//					}
//					ImGui::TreePop();
//				}
//				ImGui::End();
//
//				//ImGui::ShowDemoWindow();
//			} 
//			ImGui::Render();
//			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//			window.SwapBuffers();
//			glfwPollEvents();
//			
//			if (isSetupDone)
//			{
//				ImGui_ImplOpenGL3_Shutdown();
//				ImGui_ImplGlfw_Shutdown();
//				ImGui::DestroyContext();
//			}
//		}
//		//Render Automata
//		else
//		{	
//			renderer.Clear(0.154f, 0.164f, 0.174f, 1.0f);
//			int textureSlot = 0;
//			shader->Bind();
//			texture.Bind(textureSlot);
//
//			glfwGetCursorPos(window.GetWindow(), &xpos, &ypos);
//
//			shader->SetUniform1i("uTexture", textureSlot);
//			shader->SetUniform1i("uWidth", texture.GetWidth());
//			shader->SetUniform1i("uHeight", texture.GetHeight());
//			shader->SetUniform1f("uIntensity", intensity);
//			shader->SetUniform1f("uQuantize", (time * 100) + 1);
//			shader->SetUniform1f("uTime", time);
//			shader->SetUniform2f("uMousePos", (float)xpos, -(float)ypos + 800);
//			shader->SetUniform4f("uColor", colorA.x, colorA.y, colorA.z, colorA.w);
//			shader->SetUniformMatrix4fv("uModel", model);
//			renderer.Draw(VertexArrayObject, ElementBufferObject, *shader);
//
//			window.SwapBuffers();
//			glfwPollEvents();
//			storeRenderData(&buffer);
//			texture.Unbind();
//			texture.NewBufferData(&buffer);
//			time += .0001f;
//		}
//	}
//	saveImage("Resources/Textures/result.jpg", &buffer, nrChannels, stride);
//	return 0;
//}

#include "LoopBlueprint.h"

int main()
{
	LoopDemo demo = LoopDemo("Tesis Shaders y Autómatas");

	while (!demo.EndLoopCondition())
	{
		demo.ExecuteLoop();
	}
	demo.EndLoop();
}