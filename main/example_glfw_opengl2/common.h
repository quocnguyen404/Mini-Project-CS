#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <memory>

#include "Header/ui.h"


#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR) / sizeof(*(_ARR))))     // Size of a static C-style array. Don't use on pointers!


const int NUM_WORD_LINE = 3;
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
    std::string getCateName();
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
    bool existCategory(int cateID);
    void addCategory(std::shared_ptr<Category>& ntype);
    void addWord(std::shared_ptr<Word>& nWord);
    void removeCategory(int categoryID);
    std::map <int, std::shared_ptr<Category>>* getCategorys();
};

//Singleton
//Do not pass nullptr to this class constructor
//Messenger class
class Messenger
{
private:
    std::vector<std::string> messenger;

public:
    Messenger(std::string& messenger);
    Messenger(std::shared_ptr<Word>& word);
    Messenger(std::shared_ptr<Category>& category);
    void addMessenger(std::string additionMessenger);
    std::vector<std::string>& getMessenger();

};


//Messenger Handler class
class MessengerHandler
{
private:
    static MessengerHandler instance;
    std::vector<std::shared_ptr<Messenger>> messengers;

public:
    static MessengerHandler& get();
    bool hasMessenger();
    void addMessenger(std::shared_ptr<Messenger> messenger);
    void printMessenger();
};

void loadCategory();
void loadData();
std::shared_ptr<Word> createWord(int cateID, std::string word, std::string rawRelate);
void createCategory(int cateID, std::string cateName);
