#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "libFunciones.h"
#include "publicaciones.h"
#define QTY 20
#define QTY2 30

/** \brief funcion que da inicio al programa
 *  \param No recibe
 *  \return No devuelve ningun valor
 */
void ejecutarPrograma()
{
    char auxChar[2];
    int opcion,contClientes=0;
    eCliente clientes[QTY];
    ePublicacion publicaciones[QTY2];
    blanqueoClientes(clientes,QTY,0);
    harcodeoDatos(clientes,publicaciones,5);
    contClientes=5;
    do
    {
        if(menu(auxChar))
        {
            opcion=atoi(auxChar);
            if(opcion != 11)
            {
                operaciones(opcion,clientes,QTY,publicaciones,QTY2,&contClientes);
            }
        }
        system("cls");
    }while(opcion !=11);
}

/** \brief cargo un set de datos en la estructura para realizar pruebas
 * \param eCliente clientes[] recibo el array de la esctructura
 * \param int cantidad recibo el tamaño del array
 * \return void
 *
 */
void harcodeoDatos(eCliente clientes[],ePublicacion publicaciones[],int cantidad)
{
    int i,rubro[5]={12,40,5,10,20};
    char nombre[5][30]={"mario","ana","daira","nico","robert"};
    char apellido[5][30]={"silva","perez","zerr","rodriguez","paez"};
    char aviso[5][30]={"se busca mesera","se busca albañil","se busca vendedor","se busca auto","se busca carpintero"};
    char cuit[5][9]={"36296345","36296346","36296347","36296348","36296349",};
    for(i=0;i<cantidad;i++)
    {
        strcpy(clientes[i].nombre,nombre[i]);
        strcpy(clientes[i].apellido,apellido[i]);
        strcpy(clientes[i].cuit,cuit[i]);
        clientes[i].id=proximoId();
        clientes[i].estado=1;
        publicaciones[i].idCliente=clientes[i].id;
        publicaciones[i].numRubro=rubro[i];
        strcpy(publicaciones[i].textoAviso,aviso[i]);
        publicaciones[i].idPublicacion=proximoId();
        publicaciones[i].estado=0;
        printf("\nAlta de usuario realizada. Numero de : %d",clientes[i].id);
        printf("\nAlta de publicacion. Numero de : %d",publicaciones[i].idPublicacion);
    }
}

/** \brief Presenta al usuario un menu de opciones para que elija la acción a realizar.
 *  \param char* recibe por referencia donde debe guardar el valor ingresado por el usuasrio
 *  \return devuelvo 0 si el valor ingresado no es un numero o 1 si es un valor numerico
 */
int menu(char* auxiliar)
{
    int retorno=-1;
    printf("1- Alta cliente\n2- Modificar datos del cliente\n3- Baja cliente\n4- Publicar\n");
    printf("5- Pausar publicacion\n5- Reanudar publicacion\n7- Imprimir clientes\n8- Imprimir publicaciones\N9- Informar clientes\n10- Informar publicaciones\n11- Salir\nOpcion:");
    scanf("%s",auxiliar);
    if(validoInt(auxiliar))
    {
        retorno=1;
    }

    return retorno;
}

/** \brief esta funcion recibe la opcion elegida por el usuario y llama a las operaciones
 *
 * \param int opcion recibo la opcion seleccionada por el usuario
 * \param eCliente clientes[] recibo el array de la estructura eCliente
 * \param int cantidad recibo el tamaño del array clientes
 * \param int* contClientes este flag me indica si ya di de alta un usuario
 * \param int* contMenores contador de las clientes menores de 18 años
 * \param int* cont1835 contador de las clientes de 18 a 35 años
 * \param int* contMas35 contador de las clientes mayores de 35 años
 * \return int devuelvo un 0
 *
 */
int operaciones(int opcion,eCliente clientes[], int cantidad,ePublicacion publicaciones[],int cantPubli,int* contClientes)
{
    int posicion;
    switch(opcion)
    {
        case 1:
            if(buscarLugar(clientes,cantidad,&posicion))
            {
                if(altaCliente(posicion,clientes,*contClientes))
                {
                    *contClientes=*contClientes+1;
                }
            }
            else
            {
                mostrarMensaje("\nNo hay mas lugar para un nuevo usuario.");
            }
            system("\npause");
            break;
        case 2:
            if(*contClientes > 0)
            {
                modificarCliente(clientes,*contClientes);
            }
            system("\npause");
            break;

        case 3:
            if(*contClientes > 0)
            {
                if(bajaCliente(clientes,publicaciones))
                {
                    *contClientes=*contClientes-1;
                    //compactar(clientes,cantidad);
                }
            }
            else
            {
                mostrarMensaje("\nNo hay usuarios ingresados.");
            }
            system("\npause");
            break;/*
        case 4:
            if(*contClientes > 0)
            {
                graficoEdades(*contMenores,*cont1835,*contMas35);
            }
            else
            {
                mostrarMensaje("\nNo hay usuarios ingresados.");
            }
            system("\npause");
            break;
        case 5:
            if(*contClientes > 0)
            {
                modificarUsuario(clientes,*contClientes);
            }
            system("\npause");
            break;*/
        default:
            printf("opcion invalida");
            system("\npause");
            break;
    }

    return 0;
}

