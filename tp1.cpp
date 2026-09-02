#include <vector>

using namespace std;

enum VerticeCor { BRANCO, CINZA, PRETO };

class Grafo {
private:
    
    struct Vertice {
        int tempo_descoberta = 0;
        int tempo_fechamento = 0;
        VerticeCor cor = BRANCO;
        int pai = -1;
    };

    vector<Vertice> _vertices;
    vector<vector<int>> _lista_adjacencia;

public:
    Grafo(int num_vertices): _vertices(num_vertices), _lista_adjacencia(num_vertices) {}
    ~Grafo(){}

    void adicionarAresta(int v1, int v2){
        _lista_adjacencia[v1].push_back(v2);
        _lista_adjacencia[v2].push_back(v1);
    }
};