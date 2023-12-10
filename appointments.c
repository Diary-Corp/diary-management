//
// Created by jules on 14/11/2023.
//

#include "appointments.h"
#include <stdlib.h>
#include <stdio.h>
#include "contact.h"
#include "string.h"

void insertAppointmentAtBeginning(appointment *myAppointment, char *owner) {
    /*
     * Insert an appointment at the top of his txt file using owner name.
     */

    char filename[100];
    sprintf(filename, "../data/%s.txt", owner);
    FILE *file = fopen(filename, "a+");

    if (file != NULL) {
        char lines[500][500];
        int nbLines = 0;
        while (fgets(lines[nbLines], sizeof(lines[0]), file) != NULL) {
            nbLines++;
        }

        fclose(file);
        file = fopen(filename, "w");

        if (file != NULL) {
            char myString[500];
            sprintf(myString, "%s %d/%d/%d %d %d %s", owner,myAppointment->DateDay, myAppointment->DateMonth, myAppointment->DateYear, myAppointment->TimeHour, myAppointment->LengthMinute, myAppointment->Purpose);

            fprintf(file, "%s\n", myString);

            for (int i = 0; i < nbLines; i++) {
                fprintf(file, "%s", lines[i]);
            }

            fclose(file);
        } else {
            printf("Nous n'avons pas pu réouvrir le fichier en mode 'w' pour l'écraser\n");
        }
    } else {
        printf("Nous n'avons pas pu ouvrir ou créer le fichier %s\n", filename);
    }
}


appointment *createAppointment(int day, int month, int year, int hour, int lengthMinute, char *purpose, char *owner){
    /*
     * Create an appointment using all the needed information.
     */

    appointment *myAppointment = (appointment*)malloc(sizeof(appointment));
    myAppointment->DateDay = day;
    myAppointment->DateMonth = month;
    myAppointment->DateYear = year;
    myAppointment->TimeHour = hour;
    myAppointment->LengthMinute = lengthMinute;
    myAppointment->Purpose = purpose;

    insertAppointmentAtBeginning(myAppointment, owner);
    return myAppointment;
}

void addAppointmentToContact(struct s_contact *myContact, appointment *newAppointment) {
    /*
     * Link an appointment to an existing contact given.
     */
    myContact->nb_appointments++;
    myContact->myAppointments = (appointment**)realloc(myContact->myAppointments, myContact->nb_appointments * sizeof(appointment*));
    myContact->myAppointments[myContact->nb_appointments - 1] = newAppointment;
}

void displayAppointment(appointment *myAppointment){
    /*
     * Display the content of the appointment.
     */
    printf("-> %d/%d/%d - %dh for %d min: %s\n", myAppointment->DateDay, myAppointment->DateMonth, myAppointment->DateYear, myAppointment->TimeHour, myAppointment->LengthMinute, myAppointment->Purpose);
}

void displayAppointments(struct s_contact *myContact){
    /*
     * Display all the appointments created by a contact.
     */
    printf("Appointments of %s:\n", myContact->name);
    if (myContact->nb_appointments >= 1){
        for (int i=0; i<myContact->nb_appointments; i++){
            displayAppointment(myContact->myAppointments[i]);
        }
    } else {
        printf("None\n");
    }
}

int displayFileAppointments(char* fullname){
    /*
     * Display all the appointments saved in the txt file.
     */
    char filename[100];
    sprintf(filename, "../data/%s.txt", fullname);
    FILE *file = fopen(filename, "r");

    if (file != NULL){
        int i=1;
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            size_t newlineIndex = strcspn(line, "\n");
            line[newlineIndex] = '\0';
            printf("%d - %s\n", i, line);
            i++;
        }
        fclose(file);
        return 1;
    } else {
        printf("You have no appointments saved.\n");
        return 0;
    }
}

void deleteAppointment(int number, char* fullname) {
    /*
     * Delete the appointment situated on the x line given in parameter of a contact.
     */

    char filename[100];
    sprintf(filename, "../data/%s.txt", fullname);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("We couldn't open the file.");
    }

    char *tempBuffer = NULL;
    size_t tempBufferSize = 0;
    int appointmentDeleted = 0;

    char line[256];
    int currentLineNumber = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (currentLineNumber != number) {
            size_t lineLength = strlen(line);
            tempBuffer = realloc(tempBuffer, tempBufferSize + lineLength);
            if (tempBuffer == NULL) {
                perror("Error memory allocation");
                fclose(file);
            }
            strcpy(tempBuffer + tempBufferSize, line);
            tempBufferSize += lineLength;
        } else {
            appointmentDeleted = 1;
        }

        currentLineNumber++;
    }

    fclose(file);

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("We couldn't write into the file");
        free(tempBuffer);
    }

    if (tempBuffer != NULL) {
        fprintf(file, "%s", tempBuffer);
        free(tempBuffer);
    }

    fclose(file);

    if (appointmentDeleted){
        printf("Success : Appointment deleted.\n");
    } else {
        printf("We couldn't delete this appointment\n");
    }
}