int proximoId()
{
    static int proximoId = -1;
    proximoId++;
    return proximoId;
}

/**\brief Muestra un mensaje
 * \param no recibe
 * \return void
 */
void mostrarMensaje(char* mensaje)
{
    printf(mensaje);
}

/** \brief Pide al usuario que ingrese un dato numerico que se encuentre dentre dentro del rango especificado
 *
 * \param char* mensaje recibo el mensaje que debo mostrarle al usuario
 * \param char* mensajeError recibo el mensaje de error a mostrar su el dato ingresado no es correcto
 * \param char dato[] variable donde guardo el dato ingresao
 * \param int intentos la cantidad de intentos que tiene el usuario para ingresar el dato
 * \param int minimo recibo es el valor minimo que puede ingresar el usuario
 * \param int maximo recibo el valor maximo que puede ingresar el usuario
 * \return int devuelvo 1 si el valor ingresado es correcto y esta dentro del maximo y minimo, devuelvo 0 si no lo esta
 *
 */
int getInt(char* mensaje,char* mensajeError,char dato[],int intentos,int minimo,int maximo)
{
    int i,retorno=0;
    i=intentos;
    do
    {
        i--;
        printf(mensaje);
        fflush(stdin);
        scanf("%s",dato);
        if(validoInt(dato))
        {
            if(atoi(dato)>minimo && atoi(dato)<maximo)
            {
                retorno=1;
            }
            else
            {
                mostrarMensaje("Fuera de rango,intente de nuevo");
            }
        }
        else
        {
            printf(mensajeError);
            system("pause");
        }
    }while(i>0 && retorno ==0);

    return retorno;
}

/** \brief Pide al usuario que ingrese un dato alfanumerico
 *
 * \param char* mensaje recibo el mensaje que debo mostrarle al usuario
 * \param char* mensajeError recibo el mensaje de error a mostrar su el dato ingresado no es correcto
 * \param char dato[] variable donde guardo el dato ingresao
 * \param int minimo recibo la longitud minima que puede tener el dato ingresado
 * \param int minimo recibo la longitud maxima que puede tener el dato ingresado
 * \param int maximo la cantidad de intentos que tiene el usuario para ingresar el dato
 * \return int devuelvo 1 si el valor es correcto y su longitud esta dentro del maximo y minimo, devuelvo 0 si no lo esta
 */
int getString(char* mensaje,char* mensajeError,char dato[],int intentos, int minimo, int maximo)
{
    int i,retorno=0;
    i=intentos;
    do
    {
        i--;
        printf(mensaje);
        fflush(stdin);
        gets(dato);
        if(validoString(dato) && strlen(dato)> minimo && strlen(dato)< maximo)
        {
            retorno=1;
        }
        else
        {
            printf(mensajeError);
            system("pause");
        }
    }while(i>0 && retorno ==0);

    return retorno;
}

/**\brief Valido que el dato contenga solo letras
 * \param char dato[] contiene el dato a validar
 * \return devuelvo 1 si el dato solo contiene letras, si no 0
 */
int validoString(char dato[])
{
    int i,retorno=0;
    for(i=0;i<strlen(dato);i++)
    {
        if(dato[0] != ' ')
        {
            if(isalpha(dato[i]) || dato[i]==' ')
            {

                retorno=1;
             }
             else
             {
                retorno=0;
                continue;
             }
        }
        else
        {
            retorno=0;
            return retorno;
        }
    }

    return retorno;
}

/**\brief Valido que el dato contenga solo numeros
 * \param char dato[] contiene el dato a validar
 * \return devuelvo 1 si el dato solo contiene numeros, si no 0
 */
int validoInt(char dato[])
{
    int i,retorno=0;
    for(i=0;i<strlen(dato);i++)
    {
        if(isdigit(dato[i]))
        {
            retorno=1;
        }
        else
        {
            retorno=0;
            return retorno;
        }
    }

    return retorno;
}

