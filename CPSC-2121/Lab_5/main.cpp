/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
 int main()
 {
     Stringset wordlist;
     //testStringset(wordlist);
     loadStringset(wordlist, "wordlist.txt");

     string inputWord;
     cout << "Enter a word to spellcheck: ";
     cin >> inputWord;
     
     vector<string> similarWords = spellcheck(wordlist, inputWord);
     for (auto it : similarWords) cout << it << "\n";

     return 0;
 }
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 
 //This is a function that will load a file of words into the referenced
 //Stringset. It does this by scanning in each line and inserting the words.
 void loadStringset(Stringset& words, string filename)
 {
    ifstream file;
    file.open(filename);

    string word;
    while (getline(file, word)) {
        words.insert(word);
    }

    file.close();
 }
 
 //This is a function that will check spelling using the referenced
 //wordlist versus the provided word. It iterates through all combinations
 //of words one letter off from the original and checks if these words are
 //contained within the referenced wordlist
 vector<string> spellcheck(const Stringset& words, string word)
 {
    vector<string> similarWords;
    for (int i = 0; i < word.size(); i++) {
        for (int alphaInd = 0; alphaInd < 26; alphaInd++) {
            if (word[i] - 'a' == alphaInd) continue;

            string newWord = word;
            newWord[i] = (char)(alphaInd + 'a');

            if (words.find(newWord)) similarWords.push_back(newWord);
        }
    }


    return similarWords;
 }