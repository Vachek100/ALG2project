/**
 * @file functions.cpp
 * @brief Implementace funkcí pro práci s grafem a Dijkstrovým algoritmem.
 * @author Václav Králík    
 * <b>KRA0716</b>    
 * @version 0.1
 * @date 2024-12-07
 * 
 * Tento soubor obsahuje implementaci tříd a funkcí potřebných pro reprezentaci grafu,
 * výpočet nejkratší cesty mezi dvěma uzly pomocí Dijkstrova algoritmu a tisk výsledků.
 * 
 * - Třída Graph reprezentuje graf pomocí sousední matice a poskytuje metody pro nastavení
 *   a získání váhy hran.
 * - Třída Dijkstra poskytuje statickou metodu pro výpočet nejkratší cesty mezi dvěma uzly.
 * - Třída TransportResult ukládá výsledky výpočtu (cena a cesta) a poskytuje metodu pro tisk těchto výsledků.
 * 
 * @see functions.h pro deklarace tříd a metod.
 * 
 * @copyright Copyright (c) 2024
 */

#include "functions.h"


/**
 * @class Graph
 * @brief Třída reprezentující graf pomocí sousední matice.
 * 
 * Třída Graph umožňuje reprezentovat graf pomocí čtvercové matice, kde každá buňka
 * obsahuje váhu hrany mezi dvěma uzly (pokud hrana existuje, jinak je hodnota -1).
 */
Graph::Graph(int n) : adjMatrix(n, vector<int>(n, -1)) {}


/**
 * @brief Nastaví váhu hrany mezi dvěma uzly v grafu.
 * 
 * @param u Index prvního uzlu.
 * @param v Index druhého uzlu.
 * @param weight Váha hrany mezi uzly u a v.
 */
void Graph::setEdge(int u, int v, int weight) {
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
}


/**
 * @brief Získá váhu hrany mezi dvěma uzly v grafu.
 * 
 * @param u Index prvního uzlu.
 * @param v Index druhého uzlu.
 * @return Váha hrany mezi uzly u a v, nebo -1, pokud hrana neexistuje.
 */
int Graph::getEdgeWeight(int u, int v) const {
    return adjMatrix[u][v];
}


/**
 * @brief Získá velikost grafu (počet uzlů).
 * 
 * @return Počet uzlů v grafu.
 */
int Graph::size() const {
    return adjMatrix.size();
}


/**
 * @class Dijkstra
 * @brief Třída poskytující Dijkstra algoritmus pro výpočet nejkratší cesty.
 * 
 * Třída Dijkstra obsahuje statickou metodu pro výpočet nejkratší cesty mezi dvěma uzly
 * v grafu reprezentovaném třídou Graph.
 * 
 * Tento kod jsem pouzil a upravil podle potřem mého projektu z této stránky -> https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
 */

/**
 * @brief Vypočítá nejkratší cestu mezi dvěma uzly v grafu pomocí Dijkstrova algoritmu.
 * 
 * @param graph Graf, ve kterém se hledá nejkratší cesta.
 * @param start Index startovního uzlu.
 * @param end Index cílového uzlu.
 * @return Pair, který obsahuje cenu (váhu) nejkratší cesty a cestu ve formě seznamu uzlů.
 */
pair<double, vector<int>> Dijkstra::calculate(const Graph& graph, int start, int end) {
    int n = graph.size();
    vector<double> dist(n, numeric_limits<double>::infinity());
    vector<int> parent(n, -1);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        double current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (int v = 0; v < n; ++v) {
            if (graph.getEdgeWeight(u, v) == -1) continue;
            double weight = graph.getEdgeWeight(u, v);
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    for (int at = end; at != -1; at = parent[at])
        path.push_back(at);
    reverse(path.begin(), path.end());

    if (path.size() == 1 && path[0] != start) return {numeric_limits<double>::infinity(), {}};
    return {dist[end], path};
}

/**
 * @class TransportResult
 * @brief Třída pro uchování výsledků výpočtu (cena a cesta).
 * 
 * Třída TransportResult ukládá cenu přepravy a cestu ve formě seznamu uzlů.
 * Také obsahuje metodu pro tisk výsledků.
 */

/**
 * @brief Konstruktor třídy TransportResult.
 * 
 * @param cost Cena přepravy.
 * @param path Cesta (seznam uzlů).
 * @param withDiscount Indikuje, zda byla použita sleva (true/false).
 */
TransportResult::TransportResult(double cost, vector<int> path, bool withDiscount)
    : cost(cost), path(move(path)), withDiscount(withDiscount) {}


/**
 * @brief Vytiskne výsledky výpočtu (cena a cesta).
 * 
 * Pokud je cena rovna nekonečnu (INF), znamená to, že není žádná dostupná cesta.
 * 
 * @see calculate pro výpočet ceny a cesty.
 */
void TransportResult::print() const {
    cout << (withDiscount
        ? "Minimum price for transporting goods at a discount: "
        : "Minimum price for transport of goods without discount: ");

    if (cost == numeric_limits<double>::infinity()) {
        cout << "-1, Route: []" << endl;
    } else {
        cout << fixed << setprecision(1) << cost << ", Route: [";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
}
