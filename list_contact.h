//
// Created by march on 12/1/2023.
//

#ifndef DIARY_MANAGEMENT_LIST_CONTACT_H
#define DIARY_MANAGEMENT_LIST_CONTACT_H
#include "contact.h"

typedef struct s_d_listcontact
{
    int maxLevels;
    contact **heads;
} t_d_listcontact;

t_d_listcontact *createListContact(int maxLevels);
void insertContact(t_d_listcontact *myList, contact *myContact);

void displayContacts(t_d_listcontact *myList);

void displayLevelContact(t_d_listcontact *myList, int level);
void displayAllLevelsContact(t_d_listcontact *myList);

contact *setContactSelected(t_d_listcontact *myList, char* fullname);

void initializeContacts(t_d_listcontact *myList);

void autocompleteContact(char *name);

#endif //DIARY_MANAGEMENT_LIST_CONTACT_H
