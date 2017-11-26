
int greedy(){
	int *solucaoAux = new int [numVertices + 1];
	int *acesso = new int [numVertices + 1];
	int actual = verticeInit;
	int next = -1;
	int finish = 0;
	int custo = 0;
	int pontos = 0;
	int it = 1;
	
	
	for(int i = 0; i < numVertices+1; i++){
        acesso[i] = 0;solucaoAux[i] = -1;
	}
	acesso[verticeInit] = 1;
	solucaoAux[0] = verticeInit;
	
	while(finish != 1){
		//Procura o proximo nodo
		for(int i = 0; i < numVertices; i++){
			if(acesso[i] == 0 && (custo + adjacentMat[actual][i]) <= costLimit){
				if(next == -1 || (custo + adjacentMat[actual][i]) < (custo + adjacentMat[actual][next]))
					next = i;
			}
		}
		// Caso não encontrou nenhum nodo que nao ultrapasse o limite, retorna para o vertice inicial
		if(next == -1){
			int found;
			it--;
			while(found != 1){
				solucaoAux[it] = -1;
				pontos -= pontosVertice[actual];
				custo -= adjacentMat[solucaoAux[it-1]][actual];
				actual = solucaoAux[it-1];
				if(custo + adjacentMat[actual][verticeInit] <= costLimit){
					next = verticeInit;
					found = 1;
				}else
					it--;
			}
		}
		
		custo += adjacentMat[actual][next];
		pontos = pontos + pontosVertice[next];
		actual = next;
		solucaoAux[it] = next;
		acesso[next] = 1;
		
		
		if(next == verticeInit) finish = 1;
		
		next = -1;
		it++;
		if(it==1) acesso[verticeInit] = 0;
		if(it>numVertices+1) finish = 1;
		
	}
	
	solucaoAtual = solucaoAux;
	pontosAtual = pontos;
	custoAtual = custo;
	
	/*//Print matriz
	cout << "Custo: " << custo << "\tPremio: " << pontos << "\n";
	cout << solucaoAux[0];
    for(int i = 1; i < numVertices+1;i++){
        if(solucaoAux[i] != -1)
        	cout << " -> " << solucaoAux[i];
    }
    cout << "\n";
    /* */
    return 0;
}
