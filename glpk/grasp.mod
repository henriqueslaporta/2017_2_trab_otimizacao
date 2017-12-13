set VERTICES;
set ARCS within (VERTICES cross VERTICES);

param dist{ARCS};
param score{VERTICES} default 0;
param costLimit;
param vInit;

var x{(i,j) in ARCS} binary;


maximize premio: sum{(i,j) in ARCS} x[i,j]*score[i];

s.t. NUMBER_ARCS{i in VERTICES}:
          sum{j in VERTICES: (i,j) in ARCS} x[vInit,j] + sum{j in VERTICES: (i,j) in ARCS} x[j,vInit] =2;

s.t. BALANCE{i in VERTICES}:
          sum{j in VERTICES: (i,j) in ARCS} x[i,j] 
        - sum{j in VERTICES: (j,i) in ARCS} x[j,i]
        = 0;
        

s.t. LIMIT_COST{(i,j) in ARCS}: x[i,j]*dist[i,j] <= costLimit ;

end;
