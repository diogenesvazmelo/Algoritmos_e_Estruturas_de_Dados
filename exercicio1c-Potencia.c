#include <stdio.h>

int mult(int base, int exp){

    if (exp>=1) {
        return base*mult(base, exp-1);
    }
    else
        return 1;
}

int main (){

    int a, b;
    int quantidade;
    printf("Digite a base e o expoente inteiros: ");
    scanf("%d %d", &a, &b);

    printf("Resultado: ");
    quantidade = mult(a,b);

    printf("%d", quantidade);

    //printf("Resultado = %d", quantidade);

    //while (quantidade[100]>2){

        //printf("Resultado = ");

    //}

return 0;
}
