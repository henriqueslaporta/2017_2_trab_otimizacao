#include <stdlib.h>

#define MIN_RANDOM_RANGE 1
#define MAX_RANDOM_RANGE 100

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

	int alpha = 90; //menor que 90 dah estouro no range da linha 33
	int random = 0;
	int ephi = 0;

	while(finish != 1){
		//Procura o proximo nodo
		for(int i = 0; i < numVertices; ++i){
			
			// Pega o melhor vizinho
			if(acesso[i] == 0 && (custo + adjacentMat[actual][i]) <= costLimit){
				if(next == -1 || (custo + adjacentMat[actual][i]) < (custo + adjacentMat[actual][next]))
					next = i;
			}

			//aleatoriedade
			if (i < (numVertices - 1))
			{
				random = i + (rand() % static_cast<int>(numVertices - i + 1)); //vizinho aleatorio
				if(random > numVertices-1) random = numVertices-1; //controle para segmentation
				ephi = MIN_RANDOM_RANGE + (rand() % static_cast<int>(MAX_RANDOM_RANGE - MIN_RANDOM_RANGE + 1)); // (%) aleatorio

				//se atingiu percentual aleatório pega o vizinho aleatorio e termina o FOR
				if(ephi <= (MAX_RANDOM_RANGE - alpha)){
					if(acesso[random] == 0 && (custo + adjacentMat[actual][random]) <= costLimit){
						next = random;
						i = numVertices+1;
					}				
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
    */
    return 0;
}
