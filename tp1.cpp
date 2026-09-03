#include <vector>
#include <iostream>

using namespace std;

enum VerticeCor { BRANCO, CINZA, PRETO };

class Grafo {
private:
    
    struct Vertice {
        VerticeCor cor = BRANCO;
        int pai = -1;
    };

    vector<Vertice> _vertices;
    vector<vector<int>> _lista_adjacencia;
    int _num_vertices;
    int _distancia_max = 0;
    int _vertice_mais_distante = -1;

    void dfsInit(){
        for(int i = 0; i < _num_vertices; i++){
            _vertices[i].cor = BRANCO;
            _vertices[i].pai = -1;
        }
    }

    void dfsDistanciaRecursivo(int u, int dist){
        _vertices[u].cor = CINZA;

        if (dist > _distancia_max){
            _distancia_max = dist;
            _vertice_mais_distante = u;
        }

        for (int i = 0; i < _lista_adjacencia[u].size(); i++){
            int v = _lista_adjacencia[u][i];
            if (_vertices[v].cor != BRANCO) continue;
            _vertices[v].pai = u;
            dfsDistanciaRecursivo(v, dist + 1);
        }

        _vertices[u].cor = PRETO;
    }

public:
    Grafo(int num_vertices): _vertices(num_vertices), _lista_adjacencia(num_vertices), _num_vertices(num_vertices) {}
    ~Grafo(){}

    void adicionarAresta(int v1, int v2){
        _lista_adjacencia[v1].push_back(v2);
        _lista_adjacencia[v2].push_back(v1);
    }

    void dfsDistancia(int u){
        dfsInit();
        _distancia_max = -1;
        _vertice_mais_distante = u;
        dfsDistanciaRecursivo(u, 0);
    }
};

int main(){

}