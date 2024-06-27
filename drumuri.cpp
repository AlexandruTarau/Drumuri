#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    static constexpr int NMAX = (int)1e5 + 5;
    int n, m, x, y, z;

    /* adj - adjacent list of graph including edge costs
     * reverse_adj - adjacent list of graph in reverse order
     * (edges x->y turn into y->x)
     */
    vector<pair<int, int>> adj[NMAX];
    vector<pair<int, int>> reverse_adj[NMAX];

    void read_input() {
        ifstream fin("drumuri.in");
        fin >> n >> m;

        // Reading the edges of the graph
        for (int i = 1, a, b, c; i <= m; i++) {
            fin >> a >> b >> c;
            adj[a].push_back({b, c});

            // Form a graph with edges in reverse order
            reverse_adj[b].push_back({a, c});
        }
        fin >> x >> y >> z;
        fin.close();
    }

    // Function that calculates the minimum cost path from start to all node
    vector<long long> dijkstra(int start, vector<pair<int, int>> adj[]) {
        // Initialize the distance vector with infinite distances
        vector<long long> d(n + 1, INT64_MAX);

        /* Instead of a priority_queue<>, we use set<>, with elements being
         * tuples of the form (distance to node, node). The set keeps elements
         * ordered, so we will always have the tuple corresponding to the node
         * with the minimum distance at pq.begin()
         */
        set<pair<long long, int>> pq;

        // Insert the starting node into the queue and update its distance
        d[start] = 0;
        pq.insert({d[start], start});

        while (!pq.empty()) {
            // Remove the top element
            auto top = pq.begin();
            const auto [_, node] = *top;
            pq.erase(top);

            // Iterate through all neighbors
            for (const auto& [neigh, w] : adj[node]) {
                // If the distance improves
                if (d[node] + w < d[neigh]) {
                    // Remove the old pair/distance from the set
                    pq.erase({d[neigh], neigh});

                    // Update the distance
                    d[neigh] = d[node] + w;

                    // Insert the new distance
                    pq.insert({d[neigh], neigh});
                }
            }
        }

        // All nodes for which the distance is still INF cannot be reached from
        // the source node, so we set them to -1
        for (int node = 1; node <= n; node++) {
            if (d[node] == INT64_MAX) {
                d[node] = -1;
            }
        }

        return d;
    }

    long long get_result() {
        long long min = INT64_MAX, sum;

        // Gets the minimum cost from x to every node in graph
        vector<long long> dr1 = dijkstra(x, adj);

        // Gets the minimum cost from y to every node in graph
        vector<long long> dr2 = dijkstra(y, adj);

        // Gets the minimum cost from z to every node in the reversed graph
        vector<long long> dr3 = dijkstra(z, reverse_adj);

        /* We search for the node which is closest to all 3 points (x, y, z).
         * Therefore, the sum of the minimum paths to that node will be the
         * result.
         */
        for (int i = 1; i <= n; i++) {
            // If there is a path to the node from all 3 points
            if (dr1[i] != -1 && dr2[i] != -1 && dr3[i] != -1) {
                // Calculate the new sum and update the min if the cost is lower
                sum = dr1[i] + dr2[i] + dr3[i];
                if (min > sum) {
                    min = sum;
                }
            }
        }

        return min;
    }

    void print_output(const long long d) {
        ofstream fout("drumuri.out");
        fout << d;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
