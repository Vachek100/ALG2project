/**
 * @file functions.h
 * @brief @brief Deklarace tříd a funkcí pro výpočet minimální ceny přepravy mezi dvěma body pomocí Dijkstrova algoritmu.
 * @author Václav Králík    
 * <b>KRA0716</b>
 * @version 0.1
 * @date 2024-12-07
 * 
 * Tento soubor obsahuje deklarace tříd, které jsou použity pro reprezentaci grafu, výpočet nejkratší cesty
 * mezi dvěma uzly pomocí Dijkstrova algoritmu a pro uchování výsledků výpočtu (cena a cesta).
 * 
 *  
 * @copyright Copyright (c) 2024
 * 
 */


#include <vector>
#include <iostream>
#include <limits>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;


/**
 * @class Graph
 * @brief Třída reprezentující graf pomocí sousední matice.
 * 
 * Třída Graph obsahuje metody pro nastavení a získání váhy hran mezi uzly v grafu.
 * Graf je reprezentován jako čtvercová matice, kde každá buňka obsahuje váhu hrany mezi dvěma uzly.
 */
class Graph {
public:
    using Matrix = vector<vector<int>>; ///< Typ pro sousední matici.
    Matrix adjMatrix;

    /**
     * @brief Konstruktor pro inicializaci grafu.
     * 
     * Vytvoří graf o n uzlech, přičemž všechny hrany jsou inicializovány na hodnotu -1 (což znamená, že hrana neexistuje).
     * 
     * @param n Počet uzlů v grafu.
     */
    Graph(int n);

    /**
     * @brief Nastaví váhu hrany mezi dvěma uzly.
     * 
     * @param u Index prvního uzlu.
     * @param v Index druhého uzlu.
     * @param weight Váha hrany mezi uzly u a v.
     */
    void setEdge(int u, int v, int weight);

    /**
     * @brief Získá váhu hrany mezi dvěma uzly.
     * 
     * @param u Index prvního uzlu.
     * @param v Index druhého uzlu.
     * @return Váha hrany mezi uzly u a v, nebo -1, pokud hrana neexistuje.
     */
    int getEdgeWeight(int u, int v) const;

    /**
     * @brief Získá velikost grafu (počet uzlů).
     * 
     * @return Počet uzlů v grafu.
     */
    int size() const;
};


/**
 * @class Dijkstra
 * @brief Třída obsahující Dijkstra algoritmus pro výpočet nejkratší cesty mezi dvěma uzly v grafu.
 * 
 * Třída Dijkstra poskytuje statickou metodu pro výpočet nejkratší cesty mezi dvěma uzly
 * pomocí Dijkstrova algoritmu na grafu reprezentovaném třídou Graph.
 */
class Dijkstra {
public:
    /**
     * @brief Vypočítá nejkratší cestu mezi dvěma uzly v grafu.
     * 
     * @param graph Graf, ve kterém se hledá nejkratší cesta.
     * @param start Index startovního uzlu.
     * @param end Index cílového uzlu.
     * @return Pair, který obsahuje cenu (váhu) nejkratší cesty a cestu ve formě seznamu uzlů.
     */
    static pair<double, vector<int>> calculate(const Graph& graph, int start, int end);
};


/**
 * @class TransportResult
 * @brief Třída pro uchování výsledků výpočtu minimální ceny přepravy a cesty.
 * 
 * Třída TransportResult uchovává cenu přepravy (buď s nebo bez slevy) a seznam uzlů představující cestu.
 * Obsahuje metodu pro tisk výsledků.
 */
class TransportResult {
public:
    double cost; ///< Cena přepravy.
    vector<int> path; ///< Cesta mezi uzly ve formě seznamu uzlů.
    bool withDiscount; ///< Indikátor, zda byla použita sleva na hrany.


    /**
     * @brief Konstruktor třídy TransportResult.
     * 
     * Inicializuje objekt třídy TransportResult s danou cenou, cestou a indikátorem slevy.
     * 
     * @param cost Cena přepravy.
     * @param path Cesta (seznam uzlů).
     * @param withDiscount Indikuje, zda byla sleva použita (true/false).
     */
    TransportResult(double cost, vector<int> path, bool withDiscount);


     /**
     * @brief Vytiskne výsledky výpočtu (cena a cesta).
     * 
     * Tiskne cenu přepravy a cestu. Pokud je cena nekonečná, znamená to, že cesta neexistuje.
     */
    void print() const;
};



