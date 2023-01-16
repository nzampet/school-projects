/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 12/13/2022
 * Lab Section: 003
 * Assignment Name: Word Ladder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
unordered_map<string, bool> wordsMap; //words from wordlist05.txt in a hash map

typedef string state;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
        pred[n] = curnode;
        dist[n] = 1 + dist[curnode];
        visited[n] = true;
        to_visit.push(n);
      }
  }
}

void build_graph(void)
{
  for (auto word : V) {
    state st(word);
    for (unsigned int letter = 0; letter < st.length(); letter++) {
      state nextSt = st;
      for (int i = 0; i < 26; i++) {
        if (i == st[letter]) continue;

        nextSt[letter] = 'a' + i;
        if (wordsMap.find(nextSt) != wordsMap.end())
          nbrs[st].push_back(nextSt);
      }
      nextSt = st;
    }
  }
}

// GENERIC
string get_path(state s, state t, int &steps)
{
  string output = "";

  if (s != t) {
    steps++;
    output = get_path(s, pred[t], steps);
    output += " -> " + t;
  } else {
    output = t;
  }
  return output;
}

// GENERIC
void loadWordlist(string filename)
{
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                V.push_back(word);
                wordsMap.insert({word, true});
            }
        }
        inFile.close();
    }
}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
  loadWordlist("wordlist05.txt");
  build_graph();
  search(s);
  if (visited[t])
    p.push_back(get_path(s, t, steps));
  return;
}


int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (unsigned int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
