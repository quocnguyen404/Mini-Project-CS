#include "main/example_glfw_opengl2/common.h"

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

std::vector<std::string>* Word::getRelateWord()
{
    return &this->relate;
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

std::shared_ptr<Word> WordManager::getWord(int cateID, std::string word)
{
    return categorys[cateID]->getWord(word);
}

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
    std::cout << "add category " << nCate->getCatID() << ", " << nCate->getCateName() << "\n";
    categorys.emplace(nCate->getCatID(), nCate);
    return;
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

std::map <int, std::shared_ptr<Category>>* WordManager::getCategorys()
{
    return &this->categorys;
}

/////////////////////
// Messenger class //
/////////////////////

Messenger::Messenger(std::string& messenger)
{
    this->addMessenger("Messenger: ");
    this->addMessenger(messenger);
}

Messenger::Messenger(std::shared_ptr<Word>& word)
{
    this->addMessenger("Word: ");
    this->addMessenger(word->getWord());
    this->addMessenger(std::to_string(word->getCateID()));

    for (auto& w : *word->getRelateWord())
        this->addMessenger(w);
}

Messenger::Messenger(std::shared_ptr<Category>& category)
{
    this->addMessenger("Category: ");
    this->addMessenger(category->getCateName());
    this->addMessenger(std::to_string(category->getCatID()));
}

void Messenger::addMessenger(std::string additionMessenger)
{
    this->messenger.push_back(additionMessenger);
}

std::vector<std::string>& Messenger::getMessenger()
{
    return this->messenger;
}

/////////////////////////////
// Messenger Handler class //
/////////////////////////////

MessengerHandler MessengerHandler::instance;

MessengerHandler& MessengerHandler::get() { return instance; }


bool MessengerHandler::hasMessenger() { return messengers.size() > 0 ? true : false; }

void MessengerHandler::addMessenger(std::shared_ptr<Messenger> messenger)
{
    if (messenger == nullptr)
        return;

    messengers.emplace_back(messenger);
}

void MessengerHandler::printMessenger()
{
    ImGui::Begin("Messenger");

    for (auto& m : this->messengers)
        for (auto& s : m->getMessenger())
            ImGui::Text(s.c_str());

    ImGui::End();

    for (auto& m : this->messengers)
        m.reset();

    messengers.clear();
}
