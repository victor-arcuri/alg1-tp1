#include <vector>
#include <iostream>

using namespace std;

enum VerticeCor { BRANCO, CINZA, PRETO };

class Grafo {
private:
    
    struct Vertice {
        VerticeCor cor = BRANCO;
        int pai = -1;
        int profundidade = -1;
    };

    vector<Vertice> _vertices;
    vector<vector<int>> _lista_adjacencia;
    int _num_vertices;

    void dfsInit(){
        for(int i = 0; i < _num_vertices; i++){
            _vertices[i].cor = BRANCO;
            _vertices[i].pai = -1;
            _vertices[i].profundidade = -1;
        }
    }

    void dfsRecursivo(int v, int profundidade){
        _vertices[v].cor = CINZA;
        _vertices[v].profundidade = profundidade;
        for (int i = 0; i < _lista_adjacencia[v].size(); i++){
            if (_vertices[_lista_adjacencia[v][i]].cor != BRANCO) continue;
            _vertices[_lista_adjacencia[v][i]].pai = v;
            dfsRecursivo(_lista_adjacencia[v][i], profundidade+1);
        }
        _vertices[v].cor = PRETO;
    }

    int contarPontas(int v, int bloqueado, int profundidade, int profundidade_alvo){
        int soma = 0;
        _vertices[v].cor = CINZA;
        _vertices[v].profundidade = profundidade;

        if (profundidade == profundidade_alvo) return 1;
        for (int i = 0; i < _lista_adjacencia[v].size(); i++){
            if (_vertices[_lista_adjacencia[v][i]].cor != BRANCO) continue;
            if (_lista_adjacencia[v][i] == bloqueado) continue;
            _vertices[_lista_adjacencia[v][i]].pai = v;
            soma += contarPontas(_lista_adjacencia[v][i], bloqueado, profundidade + 1, profundidade_alvo);
        }
        _vertices[v].cor = PRETO;
        return soma;
    }

        void dfs(){
        dfsInit();
        for (int i = 0; i < _vertices.size(); i++){
            if (_vertices[i].cor != BRANCO) continue;
            dfsRecursivo(i, 0);
        }
    }

    void dfsEspecifico(int v){
        dfsInit();
        dfsRecursivo(v, 0);
    }

    int verticeMaiorProfundidade(){
        int profunidade_max = -1;
        int vertice_profunidade_max = -1;
        for (int i = 0; i < _num_vertices; i++){
            if (_vertices[i].profundidade <= profunidade_max) continue;
            profunidade_max = _vertices[i].profundidade;
            vertice_profunidade_max = i;
        }
        return vertice_profunidade_max;
    }

    vector<int> encontrarCentros(){
        vector<int> centros;

        dfs();
        int A = verticeMaiorProfundidade();

        dfsEspecifico(A);
        int B = verticeMaiorProfundidade();

        int u = B;
        int profundidade = _vertices[B].profundidade;

        for (int i = 0; i < profundidade / 2; i++){
            u = _vertices[u].pai;
        }

        centros.push_back(u);
        
        if (profundidade % 2 == 0) return centros;

        centros.push_back(_vertices[u].pai);
        return centros;
    }

public:
    Grafo(int num_vertices): _vertices(num_vertices), _lista_adjacencia(num_vertices), _num_vertices(num_vertices) {}
    ~Grafo(){}

    void adicionarAresta(int v1, int v2){
        _lista_adjacencia[v1].push_back(v2);
        _lista_adjacencia[v2].push_back(v1);
    }

    void encontrarMaiorCiclo(){
        vector<int> centros;
        long long quantidade_ciclos = 0;

        centros = encontrarCentros();

        int maior_profundidade = _vertices[verticeMaiorProfundidade()].profundidade;
        int tamanho_ciclo = maior_profundidade+ 1;
        dfsInit();
        if (centros.size() == 1){
            long long soma_acumulada = 0;
            for (int i = 0; i < _lista_adjacencia[centros[0]].size(); i++){
                int vizinho = _lista_adjacencia[centros[0]][i];
                long long pontas = contarPontas(vizinho, centros[0], 1, maior_profundidade / 2);
                quantidade_ciclos += pontas * soma_acumulada;
                soma_acumulada += pontas;
                
            }
        }
        
        else if (centros.size() == 2){
            long long primeiro_centro_pontas = contarPontas(centros[0], centros[1], 0, maior_profundidade / 2);
            long long segundo_centro_pontas = contarPontas(centros[1], centros[0], 0, maior_profundidade / 2);
            quantidade_ciclos = primeiro_centro_pontas * segundo_centro_pontas; 
        }   

        printf("%d\n", tamanho_ciclo);
        printf("%lld\n", quantidade_ciclos);
        
    }
};

int main(){
    int n;
    scanf("%d", &n);

    Grafo universidade = Grafo(n);

    for (int i = 0; i < n - 1; i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        universidade.adicionarAresta(v1 -1, v2 -1);
    }

    universidade.encontrarMaiorCiclo();

}