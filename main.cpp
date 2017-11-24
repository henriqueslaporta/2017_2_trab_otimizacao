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

float **indexVertice;
int *custoVertice;
int **adjacentMat;


/* Constantes */
int numVertices; //numero de vértices do grafo
int costLimit;  //Numero limite de distancia possivel
int verticeInit; //Vertice inicial

int readFirstLines(){
    char *token;
    if(fileHandle.eof()){ return ERROR;}

    for(int i = 0; i < 3; i++){
        fileHandle.getline (buffer,100);
    }

    // Le o numero de vertices
    fileHandle.getline(buffer,100);
    token = std::strtok(buffer, " ");
    token = std::strtok(NULL, " ");
    token = std::strtok(NULL, " ");
    numVertices = atoi(token);

    // Le o limite de distancia
    fileHandle.getline(buffer,100);
    token = std::strtok(buffer, " ");
    token = std::strtok(NULL, " ");
    token = std::strtok(NULL, " ");
    costLimit = atoi(token);

    cout << numVertices << "\n";
    cout << costLimit << "\n";

    return 0;
}

int readCoordSection(){
    char *token;
    if(fileHandle.eof()){ return ERROR;}

    indexVertice = new float *[numVertices];
    for(int n = 0; n < numVertices; n++)
          indexVertice[n] = new float[2];

    //Pula duas linhas
    fileHandle.getline (buffer,100);
    fileHandle.getline (buffer,100);

    for(int i = 0; i < numVertices; i++){
        fileHandle.getline (buffer,100);
        token = std::strtok(buffer, " ");
        int index = atoi(token);
        token = std::strtok(NULL, " ");
        indexVertice[index-1][0] = atol(token);
        token = std::strtok(NULL, " ");
        indexVertice[index-1][1] = atol(token);
    }

     //Print matriz
    for(int i = 0; i < numVertices;i++)
        cout << "index[" << i << "] (" <<indexVertice[i][0] << ") (" << indexVertice[i][1] << ")\n";
    /* */
    return 0;
}

int readScoreSection(){
    char *token;
    if(fileHandle.eof()){ return ERROR;}

    custoVertice = new int [numVertices];

    //Pula uma linha
    fileHandle.getline (buffer,100);

    for(int i = 0; i < numVertices; i++){
        fileHandle.getline (buffer,100);
        token = std::strtok(buffer, " ");
        int index = atoi(token);
        token = std::strtok(NULL, " ");
        custoVertice[index-1] = atol(token);
    }

     //Print matriz
    for(int i = 0; i < numVertices;i++)
        cout << "index[" << i << "] (" << custoVertice[i] << ")\n";
    /* */
    return 0;
}

int readInitVertice(){
    char *token;
    if(fileHandle.eof()){ return ERROR;}

    //Pula uma linha
    fileHandle.getline (buffer,100);

    fileHandle.getline (buffer,100);
    verticeInit = atoi(buffer);

    /* //Print
    cout << "Vertice inicial[" << verticeInit << "]\n";
    /* */
    return 0;
}

int readFile(){
    status = readFirstLines();
    if(status==ERROR){return ERROR;}

    status = readCoordSection();
    if(status==ERROR){return ERROR;}

    status = readScoreSection();
    if(status==ERROR){return ERROR;}

    status = readInitVertice();
    if(status==ERROR){return ERROR;}

    fileHandle.close();
    return 0;
}

int openFile(char* file){
    fileHandle.open(file);
    if (! fileHandle.is_open()){
            cout << "Error opening file";
            return ERROR;
    }
    else{
        cout << "Opening file: " << file << "\n";
        return 0;
    }
}

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

    //Print matriz
    for(int i = 0; i < numVertices; i++){
        cout << "index[" << i << "]";
        for(int j = 0; j < numVertices; j++){
            cout << " - " <<adjacentMat[i][j];
        }
        cout << "\n";
    }
    /* */

    return 0;
}



int main(){
    status = openFile("instances/a8.oplib");
    if(status==ERROR){return ERROR;}

    status = readFile();
    if(status==ERROR){return ERROR;}

    calcAdjacentMat();

    return 0;
}
