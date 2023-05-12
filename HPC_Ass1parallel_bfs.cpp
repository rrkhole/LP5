#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void bfs(vector<int> adj[], int s, bool visited[]) {
  queue<int> q;

  visited[s] = true;
  q.push(s);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    #pragma omp parallel for
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (!visited[v]) {
        visited[v] = true;
        q.push(v);
      }
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  bool visited[n + 1] = {false};
  vector<int> adj[n + 1];

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  // adj[0].push_back(1);
  // adj[0].push_back(2);
  // adj[1].push_back(3);
  // adj[2].push_back(3);
  // adj[2].push_back(5);
  // adj[3].push_back(6);
  // adj[5].push_back(9);
  // adj[9].push_back(8);

  double start_time = omp_get_wtime();

  bfs(adj, 0, visited);

  double end_time = omp_get_wtime();
  double elapsed_time = end_time - start_time;

  cout << "Visited nodes: ";
  for (int i = 0; i < n; i++) {
    if (visited[i]) {
      cout << i << " ";
    }
  }
  cout << endl;

  cout << "Time taken: " << elapsed_time << " seconds" << endl;

  return 0;
}
