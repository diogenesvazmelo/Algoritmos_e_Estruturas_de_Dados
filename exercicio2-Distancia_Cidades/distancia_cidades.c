#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <limits.h>

#define V 5


int dijkstra(int graph[V][V], int src, int destino_index, char cidades[10][21]);

typedef struct{
	char cidade1[21];
	char cidade2[21];
	int distancia;
} Rota;


int verifica_se_esta_no_vetor(char vetor[10][21], char palavra[], int tamanho_do_vetor){

    for (int i = 0; i < tamanho_do_vetor; i++){
        if (strcmp(palavra, vetor[i]) == 0){
            return 1;
        }
    }

    return 0;
}

int procura_caminhos_entre_cidades(Rota rotas_ptr[], char cidade1[], char cidade2[], int arestas){
    (rotas_ptr + 0)->cidade2;

    for(int i = 0; i < arestas; i++){
        if (strcmp((rotas_ptr + i)->cidade1, cidade1) == 0 && strcmp((rotas_ptr + i)->cidade2, cidade2) == 0){
            return (rotas_ptr + i)->distancia;
        }
	}


    return 0;
}

void impime_matriz(int matriz[V][V], int tamanho_linha, int tamanho_coluna){
    printf("\n\n");
    for (int i = 0; i < tamanho_linha; i++){
        for(int j = 0; j < tamanho_coluna; j++){
            printf("  %d  ", matriz[i][j]);
        }
        printf("\n");
    }

}


int main(int argc, char *argv[]){
	printf("Digite o nome do arquivo de entrada: ");
	char nome_do_arquivo[100];
	scanf("%s", &nome_do_arquivo);
//	char nome_do_arquivo[] = "teste.txt";

	FILE *arquivo;
 	arquivo = fopen(nome_do_arquivo, "r");
	if (arquivo == NULL){
		printf("Erro na abertura do aqruivo\n");
		return(1);
	}

	int arestas = 0;

	fscanf(arquivo, "%d", &arestas);

	Rota *rotas_ptr = (Rota*) malloc(arestas * sizeof(Rota));


	for(int i = 0; i < arestas; i++){

        fscanf(arquivo, "%s", (rotas_ptr + i)->cidade1);
		fscanf(arquivo, "%s", (rotas_ptr + i)->cidade2);
		fscanf(arquivo, "%d", &(rotas_ptr + i)->distancia);

	}

	int qt_cidades = 0;
    char cidades[10][21];

    for(int i = 0; i < arestas; i++){
        char cid[21];

        strcpy(cid, (rotas_ptr + i)->cidade1);
        int v = verifica_se_esta_no_vetor(cidades, cid, arestas);
        if (v == 0){
            strcpy(cidades[qt_cidades], cid);
            qt_cidades++;
        }
	}

    for(int i = 0; i < arestas; i++){
        char cid[21];

        strcpy(cid, (rotas_ptr + i)->cidade2);
        int v = verifica_se_esta_no_vetor(cidades, cid, arestas);
        if (v == 0){
            strcpy(cidades[qt_cidades], cid);
            qt_cidades++;
        }
	}


	char origem[21] = "";
	char destino[21] = "";

	fscanf(arquivo, "%s", origem);
	fscanf(arquivo, "%s", destino);

//	char origem[] = "A";
//    char destino[] = "D";


    int grafo[qt_cidades][qt_cidades];

    for (int i = 0; i < qt_cidades; i++){
        for(int j = 0; j < qt_cidades; j++){
            grafo[i][j] = 0;
        }
    }

    for (int i = 0; i < qt_cidades; i++){
        char linha[21];
        strcpy(linha, cidades[i]);

        for(int j = 0; j < qt_cidades; j++){
            char coluna[21];
            strcpy(coluna, cidades[j]);

            int dist = procura_caminhos_entre_cidades(rotas_ptr, linha, coluna, arestas);

            if (grafo[i][j] < dist)
                grafo[i][j] = dist;

            if (grafo[j][i] < dist)
                grafo[j][i] = dist;

        }
    }

    int origem_index = -1;
    int destino_index = -1;
    for (int i = 0; i < qt_cidades; i++){
        if (strcmp(origem, cidades[i]) == 0){
            origem_index = i;
        }
        if (strcmp(destino, cidades[i]) == 0){
            destino_index = i;
        }
    }
    if (origem_index == -1){
        printf("\n Cidade de origem não encontrada!");
        return 2;
    }
    if (destino_index == -1){
        printf("\n Cidade de destino não encontrada!");
        return 3;
    }

    //#define V qt_cidades

    printf("Menor percurso: ");
    int resposta = dijkstra(grafo, origem_index, destino_index, cidades);
    printf("%s\n", cidades[destino_index]);
    printf("Distancia total: %d", resposta);

	fclose(arquivo);
	return 0;
}






// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

//#include <limits.h>
//#include <stdio.h>

// Number of vertices in the graph
//#define V 5

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++){
		if (sptSet[v] == false && dist[v] <= min){
            min = dist[v];
            min_index = v;
		}
	}

	return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[])
{
	printf("\n\nVertex \t\t Distance from Source\n");
	for (int i = 0; i < V; i++)
		printf("%d \t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
int dijkstra(int graph[V][V], int src, int destino_index, char cidades[10][21])
{
	int dist[V]; // The output array. dist[i] will hold the shortest
	// distance from src to i

	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

    char vetor_menor_percurso[V][21];
	int vetor_menor_percurso_dist[V];
    int auxiliar2 = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;


        int auxiliar = 0;
		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++){

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v]){
				dist[v] = dist[u] + graph[u][v];
            }

            if (auxiliar == destino_index){
                strcpy(vetor_menor_percurso[auxiliar2], cidades[u]);
                vetor_menor_percurso_dist[auxiliar2] = dist[destino_index];
                auxiliar2++;
            }
            auxiliar++;

        }

	}

    int i = 0;
    do{
        printf("%s ", vetor_menor_percurso[i]);
        i++;
    }while(vetor_menor_percurso_dist[i-1] != dist[destino_index]);

//	// print the constructed distance array
//	printSolution(dist);

    return dist[destino_index];

}

