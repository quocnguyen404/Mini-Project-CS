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
void showFindWordWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items);
void showAddWordWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items);
void showAddCategoryWindow(bool* pOpen);
void showPrintWordCategoryWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items);
void showChangeDeleteWordWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items);
void showChangeDeleteCategoryWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items);

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
        if (show_main_window)
            showMainWindow(&show_main_window);


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
    static bool find_word_window = false;
    static bool add_word_window = false;
    static bool add_category_window = false;
    static bool print_word_category_window = false;
    static bool change_delete_word_window = false;
    static bool change_delete_category_window = false;

    //category item
    std::string items_str;
    std::vector<std::shared_ptr<Category>> items_cate;

    //font
    float oldSize = ImGui::GetFont()->Scale;
    ImGui::GetFont()->Scale = 1.5f;
    ImGui::PushFont(ImGui::GetFont());

    ImGuiWindowFlags window_flag = 0;
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

    ImGui::Begin(programTitle, NULL, window_flag);

    updateCategoryItems(items_cate, items_str);

    //Find word button
    if (UI::buttonAlign("Find word", 0.f))
        find_word_window = true;

    //Add word button
    if (UI::buttonAlign("Add word", 0.f))
        add_word_window = true;

    //Add category button
    if (UI::buttonAlign("Add category", 0.f))
        add_category_window = true;

    //Print all word in category
    if (UI::buttonAlign("Print all word in a category", 0.f))
        print_word_category_window = true;

    //Change and delete word
    if (UI::buttonAlign("Change or delete word", 0.f))
        change_delete_word_window = true;

    //Change and delete category
    if (UI::buttonAlign("Change or delete category", 0.f))
        change_delete_category_window = true;

    //Messenger Window
    if (MessengerHandler::get().hasMessenger())
        MessengerHandler::get().openMessengerWindow();

    if (find_word_window)
        showFindWordWindow(&find_word_window, items_cate, items_str);

    if (add_word_window)
        showAddWordWindow(&add_word_window, items_cate, items_str);

    if (add_category_window)
        showAddCategoryWindow(&add_category_window);

    if (print_word_category_window)
        showPrintWordCategoryWindow(&print_word_category_window, items_cate, items_str);

    if (change_delete_word_window)
        showChangeDeleteWordWindow(&change_delete_word_window, items_cate, items_str);

    if (change_delete_category_window)
        showChangeDeleteCategoryWindow(&change_delete_category_window, items_cate, items_str);

    ImGui::GetFont()->Scale = oldSize;
    ImGui::PopFont();

    ImGui::End();

       
}

void showFindWordWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items)
{
    static int cateID = -1;

    //window 
    ImGui::Begin("Find word", pOpen);
    ImGui::Combo("Category", &cateID, items.c_str());

    static char buf[20] = "Enter word";
    ImGui::InputText("###", buf, IM_ARRAYSIZE(buf));

    if (UI::buttonAlign("Find", 0.5f))
    {
        std::shared_ptr<Word> pWord = nullptr;
        pWord = WordManager::get().getWord(items_cate[cateID]->getCatID(), buf);

        if (pWord == nullptr)
            MessengerHandler::get().addMessenger(createMessenger("Please enter word"));
        else
            MessengerHandler::get().addMessenger(createMessenger(pWord));

        strcpy(buf, "Enter word");
        cateID = -1;
    }

    ImGui::End();
}

void showAddWordWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items)
{
    static int cateID = -1;
    //window 
    ImGui::Begin("Add word", pOpen);
    ImGui::Combo("Category", &cateID, items.c_str());

    static char buf[20] = "Enter word to add";
    static char buf1[30] = "Enter relate word";

    ImGui::InputText("###", buf, IM_ARRAYSIZE(buf));
    ImGui::InputText("##", buf1, IM_ARRAYSIZE(buf1));


    if (cateID >= 0 && UI::buttonAlign("Add", 0.f))
    {
        std::shared_ptr<Word> pWord = nullptr;

        if (WordManager::get().existCategory(items_cate[cateID]->getCatID()) &&
            strcmp(buf, "") != 0 &&
            strcmp(buf, "Enter word to add") != 0)
        {
            if (strcmp(buf1, "Enter relate word") == 0)
                strcpy(buf1, "");

            pWord = createWord(items_cate[cateID]->getCatID(), buf, buf1);
            WordManager::get().addWord(pWord);
            saveWord(pWord);
        }

        if (pWord == nullptr)
            MessengerHandler::get().addMessenger(createMessenger("Please enter word"));
        else
            MessengerHandler::get().addMessenger(createMessenger("Add word " + pWord->getWord() + " success"));

        strcpy(buf, "Enter word to add");
        strcpy(buf1, "Enter relate word");
        cateID = -1;
    }

    ImGui::End();
}

