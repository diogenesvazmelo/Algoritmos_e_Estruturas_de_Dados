#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
   char posicao1;
   char posicao2;
} bloco;

void desloca3Letras(char *palavra)
{
    //char palavra[30], aux[30];
    char aux[1000];
    int i = 0, chave = -3;

    while(palavra[i] != '\0')
    {
        aux[i] = palavra[i];
        if (aux[i] == 35)
        {
            aux[i] = 32;
        }
        if (aux[i] <= 122 && aux[i] >= 97)
        {
            aux[i] = palavra[i] + chave;
            if((palavra[i] + chave) > 122)
            {
                aux[i] -=26;
            }
            if((palavra[i] + chave) < 97)
            {
                aux[i] += 26;
            }
        }
        if (aux[i] <= 90 && aux[i] >= 65)
        {
            aux[i] = palavra[i] + chave;
            if((palavra[i] + chave) > 90)
            {
                aux[i] -=26;
            }
            if((palavra[i] + chave) < 65)
            {
                aux[i] += 26;
            }
        }
    i++;
    }
    aux[i] = '\0';
    //printf("3 letras desloc: %s ", aux);

    for(int a = 0; a <= i; a++)
    {
        palavra[a] = aux[a];
    }

    printf("\n");
}

void trocarBlocos(bloco *b1_ptr, int tamanho)
{
    bloco auxiliar[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        auxiliar[i] = b1_ptr[i];
    }


    if (tamanho%2 != 0)
    {
        for (int i = 0; i < (tamanho-1)/2; i = i + 2)
        {
            b1_ptr[i] = auxiliar[tamanho - i - 1];
            b1_ptr[tamanho - i - 1] = auxiliar[i];
        }
    }
    if (tamanho%2 == 0)
    {
        for (int i = 0; i < (tamanho)/2; i = i + 2)
        {
            b1_ptr[i] = auxiliar[tamanho - i - 1];
            b1_ptr[tamanho - i - 1] = auxiliar[i];
        }
    }
}


void trocarBlocos2(bloco *b1_ptr, int tamanho)
{
    bloco auxiliar[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        auxiliar[i] = b1_ptr[i];
    }

    b1_ptr[0] = auxiliar[tamanho - 0 - 1];
    b1_ptr[tamanho - 0 - 1] = auxiliar[0];
}


void trocarPosicoes(bloco *b1)
{
    char aux;
    aux = b1->posicao2;
    b1->posicao2 = b1->posicao1;
    b1->posicao1 = aux;
}

void imprimeValorASCII()
{
    char Ch;
    Ch='#';
    printf ("%d",Ch);  /* Imprime o caracter como inteiro */

}

void imprimeResultado(bloco *b1_ptr, int tamanho)
{

    bloco auxiliar[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        auxiliar[i] = b1_ptr[i];
    }


    //printf("\n\n");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%c", auxiliar[i].posicao1);
        printf("%c", auxiliar[i].posicao2);
    }
}


int main()
{
    char entrada[] = "msg.txt";
    //printf("\n%s", entrada);

    printf("Digite o nome do arquivo: ");
    scanf("%s", entrada);

    char *entrada2 = entrada;
    //printf("\n%s", entrada2);


    char frase[1000];

    //FILE *pont_arq;
    FILE *pont_arq = fopen(entrada2, "r");

    if (pont_arq == NULL)
    {
        printf("\n Não foi possivel abrir");
        return 1;
    }
    //fscanf(pont_arq, "%s", frase);

    //while(fgets(frase, 1000, pont_arq) != NULL)
    fgets(frase, 1000, pont_arq);
    fclose(pont_arq);

    //printf("\n\n%s", frase);


    ///-------------------------------------------------------------------------------------------

    printf("\n");
    printf("--------------------\n");
    printf("Mensagem codificada:\n");
    printf("--------------------\n");
    printf("%s", frase);
    //scanf(" %s", frase);



    ///Deslocar 3 letras:
    desloca3Letras(frase);


    ///Colocar em blocos
    bloco vet_de_blocos[strlen(frase)/2];

    int j = 0;
    for (int i = 0; i < (strlen(frase)/2); i++)
    {
        vet_de_blocos[i].posicao1 = frase[j];
        vet_de_blocos[i].posicao2 = frase[j+1];
        j += 2;
    }


    //printf("\nchave: %c ", vet_de_blocos[0].posicao1);
    ///Trocar as posições dentro dos blocos de lugar

    for (int i = 0; i < (strlen(frase)/2); i++)
    {
        trocarPosicoes(&vet_de_blocos[i]);
    }
    //printf("\nchave: %c ", vet_de_blocos[0].posicao1);


    ///Trocar os blocos de lugar
    trocarBlocos(vet_de_blocos, (strlen(frase)/2));
    //trocarBlocos2(&vet_de_blocos, (strlen(frase)/2));


    ///Imprimir Resultado

    printf("----------------------\n");
    printf("Mensagem decodificada:\n");
    printf("----------------------\n");

    imprimeResultado(vet_de_blocos, (strlen(frase)/2));

    return 0;
}
