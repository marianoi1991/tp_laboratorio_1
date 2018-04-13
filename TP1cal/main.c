#include <stdio.h>
#include <stdlib.h>
#include "Mi_libreria.h"


int main()
{
    char seguir='s';
    char auxChar[8];
    int opcion=0;
    float num1=0;
    float num2=0;
    int flagNum1=0;
    int flagNum2=0;
    while(seguir=='s')
    {
        if(menu(auxChar,flagNum1,flagNum2,num1,num2)==0)
        {
            opcion=atoi(auxChar);
            if(operaciones(opcion,&num1,&num2,&flagNum1,&flagNum2)==-1)
            {
                seguir='n';
            }
        }
        else
        {
            error3();
            system("pause");
        }

        system("cls");
    }
    return 0;
}

