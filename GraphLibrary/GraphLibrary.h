#pragma once

#include <list>
#include <vector>


namespace GraphLibrary
{
    class Graph
    {
        private:
            int vertex;
            int* matrix;
            void changeAt(int, int, int);

        public:
            Graph();
            Graph(int);
            ~Graph();
            void generate();
            void print();
    };
}