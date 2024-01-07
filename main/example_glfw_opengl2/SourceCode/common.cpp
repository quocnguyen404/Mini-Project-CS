#include "main/example_glfw_opengl2/common.h"

void loadCategory()
{
    std::ifstream file;

    file.open(CATEGORY_FILE, std::ios::in);

    if (!file)
    {
        std::string mess = "open file fail\n";
        return;
    }

    int cateID;
    std::string cateName;


    while (file >> cateID)
    {
        file >> cateName;
        createCategory(cateID, cateName);
    }

    file.close();

    std::cout << "load category done.\n";
}


void loadData()
{
    std::ifstream file;

    file.open(DATA_FILE, std::ios::in);

    if (!file)
    {
        std::string mess = "open file fail\n";
        return;
    }

    std::string cateID;
    std::string word;
    std::string rawRelate;

    while (std::getline(file, word))
    {
        std::getline(file, cateID);
        std::getline(file, rawRelate);

        WordManager::get().addWord(createWord(stoi(cateID), word, rawRelate));
    }

    file.close();
    std::cout << "load words done.\n";

}

std::shared_ptr<Word> createWord(int cateID, std::string word, std::string rawRelate)
{
    std::shared_ptr<Word> nWord(nullptr);
    nWord = std::make_shared<Word>(cateID, word);

    std::cout << "create word " << cateID << ", " << word << "\n";

    return nWord;
}

void createCategory(int cateID, std::string cateName)
{
    if (WordManager::get().existCategory(cateID))
    {
        std::string mess = "Already exist cateID";
        return;
    }

    std::shared_ptr<Category> nCate = std::make_shared<Category>(cateID, cateName);
    WordManager::get().addCategory(nCate);

    std::cout << "create category " << cateID << ", " << cateName << "\n";

}



