#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mi_libreria.h"

/** \brief esta funcion muestra por pantalla las opciones de la calculadora y toma la opcion que ingresa el usuario
 *
 * \param aux char* recibe por referencia donde tiene que guardar la opcion ingresada por el usuario
 * \param x int variable que me indica si tengo algo ingresado en el primer operando
 * \param y int variable que me indica si tengo algo ingresado en el segundo operando
 * \param Num1 float variable donde se guarda el primer operando, lo recibo para mostrarlo en pantalla
 * \param Num2 float variable donde se guarda el segundo operando, lo recibo para mostrarlo en pantalla
 * \return int devuelvo 0 si la funcion termina ok, devulevo -1 si ingreso un dato que no sea numerico
 *
 */
int menu(char* aux,int x,int y,float Num1,float Num2)
 {
    int rta=-1;
    if(x==0)
    {
        printf("1- Ingresar 1er operando (A=X)\n");
    }
    else
    {
        printf("1- Ingresar 1er operando (A=%.2f)\n",Num1);
    }
    if(y==0)
    {
        printf("2- Ingresar 2do operando (B=Y)\n");
    }
    else{
        printf("2- Ingresar 2do operando (B=%.2f)\n",Num2);
    }
    printf("3- Calcular la suma (A+B)\n4- Calcular la resta (A-B)\n5- Calcular la division (A/B)\n6- Calcular la multiplicacion (A*B)\n7- Calcular el factorial (A!)\n8- Calcular todas las operacione\n9- Salir\n\nOPCION:");
    scanf("%s",aux);
    if(validoNumeros(aux)==0)
    {
        rta=0;
    }

    return rta;
 }

 /** \brief esta funcion recibe la opcion elegida por el usuario y llama a las operaciones
  *
  * \param opcion int recibo la opcion que ingreso el usuario
  * \param num1 float* valor del primer operando
  * \param num2 float* valor del segundo operando
  * \param flagNum1 int* variable que me indica si tengo algo ingresado en el primer operando
  * \param flagNum2 int* variable que me indica si tengo algo ingresado en el segundo operando
  * \return int devuelvo 0 si esta ok, devuelvo -1 si ingrese una opcion no valida
  *
  */
 int operaciones(int opcion,float* num1,float* num2,int* flagNum1,int* flagNum2)
{
    int rta=0,codError;
    float resultado;
    switch(opcion)
    {
        case 1:
            ingresoNum(num1);
            *flagNum1=1;
            system("pause");
            break;
        case 2:
            ingresoNum(num2);
            *flagNum2=1;
            system("pause");
            break;
        case 3:
            printf("Suma\n-----\n");
            if(sumar(num1,num2,flagNum1,flagNum1,&resultado)==0)
            {
                printf("Resultado: %.2f\n",resultado);
            }
            else
            {
                error1();
            }
            system("pause");
            break;
        case 4:
            printf("Resta\n-----\n");
            if(resta(num1,num2,flagNum1,flagNum1,&resultado)==0)
            {
                printf("Resultado: %.2f\n",resultado);
            }
            else
            {
                error1();
            }
            system("pause");
            break;
        case 5:
            printf("Division\n-------\n");
            codError=division(num1,num2,flagNum1,flagNum2,&resultado);
            if(codError==0)
            {
                printf("Resultado: %.2f\n",resultado);
            }
            else
            {
                if(codError==-1)
                {
                    error1();
                }
                else
                {
                    error2();
                }
            }
            system("pause");
            break;
        case 6:
            printf("Multiplicacion\n---------\n");
            if(multiplicacion(num1,num2,flagNum1,flagNum2,&resultado)==0)
            {
                printf("Resultado: %.2f\n",resultado);
            }
            else
            {
                error1();
            }
            system("pause");
            break;
        case 7:
            printf("Factorial\n---------\n");
            codError=factorial(num1,flagNum1,&resultado);
            if(codError==0)
            {
                printf("Resultado: %.2f\n",resultado);
            }
            else
            {
                if(codError=-1)
                {
                    error1();
                }
                else
                {
                    error4();
                }
            }
            system("pause");
            break;
        case 8:
            calculoTodo(num1,num2,flagNum1,flagNum1);
            system("pause");
            break;
        case 9:
            rta=-1;
            return rta;
            break;
        default:
            error3();
            system("pause");
            break;
    }

    return rta;
}

