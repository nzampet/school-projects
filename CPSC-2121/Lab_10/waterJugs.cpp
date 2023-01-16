/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 12/5/2022
 * Lab Section: 003
 * Assignment Name: Using Breadth-First Search to Solve Puzzles
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

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

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

vector<state> get_neighbors(state st) {
  vector<state> neighbors;
  neighbors.push_back(state(3, st.second));
  neighbors.push_back(state(st.first, 4));
  neighbors.push_back(state(0, st.second));
  neighbors.push_back(state(st.first, 0));
  int totalUnits = st.first + st.second;
  if (totalUnits > 4) neighbors.push_back(state(totalUnits - 4, 4));
  else neighbors.push_back(state(0, totalUnits));
  if (totalUnits > 3) neighbors.push_back(state(3, totalUnits - 3));
  else neighbors.push_back(state(totalUnits, 0));
  return neighbors;
}

void build_graph(void)
{
  //Implement this function
  //Loop through states
  for (int a = 0; a <= 3; a++) {
    for (int b = 0; b <= 4; b++) {
      state st(a, b);
      vector<state> neighbors = get_neighbors(st);
      int i = 0;
      for (state nextSt : neighbors) {
        nbrs[st].push_back(nextSt);
        edge_label[make_pair(st, nextSt)] = actions[i++];
      }
    }
  }
}

int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
