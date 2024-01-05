#include "main/example_glfw_opengl2/header.h"

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

    int cateID;
    std::string word, rawRelate;

    while (std::getline(file, word))
    {
        file >> cateID;
        std::ignore;
        //std::getline(file, rawRelate);

        WordManager::get().addWord(createWord(cateID, word, "rawRelate"));
    }

    file.close();
    std::cout << "load data done.\n";

}

std::shared_ptr<Word> createWord(int cateID, std::string word, std::string rawRelate)
{
    std::shared_ptr<Word> nWord(nullptr);
    nWord = std::make_shared<Word>(cateID, word);

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
}



