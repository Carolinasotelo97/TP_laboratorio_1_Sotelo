/*
 * estudiante.c
 *
 *  Created on: 26 jun. 2021
 *      Author: caroo
 */


#include "estudiante.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student* student_new()
{
    return (Student*) malloc(sizeof(Student));
}

Student* student_newParams(int id,char*nombre,char sexo,float promedio)
{
    Student* newStudent=student_new();

    if(newStudent)
    {
        if(student_setId(newStudent,id)==-1
           ||student_setNombre(newStudent,nombre)==-1
           ||student_setSexo(newStudent,sexo)==-1
           ||student_setPromedio(newStudent,promedio)==-1)//si laguno de los parametros falla
        {
            student_delete(newStudent);
        }
    }

    return newStudent;
}

void student_delete(Student* this)
{
    if(this!=NULL)
    {
        free(this);
        this=NULL;
    }
}

int student_setId(Student* this,int id)
{
    int retorno=-1;

    if(this!=NULL&&id>=0)
    {
        this->id=id;
        retorno=0;
    }

    return retorno;
}

int student_getId(Student* this,int* id)
{
    int retorno=-1;

    if(this!=NULL&&id!=NULL)
    {
        *id=this->id;
        retorno=0;
    }

    return retorno;
}

int student_setNombre(Student* this,char* nombre)
{
    int retorno=-1;

    if(this!=NULL&&nombre!=NULL)
    {
        strcpy(this->nombre,nombre);
        retorno=0;
    }

    return retorno;
}

int student_getNombre(Student* this,char* nombre)
{
    int retorno=-1;

    if(this!=NULL&&nombre!=NULL)//no existen nombres de 2 letras
    {
        strcpy(nombre,this->nombre);
        retorno=0;
    }

    return retorno;
}

int student_setSexo(Student* this,char sexo)
{
    int retorno=-1;

    if(this!=NULL&&(sexo=='m'||sexo=='M'||sexo=='f'||sexo=='F'))
    {
        this->sexo=sexo;
        retorno=0;
    }

    return retorno;
}

int student_getSexo(Student* this,char* sexo)
{
    int retorno=-1;

    if(this!=NULL&&sexo!=NULL)
    {
        *sexo=this->sexo;
        retorno=0;
    }

    return retorno;
}

int student_setPromedio(Student* this,float promedio)
{
    int retorno=-1;

    if(this!=NULL&&promedio>=0&&promedio<=10)//el promedio puede ir de 0 a 10
    {
        this->promedio=promedio;
        retorno=0;
    }

    return retorno;
}

int student_getPromedio(Student* this,float* promedio)
{
    int retorno=-1;

    if(this!=NULL&&promedio!=NULL)
    {
        *promedio=this->promedio;
        retorno=0;
    }

    return retorno;
}

void printStudent(Student* this)
{
    int auxId;
    char auxNombre[25];
    char auxSexo;
    float auxPromedio;

    if(this)
    {
        if(!student_getId(this,&auxId)&&
           !student_getNombre(this,auxNombre)&&
           !student_getSexo(this,&auxSexo)&&
           !student_getPromedio(this,&auxPromedio))
        {
            printf(" %-3d %10s %c %.2f\n",auxId,auxNombre,auxSexo,auxPromedio);
        }
    }
}

int findStudentById(LinkedList* pArray,int id)
{
    int retorno=-1;
    int len;
    int auxId;
    Student* auxStudent;

    if(pArray!=NULL&&id>=0)
    {
        len=ll_len(pArray);


        for(int i=0;i<len;i++)
        {
            auxStudent=ll_get(pArray,i);
            student_getId(auxStudent,&auxId);
            if(auxId==id)
            {
                retorno=i;
                break;
            }

        }
    }

    return retorno;
}

int compararPorId(void* s1,void* s2)
{
    int retorno;
    Student* a=(Student*) s1;//lo casteo poruqe era puntero a void
    Student* b=(Student*) s2;
    int auxIdA;
    int auxIdB;

    student_getId(a,&auxIdA);
    student_getId(b,&auxIdB);

    if(auxIdA>auxIdB)
    {
        retorno=1;
    }else if(auxIdA==auxIdB)
    {
        retorno=0;
    }else
    {
        retorno=-1;
    }
    //auxIdA-auxIdB

    return retorno;
}

int compararPorNombre(void* s1,void* s2)
{
    int retorno;
    Student* a=(Student*) s1;//lo casteo porque era puntero a void
    Student* b=(Student*) s2;
    char bufferA[128];
    char bufferB[128];

    student_getNombre(a,bufferA);
    student_getNombre(b,bufferB);

    retorno=stricmp(bufferA,bufferB);

    return retorno;
}

int compararPorSexo(void* s1,void* s2)
{
    int retorno;
    Student* a=(Student*) s1;//lo casteo poruqe era puntero a void
    Student* b=(Student*) s2;
    char auxSexoA;
    char auxSexoB;

    student_getSexo(a,&auxSexoA);
    student_getSexo(b,&auxSexoB);

    if(auxSexoA>auxSexoB)
    {
        retorno=1;
    }else if(auxSexoA==auxSexoB)
    {
        retorno=0;
    }else
    {
        retorno=-1;
    }

    return retorno;
}

int compararPorPromedio(void* s1,void* s2)
{
    int retorno;
    Student* a=(Student*) s1;//lo casteo poruqe era puntero a void
    Student* b=(Student*) s2;
    float auxPromedioA;
    float auxPromedioB;

    student_getPromedio(a,&auxPromedioA);
    student_getPromedio(b,&auxPromedioB);

    if(auxPromedioA>auxPromedioB)
    {
        retorno=1;
    }else if(auxPromedioA==auxPromedioB)
    {
        retorno=0;
    }else
    {
        retorno=-1;
    }

    return retorno;
}
