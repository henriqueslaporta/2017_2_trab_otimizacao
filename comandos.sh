#!/bin/bash
    echo "Iniciando teste kroA200"
  ./bin/main 700000 85 200 instances/a8.oplib > output/final/a8_final.dat
  ./bin/main 700000 85 200 instances/a16.oplib > output/final/a16_final.dat
  ./bin/main 700000 85 200 instances/ber25.oplib > output/final/ber25_final.dat
  ./bin/main 700000 85 200 instances/eil51.oplib > output/final/eil51_final.dat
  ./bin/main 700000 85 200 instances/eil76.oplib > output/final/eil76_final.dat
  ./bin/main 700000 85 200 instances/rat99.oplib > output/final/rat99_final.dat
  ./bin/main 700000 85 200 instances/lin105.oplib > output/final/lin105_final.dat
  ./bin/main 700000 85 200 instances/bier127.oplib > output/final/bier127_final.dat
  ./bin/main 700000 85 200 instances/pr152.oplib > output/final/pr152_final.dat
  ./bin/main 700000 85 200 instances/kroA200.oplib > output/final/kroA200_final.dat