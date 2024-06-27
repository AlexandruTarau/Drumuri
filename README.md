# Drumuri obligatorii

 - Complexity:
   - Time: O(m * logn)
      - Explanation: Dijkstra -> O(m * logn). Finding the closest node to all 3 points (x, y, z) -> O(n). O(m * logn + n) = O(m * logn).
   - Space: O(n + m)
      - Explanation: Graph is represented as an adjacency list -> O(n + m). Dijkstra -> O(n). O(n + m + n) = O(n + m).
 - We read the each edge and compute the graph but also reverse the edges and compune a new reversed graph (edges x -> y turn into y -> x).
 - We use dijkstra for x and y to find the minimum cost paths to the rest of the nodes in the normal graph (adj).
 - We use dijkstra for z on the reversed graph (reverse_adj) to also find all minimum cost paths to each node.
 - Applying Dijkstra 3 times like this has the purpose of finding that one node that is closest to all 3 nodes (x, y, z). Finding this node is equivalent to finding the minimum sum between the distances from start (x, y, z) to that node, which is also the answer to the problem.
