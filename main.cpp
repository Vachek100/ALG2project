/**
 * @file main.cpp
 * @brief Hlavní program pro výpočet minimální ceny přepravy mezi dvěma body pomocí Dijkstrova algoritmu.
 * @author Václav Králík    
 * <b>KRA0716</b>
 * @version 0.1
 * @date 2024-12-07
 * 
 * Tento program čte graf ze souboru (reprezentovaný jako sousední matice) a vypočítá nejkratší cestu
 * mezi dvěma uzly (A a B), a to jak bez slevy, tak se slevou na váhách hran.
 * Program používá Dijkstrův algoritmus k výpočtu nejkratší cesty a její ceny, nejprve bez jakékoliv slevy
 * a poté tím, že zkrátí váhu každé hrany v grafu na polovinu a znovu spočítá cestu a cenu.
 * 
 * 
 * Program vypíše dva výsledky:
 * 1. Minimální cena přepravy a cesta bez slevy.
 * 2. Minimální cena přepravy a cesta se slevou aplikovanou na hrany.
 * 
 * 
 * @see functions.h, functions.cpp pro implementaci třídy Graph, Dijkstrova algoritmu a formátování výsledků.
 * 
 * @copyright Copyright (c) 2024
 */
#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;

int main() {
    ifstream inputFile("matrixes/Matrix1.txt");
    if (!inputFile) {
        cerr << "Failed to open file Matrix1.txt" << endl;
        return 1;
    }

    int n;
    inputFile >> n;
    Graph graph(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int weight;
            inputFile >> weight;
            graph.setEdge(i, j, weight);
        }
    }

    int A, B;
    inputFile >> A >> B;
    inputFile.close();

    auto result_no_discount = Dijkstra::calculate(graph, A, B);
    double cost_no_discount = result_no_discount.first;
    vector<int> path_no_discount = result_no_discount.second;

    double min_cost_with_discount = numeric_limits<double>::infinity();
    vector<int> best_path_with_discount;

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (graph.getEdgeWeight(u, v) > 0) {
                int original_weight = graph.getEdgeWeight(u, v);
                graph.setEdge(u, v, original_weight / 2);

                auto result_with_discount = Dijkstra::calculate(graph, A, B);
                double cost_with_discount = result_with_discount.first;
                vector<int> path_with_discount = result_with_discount.second;

                if (cost_with_discount < min_cost_with_discount) {
                    min_cost_with_discount = cost_with_discount;
                    best_path_with_discount = path_with_discount;
                }

                graph.setEdge(u, v, original_weight);
            }
        }
    }

    TransportResult result_no_discount_obj(cost_no_discount, path_no_discount, false);
    TransportResult result_with_discount_obj(min_cost_with_discount, best_path_with_discount, true);

    result_no_discount_obj.print();
    result_with_discount_obj.print();

    return 0;
}
