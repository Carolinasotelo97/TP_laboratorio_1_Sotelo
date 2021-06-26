/*
 * menu.c
 *
 *  Created on: 26 jun. 2021
 *      Author: caroo
 */

#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"
#include "controller.h"
#include "menu.h"

#include "estudiante.h"

int main()
{
    LinkedList* estudiantes=ll_newLinkedList();
    char confirma='n';
    int rta;
    int flag=0;//se levanta si se cargaron empleados desde el archivo

    do
    {
        switch(menu())
        {
        case 1:
            if(!flag)
            {
                if(!controller_chargeTxt(estudiantes,"estudiantes.csv"))
                {
                    printf("\nEmpleados cargados exitosamente!\n\n");
                    flag=1;
                }else
                {
                    printf("\nProblemas para cargar a los estudiantes\n\n");
                }
            }else
            {
                printf("\nLos empleados ya fueron cargados\n\n");
            }
            break;
        case 2:
            if(!controller_addStudent(estudiantes))
            {
                printf("\n\nAlta exitosa\n\n");
            }else
            {
                printf("\n\nProblemas para dar de alta\n\n");
            }
            break;
        case 3:
            if(!ll_isEmpty(estudiantes))
            {
                if(!controller_edit(estudiantes))
                {
                    printf("\nModificacion exitosa\n\n");
                }else
                {
                    printf("\nProblemas para modificar\n\n");
                }
            }else
            {
                printf("\nPrimero debe cargar algun estudiante\n\n");
            }
            break;
        case 4:
            if(!ll_isEmpty(estudiantes))
            {
                if(controller_remove(estudiantes))
                {
                    printf("\nProblemas para dar de baja\n\n");
                }
            }else
            {
                printf("\nPrimero debe cargar algun estudiante\n\n");
            }
            break;
        case 5:
            if(!ll_isEmpty(estudiantes))
            {
                if(!controller_sortStudents(estudiantes))
                {
                    printf("\nOrdenamiento exitoso!\n\n");
                }else
                {
                    printf("\nProblemas para dar de ordenar\n\n");
                }
            }else
            {
                printf("\nPrimero debe cargar algun estudiante\n\n");
            }
            break;
        case 6:
            if(!ll_isEmpty(estudiantes))
            {
                system("cls");
                controller_listStudents(estudiantes);
            }else
            {
                printf("\nNo hay estudiantes para listar aun\n\n");
            }
            break;
        case 7:
            if(!controller_insertStudent(estudiantes))
            {
                printf("\nEstudiante agregado exitosamente!\n\n");
            }else
            {
                printf("\nProblemas para agregar estudiante\nChequee que el indice indicado sea valido\n\n");
            }
            break;
        case 8:
            if(!ll_isEmpty(estudiantes))
            {
                rta=controller_clearList(estudiantes);
                if(rta==-1)
                {
                    printf("Problemas para cargar la lista\n\n");
                }else if(!rta)
                {
                    printf("La lista ya esta vacia\n\n");
                }else
                {
                    printf("Operacion cancelada\n\n");
                }
            }else
            {
                printf("\nPrimero debe cargar algun estudiante\n\n");
            }
            break;
        case 9://ANDA MASO TESTEAR MAS
            if(!ll_isEmpty(estudiantes))
            {
                if(!controller_backupFile(estudiantes,"estudiantesSeguridad.csv"))
                {
                    printf("\nArchivo de seguridad creado exitosamente\n\n");
                }else
                {
                    printf("\nNo se pudo crear el archivo\n\n");
                }
            }else
            {
                printf("\nNo hay estudiantes para listar aun\n\n");
            }
        break;
        case 10:
            if(!ll_isEmpty(estudiantes))
            {
                printf("\nPrimero cargue algun estudiante\n\n");
            }else
            {
                if(!controller_saveAsTxt(estudiantes,"estudiantes.csv"))
                {
                    printf("\nEstudiantes guardados exitosamente!\n\n");
                }else
                {
                    printf("\nProblemas al guardar estudiantes\n\n");
                }
            }
            break;
        default:
            printf("\nOpcion no valida\n\n");
            break;
        }

        system("pause");

    }while(confirma!='s');

    ll_deleteLinkedList(estudiantes);//borro la lista cuando termina el programa

    return 0;
}













