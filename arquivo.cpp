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

	//Print
    cout << "param costLimit :=" << costLimit << ";\n";
	
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
    //for(int i = 0; i < numVertices;i++)
    //    cout << "index[" << i << "] " <<indexVertice[i][0] << " " << indexVertice[i][1] << "\n";
    //cout << "\n";
    
    return 0;
}

int readScoreSection(){
    char *token;
    if(fileHandle.eof()){ return ERROR;}

    pontosVertice = new int [numVertices];

    //Pula uma linha
    fileHandle.getline (buffer,100);

    for(int i = 0; i < numVertices; i++){
        fileHandle.getline (buffer,100);
        token = std::strtok(buffer, " ");
        int index = atoi(token);
        token = std::strtok(NULL, " ");
        pontosVertice[index-1] = atol(token);
    }

    //Print matriz
    cout << "param: VERTICES: score := "<<endl;
    for(int i = 0; i < numVertices;i++)
        cout <<  i+1 << "\t" << pontosVertice[i] << endl;
    cout << ";\n";
    
    return 0;
}

int readInitVertice(){
    if(fileHandle.eof()){ return ERROR;}

    //Pula uma linha
    fileHandle.getline (buffer,100);

    fileHandle.getline (buffer,100);
    verticeInit = atoi(buffer) - 1;

    //Print
    cout << "param vInit := 1" << ";\n";
    //cout << "\n";
    
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
            cout << "Error opening file" << endl;
            return ERROR;
    }
    else{
        //cout << "Opening file: " << file << endl;
        return 0;
    }
}