void showAddCategoryWindow(bool* pOpen)
{
    ImGui::Begin("Add category", pOpen);

    static char buf[30] = "Enter category to add";
    ImGui::InputText("###", buf, IM_ARRAYSIZE(buf));

    if (UI::buttonAlign("Add", 0.f))
    {
        std::shared_ptr<Category> pCate = nullptr;

        if (!WordManager::get().existCategory(buf) &&
            strcmp(buf, "") != 0 &&
            strcmp(buf, "Enter category to add") != 0)
        {
            int nCateID = WordManager::get().getLargestCateID() + 1;
            pCate = createCategory(nCateID, buf);
            WordManager::get().addCategory(pCate);
            saveCategory(pCate);
        }

        if (pCate == nullptr)
            MessengerHandler::get().addMessenger(createMessenger("Please enter category name"));
        else
            MessengerHandler::get().addMessenger(createMessenger("Add category: " + pCate->getCateName() + " success"));

        strcpy(buf, "Enter category to add");
    }

    ImGui::End();
}

void showPrintWordCategoryWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items)
{
    static int cateID = -1;

    //window
    ImGui::Begin("Print all word in a category", pOpen);
    ImGui::Text("Choose category to print all word");
    ImGui::Combo("Category", &cateID, items.c_str());

    if (UI::buttonAlign("Print", 0.f) &&
        cateID >= 0 &&
        WordManager::get().existCategory(items_cate[cateID]->getCatID()))
    {
        if (WordManager::get().getCategory(items_cate[cateID]->getCatID())->getWords().size() == 0)
            MessengerHandler::get().addMessenger(createMessenger("There is no word in " + WordManager::get().getCateName(items_cate[cateID]->getCatID())));
        else
            for (auto& w : WordManager::get().getCategory(items_cate[cateID]->getCatID())->getWords())
                MessengerHandler::get().addMessenger(createMessenger(w));

        cateID = -1;
    }

    ImGui::End();
}

void showChangeDeleteWordWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items)
{
    static int cateID = -1;
    static int wordID = -1;

    //window
    ImGui::Begin("Change or delete word", pOpen);
    ImGui::Text("Change or delete word");
    ImGui::Combo("Category", &cateID, items.c_str());

    if (cateID >= 0 && WordManager::get().existCategory(items_cate[cateID]->getCatID()))
    {
        /*static*/ std::string items_str = "";
        /*static*/ std::vector<std::string> words;

        updateWordItems(words, items_str, items_cate[cateID]->getCatID());
        ImGui::Combo("Choose word", &wordID, items_str.c_str());
        static char buf[20] = "Enter new word";
        ImGui::InputText("###", buf, IM_ARRAYSIZE(buf));

        if (wordID >= 0)
        {
            if (UI::buttonAlign("Change", 0.f) &&
                strcmp(buf, "") != 0 &&
                strcmp(buf, "Enter new word") != 0)
            {
                WordManager::get().updateWord(items_cate[cateID]->getCatID(), words[wordID], buf);
                updateWordsToFile();

                MessengerHandler::get().addMessenger(createMessenger("Change word " + words[wordID] + " to " + std::string(buf) + " success"));
                cateID = -1;
                wordID = -1;
                strcpy(buf, "Enter new word");
            }

            ImGui::SameLine();
        }

        if (UI::buttonAlign("Delete", 0.f) &&
            wordID >= 0)
        {
            auto pWord = WordManager::get().getWord(items_cate[cateID]->getCatID(), words[wordID]);
            WordManager::get().removeWord(items_cate[cateID]->getCatID(), pWord);
            updateWordsToFile();

            MessengerHandler::get().addMessenger(createMessenger("Delete " + words[wordID] + " success"));

            cateID = -1;
            wordID = -1;
            strcpy(buf, "Enter new word");
        }
    }

    ImGui::End();
}

void showChangeDeleteCategoryWindow(bool* pOpen, std::vector<std::shared_ptr<Category>>& items_cate, std::string& items)
{
    static int cateID = -1;

    //window
    ImGui::Begin("Change or delete category", pOpen);
    ImGui::Text("Change or delete category");
    ImGui::Combo("Category", &cateID, items.c_str());

    if (cateID >= 0 && WordManager::get().existCategory(items_cate[cateID]->getCatID()))
    {
        std::string oldCateName = WordManager::get().getCateName(items_cate[cateID]->getCatID());
        static char buf[20] = "Enter new category";
        ImGui::InputText("###", buf, IM_ARRAYSIZE(buf));

        if (UI::buttonAlign("Change", 0.f) &&
            strcmp(buf, "") != 0 &&
            strcmp(buf, "Enter new category") != 0)
        {
            WordManager::get().updateCategory(items_cate[cateID]->getCatID(), buf);
            updateCategoryToFile();

            MessengerHandler::get().addMessenger(createMessenger("Change category " + oldCateName + " to " + std::string(buf) + " success"));
            cateID = -1;
            strcpy(buf, "Enter new category");
            updateCategoryItems(items_cate ,items);
        }

        ImGui::SameLine();

        if (UI::buttonAlign("Delete", 0.f))
        {
            WordManager::get().removeCategory(items_cate[cateID]->getCatID());
            updateCategoryToFile();

            MessengerHandler::get().addMessenger(createMessenger("Delete category " + oldCateName + " success"));

            cateID = -1;
            strcpy(buf, "Enter new category");
            updateWordsToFile();
            //updateCategoryItems(items_cate, items);
        }
    }

    ImGui::End();
}
