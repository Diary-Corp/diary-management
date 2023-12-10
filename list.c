//
// Created by march on 10/24/2023.
//

#include "list.h"
#include "cell.h"
#include "stdlib.h"
#include "stdio.h"

t_d_list *createList(int max_levels){
    /*
     * Create an empty list with the given parameter.
     */
    t_d_list *myList = (t_d_list*)malloc(sizeof(t_d_list));

    myList->max_levels = max_levels;
    myList->heads = (t_d_cell**)malloc(sizeof (t_d_cell*) * max_levels);

    for(int i=0; i<max_levels; i++){
        myList->heads[i] = NULL;
    }

    return myList;
}

void insertCell(t_d_list *myList, t_d_cell *myCell){
    /*
     * Insert a new cell inside the given list in all the levels wanted.
     */
    for (int i=0; i<myCell->nb_levels; i++){
        t_d_cell *tempCell = myList->heads[i];
        myList->heads[i] = myCell;
        myCell->next[i] = tempCell;
    }
}

void displayLevel(t_d_list *myList, int level){
    /*
     * Display one specific level of the list.
     */
    t_d_cell *tempCell = myList->heads[level];
    printf("[list head_%d @- ]-->", level);
    while (tempCell != NULL) {
        printf("[ %d|@- ]-->", tempCell->value);
        tempCell = tempCell->next[level];
    }
    printf("NULL\n");
}

void displayAllLevels(t_d_list *myList){
    /*
     * Display all levels of the list.
     */
    for (int i=0; i<myList->max_levels; i++) {
        displayLevel(myList, i);
    }
}

void insertSorted(t_d_list *myList, t_d_cell *myCell) {
    /*
     * Insert a new element inside the list in a sorted ascendant order.
     */
    for (int i = 0; i < myCell->nb_levels; i++) {
        t_d_cell *current = myList->heads[i];
        t_d_cell *prev = NULL;
        while (current != NULL && current->value < myCell->value) {
            prev = current;
            current = current->next[i];
        }
        if (prev == NULL) {
            myList->heads[i] = myCell;
        } else {
            prev->next[i] = myCell;
        }
        myCell->next[i] = current;
    }
}

void insertCells(t_d_list *myList, int nb_elements){
    /*
     * Insert nb_elements cells inside the list in the first level.
     */
    for(int i=1; i<nb_elements; i++){
        t_d_cell *myCell= createCell(i, 1);
        insertSorted(myList, myCell);
    }
}


void insertLevelCells(t_d_list *myList, int nb_elements){
    /*
     * Insert nb_elements cells inside the list with the corresponding levels.
     */
    for(int i=1; i<nb_elements; i++){
        if (i%16==0) {
            t_d_cell *myCell16 = createCell(i, 5);
            insertSorted(myList, myCell16);
        } else if (i%8==0) {
            t_d_cell *myCell8 = createCell(i, 4);
            insertSorted(myList, myCell8);
        } else if (i%4==0) {
            t_d_cell *myCell4 = createCell(i, 3);
            insertSorted(myList, myCell4);
        } else if (i%2==0) {
            t_d_cell *myCell2 = createCell(i, 2);
            insertSorted(myList, myCell2);
        } else {
            t_d_cell *myCell= createCell(i, 1);
            insertSorted(myList, myCell);
        }
    }
}

int searchValueBis(t_d_list *myList, int value){
    /*
     * Same as searchValue but with the prints
     */
    int nbOpe=0;
    if (myList->heads == NULL){
        return 0;
    }

    t_d_cell *current = myList->heads[0];
    while (current != NULL){
        if (current->value == value){
            printf("Number of values compared : %d\n", nbOpe);
            return 1;
        }
        nbOpe++;
        current = *current->next;
    }
    printf("Number of values compared : %d\n", nbOpe);
    return 0;
}


int searchLevelValueBis(t_d_list *myList, int value) {
    /*
     * Same as searchLevelValue but with the prints
     */
    int nbOpe=0;

    if (myList->heads[0] == NULL) {
        return 0;
    }

    int startLevel = myList->max_levels - 1;
    while (startLevel > 0 && myList->heads[startLevel] == NULL) {
        startLevel--;
    }

    t_d_cell *current = myList->heads[startLevel];

    for (int i = startLevel; i >= 0; i--) {
        while (current->next[i] != NULL && current->next[i]->value < value) {
            current = current->next[i];
            nbOpe++;
        }

        if (current->next[i] != NULL && current->next[i]->value == value) {
            printf("Number of values compared: %d\n", nbOpe);
            return 1;
        }
    }

    printf("Number of values compared using levels: %d\n", nbOpe);
    return 0;
}

int searchValue(t_d_list *myList, int value){
    /*
     * Search for a specific value inside the list without using dichotomic search.
     */
    if (myList->heads == NULL){
        return 0;
    }

    t_d_cell *current = myList->heads[0];
    while (current != NULL){
        if (current->value == value){
            return 1;
        }
        current = *current->next;
    }

    return 0;
}


int searchLevelValue(t_d_list *myList, int value) {
    /*
     * Search for a value inside using dichotomic search (using levels).
     */
    if (myList->heads[0] == NULL) {
        return 0;
    }

    t_d_cell *current = myList->heads[myList->max_levels - 1];

    for (int i = myList->max_levels - 1; i >= 0; i--) {

        while (current->next[i] != NULL && current->next[i]->value < value) {
            current = current->next[i];
        }

        if (current->next[i] != NULL && current->next[i]->value == value) {
            return 1;
        }
    }

    return 0;
}

int getSizeOfInt(int n){
    /*
     * Get the size of an integer.
     */
    int digits=0;
    while (n!=0){
        n=n/10;
        digits++;
    }
    return digits;
}

void displayAllLevelsAligned(t_d_list *myList){
    /*
     * Display all the levels aligned in the cmd.
     */
    for (int i=0; i<myList->max_levels; i++) {
        displayLevelAligned(myList, i);
    }
}

void displayLevelAligned(t_d_list *myList, int level){
    /*
     * Display one level aligned in the cmd.
     */
    t_d_cell *tempCell = myList->heads[level];
    int counter=0;
    int delayNextLine=0;
    int spaces=0;
    printf("[list head_%d @- ]-->", level);
    delayNextLine=(19+ (getSizeOfInt(level+1)));
    counter+=delayNextLine;
    while (tempCell != NULL) {
        spaces=0;
        printf("[ %d", tempCell->value);
        while ((spaces+getSizeOfInt(tempCell->value))<=3){
            printf(" ");
            spaces++;
            counter++;
        }
        printf("|@- ]-->");
        counter += (10+ getSizeOfInt(tempCell->value));
        tempCell = tempCell->next[level];
        if (counter >99){
            printf("\n");
            for (int i = 0; i < delayNextLine-1; i ++) {
                printf(" ");
            }
            printf(">");
            counter=19+ getSizeOfInt(level);
        }
    }
    printf("NULL\n");
}
