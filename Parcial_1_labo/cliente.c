#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "libFunciones.h"
#include "publicaciones.h"

/**\brief Inicializa un array con el valor recibo
 * \param eCliente clientes Es el array a ser inicializado
 * \param int cantad Indica la longitud del array
 * \param int dato Es el valor que sera cargado en el campo estado
 * \return vo
 */
void blanqueoClientes(eCliente clientes[],int cantad,int dato)
{
    int i;
    for(i=0;i<cantad; i++)
    {
        clientes[i].estado= dato;
    }
}

/**\brief Solicita los datos al usuario para realizar el alta
 * \param eCliente clientes Es el array donde guardo los datos del usuario
 * \param int posicion recibo la posicion del array donde voy a guardar los datos del alta
 * \param int cantad Indica la longitud del array
 * \return si el alta se realiza devuelvo 1, si no se realizo devuelvo 0
 */
int altaCliente(int posicion,eCliente clientes[],int cantad)
{
    int retorno=0;
    char cuitAux[50],stringAux[30];
    system("cls");
    printf("\nALTA DE CLIENTE\n---------------");
    if(getString("\nIngrese su nombre: ","\nError, ingrese solo letras",stringAux,2,3,21))
    {
        strcpy(clientes[posicion].nombre,stringAux);
        if(getString("\nIngrese su apello: ","\nError, ingrese solo letras",stringAux,2,3,21))
        {
            strcpy(clientes[posicion].apellido,stringAux);
            if(getInt("Ingrese su CUIT: ","Error, ingrese solo numeros",cuitAux,2,1000,100000000))
            {
                    strcpy(clientes[posicion].cuit,cuitAux);
                    clientes[posicion].estado=1;
                    clientes[posicion].id=proximoId();
                    printf("\nAlta de usuario realizada. Numero de : %d",clientes[posicion].id);
                    retorno=1;
            }
            else
            {
                mostrarMensaje("Error, el DNI ingresado ya fue dado de alta");
            }
        }
        else
        {
            mostrarMensaje("\nError, no ingreso un dato valo");
        }
    }
    else
    {
        mostrarMensaje("\nError, no ingreso un dato valo");;
    }

    return retorno;
}


/**\brief Realizo la baja logica de una persona
 * \param eCliente clientes Es el array en el cual realizo la baja
 * \return si baja se realizo devuelvo 1, si no se realizo devuelvo 0
 */
int bajaCliente(eCliente clientes[],ePublicacion publicaciones[])
{
    char auxID[5],opcion[3],ok[3]={"si"};
    int retorno=0,posicion;

    system("cls");
    printf("BAJA DE CLIENTE\n---------------\n");
    if(getInt("Ingrese el ID del usuario a dar de baja: ","Error, ingrese solo numeros",auxID,2,0,40000))
    {
        if(buscarID(clientes,auxID,&posicion))
        {
            if(buscarPublicaciones(publicaciones,auxID)==0)
            {
                mostrarMensaje("\nEl cliente no tenia publiaciones");
            }

            if(getString("\nConfirma la baja del usuario? SI / NO: ","\nError, ingrese solo letras",opcion,2,1,3))
            {
                if(strcmp(opcion,ok)==0)
                {
                    clientes[posicion].estado=0;
                }
                else
                {
                    printf("\nOperacion cancelada");
                }
            }
        }
        else
        {
            mostrarMensaje("\nEl ID ingresado, no existe");
        }

    }
    else
    {
        mostrarMensaje("\ndato ingresado invalido, no tiene mas intentos");
    }


    return retorno;
}


/**\brief listarclientes la lista de clientes, ordenadas por nombre alfabeticamente
 * \param eCliente clientes Es el array donde tengo los datos de las clientes
 * \param int cantad recibo la cantad de usuarios dados de alta dentro del programa
 * \return vo
 */
