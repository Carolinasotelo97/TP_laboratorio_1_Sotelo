/*
 * parser.c
 *
 *  Created on: 24 jun. 2021
 *      Author: caroo
 */


#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include "estudiante.h"

int parserStudentFromTxt(FILE*pFile,LinkedList* pArray)
{
    int retorno=-1;
    int cant;
    char buffer[4][128];
    Student* newStudent=NULL;

    if(pFile!=NULL&&pArray!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3]);//leo el encabezado
        while(!feof(pFile))
        {
            cant=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3]);
            if(cant==4)
            {
                newStudent=student_newParams(atoi(buffer[0]),buffer[1],buffer[2][0],atof(buffer[3]));
                if(newStudent!=NULL)
                {
                    ll_add(pArray,newStudent);
                    retorno=0;
                }
            }else
            {
                break;
            }
        }

    }

    return retorno;
}