/** \brief pido por pantalla al usuario los digitos a utilizar en las operaciones y valido que sean datos numericos
 *
 * \param dato float* recibo por referencia donde tengo que guardar el dato ingresado por el usuario
 * \return int devuelvo 0 si esta ok, devuelvo -1 si ingrese un dato no numerico
 *
 */
int ingresoNum(float* dato)
{
    int rta=-1;
    char aux[6];
    do
    {
        printf("Ingrese el numero\n");
        scanf("%s",&aux);
        if(validoNumeros(aux)==0)
        {
            *dato=atof(aux);
            rta=0;
        }
        else
        {
            error3();
        }
    }while(rta!=0);

    return rta;
}

/** \brief valido que el dato ingresado sea numerico
 *
 * \param numero[] char recibo el dato a validar
 * \return int devuelvo 0 si esta ok, devuelvo -1 si no es un dato numerico
 *
 */
int validoNumeros(char numero[])
{
    int i,flagNegativo=0,flagPunto=0;
    int largo=0;
    int rta=-1;
    largo=strlen(numero);
    for(i=0;i<largo;i++)
    {
        if(numero[0]!='.')
        {
            if(numero[i]=='-')
            {
                flagNegativo++;
            }
            if(numero[i]=='-'||isdigit(numero[i])||numero[i]=='.')
            {
                if(flagNegativo < 2 || flagPunto<2)
                {
                    if(numero[i]=='.')
                    {
                        flagPunto++;
                    }
                    rta=0;
                }
                else
                {
                    rta=-1;
                }

            }
            else
            {
                rta=-1;
            }
        }
        else
        {
            rta=-1;
        }
    }

    return rta;
}

/** \brief suma dos numeros flotantes
 *
 * \param num1 float* recibo el primer operando
 * \param num2 float* recibo el segundo operando
 * \param flag1 int* bandera que me avisa si ingresa un dato en el primer operando
 * \param flag2 int* bandera que me avisa si ingresa un dato en el segundo operando
 * \param resultado float* guardo el resultado de la operacion
 * \return int devuelvo 0 si esta ok, -1 si faltan datos
 *
 */
int sumar(float* num1,float* num2,int* flag1,int* flag2,float* resultado)
{
    int rta=-1;
    if(*flag1>0&&*flag2>0)
    {
        *resultado=*num1+*num2;
        rta=0;
    }

    return rta;
}

/** \brief resta dos numeros flotantes
 *
 * \param num1 float* recibo el primer operando
 * \param num2 float* recibo el segundo operando
 * \param flag1 int* bandera que me avisa si ingresa un dato en el primer operando
 * \param flag2 int* bandera que me avisa si ingresa un dato en el segundo operando
 * \param resultado float* guardo el resultado de la operacion
 * \return int devuelvo 0 si esta ok, -1 si faltan datos
 *
 */
int resta(float* num1,float* num2,int* flag1,int* flag2,float* resultado)
{
    int rta=-1;
    if(*flag1>0&&*flag2>0)
    {
        *resultado=*num1-*num2;
        rta=0;
    }

    return rta;
}

/** \brief divide dos numeros flotantes
 *
 * \param num1 float* recibo el primer operando
 * \param num2 float* recibo el segundo operando
 * \param flag1 int* bandera que me avisa si ingresa un dato en el primer operando
 * \param flag2 int* bandera que me avisa si ingresa un dato en el segundo operando
 * \param resultado float* guardo el resultado de la operacion
 * \return int devuelvo 0 si esta ok, -1 si faltan datos, -2 si intento dividir por 0
 *
 */
int division(float* num1,float* num2,int* flag1,int* flag2,float* resultado)
{
    int rta=-1;
    if(*flag1>0&&*flag2>0)
    {
        if(*num1>0&&*num2>0)
        {
            *resultado=*num1/ *num2;
            rta=0;
        }
        else
        {
            rta=-2;
        }
    }

    return rta;
}