void listarclientes(eCliente clientes[],int cantidad)
{
    int i,j;
    eCliente auxChar;
    system("cls");
    mostrarMensaje("Lista de clientes\n----------------\n");
    for (i = 1; i < cantidad; i++)
    {
        auxChar=clientes[i];
        j = i-1;
        while (j >= 0 && strcmp(clientes[j].nombre,auxChar.nombre)==1)
        {
            clientes[j+1]=clientes[j];
            j--;
        }
        clientes[j+1]=auxChar;
    }
    for(i=0;i<cantidad;i++)
    {
        printf("NOMBRE: %s   DNI: %s    EDAD: %d\n",clientes[i].nombre,clientes[i].cuit,clientes[i].id);
    }
}

/**\brief Obtengo el primer indice del array disponible
 * \param ePeronas clientes Es el array donde realizo la busqueda
 * \param int cantad Indica la logitud del array
 * \return si encontro un lugar disponible devuelve 1, si no encontro nigun ligar devuelve 0
 */
int buscarLugar(eCliente clientes[],int cantad,int* posicion)
{
    int i=0,retorno=0;
    for(i=0;i<cantad;i++)
    {
        if(clientes[i].estado==0)
        {
            *posicion=i;
            retorno=1;
            return retorno;
        }
    }

    return retorno;
}

int modificarCliente(eCliente clientes[],int cantidad)
{
    int i,posicion,retorno=0,rta;
    char nombreAux[20],apelloAux[20],auxId[5],auxCuit[50],opcion[3],ok[3]={"si"};
    if(getInt("Ingrese el ID a modificar: ","Error, ingrese solo numeros",auxId,2,0,100000))
    {

        if(buscarID(clientes,auxId,&posicion))
        {
            if(getString("\nIngrese el nuevo nombre del usuario: ","\nError, ingrese solo letras",nombreAux,2,2,21))
            {
                if(getString("\nIngrese el nuevo apello del cliente: ","\nError, ingrese solo letras",apelloAux,2,2,21))
                {
                    if(getInt("Ingrese el nuevo cuit: ","Error, ingrese solo numeros",auxCuit,2,0,100000000))
                    {
                        if(getString("\nConfirma la modificacion del usuario? SI / NO: ","\nError, ingrese solo letras",opcion,2,1,3))
                        {
                            if(strcmp(opcion,ok)==0)
                            {
                                strcpy(clientes[posicion].nombre,nombreAux);
                                strcpy(clientes[posicion].apellido,apelloAux);
                                strcpy(clientes[posicion].cuit,auxCuit);
                                mostrarMensaje("\nModificacion exitosa");
                                retorno=1;
                            }
                            else
                            {
                                printf("\nOperacion cancelada");
                            }
                        }
                        else
                        {
                            mostrarMensaje("\nError, supero la cantad de intentos");
                        }
                    }
                    else
                    {
                        mostrarMensaje("\nError, supero la cantad de intentos");
                    }
                }
                else
                {
                    mostrarMensaje("\nEl  ingresado, no existe");
                }
            }
            else
            {
                mostrarMensaje("\nError, supero la cantad de intentos");
            }
        }
        else
        {
            mostrarMensaje("\nError, supero la cantad de intentos");
        }
    }
    else
    {
        mostrarMensaje("\nError, supero la cantad de intentos");
    }

    return retorno;
}

/**\brief Busco un dni dentro de la estructura  eCliente
 * \param eCliente clientes Es el array sobre el cual realizo la busqueda
 * \param char dni contiene el dato a ser buscado dentro del array
  * \param int* posicion  si encuentro el dato que busco, guardo el indice del array dentro de esta variable
 * \return si encontro el dni devuelvo un 1, si no devuelvo 0
 */
int buscarID(eCliente clientes[],char id[],int *posicion)
{
     int retorno=0,i=0;
     for(i=0;clientes[i].estado==1;i++)
     {
         if(clientes[i].id==atoi(id))
         {
             *posicion=i;
             retorno=1;
             return retorno;
         }
     }

     return retorno;
}
