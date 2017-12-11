#define DeleteNode	0
#define AddNode 	1
#define optNode		2

void localSearch(int iteracoes){
	// Implementação do Hill Climbing
	// Variações de vizinhança:
	//		- Retirar um nodo aleatoriamente
	//		- Adicionar um nodo aleatóriamente
	//		- Selecionar um ńodo aleatório e realizar a troca 2-opt

	int *solucaoAux = new int [numVertices + 1];
	std::copy_n(solucaoAtual, numVertices+1, solucaoAux);
	int *acessoAux = new int [numVertices + 1];
	std::copy_n(acessoAtual, numVertices+1, acessoAux);
	int pontosAux = pontosAtual;
	int custoAux = custoAtual;
	int nodeRandom, opRandom;

	for(int k = 0; k < iteracoes; k++){
		opRandom = rand() % 3; //Numero aleatório para escolher qual opção vai ocorrer
		switch(opRandom){
			case DeleteNode:
					nodeRandom = rand() % (numVertices - 1);
					if(nodeRandom == verticeInit) break;
					// Testa se o nodo aleatório esta sendo utilizado na solucao
					if(acessoAux[nodeRandom] == 1){
						int achou = ERROR;
						//Procura a posicao do nodo na solucao atual
						for(int i = 0; i < numVertices + 1; i++){
							//Achou o nodo e atualiza os valores de custo e pontos
							if(solucaoAux[i] == nodeRandom){
								achou = TRUE;
								custoAux += adjacentMat[solucaoAux[i-1]][solucaoAux[i+1]];
								custoAux -= adjacentMat[solucaoAux[i-1]][nodeRandom] + adjacentMat[solucaoAux[i+1]][nodeRandom];
								pontosAux -= pontosVertice[nodeRandom];
							}
							//Arruma o array para a nova solucao atual
							else if(achou == TRUE){
								solucaoAux[i-1] = solucaoAux[i];
								if(solucaoAux[i] == -1){
									i = numVertices+1;
								}
							}
						} //END for
					} //END if
				break;
			case AddNode:
					nodeRandom = rand() % (numVertices - 1);
					// Teste se o nodo nao esta sendo utilizado para poder adicionar
					if(acessoAux[nodeRandom] == 0){
						//Gera uma posicao aleatoria
						int posRandom = rand() % (numVertices - 1);
						if(posRandom == verticeInit) break;
						int achou = ERROR;
						int aux1, aux2;
						//Procura a posição para inserir o nodo
						for(int i = 0; i < numVertices + 1; i++){
							//Achou a posicao e atualiza os valores de custo e pontos (se possivel)
							if(solucaoAux[i] == posRandom){
								int custo = custoAux + (adjacentMat[solucaoAux[i]][nodeRandom] + adjacentMat[solucaoAux[i+1]][nodeRandom]);
								custo -= adjacentMat[solucaoAux[i]][solucaoAux[i+1]];
								if( custo > costLimit)
									break;
								else{
									achou = TRUE;
									custoAux = custo;
									pontosAux += pontosVertice[nodeRandom];
									aux1 = solucaoAux[i+1];
									solucaoAux[i+1] = nodeRandom;
									acessoAux[nodeRandom] = 1;
								}
							}
							//Arruma o array para a nova solucao atual
							else if(achou == TRUE){
								if(solucaoAux[i] == -1){
									i = numVertices+1;
								}
								aux2 = solucaoAux[i+1];
								solucaoAux[i+1] = aux1;
								aux1 = aux2;							
							}
						} //END for
					}//END if
				break;
			case optNode:
					nodeRandom = rand() % (numVertices - 1);
					if(nodeRandom == verticeInit) break;
					// verifica se o nodo selecionado realmente esta sendo utilizado
					if(acessoAux[nodeRandom]){
						//Procura a posição para inserir o nodo
						for(int i = 0; i < numVertices + 1; i++){
							//Achou a posicao e atualiza os valores de custo e pontos (se possivel)
							if(solucaoAux[i] == nodeRandom){
								if(solucaoAux[i-1] == verticeInit || solucaoAux[i+1] == verticeInit){i=numVertices+1; break;}
								
								int custo = custoAux + adjacentMat[solucaoAux[i-2]][solucaoAux[i+1]] + adjacentMat[solucaoAux[i+1]][nodeRandom] + adjacentMat[nodeRandom][solucaoAux[i-1]] + adjacentMat[solucaoAux[i-1]][solucaoAux[i+2]];
								custo -= adjacentMat[solucaoAux[i-2]][solucaoAux[i-1]] - adjacentMat[solucaoAux[i-1]][nodeRandom] - adjacentMat[nodeRandom][solucaoAux[i+1]] - adjacentMat[solucaoAux[i+1]][solucaoAux[i+2]];
								
								if( custo > costLimit){i=numVertices+1; break;}
								else{
									custoAux = custo;
									int aux1 = solucaoAux[i-1];
									int aux2 = solucaoAux[i+1];
									solucaoAux[i-1] = aux2;
									solucaoAux[i+1] = aux1;
								}
							}
						} //END for
					}
				break;
		}//END Switch
		if(pontosAux >= pontosAtual){
			std::copy_n(solucaoAux, numVertices+1, solucaoAtual);
			std::copy_n(acessoAux, numVertices+1, acessoAtual);
			pontosAtual = pontosAux;
			custoAtual = custoAux;
		}
	}//END for iteracoes

	free(solucaoAux);
	free(acessoAux);

	return;
}