/** \brief multiplica dos numeros flotantes
 *
 * \param num1 float* recibo el primer operando
 * \param num2 float* recibo el segundo operando
 * \param flag1 int* bandera que me avisa si ingresa un dato en el primer operando
 * \param flag2 int* bandera que me avisa si ingresa un dato en el segundo operando
 * \param resultado float* guardo el resultado de la operacion
 * \return int devuelvo 0 si esta ok, -1 si faltan datos
 *
 */
int multiplicacion(float* num1,float* num2,int* flag1,int* flag2,float* resultado)
{
   int rta=-1;
    if(*flag1>0&&*flag2>0)
    {
        *resultado=*num1* *num2;
        rta=0;
    }

    return rta;
 }

/** \brief calculo el factorial del primer operando
 *
 * \param num1 float* recibo el primer operando
 * \param flag1 int* bandera que me avisa si ingrese el primer operando
 * \param resultado float* guardo el resultado de la operacion
 * \return int devuelvo 0 si esta ok, -1 si faltan datos, -2 si intento calcular factorial de un numero negativo
 *
 */
int factorial(float* num1,int* flag1,float *resultado)
 {
    int i,rta=-1;
    int fact=1;
    if(*flag1>0)
    {
        if(num1>=0)
        {
            rta=0;
            for(i=1;i<=(int)*num1;i++)
            {
                fact=fact*i;
            }
            *resultado=(float)fact;
        }
        else
        {
            rta=-2;
        }
    }

    return rta;
 }

 /** \brief imprimo mensaje de error por pantalla
  *
  * \return void
  *
  */
 void error1()
 {
     printf("Faltan datos para realizar la operacion,ingrese todos los operando\n");
 }


 /** \brief imprimo mensaje de error por pantalla
  *
  * \return void
  *
  */
 void error2()
 {
     printf("Error, intenta dividir por 0. Ingrese otro valor para el operando\n");
 }

 /** \brief imprimo mensaje de error por pantalla
  *
  * \return void
  *
  */
 void error3()
 {
     printf("Error, dato invalido intente nuevamente\n");
 }

 /** \brief imprimo mensaje de error por pantalla
  *
  * \return void
  *
  */
 void error4()
 {
     printf("Error, intenta calcular el factorial de un numero negativo\n");
 }


 /** \brief llama a todas las operaciones para realizar todos los calculos a la ves
  *
  * \param num1 float* recibo el primer operando
  * \param num2 float* recibo el segundo operando
  * \param flag1 int* me avisa si ingrese el primer operando
  * \param flag2 int* me avisa si ingrese el segundo operando
  * \return void
  *
  */
 void calculoTodo(float* num1,float* num2,int* flag1,int* flag2)
 {
    int codError=-1;
    float resultado;
    printf("Suma\n-----\n");
    if(sumar(num1,num2,flag1,flag1,&resultado)==0)
    {
        printf("Resultado A+B= %.2f\n\n",resultado);
    }
    else
    {
        error1();
    }
    printf("Resta\n-----\n");
    if(resta(num1,num2,flag1,flag2,&resultado)==0)
    {
        printf("Resultado A-B= %.2f\n\n",resultado);
    }
    else
    {
        error1();
    }
    printf("Division\n-------\n");
    codError=division(num1,num2,flag1,flag2,&resultado);
    if(codError==0)
    {
        printf("Resultado: %.2f\n\n",resultado);
    }
    else
    {
        if(codError==-1)
        {
            error1();
        }
        else
        {
            error2();
        }
    }
    printf("Multiplicacion\n---------\n");
    if(multiplicacion(num1,num2,flag1,flag2,&resultado)==0)
    {
        printf("Resultado: %.2f\n\n",resultado);
    }
    else
    {
        error1();
    }
    printf("Factorial\n---------\n");
    codError=factorial(num1,flag1,&resultado);
    if(codError==0)
    {
        printf("Resultado: %.2f\n\n",resultado);
    }
    else
    {
        if(codError=-1)
        {
            error1();
        }
        else
        {
            error4();
        }
    }
}
