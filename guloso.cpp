#include <stdlib.h>

#define MIN_RANDOM_RANGE 1
#define MAX_RANDOM_RANGE 100

int greedy(int argAlpha){
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

	int alpha = argAlpha;
	int random = 0;
	int ephi = 0;

	while(finish != 1){
		ephi = rand() % MAX_RANDOM_RANGE; // (%) aleatorio

		//se atingiu percentual aleatório pega o vizinho aleatorio e termina
		if(ephi <= (MAX_RANDOM_RANGE - alpha) ){
			for(int i = 0; i < numVertices * 10 ; ++i){
				random = rand() % numVertices-1; //vizinho aleatorio
				if(random >= 0 && random < numVertices && random != verticeInit && acesso[random] == 0){
					if((custo + adjacentMat[actual][random]) <= costLimit){
						next = random;
						i = numVertices * 10 + 1;
					}
				}
			}
		}
		else{
			//Procura o proximo nodo
			for(int i = 0; i < numVertices; ++i){
				// Pega o melhor vizinho
				if(acesso[i] == 0 && (custo + adjacentMat[actual][i]) <= costLimit){
					if(next == -1 || (custo + adjacentMat[actual][i]) < (custo + adjacentMat[actual][next]))
						next = i;
				}
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
		
		
		if(next == verticeInit)
			finish = 1;
		
		next = -1;
		it++;
		if(it==1) 
			acesso[verticeInit] = 0;

		if(it>numVertices+1) 
			finish = 1;
		
	}
	
	std::copy_n(solucaoAux, numVertices+1, solucaoAtual);
	std::copy_n(acesso, numVertices+1, acessoAtual);
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
    */

    free(solucaoAux);
	free(acesso);
    return 0;
}
