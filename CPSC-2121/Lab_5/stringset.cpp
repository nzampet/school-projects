/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 10/17/22
 * Lab Section: 003
 * Assignment Name: Lab 5: Stringset Implementation
 */

#include "stringset.h"
#include <functional>

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

std::hash<std::string> stringHash;

//This is the insert function that will add a new string to our Stringset
//It does this by hashing the inputted string, checking if the table
//already contains it, and adds it if it doesn't exist. If the number of
//words reaches the size of the table, it will double the size and rehash
//all of the words into it.
void Stringset::insert(string word)
{
    //Get hash
    size_t hash = stringHash(word);
    int pos = hash % size;

    // Check if exists
    for (auto it : table[pos])
        if (word == it)
            return;

    // If full, double size
    if (num_elems == size) {
        //Move all of the words into a temporary vector
        std::vector<std::string> tmpWords;
        for(auto it : table) {
            for (auto word : it) {
                tmpWords.push_back(word);
            }
        }

        //Empty table
        num_elems = 0;
        table.clear();
        //Resize table
        size *= 2;
        table.resize(size);
        //Insert old words into new table
        for (auto word : tmpWords) insert(word);

        //Get updated hash
        hash = stringHash(word);
        pos = hash % size;
    }

    //Insert word
    table[pos].push_back(word);
    num_elems++;
}

//This is a function for our Stringset that outputs a boolean indicating
//whether the word is already in our set. It works by hashing the inputted
//word and checking all elements in the list at that hash index for the word.
bool Stringset::find(string word) const
{
    //Get hash
    size_t hash = stringHash(word);
    int pos = hash % size;
    //Return true if found else false
    for (auto it : table[pos])
        if (word == it)
            return true;
    return false;
}

//This is a function that removes the inputted word from the hash table. It
//works by hashing the word to get the hash index and then removing the word
//from the list at that index.
void Stringset::remove(string word)
{
    //Get hash
    size_t hash = stringHash(word);
    int pos = hash % size;
    //Remove word
    table[pos].remove(word);
    num_elems--;
}