#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>

#define ERROR -1

using namespace std;

ifstream fileHandle;
char buffer[256];
int status;

list<float> **indexVertice;

/* Constantes */
int numVertices; //numero de vértices do grafo
int costLimit;  //Numero limite de distancia possivel
int verticeInit; //Vertice inicial

int readFirstLines(){
    char *token;
    if(fileHandle.eof()){ return ERROR;}

    for(int i = 0; i < 3; i++){
        fileHandle.getline (buffer,100);
        cout << buffer << endl;
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
}

int readFile(){
    status = readFirstLines();
    if(status==ERROR){return ERROR;}



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

int main(){
    status = openFile("instances/a8.oplib");
    if(status==ERROR){return ERROR;}

    status = readFile();
    if(status==ERROR){return ERROR;}
    while (! fileHandle.eof() ){
        fileHandle.getline (buffer,100);
        cout << buffer << endl;
    }
    return 0;
}
