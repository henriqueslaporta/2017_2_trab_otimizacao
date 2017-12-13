set VERTICES;
set ARCS within (VERTICES cross VERTICES);

/* Custo limite total da soma dos arcos*/
param costLimit;

/* Vertice inicial */
param vInit;

/* Pontuacao de cada vertice */
param score{VERTICES} default 0;

/* Posição X de cada vertice */
param posX{VERTICES} default 0;

/* Posição Y de cada vertice */
param posY{VERTICES} default 0;

/* Se o arco Xij participa da solução */
var x{(i,j) in ARCS} binary;

var cost{(i,j) in ARCS} = round(sqrt( (posX[i]-posX[j])*(posX[i]-posX[j]) + (posY[i]-posY[j])*(posY[i]-posY[j]) ) + 0.5);

/* Formulação */
maximize premio: sum{(i,j) in ARCS} x[i,j]*score[i];

/* Verifica se começa e termina no mesmo vertice */
s.t. INIT{i in VERTICES}: sum{j in VERTICES: (vInit, j) in ARCS} x[vInit, j] + sum{j in VERTICES: (j, vInit) in ARCS} x[j, vInit] = 2;

/* Verifica se o mesmo arco entre dois vertices "vai e volta" A <-> B */
s.t. NUMBER_SAME_ARCS{i in VERTICES}:
          sum{j in VERTICES: (i,j) in ARCS} x[i,j] <=2;

/* Verifica o numero de arcos de entrada e saida */
s.t. NUMBER_ARCS{i in VERTICES}:
          sum{j in VERTICES: (i,j) in ARCS} x[i,j] 
          = sum{j in VERTICES: (j,i) in ARCS} x[j,i] ;

/* Verifica se a solução não ultrapassa do limite */
s.t. CAP {(i,j) in ARCS}: sum{i in VERTICES: sum{j in VERTICES: (i,j) in ARCS}} cost[i,j]*x[i,j] <= costLimit;

end;