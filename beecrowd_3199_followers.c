// https://judge.beecrowd.com/en/problems/view/3139

#include <stdio.h>
#include <math.h>

int calculaMedia(int vetor[]){
    int soma = 0;
    for(int i = 0; i < 30; i++){
        soma += vetor[i];
    }

    return ceil((double)soma / 30);

}

int main() {
    int N, M;
    int vetor[30];
    int contador = 0;
    int dias_totais = 0;

    do{
        scanf("%d %d", &N, &M);
    }while(M <= N);


    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &vetor[0], &vetor[1], &vetor[2], &vetor[3], &vetor[4], &vetor[5], &vetor[6],
      &vetor[7], &vetor[8], &vetor[9], &vetor[10], &vetor[11], &vetor[12], &vetor[13], &vetor[14], &vetor[15], &vetor[16], &vetor[17], &vetor[18], &vetor[19], &vetor[20], &vetor[21],
     &vetor[22], &vetor[23], &vetor[24], &vetor[25], &vetor[26], &vetor[27], &vetor[28], &vetor[29]);


    while(N < M){
        int media = calculaMedia(vetor);
        N += media;
        vetor[contador] = media;
        contador++;

        if(contador > 29){
            contador = 0;
        }

        dias_totais++;
    }

    printf("%d\n", dias_totais);

    return 0;
}