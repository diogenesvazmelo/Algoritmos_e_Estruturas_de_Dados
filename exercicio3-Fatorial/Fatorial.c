#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_DO_RESULTADO 35661
int vetor[LEN_DO_RESULTADO];


typedef struct{
    int carry;
    int resto;
} Carry_e_Resto;

int conta_digitos(numero){
    int i = 0;

    while (numero >= 10){
        numero = numero/10;
        i++;
    }
    if (numero < 10){
        i++;
    }
    return i;
}

void inicializa_vetor(){
    for (int i = 0; i < LEN_DO_RESULTADO; i++){
        vetor[i] = -1;
    }
}

void coloca_no_vetor(int numero, int j){
    for (int i = 0; i < j; i++){
        vetor[i] = numero % 10;
        numero = numero / 10;
    }
}

Carry_e_Resto multiplica(int a, int b, int carry){
    int c =  (a * b) + carry;

    Carry_e_Resto c_e_r;

    c_e_r.resto = c % 10;
    c_e_r.carry = c / 10;

    return c_e_r;
}

void imprime_o_vetor(int qt_digitos){
//    int i = 0;
//    while(vetor[i] != -1){
//        printf("%d", vetor[i]);
//        i++;
//    }
    for (int i = qt_digitos-1; i >= 0; i--){
        printf("%d", vetor[i]);
    }
}

int main(){
    inicializa_vetor();

	// Armazena a entrada do teclado
	int numero = 0;
	printf("Insira o numero: ");
	scanf("%d", &numero);

	// j será o índice para percorrer cada número da string
    int j = conta_digitos(numero);
    printf("Valor de j = %d\n\n\n", j);
    // Salva o número anterior em um vetor
    coloca_no_vetor(numero, j);

    int qt_digitos = 0;
    for (numero--; numero > 1; numero--){
        int carry = 0;
        qt_digitos = 0;
        for (int i = 0; vetor[i] != -1; i++){
            int a = vetor[i];
            int b = numero;

            ///printf("\nvetor[%d] antes: %d\n", i, vetor[i]);

            Carry_e_Resto cr = multiplica(a, b, carry);
            vetor[i] = cr.resto;
            carry = cr.carry;
            ///printf("\nvetor[%d] depois: %d\n", i, vetor[i]);

            qt_digitos++;
            if (vetor[i+1] == -1 && carry != 0){
                for (carry = carry; carry >= 10; carry = carry / 10){
                    i++;
                    vetor[i] = carry % 10;
                    qt_digitos++;
                }
                if (carry > 0){
                    vetor[i+1] = carry;
                    qt_digitos++;
                }
                break;
            }
        }
        ///printf("\n#########numero: %d\n ", numero);
    }

    printf("\n\n\n--------------------\n");
    imprime_o_vetor(qt_digitos);

    return 0;

}
