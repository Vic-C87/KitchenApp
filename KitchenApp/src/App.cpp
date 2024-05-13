#include "App.h";

namespace Organizer
{
	App::App()
		: myProductFactory(nullptr), myWindow(nullptr),
		myWidth(1200), myHeight(720)
	{
		mySecondState = Utilities::EAppSecondState::ProductList;
		myThirdState = Utilities::EAppThirdState::None;
	}

	App::~App()
	{
		delete myProductFactory;
	}

	bool App::Initialize()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		myWindow = glfwCreateWindow(myWidth, myHeight, "Kitchen APP", NULL, NULL);
		glfwMakeContextCurrent(myWindow);

		if (myWindow == NULL)
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			glfwTerminate();
			return false;
		}

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0)
		{
			std::cout << "Failed to initialize glad!" << std::endl;
			return false;

		}

		glViewport(0, 0, myWidth, myHeight);

		//register callbacks
		glfwSetKeyCallback(myWindow, CBKeyInput);
		glfwSetFramebufferSizeCallback(myWindow, CBWindowResize);
		glfwSetDropCallback(myWindow, CBDropFile);
		
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

		ImGui_ImplGlfw_InitForOpenGL(myWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();

		glEnable(GL_DEPTH_TEST);

		myProductFactory = new ProductFactory();
		myProductFactory->Load("productList.vic");

		return true;
	}

	void App::Update()
	{
		ImGuiIO& io = ImGui::GetIO();
		int selectedProductIndex = 0;

		while (!glfwWindowShouldClose(myWindow))
		{
			glfwPollEvents();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ImGui::NewFrame();

			DockSpace(io);

			switch (mySecondState)
			{
			case Utilities::EAppSecondState::StartMenu:
				StartScreen(io);
				break;
			case Utilities::EAppSecondState::CookBookSelection:
				break;
			case Utilities::EAppSecondState::RecipeList:
				break;
			case Utilities::EAppSecondState::ProductList:
				ProductScreen(io, selectedProductIndex);
				break;
			default:
				break;
			}

			switch (myThirdState)
			{
			case Utilities::EAppThirdState::None:
				break;
			case Utilities::EAppThirdState::ProductDetails:
				ProductDetailsScreen(io, *myProductFactory->SearchByIndex(selectedProductIndex));
				break;
			case Utilities::EAppThirdState::CreateProduct:
				CreateProductScreen(io);
				break;
			case Utilities::EAppThirdState::EditProduct:
				break;
			case Utilities::EAppThirdState::CreateIngredient:
				break;
			case Utilities::EAppThirdState::EditIngredient:
				break;
			default:
				break;
			}

			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			glfwSwapBuffers(myWindow);

		}
		myProductFactory->SaveToFile("productList.vic");
		glfwTerminate();
	}

	void App::DockSpace(ImGuiIO& anIO)
	{
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("MyDockSpace", NULL, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		if (anIO.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		else
		{
			//ShowDockingDisabledMessage();
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
				if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
				if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("More"))
			{
				ImGui::MenuItem("Info");
				ImGui::Separator();

				ImGui::EndMenu();
			}
			/*HelpMarker(
				"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
				"- Drag from window title bar or their tab to dock/undock." "\n"
				"- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
				"- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
				"- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)" "\n"
				"This demo app has nothing to do with enabling docking!" "\n\n"
				"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window." "\n\n"
				"Read comments in ShowExampleAppDockSpace() for more details.");*/

			ImGui::EndMenuBar();
		}
		ImGui::End();
	}

	void App::StartScreen(ImGuiIO& anIO)
	{
		if (ImGui::Begin("KitchenApp"))
		{
			ImGui::Text("Test!");

			ImGui::End();

		}
	}

	void App::ProductScreen(ImGuiIO& anIO, int& aSelectedProductIndex)
	{
		if (ImGui::Begin("Products"))
		{
			ImGuiStyle& style = ImGui::GetStyle();
			ImVec2 listBoxSize(style.FramePadding.x / 2, ImGui::GetContentRegionAvail().y * .5f);
			static bool language = myProductFactory->GetDisplayLanguage() == Utilities::EDisplayLanguage::English;
			ImGui::Checkbox("English", &language);

			if (language)
			{
				myProductFactory->SetDisplayLanguage(Utilities::EDisplayLanguage::English);
			}
			else
			{
				myProductFactory->SetDisplayLanguage(Utilities::EDisplayLanguage::Svenska);
			}

			ImGui::PushItemWidth(myWidth * 0.25f);
			if (ImGui::BeginListBox("Products"))
			{
				switch (myProductFactory->GetDisplayLanguage())
				{
				case Utilities::EDisplayLanguage::Svenska:
					for (int n = 0; n < myProductFactory->GetProductCount(); n++)
					{
						const bool is_selected = (aSelectedProductIndex == n);
						if (ImGui::Selectable(myProductFactory->SearchByIndex(n)->Name.c_str(), is_selected))
						{
							aSelectedProductIndex = n;
							myThirdState = Utilities::EAppThirdState::ProductDetails;
						}

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					break;
				case Utilities::EDisplayLanguage::English:
					for (int n = 0; n < myProductFactory->GetProductCount(); n++)
					{
						const bool is_selected = (aSelectedProductIndex == n);
						if (ImGui::Selectable(myProductFactory->SearchByIndex(n)->NameEnglish.c_str(), is_selected))
						{
							aSelectedProductIndex = n;
							myThirdState = Utilities::EAppThirdState::ProductDetails;
						}

						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					break;
				default:
					break;
				}
				
				ImGui::EndListBox();
			}

			if (ImGui::Button("NEW"))
			{
				myThirdState = Utilities::EAppThirdState::CreateProduct;
			}

			ImGui::End();
		}
	}

	void App::CreateProductScreen(ImGuiIO& anIO)
	{
		static float f = 0.0f;
		static int counter = 0;

		bool shouldClose = false;
		static char nameField[32] = "";
		static char nameFieldEnglish[32] = "";
		static int item_current_1 = -1;
		const char* storageTypes[] = { "Freezer", "Refridgerator", "Dark n' Cool", "Room" };
		static int item_current_2 = -1;
		const char* messurementTypes[] = { "Weight", "Volume", "Piece" };
		static int gramPerMessurement;


		if (ImGui::Begin("Options"))
		{
			ImGui::Text("Namn(Swe):\t\t\t"); ImGui::SameLine(); 
			ImGui::InputText("namn", nameField, IM_ARRAYSIZE(nameField));

			ImGui::Text("Name(Eng):\t\t\t"); ImGui::SameLine();
			ImGui::InputText("namnEng", nameFieldEnglish, IM_ARRAYSIZE(nameFieldEnglish));

			ImGui::Text("Storage:  \t\t\t"); ImGui::SameLine();			
			ImGui::Combo("Storage", &item_current_1, storageTypes, IM_ARRAYSIZE(storageTypes));

			ImGui::Text("Messurement:  \t\t"); ImGui::SameLine();
			ImGui::Combo("Messurement", &item_current_2, messurementTypes, IM_ARRAYSIZE(messurementTypes));

			ImGui::Text("Gram per Messurement: "); ImGui::SameLine();
			ImGui::InputInt("GperM", &gramPerMessurement);

			if (ImGui::Button("Create"))
			{
				Utilities::EStorageType storage = Utilities::GetEStorageType(storageTypes[item_current_1]);
				Utilities::EMessurement messurement = Utilities::GetEMessurementType(messurementTypes[item_current_2]);
				Utilities::Product newProduct((std::string)nameField, (std::string)nameFieldEnglish, storage, messurement, gramPerMessurement, 0);
				myProductFactory->Add(newProduct);
				shouldClose = true;
			}

			ImGui::SameLine();
			if (ImGui::Button("Close"))
			{
				shouldClose = true;
			}
			ImGui::End();
		}

		if (shouldClose)
		{
			memset(nameField, 0, 32 * nameField[0]);
			memset(nameFieldEnglish, 0, 32 * nameFieldEnglish[0]);
			item_current_1 = -1;
			item_current_2 = -1;
			gramPerMessurement = 0;
			myThirdState = Utilities::EAppThirdState::None;
		}
		
	}

	void App::ProductDetailsScreen(ImGuiIO& anIO, Utilities::Product& aProduct)
	{
		bool shouldClose = false;

		if (ImGui::Begin("Details"))
		{
			switch (myProductFactory->GetDisplayLanguage())
			{
			case Utilities::EDisplayLanguage::Svenska:
				ImGui::Text(aProduct.Name.c_str());
				break;
			case Utilities::EDisplayLanguage::English:
				ImGui::Text(aProduct.NameEnglish.c_str());
				break;
			default:
				break;
			}
			ImGui::Text("Stored in :"); ImGui::SameLine();
			ImGui::Text(Utilities::GetStorageTypeString(aProduct.StandardLocation).c_str());
			ImGui::Text("Standard messurement type:"); ImGui::SameLine();
			ImGui::Text(Utilities::GetMessurementTypeString(aProduct.StandardMessurement).c_str());
			ImGui::Text("Weight(gram) per messurement unit:"); ImGui::SameLine();
			ImGui::Text(std::to_string(aProduct.GramPerMessurement).c_str());
			ImGui::Text("Product ID:"); ImGui::SameLine();
			ImGui::Text(std::to_string(aProduct.UniqueID).c_str());


			if (ImGui::Button("Close"))
			{
				shouldClose = true;
			}

			ImGui::End();
		}

		if (shouldClose)
		{
			myThirdState = Utilities::EAppThirdState::None;
		}
	}

	void App::CBKeyInput(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode)
	{
		if (aKey == GLFW_KEY_ESCAPE && anAction == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(aWindow, GL_TRUE);
		}
	}
	void App::CBWindowResize(GLFWwindow* aWindow, int aWidth, int aHeight)
	{
		glViewport(0, 0, aWidth, aHeight);
	}
	void App::CBDropFile(GLFWwindow* aWindow, int aCount, const char** somePaths)
	{
		for (int i = 0; i < aCount; i++)
		{
			std::cout << "Path: " << somePaths[i] << std::endl;
		}
	}
}