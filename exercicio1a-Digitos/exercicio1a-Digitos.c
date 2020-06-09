#include <stdio.h>

int Digitos(int N){
  //int cont = 1;

  if (N < 10)
    return 1;
  else{
    //cont++;
    return (Digitos(N/10))+1;
  }

  //return cont;
}

int main (){

    int a, quantidade;
    printf("Digite um numero inteiro: ");
    scanf("%d", &a);

    quantidade = Digitos(a);

    printf("Resultado: %d", quantidade);

return 0;
}
