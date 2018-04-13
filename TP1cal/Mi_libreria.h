#ifndef MI_LIBRERIA_H_INCLUDED
#define MI_LIBRERIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

int sumar(float*,float*,int*,int*,float*);
int resta(float*,float*,int*,int*,float*);
int division(float*,float*,int*,int*,float*);
int multiplicacion(float*,float*,int*,int*,float*);
int factorial(float*,int*,float*);
void error1();
void error2();
void error3();
void error4();
int menu(char*,int,int,float,float);
int validoNumeros(char[]);
int operaciones(int,float*,float*,int*,int*);
int ingresoNum(float*);
void calculoTodo(float*,float*,int*,int*);



#endif // MI_LIBRERIA_H_INCLUDED
