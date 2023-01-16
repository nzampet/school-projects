/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 10/27/2022
 * Assignment Name: Single-Word Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

int main()
{
    vector<string> words;
    vector<string> anagrams;
    string inputWord;
    words=loadWordlist("wordlist.txt");
    cout << "Find single-word anagrams for the following word: ";
    cin >> inputWord;
    anagrams = anagram(inputWord, words);
    for (int i=0; i<anagrams.size(); i++)
    {
        cout << anagrams[i] << endl;
    }
    return 0;
}

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

//Returns a string with each character representing the frequency of a letter
//The index represents the letters index in the alphabet
string freqStringFromWord(string word) {
    uint8_t letterCnt[26] = {};
    for (char &letter : word) {
        letterCnt[letter - 'a']++;
    }
    string letterStr = "";
    for (uint8_t &num : letterCnt) {
        letterStr += (char) num;
    }
    return letterStr;
}

//Returns a list of anagrams for a given word in a given wordlist
//This works using a unordered_map with the keys being frequencys of
//each letter within a word
vector<string> anagram(string word, vector<string> wordlist) {
    unordered_map<string, vector<string>> anagramMap;
    for (string &w : wordlist) { //Add words
        string freqString = freqStringFromWord(w);
        auto it = anagramMap.find(freqString);
        if (it == anagramMap.end()) { //If key not in list
            anagramMap.insert(make_pair(freqString, vector<string>{w}));
        } else { //Key in list so push back word
            it->second.push_back(w);
        }
    }

    //Find and return
    auto it = anagramMap.find(freqStringFromWord(word));
    if (it != anagramMap.end()) {
        return it->second;
    }
    return vector<string>();
}