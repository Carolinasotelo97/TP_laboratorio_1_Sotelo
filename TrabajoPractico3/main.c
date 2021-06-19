/*
 ============================================================================
 Name        : TrabajoPractico3.c
 Author      : Sotelo Carolina
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "validaciones.h"
#include "menu.h"
/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/
int main()
{
    /*ACORDARME DE BORRAR LO DE PROXID CUANDO LO ENTREGUE*/
    int option=0;
    int flagTxt=0;
    int flagBin=0;
    int flagAdd=0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
        option=menu();
        switch(option)
        {
            case 1:
                if(flagBin||flagTxt)//si ya se cargaron desde un archivo
                {
                    printf("\nLos empleados ya fueron cargados\n\n");
                }else
                {
                    if(!controller_loadFromText("data.csv",listaEmpleados))
                    {
                        printf("\nEmpleados cargados exitosamente!\n\n");
                        flagTxt=1;
                    }else
                    {
                        printf("\nProblemas para cargar los empleados\n\n");
                    }
                }
                break;
            case 2:
                if(flagTxt||flagBin)//si ya se cargaron desde un archivo
                {
                    printf("\nLos empleados ya fueron cargados\n\n");
                }else
                {
                    if(!controller_loadFromBinary("data.bin",listaEmpleados))
                    {
                        printf("\nEmpleados cargados exitosamente!\n\n");
                        flagBin=1;
                    }else
                    {
                        printf("\nProblemas para cargar los empleados\n\n");
                    }
                }
                break;
            case 3:
                if(!controller_addEmployee(listaEmpleados))
                {
                    printf("\nAlta exitosa!!!\n\n");
                    flagAdd=1;
                }else
                {
                    printf("\nProblemas para dar de alta\n\n");
                }
                break;
            case 4:
                if(flagAdd||flagBin||flagTxt)
                {
                    switch(controller_editEmployee(listaEmpleados))
                    {
                    case -1:
                        printf("\nProblemas para modificar\n\n");//algun parametro es null o el id no existe
                        break;
                    case 0:
                        printf("\nModificacion exitosa!\n\n");
                        break;
                    case 1:
                        printf("\nOperacion cancelada\n\n");
                        break;
                    }
                }else
                {
                    printf("\nPrimero debe cargar un empleado\n\n");
                }
                break;
            case 5:
                if(flagAdd||flagBin||flagTxt)
                {
                    switch(controller_removeEmployee(listaEmpleados))
                    {
                    case -1:
                        printf("\nProblemas para dar de baja\n\n");//algun parametro es null o el id no existe
                        break;
                    case 0:
                        printf("\nBaja exitosa!\n\n");
                        break;
                    case 1:
                        printf("\nOperacion cancelada\n\n");
                        break;
                    }
                }else
                {
                    printf("\nPrimero debe cargar un empleado\n\n");
                }
                break;
            case 6:
                if(flagAdd||flagBin||flagTxt)
                {
                    controller_ListEmployee(listaEmpleados);
                }else
                {
                    printf("\nPrimero debe cargar un empleado\n\n");
                }
                break;
            case 7:
                if(flagAdd||flagBin||flagTxt)
                {
                    if(!controller_sortEmployee(listaEmpleados))
                    {
                        printf("\nEmpleados ordenados!\n\n");
                    }else
                    {
                        printf("\nProblemas para ordenar a los empleados\n\n");
                    }
                }else
                {
                    printf("\nPrimero debe cargar un empleado\n\n");
                }
                break;
            case 8:
                if(flagAdd||flagBin||flagTxt)
                {
                    if(!controller_saveAsText("data.csv",listaEmpleados))
                    {
                        printf("\nEmpleados guardados exitosamente\n\n");
                    }else
                    {
                        printf("\nProblemas para guardar a los empleados\n\n");
                    }
                }else
                {
                    printf("\nNo hay empleados para cargar\n\n");
                }
                break;
            case 9:
                if(!controller_saveAsBinary("data.bin",listaEmpleados))
                {
                    printf("\nEmpleados guardados exitosamente\n\n");
                }else
                {
                    printf("\nNo se pudieron cagar los empleados\n\n");
                }
                break;
            case 10:
                break;//porque es la opcion para salir
            default:
                printf("\nOpcion no valida\n\n");
                break;
        }
        system("pause");//pauso la pantalla
    }while(option != 10);
    ll_deleteLinkedList(listaEmpleados);
    return 0;
}
