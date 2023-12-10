//
// Created by march on 12/1/2023.
//

#include "list_contact.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

t_d_listcontact *createListContact(int maxLevels){
    /*
     * Create the empty list of contacts.
     */
    t_d_listcontact *myList = (t_d_listcontact*)malloc(sizeof(t_d_listcontact));
    myList->maxLevels = maxLevels;

    myList->heads = (contact **)malloc(sizeof (contact *) * maxLevels);

    for(int i=0; i<maxLevels; i++){
        myList->heads[i] = NULL;
    }
    return myList;
}

void insertContact(t_d_listcontact *myList, contact *myContact){
    /*
     * Insert a contact inside the list
     */
    for (int i=0; i<myContact->nb_levels; i++){
        contact *tempContact = myList->heads[i];
        myList->heads[i] = myContact;
        myContact->next[i] = tempContact;
    }
}

void displayLevelContact(t_d_listcontact *myList, int level){
    /*
     * Display all the contact inside one specific level.
     */
    if (myList->heads[level]!=NULL){
        contact *tempContact = myList->heads[level];
        printf("[list head_%d @- ]-->", level);
        while (tempContact != NULL) {
            printf("[ %s|@- ]-->", tempContact->name);
            tempContact = tempContact->next[level];
        }
        printf("NULL\n");
    } else {
        printf("No contacts");
    }
}

void displayAllLevelsContact(t_d_listcontact *myList){
    /*
     * Display all the contacts contained in all levels.
     */
    if (myList->heads[0]!=NULL) {
        for (int i = 0; i < myList->maxLevels; i++) {
            displayLevelContact(myList, i);
        }
    } else {
        printf("No contacts");
    }
}

void initializeContacts(t_d_listcontact *myList){
    /*
     *  Initialize the contacts stored in text data/contacts.txt file and add them to the list.
     */
    FILE *file = fopen("../data/contacts.txt", "r+");

    if(file != NULL){
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            size_t newlineIndex = strcspn(line, "\n");
            line[newlineIndex] = '\0';
            contact *myContact = initializeContact(line, 5);
            insertContact(myList, myContact);
        }
        fclose(file);
    } else {
        printf("There is no contacts.");
    }
}

void displayContacts(t_d_listcontact *myList){
    /*
     * Display the contact list contained inside the list.
     */
    contact *tempContact = myList->heads[0];
    if (tempContact != NULL){
        while(tempContact != NULL){
            printf("- %s\n", tempContact->name);
            tempContact = tempContact->next[0];
        }
    } else {
        printf("No contacts in the list\n");
    }
}

contact *setContactSelected(t_d_listcontact *myList, char* fullname){
    /*
     * Return the pointer toward the contact fullname wanted.
     */
    contact *tempContact = myList->heads[0];
    if (tempContact != NULL){
        while(tempContact != NULL){
            if (strcmp(tempContact->name, fullname) == 0) {
                return tempContact;
            }
            tempContact = tempContact->next[0];
        }
    }
    return NULL;
}

void autocompleteContact(char *name){
    /*
     * Autocomplete the contact name during the selection.
     */
    FILE *file = fopen("../data/contacts.txt", "r+");
    if (file == NULL){
        printf("Filename is not correct, cannot open");
        return;
    }
    else{
        char nameFile[100];
        printf("Here are all the contacts starting by '%s': \n", name);
        while (fgets(nameFile, sizeof(nameFile), file)!= NULL){
            nameFile[strcspn(nameFile,"\n")]='\0';

            if (strncmp(name, nameFile, 3) ==0){
                printf("%s\n", nameFile);
            }
        }
    }
    fclose(file);
}