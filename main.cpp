#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include <ctime>

#define TRUE	1
#define ERROR	-1

using namespace std;

ifstream fileHandle;
char buffer[256];
int status;

// Constantes
int numVertices; //numero de vértices do grafo
int costLimit;  //Numero limite de distancia possivel
int verticeInit; //Vertice inicial]

float **indexVertice;
int *pontosVertice;
int **adjacentMat;

// Melhor solução conhecida
int *solucaoMax;
int *acessoMax;
int pontosMax;
int custoMax;

// Solução atual
int *solucaoAtual;
int *acessoAtual;
int pontosAtual;
int custoAtual;

#include "arquivo.cpp"
#include "guloso.cpp"
#include "buscaLocal.cpp"

int calcAdjacentMat(){
	int xd, yd;

	adjacentMat = new int *[numVertices];
	for(int n = 0; n < numVertices; n++)
		  adjacentMat[n] = new int[numVertices];

	for(int i = 0; i < numVertices; i++){
		for(int j = 0; j < numVertices; j++){
			xd = indexVertice[i][0] - indexVertice[j][0];
			yd = indexVertice[i][1] - indexVertice[j][1];
			adjacentMat[i][j] = (int)(sqrt( xd*xd + yd*yd) + 0.5);
		}
	}

	/*//Print matriz
	cout << "Vertice";
	for(int i = 0; i < numVertices; i++){
		cout << "    " << i; 
	}
	cout << "\n";
	for(int i = 0; i < numVertices; i++){
		cout << "index[" << i << "]";
		for(int j = 0; j < numVertices; j++){
			cout << " - " <<adjacentMat[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
	*/
	return 0;
}

void printInfosAtual(){
	cout << "------------------ Infos --------------------------" << endl;
	cout << "Numero de Vertices: " << numVertices << "\tCusto Limite: " << costLimit << endl;
	cout << "Solucao Atual:\nCusto: " << custoAtual << "\tPremio: " << pontosAtual << endl;
	cout << solucaoAtual[0];
	for(int i = 1; i < numVertices+1;i++){
		if(solucaoAtual[i] != -1)
			cout << " -> " << solucaoAtual[i];
	}
	cout << endl;
	for(int i = 1; i < numVertices+1;i++){
		if(acessoAtual[i] != -1)
			cout << " -> " << acessoAtual[i];
	}
	cout << endl;
}

void printInfosMax(){
	cout << "------------------ Infos --------------------------" << endl;
	cout << "Numero de Vertices: " << numVertices << "\tCusto Limite: " << costLimit << endl;
	cout << "Solucao Max:\nCusto: " << custoMax << "\tPremio: " << pontosMax << endl;
	cout << solucaoMax[0];
	for(int i = 1; i < numVertices+1;i++){
		if(solucaoMax[i] != -1)
			cout << " -> " << solucaoMax[i];
	}
	cout << endl;
}

void grasp(int iteracoes, int alpha, int itLocal){
	int i;
	for(i = 0; i < iteracoes; i++){
		custoAtual = 0;
		pontosAtual = 0;
		cout << ""; //Por motivos magicos se eu tirar esse linha ocorre segmentation fault
		greedy(alpha);
		localSearch(itLocal);
		if(pontosAtual > pontosMax){
			pontosMax = pontosAtual;
			custoMax = custoAtual;
			solucaoMax = solucaoAtual;
			//printInfosMax();
		}
	}
	return;
}

int main(int argc, char * argv[]){

	if (argc != 5)
	{
		cerr << " USO CORRETO: ./bin/main IteracoesGRASP Alpha IteracoesBuscaLocal NAMEFILE.oplib > output/OUT.dat " << endl;
		return 0;
	}

	int iteracoes = atoi(argv[1]);
	int alpha = atoi(argv[2]);
	int itLocal = atoi(argv[3]);
	char *pathfile = argv[4];

	status = openFile(pathfile);
	if(status==ERROR){return ERROR;}

	status = readFile();
	if(status==ERROR){return ERROR;}

	int start_t = clock();

	calcAdjacentMat();

	solucaoAtual = new int [numVertices + 1];

	grasp(iteracoes,alpha, itLocal);

	printInfosMax();

	int stop_t = clock();

	cout << "time :" << (stop_t - start_t) / double(CLOCKS_PER_SEC)*1000 << endl;

	return 0;
}
