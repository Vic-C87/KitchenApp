#include "WindowManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

const int WIDTH = 800;
const int HEIGHT = 600;

//Callbacks
void CBKeyInput(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
void CBWindowResize(GLFWwindow* aWindow, int aWidth, int aHeight);
void CBDropFile(GLFWwindow* aWindow, int aCount, const char** somePaths);

int main()
{
	WindowManager winManager(WIDTH, HEIGHT);
	if (!winManager.Initialize())
	{
		return -1;
	}
	GLFWwindow* window = winManager.GetWindow();	

	//register callbacks
	glfwSetKeyCallback(window, CBKeyInput);
	glfwSetFramebufferSizeCallback(window, CBWindowResize);
	glfwSetDropCallback(window, CBDropFile);

	//IMGUI setup (DO THIS AFTER CALLBACK REGISTERS)
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	glEnable(GL_DEPTH_TEST);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		glClearColor(.2f, .3f, .2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Start the Dear ImGui frame
		ImGui::NewFrame();
		ImGui::Begin("Render inside IMGUI");

		ImGui::Text("Test!");
		
		ImGui::End();


		//// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		//{
		//	static float f = 0.0f;
		//	static int counter = 0;

		//	ImGui::Begin("Options");                          // Create a window called "Hello, world!" and append into it.

		//	ImGui::InputFloat3("Position", &position[0]);
		//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//		counter++;
		//	ImGui::SameLine();
		//	ImGui::Text("counter = %d", counter);

		//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		//	ImGui::End();
		//}

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

#pragma region CallBacks

void CBKeyInput(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode)
{
	if (aKey == GLFW_KEY_ESCAPE && anAction == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(aWindow, GL_TRUE);
	}
}

void CBWindowResize(GLFWwindow* aWindow, int aWidth, int aHeight)
{
	glViewport(0, 0, aWidth, aHeight);
}

void CBDropFile(GLFWwindow* aWindow, int aCount, const char** somePaths)
{
	for (int i = 0; i < aCount; i++)
	{
		std::cout << "Path: " << somePaths[i] << std::endl;
	}
}

#pragma endregion 