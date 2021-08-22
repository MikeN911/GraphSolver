#pragma once

#include <iostream>
#include <list>
#include <vector>
using namespace std;

namespace GraphLibrary
{
    class Graph
    {
        int const EDGE = 1;
        float const RATE = 0.3f;

        private:
            int vertices;
            int* matrix;
            list<list<int>> components;

            void init();
            void changeAt(int, int, int);
            int get(int, int);

        public:
            Graph();
            Graph(int);
            ~Graph();
 
            void generate();
            void makeEdge(int, int, bool);
            void print();

            list<int> BFS(int);

            void findComponents();
            list<int> getComponentWithMaxVerticles();

            bool isConnected();
            list<vector<int>> helpConnected();

            void findPath(int, int);
            bool isSafe(int, int path[], int);
            bool hamCycleUtil(int path[], int, int);
            bool hamCycle(int, int);
    };
}