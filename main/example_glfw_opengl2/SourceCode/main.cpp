// Dear ImGui: standalone example application for GLFW + OpenGL2, using legacy fixed pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_glfw_opengl2/ folder**
// See imgui_impl_glfw.cpp for details.

#include "main/example_glfw_opengl2/common.h";

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description);
void showMainWindow(bool* pOpen);
std::shared_ptr<Word> showFindWordWindow(bool* pOpen, std::string& items);
void showAddWordWindow(bool* pOpen);
void showAddCategoryWindow(bool* pOpen);
void showPrintWordCategoryWindow(bool* pOpen);
void showChangeDeleteWordWindow(bool* pOpen);
void showChangeDeleteCategoryWindow(bool* pOpen);
void showOutputWindow(bool* pOpen);

char programTitle[] = "BKEncyclopedia";

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, programTitle, nullptr, nullptr);

    if (window == nullptr)
        return 1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    std::string outputText;

    //Message
    std::vector<std::string> mess;

    loadCategory();
    loadData();

    //Our state
    bool show_main_window = true;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Our code
        if (show_main_window) showMainWindow(&show_main_window);

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void showMainWindow(bool* pOpen)
{
    ImGuiIO& io = ImGui::GetIO();

    static bool find_word_window = false;
    static bool add_word_window = false;
    static bool add_category_window = false;
    static bool print_word_category_window = false;
    static bool change_delete_word_window = false;
    static bool change_delete_category_window = false;
    static bool output_window = false;

    //category item
    static std::string items_str;
    std::vector<std::string> items;

    //font
    float oldSize = ImGui::GetFont()->Scale;
    ImGui::GetFont()->Scale = 1.5f;
    ImGui::PushFont(ImGui::GetFont());
    ImGui::GetFont()->Scale = oldSize;

    if (find_word_window) showFindWordWindow(&find_word_window, items_str);
    if (add_word_window) showAddWordWindow(&add_word_window);
    if (add_category_window) showAddCategoryWindow(&add_category_window);
    if (print_word_category_window) showPrintWordCategoryWindow(&print_word_category_window);
    if (change_delete_word_window) showChangeDeleteWordWindow(&change_delete_word_window);
    if (change_delete_category_window) showChangeDeleteCategoryWindow(&change_delete_category_window);
    if (output_window) showOutputWindow(&output_window);

    ImGuiWindowFlags window_flag = 0;
    window_flag = ImGuiWindowFlags_NoFocusOnAppearing;
    {
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f));

        ImGui::Begin(programTitle, NULL, ImGuiWindowFlags_None);


        ImGui::Text("Hello");

        if (UI::buttonAlign("Find word", 0.1f))
        {
            if (items.size() == WordManager::get().getCategorys()->size())
                return;

            items_str = "";
            for (auto& c : *WordManager::get().getCategorys())
                items_str += c.second->getCateName() + '\0';

            find_word_window = true;
        }

        ImGui::End();
    }

    ImGui::PopFont();
    //font
}

std::shared_ptr<Word> showFindWordWindow(bool* pOpen, std::string& items)
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_None, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(450.f, 200.f));

    ImGui::Begin("Find word", pOpen);

    static int cateID = -1;

    ImGui::Combo("Category", &cateID, items.c_str());

    char buf[100] = "Enter word";
    ImGui::InputText("###", buf, IM_ARRAYSIZE(buf));


    if (ImGui::IsKeyDown(ImGuiKey_Enter))
    {
        if (!WordManager::get().existCategory(cateID))
            return nullptr;

        return WordManager::get().getWord(cateID, buf);
    }

    if (UI::buttonAlign("Find", 0.5f))
    {
        return WordManager::get().getWord(cateID, buf);
    }

    ImGui::End();

    return nullptr;
}

void showAddWordWindow(bool* pOpen)
{

}

void showAddCategoryWindow(bool* pOpen)
{

}

void showPrintWordCategoryWindow(bool* pOpen)
{

}

void showChangeDeleteWordWindow(bool* pOpen)
{

}

void showChangeDeleteCategoryWindow(bool* pOpen)
{

}

void showOutputWindow(bool* pOpen)
{

}



