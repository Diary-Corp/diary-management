//
// Created by march on 10/24/2023.
//

#include "cell.h"
#include "list.h"
#include "stdio.h"
#include "timer.h"
#include "contact.h"
#include <string.h>
#include "list_contact.h"

int main(){

    int choice, menu=1;

    //create our contact list
    t_d_listcontact *myContacts = createListContact(5);

    char *actualContactName = strdup("None");
    contact *actualContactPtr = NULL;

    //initialize the previous contacts
    initializeContacts(myContacts);

    while(menu){

        //vertical menu of our program
        printf("-------------------\n");
        printf("Actual Contact : %s\n", actualContactName);
        printf("-------------------\n");
        printf("1 - Select a contact\n");
        printf("2 - View a contact's appointment\n");
        printf("3 - Create a contact\n");
        printf("4 - Display contacts\n");
        printf("5 - Create an appointment\n");
        printf("6 - Delete an appointment\n");
        printf("7 - See previous appointments (load file)\n");
        printf("8 - Calculation time example\n");
        printf("9 - Display of part 2\n");
        printf("10 - Quit & Save\n");
        printf("-------------------\n");
        printf("Enter your choice :\n");
        printf("-------------------\n");
        scanf("%d", &choice);

        if (choice == 1){

            //Selection of the contact
            char contactName[100];
            char autocompleteInput[100];
            printf("-------------------\n");
            printf("Enter the first three letters of the last name of the contact :\n");
            printf("-------------------\n");
            scanf("%s",autocompleteInput);
            while (strlen(autocompleteInput)>3){
                printf("Invalid input, please try again :");
                scanf("%s",autocompleteInput);
                //failsafe if the input is > 3 letters
            }
            autocompleteContact(autocompleteInput);

            printf("-------------------\n");
            printf("Which contact would you like to select ? (full name)\n");
            printf("-------------------\n");
            scanf(" %s", contactName);

            actualContactPtr = setContactSelected(myContacts, contactName);

            if (actualContactPtr != NULL) {
                actualContactName = actualContactPtr->name;
                printf("Contact selected !\n");
            } else {
                printf("Contact not found.\n");
                actualContactName = strdup("None");
            }

        } else if (choice == 2){

            //View the appointments of a contact just created
            if (actualContactPtr!=NULL){
                displayAppointments(actualContactPtr);
            } else {
                printf("No contact selected\n");
            }

        } else if (choice == 3){

            //Create a new contact and store it inside our txt file
            char firstName[50], lastName[50];
            printf("Enter the first name of your contact\n");
            scanf(" %s", firstName);
            printf("Enter the last name of your contact\n");
            scanf(" %s", lastName);

            contact *newContact = createContact(firstName, lastName, 5);
            insertContact(myContacts, newContact);

        } else if (choice == 4){

            //display the list of all the contacts store inside the txt file
            displayContacts(myContacts);

        } else if (choice == 5){

            //Creation of a new appointment and add in to the contact selected
            int day, month, year, time, length;
            char purpose[200];

            if (strcmp(actualContactName, "None") == 1) {
                printf("Create an appointment:\n");
                printf("Step 1 - On which day dd/mm/yyyy format ?\n");
                scanf("%d/%d/%d", &day, &month, &year);
                printf("Step 2 - At which hour ?\n");
                scanf("%d", &time);
                printf("Step 3 - How long would it be ? In minutes\n");
                scanf("%d", &length);
                printf("Final Step - What is the purpose of the appointment ?\n");
                scanf(" %[^\n]", purpose);
                appointment *myAppointment = createAppointment(day, month, year, time, length, purpose, actualContactName);
                displayAppointment(myAppointment);
                addAppointmentToContact(actualContactPtr, myAppointment);
            } else {
                printf("No contact selected\n");
            }

        } else if (choice == 6){

            //Delete a specific appointment of the selected contact
            if (actualContactPtr!=NULL){
                int appointmentNumber, success;
                success = displayFileAppointments(actualContactName);
                if (success){
                    printf("-------------------\n");
                    printf("Which appointment whould you like to delete ?\n");
                    printf("-------------------\n");
                    scanf("%d", &appointmentNumber);
                    deleteAppointment(appointmentNumber, actualContactName);
              } else {
                    printf("Nothing to delete here.");
                }
            } else {
                printf("No contact selected\n");
            }

        } else if (choice == 7){

            //Display the appointments stored inside the txt file of the contact selected
            if (actualContactPtr!=NULL){
                displayFileAppointments(actualContactName);
            } else {
                printf("No contact selected\n");
            }

        } else if (choice == 8){

            //Provide an example of the complexity timer between the two algorithms (dichotomic vs standart)
            printf("You will now test the complexity of a standard search algorithm VS a level based algorithm.\n\n");
            complexityTest();

        } else if (choice == 9){

            //Provide a more concrete illustration of the second part of the project
            int nbTerms, value;
            t_d_list *myList = createList(5);
            printf("Enter the number of elements inside the list: \n");
            scanf("%d", &nbTerms);
            insertLevelCells(myList, nbTerms);
            displayAllLevelsAligned(myList);
            printf("Which value would you like to find?\n");
            scanf("%d", &value);
            searchValueBis(myList, value);
            searchLevelValueBis(myList, value);
            printf("This comparaison has been made using only 5 levels.\n");

        } else if (choice==10){

            //Exit the program
            printf("See you!");
            break;

        } else {

            //Handle bad choices
            printf("Wrong choice!\n");

        }

    }

    return 0;
}


