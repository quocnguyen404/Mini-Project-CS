#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>

#include "Header/ui.h"


#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR) / sizeof(*(_ARR))))     // Size of a static C-style array. Don't use on pointers!

const std::string DATA_FILE = "data.txt";
const std::string CATEGORY_FILE = "category.txt";

//Word class
class Word
{
private:
    int categoryID;
    std::string word;
    std::vector<std::string> relate;

public:
    Word(int cateID, std::string word);
    int getCateID();
    std::string getWord();
    void setWord(std::string nWord);
    void addRelateWord(std::string relateWord);
    void removeRelateWord(std::string relateWord);
    std::vector<std::string>* getRelateWord();
};

//Category class
class Category
{
private:
    int categoryID;
    std::string categoryName;
    std::vector<std::shared_ptr<Word>> words;

public:
    Category(int categoryID, std::string categoryName);
    int getCatID();
    std::string& getCateName();
    void setCateName(std::string nCateName);    
    std::vector<std::shared_ptr<Word>> getWords();
    std::shared_ptr<Word> getWord(std::string word);
    void addWord(std::shared_ptr<Word>& word);
    void removeWord(std::string word);
};

//Singleton
//WordManager class
class WordManager
{
private:
    static WordManager instance;
    std::map<int, std::shared_ptr<Category>> categorys;
    WordManager() {};

public:
    static WordManager& get();
    std::shared_ptr<Word> getWord(int cateID, std::string word);
    std::string& getCateName(int cateID);
    int getLargestCateID();
    bool existCategory(int cateID);
    bool existCategory(std::string cateName);
    void updateWord(int cateID, std::string oldWord, std::string nWord);
    void updateCategory(int cateID, std::string nCateName);
    void addCategory(std::shared_ptr<Category> nCate);
    void addWord(std::shared_ptr<Word> nWord);
    void removeWord(int cateID, std::shared_ptr<Word> word);
    void removeCategory(int categoryID);
    std::shared_ptr<Category>& getCategory(int cateID);
    std::shared_ptr<Category>& getCategory(std::string cateName);
    std::map <int, std::shared_ptr<Category>>* getCategorys();
};

//Do not pass nullptr to this class constructor
//Messenger class
class Messenger
{
private:
    std::vector<std::string> messenger;

public:
    Messenger(char* messenger);
    Messenger(std::string& messenger);
    Messenger(std::shared_ptr<Word>& word);
    Messenger(std::shared_ptr<Category>& category);
    void addMessenger(std::string additionMessenger);
    std::vector<std::string> getMessenger();
};

//Singleton
//Messenger Handler class
class MessengerHandler
{
private:
    static MessengerHandler instance;
    std::vector<std::shared_ptr<Messenger>> messengers;

public:
    static MessengerHandler& get();
    bool hasMessenger();
    void addMessenger(std::shared_ptr<Messenger>& messenger);
    //void addMessenger(Messenger& messenger);
    void openMessengerWindow();
    void closeMessengerWindow();
};

void loadCategory();
void loadData();
void saveWord(std::shared_ptr<Word> pWord);
void saveCategory(std::shared_ptr<Category>& pCate);
void updateWordsToFile();
void updateCategoryToFile();
std::shared_ptr<Word> createWord(int cateID, std::string word, std::string rawRelate);
std::shared_ptr<Category> createCategory(int cateID, std::string cateName);
std::shared_ptr<Messenger> createMessenger(char* messenger);
std::shared_ptr<Messenger> createMessenger(std::string& messenger);
std::shared_ptr<Messenger> createMessenger(std::shared_ptr<Word>& word);
std::shared_ptr<Messenger> createMessenger(std::shared_ptr<Category>& category);
void rawRelateHandle(std::shared_ptr<Word> pWord, std::string rawRelate);
std::string removeExtraWhiteSpace(std::string string);
void updateCategoryItems(std::vector<std::shared_ptr<Category>>& categorys, std::string& items_str);
void updateWordItems(std::vector<std::string>& words, std::string& items_str, int cateID);
