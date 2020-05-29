#include <stdio.h>

int mdc(int num1, int num2)
{
    if (num1%num2 == 0)
        return num2;

    return mdc(num2, num1%num2);

}

int main()
{
    int num1 = 0, num2 = 0;
    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &num1, &num2);

    if (num1 < num2)
    {
        int aux = num2;
        num2 = num1;
        num1 = aux;
    }

    if (num1%num2 == 0)
    {
        printf("Resultado: %d\n", num2);
    }
    else
    {
        printf("Resultado: %d\n", mdc(num1, num2));
    }

    return 0;
}


