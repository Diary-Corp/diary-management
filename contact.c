//
// Created by march on 11/14/2023.
//

#include "contact.h"
#include <ctype.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_BUFFER_SIZE 1000

void toLowerCase(char *string){
    /*
     * transform a string to a lower case string.
     */
    if (string == NULL) {
        return;
    }

    for (int i = 0; string[i] != '\0'; ++i) {
        string[i] = tolower(string[i]);
    }
}

void insertStringInSortedFile(const char *myString) {
    /*
     * Insert a new contact in the list of contact sorted contained in the txt file data/contacts.txt.
     */
    FILE *file = fopen("../data/contacts.txt", "r+");

    if (file != NULL) {
        char lines[100][100];
        int nbLines = 0;

        while (fgets(lines[nbLines], sizeof(lines[0]), file) != NULL) {
            nbLines++;
        }

        int insertIndex = 0;
        while (insertIndex < nbLines && strcmp(myString, lines[insertIndex]) > 0) {
            insertIndex++;
        }

        for (int i = nbLines; i > insertIndex; i--) {
            strcpy(lines[i], lines[i - 1]);
        }

        strcpy(lines[insertIndex], myString);
        nbLines++;

        rewind(file);

        for (int i = 0; i < nbLines; i++) {
            fprintf(file, "%s", lines[i]);
            if (i == insertIndex) {
                fprintf(file, "\n");
            }
        }
        fclose(file);
    } else {
        printf("We could not open the file contacts.txt\n");
    }
}

contact *createContact(char *firstName, char *lastName, int nbLevels){
    /*
     * Create a new contact using the given information and save it in the txt file.
     */
    toLowerCase(firstName);
    toLowerCase(lastName);

    size_t totalLength = strlen(firstName) + strlen("_") + strlen(lastName) + 1;
    char fullName[totalLength];
    strcpy(fullName, lastName);
    strcat(fullName, "_");
    strcat(fullName, firstName);
    printf("New contact %s created\n", fullName);

    char *contactName = (char*)malloc(totalLength);
    strcpy(contactName, fullName);

    insertStringInSortedFile(fullName);

    contact *newContact = (contact*)malloc(sizeof (contact));
    newContact->name = contactName;
    newContact->myAppointments = NULL;
    newContact->nb_appointments=0;
    newContact->nb_levels = 5;
    newContact->next = (contact**)malloc(sizeof(contact*) *nbLevels);

    return newContact;
}

contact *initializeContact(char *fullname, int nbLevels){
    /*
     * Initialize the previous contact created who are contained inside the txt file data/contacts.txt
     */
    contact *Contact = (contact*)malloc(sizeof (contact));
    Contact->name = (char*)malloc(strlen(fullname) + 1);
    strcpy(Contact->name, fullname);
    Contact->nb_appointments=0;
    Contact->myAppointments = NULL;
    Contact->nb_levels = 5;
    Contact->next = (contact**)malloc(sizeof(contact*) *nbLevels);

    return Contact;
}


void displayContactsFile(){
    /*
     * Display the first 100 contacts of the txt file.
     */
    FILE *file = fopen("../data/contacts.txt", "r+");

    if(file != NULL){
        char line[100];
        int i=1;
        printf("Display the first 100 contacts :\n");
        printf("-------------------\n");
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%d - %s",i, line);
            i++;
        }
        printf("\n");
        fclose(file);
    } else {
        printf("There is no contact.");
    }
}

