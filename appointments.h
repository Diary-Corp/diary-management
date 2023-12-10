//
// Created by jules on 14/11/2023.
//

#ifndef DIARY_MANAGEMENT_APPOINTMENTS_H
#define DIARY_MANAGEMENT_APPOINTMENTS_H
struct s_contact;

typedef struct s_appointment{
    int DateDay;
    int DateMonth; 
    int DateYear;
    int TimeHour;
    int TimeMinute;
    int LengthMinute;
    char *Purpose;
} appointment;


void insertAppointmentAtBeginning(appointment *myAppointment, char *owner);

appointment *createAppointment(int day, int month, int year, int hour, int lengthMinute, char *purpose, char *owner);
void addAppointmentToContact(struct s_contact *myContact, appointment *newAppointment);

void displayAppointment(appointment *myAppointment);
void displayAppointments(struct s_contact *myContact);
int displayFileAppointments(char* fullname);

void deleteAppointment(int number, char* fullname);

#endif //DIARY_MANAGEMENT_APPOINTMENTS_H