@vanunuraz@gmail.com
~Graph Project – Graph Implementation, Algorithms, and Data Structures~
This project implements a graph in C++ using an adjacency list without relying on STL containers (such as vector, stack, etc.).

The project executes several classical algorithms on an undirected graph, including:
    •BFS – Breadth-first search to create a BFS tree.
    •DFS – Depth-first search to create a DFS (tree or forest).
    •Dijkstra – Finding the shortest paths from the source to every vertex.
    •Prim – Building a minimum spanning tree (MST) using Prim's algorithm.
    •Kruskal – Building an MST using Kruskal's algorithm.

Project Structure:
The project is organized in a modular way. All the source files are arranged in a set of directories as described in the provided diagram. The main components include the graph implementation, algorithm implementations, the union-find data structure, a custom queue implementation, and unit tests.

realization:
    Graph Class
        Representation:
        The graph is implemented as an array of pointers to linked lists (an adjacency list). Each vertex has its own linked list containing the edges (instances of the Edge structure) adjacent to it.
        Main functions:
            •addEdge(int sourceId, int destId, int wheight): Adds an edge in both directions (for an undirected graph).
            •removeEdge(int sourceId, int destId): Removes an edge from the graph, including handling the removal in both directions.
            •print_graph(): Prints the graph in a readable format.
        In addition, the Graph class implements the copy constructor, assignment operator, and destructor to properly manage dynamic memory (following the rule of three).

    Algorithms Class
        This class contains static functions that implement various algorithms on the graph:
            •BFS: Generates a BFS tree from the graph starting at a given vertex.
            •DFS: Generates a DFS tree (or forest) from the graph, with function dfsVisit.
            •Dijkstra: Computes the shortest paths from the source to all vertices using the “relax” operation.
            •Prim: Builds a Minimum Spanning Tree (MST) using Prim’s algorithm. It checks for graph connectivity and throws an exception if the graph is not connected.
            •Kruskal: Constructs an MST by sorting the graph’s edges and using Union-Find to prevent cycles.
        Furthermore, there is a function called getDistance() that computes the distances in the graph after running Dijkstra’s algorithm. Also, there is a function called minimaliNode() that help to find short way at dijkstra and prime.
        Furthermore, there is a function called totalWeight() for the tests of MST (Prime, Kruskal).


    UnionFind Data Structure
        The UnionFind (or Disjoint Set) data structure implements the following operations:
            •find: Determines the representative (root) of a given element’s set, employing path compression to speed up subsequent lookups.
            •unionSets: Merges two sets using union by rank to keep the tree shallow.
        This structure is utilized within Kruskal’s algorithm to ensure that no edge is added that would create a cycle.

    Queue Class
        The Queue is implemented as a circular queue using an array. Its primary functions include:
            •enqueue: Adds an element to the queue, following the First-In-First-Out (FIFO) principle.
            •dequeue: Removes and returns an element from the queue.
            •isEmpty: Checks whether the queue is empty.
        Error handling is incorporated (e.g., throwing exceptions when attempting to enqueue to a full queue or dequeue from an empty queue).

Memory Management:
Memory is managed explicitly using dynamic allocation (new/delete and new[]/delete[]). The code carefully allocates and frees memory to avoid leaks, and all memory management is verified using Valgrind.

Unit Testing:
Unit tests have been written using the doctest framework to verify the correctness of all components. These tests cover scenarios for the graph operations, custom queue, union-find, and the various algorithms (BFS, DFS, Dijkstra, Prim, and Kruskal).

Requirements:
    •System Requirements:
        1. C++11 or higher.
        2. A compiler such as g++ or Visual Studio C++ (with support for C++11).
        3. Valgrind installed for memory leak detection.
    •Running the Project:
        The project uses a Makefile that includes targets for building and running the demo program, running unit tests, checking memory leaks via Valgrind, and cleaning up generated files.
        1. make clean
        2. make valgrind
        3. make Main
        4. make test

Implementation Approach:
The logic of the algorithms is implemented based on materials from the Algorithms 1 course, ensuring that the underlying principles are correctly applied to produce the required functionality.


