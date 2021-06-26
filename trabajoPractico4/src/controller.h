/*
 * controller.h
 *
 *  Created on: 24 jun. 2021
 *      Author: caroo
 */
#include "LinkedList.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_



#endif /* CONTROLLER_H_ */

int controller_chargeTxt(LinkedList*pArray,char*path);
int controller_addStudent(LinkedList*pArray);
int controller_edit(LinkedList*pArray);
int controller_remove(LinkedList*pArray);
int controller_sortStudents(LinkedList*pArray);
int controller_listStudents(LinkedList* pArray);
int controller_insertStudent(LinkedList*pArray);
int controller_clearList(LinkedList*pArray);
int controller_backupFile(LinkedList*pArray,char*path);
int controller_saveAsTxt(LinkedList*pArray,char*path);
