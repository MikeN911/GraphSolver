// GraphLibrary.cpp : Definuje funkce pro statickou knihovnu.
//

#include "GraphLibrary.h"



namespace GraphLibrary
{
    Graph::Graph()
    {
        this->vertices = 5;
        this->init();
    }


    Graph::Graph(int vertex)
    {
        this->vertices = vertex;
        this->init();
    }


    Graph::~Graph()
    {
        delete[] this->matrix;
    }


    void Graph::init()
    {
        this->matrix = new int[this->vertices * this->vertices];

        for (int i = 0; i < this->vertices * this->vertices; i++)
        {
            this->matrix[i] = 0;
        }
    }


    void Graph::generate()
    {
        for (int i = 0; i < this->vertices; i++)
        {
            int neighborhoods = rand() % this->vertices;
            for (int i = 0; i < neighborhoods; i++)
            {
                int neighborhood = rand() % (int)(this->vertices * Graph::RATE);
                this->makeEdge(i, neighborhood, true);
            }
        }
    }


    void Graph::changeAt(int x, int y, int value)
    {
        if (x >= this->vertices || x < 0) {
            return;
        }

        if (y >= this->vertices || y < 0) {
            return;
        }

        this->matrix[x * this->vertices + y] = value;
    }


    int Graph::get(int x, int y)
    {
        return this->matrix[x * this->vertices + y];
    }


    void Graph::makeEdge(int vertex_a, int vertex_b, bool indirect)
    {
        // Reálně hrana mezi dvěma stejnými body nemůže být
        if (vertex_a == vertex_b) {
            return;
        }
        
        this->changeAt(vertex_a, vertex_b, Graph::EDGE);

        if (indirect) {
            this->makeEdge(vertex_b, vertex_a, false);
        }
    }


    void Graph::print()
    {
        for (int i = 0; i < this->vertices; i++)
        {
            std::cout << '[';
            for (int j = 0; j < this->vertices; j++)
            {
                std::cout << this->matrix[i * this->vertices + j];
                if (this->vertices > (j + 1)) {
                    std::cout << ',';
                }
            }
            std::cout << ']' << std::endl;
        }
    }


    list<int> Graph::BFS(int start) 
    {
        bool* visited = new bool[this->vertices];
        for (int i = 0; i < this->vertices; i++)
            visited[i] = false;

        list<int> queue;
        list<int> list_visited;

        visited[start] = true;
        queue.push_front(start);

        while (!queue.empty()) {
            int v = queue.front();
            queue.pop_front();
            list_visited.push_front(v);

            for (int j = 0; j < this->vertices; j++) {
                if (this->matrix[v * this->vertices + j] && !visited[j]) {
                    queue.push_front(j);
                    visited[j] = true;
                }
            }
        }
        return list_visited;
    }

    void Graph::findComponents()
    {
        list<int> queue;
        for (int i = 0; i < this->vertices; i++) {
            queue.push_front(i);
        }

        this->components.clear();

        while (!queue.empty()) {
            int v = queue.front();
            list<int> component = this->BFS(v);
            this->components.push_back(component);

            for (int v : component) {
                queue.remove(v);
            }
        }
    }


    list<int> Graph::getComponentWithMaxVerticles()
    {
        this->findComponents();

        list<int> last_item = this->components.front();
        for (list<int> component : this->components) {
            if (component.size() > last_item.size()) {
                last_item = component;
            }
        }
        return last_item;
    }


    bool Graph::isConnected() {
        bool* visited = new bool[this->vertices];
        for (int i = 0; i < this->vertices; i++)
            visited[i] = false;

        list<int> queue;
        list<int> list_visited;

        visited[0] = true;
        queue.push_front(0);

        bool all = false;

        while (!queue.empty() && !all) {
            int v = queue.front();
            queue.pop_front();
            for (int j = 0; j < this->vertices; j++) {
                if (this->matrix[v * this->vertices + j] && !visited[j]) {
                    queue.push_front(j);
                    visited[j] = true;
                }
            }

            all = true;
            for (int j = 0; j < this->vertices; j++)
            {
                if (!visited[j]) all = false;
            }
        }
        return all;
    }


    list<vector<int>> Graph::helpConnected()
    {
        this->findComponents();
        int count = this->components.size();
        list<vector<int>> edges;

        list<int> last_comp = this->components.front();
        for (list<int> comp : this->components)
        {
            if (comp != last_comp) {
                last_comp.sort();
                comp.sort();
                vector<int> edge = vector<int>{ last_comp.back(), comp.front() };
                edges.push_front(edge);
                last_comp = comp;
            }
        }
        return edges;
    }


    void Graph::findPath(int start, int end)
    {
        this->findComponents();
        bool contain_both = false;
        list<int> component_found;
        for (list<int> comp : this->components)
        {
            bool contain_start = false;
            bool contain_end = false;
            
            for (int i : comp)
            {
                if (i == start) contain_start = true;
                if (i == end) contain_end = true;
            }

            if (contain_start && contain_end) {
                contain_both = true;
                component_found = comp;
                break;
            }
        }

        if (!contain_both) {
            cout << "Cesta nelze nalést, graf není spojítý a body patří do různých komponent";
            return;
        }

        this->hamCycle(start, end);
    }


    bool Graph::isSafe(int v, int path[], int pos)
    {
        if (this->get(path[pos - 1], v) == 0) {
            return false;
        }
        for (int i = 0; i < pos; i++)
            if (path[i] == v)
                return false;
        return true;
    }

    bool Graph::hamCycleUtil(int path[], int pos, int stop)
    {
        if (pos == this->vertices)
        {
            if (this->get(path[pos - 1], path[0]) == 1) {
                return true;
            } else {
                return true;

            }
        }
        for (int v = 1; v < this->vertices; v++)
        {
            if (this->isSafe(v, path, pos))
            {
                path[pos] = v;
                if (this->hamCycleUtil(path, pos + 1, stop) == true)
                    return true;
                path[pos] = -1;
            }
        }
        return false;
    }


    bool Graph::hamCycle(int start, int stop)
    {
        int* path = new int[this->vertices];
        for (int i = 0; i < this->vertices; i++)
            path[i] = -1;

        path[0] = start;
        if (this->hamCycleUtil(path, 1, stop) == false)
        {
            cout << "\nSolution does not exist" << endl;
            return false;
        }
        
        for (int i = 0; i < this->vertices; i++)
            cout << path[i] << ", ";
        
        cout << path[0] << ", ";
        cout << endl;
        
        return true;
    }
}
