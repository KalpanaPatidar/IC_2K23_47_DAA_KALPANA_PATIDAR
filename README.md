# Unit 7 – Graphs (Data Structures Lab)

This folder contains C++ implementations of the Unit 7 Graph topics from the IC-307D Data Structures Lab assignment.

## Programs

1. `01_Adjacency_Matrix.cpp` – Graph representation using an adjacency matrix.
2. `02_Adjacency_List.cpp` – Graph representation using an adjacency list.
3. `03_BFS_Traversal.cpp` – Breadth First Search using a queue.
4. `04_DFS_Recursive.cpp` – Depth First Search using recursion.
5. `05_DFS_Iterative.cpp` – Depth First Search using a stack.
6. `06_Dijkstra_Shortest_Path.cpp` – Shortest distances in a non-negative weighted undirected graph.
7. `07_Social_Network.cpp` – Direct friends and friends-of-friends.
8. `08_Maze_Solver_BFS.cpp` – Finds a shortest path through a fixed 5×5 maze using BFS.
9. `09_Topological_Sort.cpp` – Topological sorting using Kahn's algorithm.
10. `10_Connected_Components.cpp` – Finds connected components using DFS.

## Compile and run

Using g++:

```bash
g++ 03_BFS_Traversal.cpp -o bfs
./bfs
```

On Windows:

```bash
g++ 03_BFS_Traversal.cpp -o bfs.exe
bfs.exe
```

Replace the filename and output name for the program you want to run.

## Notes

- Most graph programs use vertex numbering from `0` to `n-1`.
- The adjacency matrix/list, BFS, DFS, social network, and connected-components examples use undirected graphs.
- Topological sorting uses directed edges (`u v` means `u -> v`) and works only for a Directed Acyclic Graph (DAG).
- Dijkstra's algorithm requires non-negative edge weights.
- The maze program uses `0` for an open cell and `1` for a wall.

## Learning outcomes

- Understand graph representations.
- Perform BFS and DFS traversals.
- Apply graphs to shortest-path, social-network, maze, and dependency problems.
- Identify connected components and understand topological ordering.
