/*
 * estudiante.h
 *
 *  Created on: 26 jun. 2021
 *      Author: caroo
 */
#include "LinkedList.h"

#ifndef ESTUDIANTE_H_
#define ESTUDIANTE_H_


typedef struct
{
    int id;
    char nombre[25];
    char sexo;
    float promedio;
}Student;

#endif /* ESTUDIANTE_H_ */

Student* student_new();
Student* student_newParams(int id,char*nombre,char sexo,float promedio);
void student_delete(Student* this);
int student_setId(Student* this,int id);
int student_getId(Student* this,int* id);
int student_setNombre(Student* this,char* nombre);
int student_getNombre(Student* this,char* nombre);
int student_setSexo(Student* this,char sexo);
int student_getSexo(Student* this,char* sexo);
int student_setPromedio(Student* this,float promedio);
int student_getPromedio(Student* this,float* promedio);
void printStudent(Student* this);
int findStudentById(LinkedList*pArray,int id);
////////////////////////////////////////////////////////
int compararPorId(void* s1,void* s2);
int compararPorNombre(void* s1,void* s2);
int compararPorSexo(void* s1,void* s2);
int compararPorPromedio(void* s1,void* s2);
