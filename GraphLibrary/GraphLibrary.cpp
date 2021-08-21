// GraphLibrary.cpp : Definuje funkce pro statickou knihovnu.
//

#include "GraphLibrary.h"
#include <iostream>

namespace GraphLibrary
{
    Graph::Graph()
    {
        this->vertex = 5;
        this->generate();
    }

    Graph::Graph(int vertex)
    {
        this->vertex = vertex;
    }

    Graph::~Graph()
    { 
        delete[] this->matrix;
    }

    void Graph::generate()
    {
        this->matrix = new int[this->vertex * this->vertex];

        for (int i = 0; i < this->vertex; i++)
        {
            for (int j = 0; j < this->vertex; j++)
            {
                this->matrix[i * this->vertex + j] = 0;
            }
        }
    }

    void Graph::changeAt(int x, int y, int value)
    {
        if (x > this->vertex || x < 0) {
            return;
        }

        if (y > this->vertex || y < 0) {
            return;
        }

        this->matrix[x * this->vertex + y] = value;
    }

    void Graph::print()
    {
        for (int i = 0; i < this->vertex; i++)
        {
            std::cout << '[';
            for (int j = 0; j < this->vertex; j++)
            {
                std::cout << this->matrix[i * this->vertex + j];
                if (this->vertex > (j + 1)) {
                    std::cout << ',';
                }
            }
            std::cout << ']' << std::endl;
        }
    }
}
