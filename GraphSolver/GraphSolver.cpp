// GraphSolver.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
// 

/*
* ZADÁNÍ :
* Vytvorte aplikaci, ktera s vyuzitim vasi naimportovane knihovny bude resit nasledujici grafove algoritmy:
*   Nalezne a vypise cestu mezi vrcholy zadanymi uzivatelem.
*   Nalezne komponentu s nejvetsim poctem vrcholu. Vypise vrcholy teto komponenty.
*   Zjisti, jestli je graf spojity, pokud ne, navrhne, ktere vrcholy spojit hranou, aby se graf stal spojitym.
* 
* Aplikace nabidne uzivateli 3 ruzne grafy reprezentovane matici (vypise na obrazovku), pricemz alespon jeden graf bude mit jiny pocet vrcholu, nez zbyle dva.
* Uzivatel si vybere jeden z grafu a nasledne si vybere algoritmus.
* Knihovna bude importovana - tj. funkce pro praci s dynamickou strukturou nebudou soucasti predkladane aplikace, ale budou volany z knihovny.
*/

#include <iostream>
#include "GraphLibrary.h"

using namespace std;
using namespace GraphLibrary;

int main()
{
    cout << "GRAPH A:" << endl;
    Graph graphA(10);
    graphA.generate();
    graphA.print();
    cout << endl;

    cout << "GRAPH B:" << endl;
    Graph graphB(8);
    graphB.generate();
    graphB.print();
    cout << endl;
    

    cout << "GRAPH C:" << endl;
    Graph graphC(8);
    graphC.makeEdge(0, 1, true);
    graphC.makeEdge(1, 2, true);
    graphC.makeEdge(1, 3, true);
    graphC.makeEdge(2, 3, true);
    graphC.makeEdge(0, 3, true);

    graphC.makeEdge(4, 5, true);
    graphC.makeEdge(4, 6, true);
    graphC.makeEdge(4, 7, true);
    graphC.makeEdge(5, 7, true);
    graphC.print();
    cout << endl;


    cout << "Vyberte graf [A/B/C]:" << endl;
    string graph_id;
    cin >> graph_id;


    Graph *current_graph;
    if (graph_id == "A") {
        current_graph = &graphA;
    } else if (graph_id == "B") {
        current_graph = &graphB;
    } else if (graph_id == "C") {
        current_graph = &graphC;
    } else {
        cout << "Nebyl vybran vhodny graf." << endl;
        return 0;
    }
    cout << "Vybrany graf:" << endl << endl;
    current_graph->print();

    
    cout << "Vyberte algoritmus [pathfinder/max_verticles/connected]:" << endl;
    string algorithm;
    cin >> algorithm;
    

    if (algorithm == "max_verticles") {
        list<int> max_component = current_graph->getComponentWithMaxVerticles();
        cout << "Komponenta s maximalnim poctem vrcholu:" << endl;
        for (int i : max_component)
        {
            cout << i << ", ";
        }
        cout << endl;
        return 0;
    }
    

    if (algorithm == "connected") {
        if (current_graph->isConnected()) {
            cout << "Graf je spojity" << endl;
        }
        else {
            cout << "Graf neni spojity" << endl;
            list<vector<int>> edges = current_graph->helpConnected();

            for (vector<int> i : edges)
            {
                cout << "Spojit vrchol " << i.at(0) << " a " << i.at(1) << endl;
                current_graph->makeEdge(i.at(0), i.at(1), true);
            }
        }
        return 0;
    }
    

    if (algorithm == "pathfinder") {
        int start, end;
        cout << "Zadejte vychozi bod:" << endl;
        cin >> start;
        cout << "Zadejte koncovy bod:" << endl;
        cin >> end;

        current_graph->findPath(start, end);
        return 0;
    }

    cout << "Nebyl vybran vhodny algoritmus." << endl;
    return 0;
}
