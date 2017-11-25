#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <math.h>

#define ERROR -1

using namespace std;

ifstream fileHandle;
char buffer[256];
int status;

/* Constantes */
int numVertices; //numero de v�rtices do grafo
int costLimit;  //Numero limite de distancia possivel
int verticeInit; //Vertice inicial]

float **indexVertice;
int *pontosVertice;
int **adjacentMat;
int *solucaoAtual;

int pontosAtual;
int custoAtual;

#include "arquivo.cpp"
#include "guloso.cpp"


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
    /* */

    return 0;
}

void printInfos(){
	cout << "Infos:\n";
	cout << "Numero de Vertices: " << numVertices << "\tCusto Limite: " << costLimit << "\n";
	cout << "Solucao Atual:\nCusto: " << custoAtual << "\tPremio: " << pontosAtual << "\n";
	cout << solucaoAtual[0];
    for(int i = 1; i < numVertices+1;i++){
        if(solucaoAtual[i] != -1)
        	cout << " -> " << solucaoAtual[i];
    }
    cout << "\n";
}

int main(){
    status = openFile("instances/bier127.oplib");
    if(status==ERROR){return ERROR;}

    status = readFile();
    if(status==ERROR){return ERROR;}

    solucaoAtual = new int [numVertices + 1];

    calcAdjacentMat();

	greedy();
	
	printInfos();

    return 0;
}