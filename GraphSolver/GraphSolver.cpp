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

using namespace GraphLibrary;

int main()
{
  
     Graph graph1;

     graph1.print();
    
     //std::cout << Graph::Add(5, 10) << std::endl;
}
