#include "main/example_glfw_opengl2/header.h"

//////////////////////////
// Word class defintion //
//////////////////////////
Word::Word(int cateID, std::string word)
    : categoryID(cateID), word(word), relate() {}

int Word::getCateID() { return this->categoryID; }

std::string Word::getWord() { return this->word; }

///////////////////////////////
// Category class definition //
///////////////////////////////
Category::Category(int categoryID, std::string categoryName)
    : categoryID(categoryID), categoryName(categoryName) {}

int Category::getCatID() { return this->categoryID; }

std::string Category::getCateName() { return this->categoryName; }

std::shared_ptr<Word> Category::getWord(std::string word)
{
    for (auto& w : this->words)
        if (strcmp(word.c_str(), w->getWord().c_str()) != 0)
            return w;

    return nullptr;
}

void Category::addWord(std::shared_ptr<Word>& word)
{
    this->words.push_back(word);
}

void Category::removeWord(std::string word)
{
    std::shared_ptr<Word> w = this->getWord(word);

    if (w == nullptr)
        return;

    this->words.erase(find(this->words.begin(), this->words.end(), w), this->words.end());
    w.reset();
}

//////////////////////////////////
// WordManager class definition //
//////////////////////////////////
WordManager WordManager::instance;

WordManager& WordManager::get() { return instance; }

bool WordManager::existCategory(int cateID)
{
    for (auto& cate : this->categorys)
    {
        if (cate.second->getCatID() == cateID)
            return true;
    }

    return false;
}

void WordManager::addCategory(std::shared_ptr<Category>& nCate)
{
    categorys.emplace(nCate->getCatID(), nCate);
}

void WordManager::addWord(std::shared_ptr<Word>& nWord)
{
    if (!existCategory(nWord->getCateID()))
    {
        std::string mess = "Not exist category";
        return;
    }

    this->categorys[nWord->getCateID()]->addWord(nWord);
}

void WordManager::removeCategory(int cateID)
{
    if (categorys.find(cateID) == categorys.end())
    {
        std::string mes = "Not exist category.\n";
        return;
    }

    categorys[cateID].reset();
    categorys.erase(cateID);
}

    
