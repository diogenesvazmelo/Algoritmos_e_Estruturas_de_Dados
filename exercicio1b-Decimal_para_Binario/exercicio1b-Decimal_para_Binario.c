#include <stdio.h>

void dec2bin(int dec){

    if (dec>=2) {
        dec2bin(dec/2);
    }
    printf("%d", (dec%2));
}

int main (){

    int a=0;
   
    printf("Digite um numero inteiro: ");
    scanf("%d", &a);

    printf("Resultado: ");
    dec2bin(a);

    return 0;
}
