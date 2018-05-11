#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "libFunciones.h"
#include "publicaciones.h"
void blanqueoPubli(ePublicacion publicaciones[],int cantidad,int dato)
{
    int i;
    for(i=0;i<cantidad; i++)
    {
        publicaciones[i].estado= dato;
    }
}

int buscarPublicaciones(ePublicacion publicaciones[],char id[])
{
    int retorno=0,i=0;
    for(i=0;publicaciones[i].estado==1;i++)
    {
        if(publicaciones[i].idCliente==atoi(id))
        {
           printf("\nPublicaciones del cliente:\nRubro: %d     Mensaje: %s",publicaciones[i].numRubro,publicaciones[i].textoAviso);
           publicaciones[i].estado=0;
           retorno=1;
        }
    }

    return retorno;
}
