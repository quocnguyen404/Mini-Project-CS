#include "main/example_glfw_opengl2/common.h"

//////////////////////////
// Word class defintion //
//////////////////////////
Word::Word(int cateID, std::string word)
    : categoryID(cateID), word(word), relate() {}

int Word::getCateID() { return this->categoryID; }

std::string Word::getWord() { return this->word; }

void Word::setWord(std::string nWord) { this->word = nWord; }

void Word::addRelateWord(std::string relateWord)
{
    this->relate.push_back(relateWord);
}

void Word::removeRelateWord(std::string relateWord)
{
    this->relate.erase(find(this->relate.begin(), this->relate.end(), relateWord));
}

///////////////////////////////
// Category class definition //
///////////////////////////////
Category::Category(int categoryID, std::string categoryName)
    : categoryID(categoryID), categoryName(categoryName), words()  {}

int Category::getCatID() { return this->categoryID; }


std::string& Category::getCateName() { return this->categoryName; }

std::vector<std::shared_ptr<Word>> Category::getWords()
{
    return this->words;
}

void Category::setCateName(std::string ncateName)
{
    this->categoryName = ncateName;
}


std::shared_ptr<Word> Category::getWord(std::string word)
{
    for (int i = 0; i < this->words.size(); i++)
        if (strcmp(word.c_str(), words[i]->getWord().c_str()) == 0)
            return this->words[i];

    return nullptr;
}

std::vector<std::string>* Word::getRelateWord()
{
    return &this->relate;
}

void Category::addWord(std::shared_ptr<Word>& word)
{
    this->words.emplace_back(word);
}

void Category::removeWord(std::string word)
{
    std::shared_ptr<Word> w = this->getWord(word);

    if (w == nullptr)
        return;

    this->words.erase(find(this->words.begin(), this->words.end(), w));
    w.reset();
}

//////////////////////////////////
// WordManager class definition //
//////////////////////////////////

WordManager WordManager::instance;

WordManager& WordManager::get() { return instance; }

std::shared_ptr<Word> WordManager::getWord(int cateID, std::string word)
{
    if (!this->existCategory(cateID))
        return nullptr;

    return categorys[cateID]->getWord(word);
}


std::string& WordManager::getCateName(int cateID)
{
    return this->categorys[cateID]->getCateName();
}

int WordManager::getLargestCateID()
{
    int max = 0;
    for (auto& cate : this->categorys)
        max = max < cate.second->getCatID() ? cate.second->getCatID() : max;

    return max;
}

bool WordManager::existCategory(int cateID)
{
    for (auto& cate : this->categorys)
        if (cate.second->getCatID() == cateID)
            return true;

    return false;
}

bool WordManager::existCategory(std::string cateName)
{
    for (auto& cate : this->categorys)
        if (strcmp(cate.second->getCateName().c_str(), cateName.c_str()) == 0)
            return true;

    return false;
}

//update word in program not in file
void WordManager::updateWord(int cateID, std::string oldWord, std::string nWord)
{
    auto pWord = this->getWord(cateID, oldWord);
    pWord->setWord(nWord);
}

void WordManager::updateCategory(int cateID, std::string nCateName)
{
    auto pCate = this->categorys[cateID];

    pCate->setCateName(nCateName);
}


void WordManager::addCategory(std::shared_ptr<Category> nCate)
{
    if (nCate == nullptr)
        return;

    std::cout << "add category " << nCate->getCatID() << ", " << nCate->getCateName() << "\n";
    categorys.emplace(nCate->getCatID(), nCate);
    return;
}

void WordManager::addWord(std::shared_ptr<Word> nWord)
{
    if (!existCategory(nWord->getCateID()))
    {
        std::string mess = "Not exist category";
        return;
    }

    this->categorys[nWord->getCateID()]->addWord(nWord);
}

void WordManager::removeWord(int cateID, std::shared_ptr<Word> word)
{
    this->categorys[cateID]->removeWord(word->getWord());
}


void WordManager::removeCategory(int cateID)
{
    if (this->categorys.find(cateID) == categorys.end())
    {
        std::string mes = "Not exist category.\n";
        return;
    }

    this->categorys[cateID].reset();
    this->categorys.erase(cateID);
}

std::shared_ptr<Category>& WordManager::getCategory(int cateID)
{
    return this->categorys[cateID];
}

std::shared_ptr<Category>& WordManager::getCategory(std::string cateName)
{
    for (auto& c : this->categorys)
        if (strcmp(c.second->getCateName().c_str(), cateName.c_str()) == 0)
            return c.second;
}


std::map <int, std::shared_ptr<Category>>* WordManager::getCategorys()
{
    return &this->categorys;
}

/////////////////////
// Messenger class //
/////////////////////

Messenger::Messenger(char* messenger)
    : messenger()
{
    this->addMessenger(messenger);
}

Messenger::Messenger(std::string& messenger)
    : messenger()
{
    this->addMessenger("Messenger: " + messenger);
}

Messenger::Messenger(std::shared_ptr<Word>& word)
    : messenger()
{
    this->addMessenger("Word: " + word->getWord());
    this->addMessenger("Category ID: " + std::to_string(word->getCateID()));
    this->addMessenger("Category name: " + WordManager::get().getCateName(word->getCateID()));

    std::string str = "Relate word: ";
    for (std::string& w : *word->getRelateWord())
        str += w + ", ";

    this->addMessenger(str);
}

Messenger::Messenger(std::shared_ptr<Category>& category)
    : messenger()
{
    this->addMessenger("Category: ");
    this->addMessenger(category->getCateName());
    this->addMessenger(std::to_string(category->getCatID()));
}

void Messenger::addMessenger(std::string additionMessenger)
{
    this->messenger.push_back(additionMessenger);
}

std::vector<std::string> Messenger::getMessenger()
{
    return this->messenger;
}

/////////////////////////////
// Messenger Handler class //
/////////////////////////////

MessengerHandler MessengerHandler::instance;

MessengerHandler& MessengerHandler::get() { return instance; }


bool MessengerHandler::hasMessenger() { return messengers.size() > 0 ? true : false; }

void MessengerHandler::addMessenger(std::shared_ptr<Messenger>& messenger)
{
    if (messenger == nullptr)
        return;

    messengers.emplace_back(messenger);
}

//void MessengerHandler::addMessenger(Messenger& messenger)
//{
//    if (messenger.getMessenger().size() == 0)
//        return;
//
//    messengers.emplace_back(messenger);
//}

void MessengerHandler::openMessengerWindow()
{
    ImGui::Begin("Messenger");

    for (auto& m : this->messengers)
        for (auto& s : m->getMessenger())
            ImGui::Text(s.c_str());

    if (UI::buttonAlign("Close/Clear", 0.f))
        this->closeMessengerWindow();

    ImGui::End();
}

void MessengerHandler::closeMessengerWindow()
{
    for (auto& m : this->messengers)
        m.reset();

    messengers.clear();
}
