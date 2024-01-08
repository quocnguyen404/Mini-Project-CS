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
        WordManager::get().addCategory(createCategory(cateID, cateName));
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
        std::cout << "open file fail\n";
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

void saveWord(std::shared_ptr<Word> pWord)
{
    std::ofstream file;

    file.open(DATA_FILE, std::ios::app);

    if (!file)
    {
        std::cout << "open file fail, can't save " << pWord->getWord() << "\n";
        return;
    }

    file << pWord->getWord() << "\n";
    file << pWord->getCateID() << "\n";

    for (std::string& s : *pWord->getRelateWord())
        file << s;

    file << "\n";

    file.close();
    std::cout << "Save word: " << pWord->getWord() << " successful" << "\n";
}

void saveCategory(std::shared_ptr<Category>& pCate)
{
    std::ofstream file;

    file.open(CATEGORY_FILE, std::ios::app);

    if (!file)
    {
        std::cout << "open file fail, can't save " << pCate->getCateName() << "\n";
        return;
    }

    file << pCate->getCatID() << " ";
    file << pCate->getCateName() << "\n";
    file.close();

    std::cout << "Save word: " << pCate->getCateName() << " successful" << "\n";
}

std::shared_ptr<Word> createWord(int cateID, std::string word, std::string rawRelate)
{
    std::shared_ptr<Word> nWord(nullptr);

    nWord = std::make_shared<Word>(cateID, word);

    std::cout << "create word " << cateID << ", " << word << "\n";
    return nWord;
}

std::shared_ptr<Category> createCategory(int cateID, std::string cateName)
{
    if (WordManager::get().existCategory(cateID))
    {
        std::string mess = "Already exist cateID";
        return nullptr;
    }

    std::shared_ptr<Category> nCate(nullptr);

    nCate = std::make_shared<Category>(cateID, cateName);
    std::cout << "create category " << cateID << ", " << cateName << "\n";

    return nCate;
}

std::string removeExtraWhiteSpace(std::string str)
{
    std::string nstr;
    for (int i = 0; i < str.length(); )
    {
        if (str[i] == ' ')
        {
            if (i == 0 || i == str.length() - 1)
            {
                i++;
                continue;
            }

            while (str[i + 1] == ' ')
                i++;
        }
        nstr += str[i++];
    }


    if (nstr[nstr.length() - 1] == ' ')
        nstr[nstr.length() - 1] = '\0';

    return nstr;
}

void updateCategory(std::vector<std::string>& items, std::string& items_str)
{
    if (items.size() == WordManager::get().getCategorys()->size())
        return;

    items_str = "";
    for (auto& c : *WordManager::get().getCategorys())
        items_str += c.second->getCateName() + '\0';
}


