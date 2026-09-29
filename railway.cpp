#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SEATS 20

/* =========================
   PASSENGER STRUCTURE
   ========================= */

struct Passenger
{
    int pnr;
    char name[30];
    int age;
    char gender;
    int seatNo;
    int trainNo;

    Passenger *next;
};


/* =========================
   WAITING QUEUE
   ========================= */

struct WaitingPassenger
{
    int pnr;
    char name[30];
    int age;
    char gender;
    int trainNo;

    WaitingPassenger *next;
};


/* =========================
   TRAIN STRUCTURE
   ========================= */

struct Train
{
    int trainNo;
    char trainName[30];
    char source[30];
    char destination[30];

    int platform;
    int totalSeats;
    int availableSeats;

    /* Each train has its OWN seats */
    int seat[MAX_SEATS];

    Passenger *passengerHead;

    WaitingPassenger *front;
    WaitingPassenger *rear;

    Train *next;
};


/* =========================
   GLOBAL VARIABLES
   ========================= */

Train *trainHead = NULL;

int nextPNR = 1001;


/* =========================
   ADMIN LOGIN
   ========================= */

int adminLogin()
{
    char username[20];
    char password[20];

    clrscr();

    cout << "\n====================================";
    cout << "\n          ADMIN LOGIN";
    cout << "\n====================================";

    cout << "\nEnter Username : ";
    cin >> username;

    cout << "Enter Password : ";
    cin >> password;

    if(strcmp(username, "admin") == 0 &&
       strcmp(password, "1234") == 0)
    {
        cout << "\nLogin Successful!";
        getch();
        return 1;
    }

    cout << "\nInvalid Username or Password!";
    getch();

    return 0;
}


/* =========================
   USER LOGIN
   ========================= */

int userLogin()
{
    char username[20];
    char password[20];

    clrscr();

    cout << "\n====================================";
    cout << "\n           USER LOGIN";
    cout << "\n====================================";

    cout << "\nEnter Username : ";
    cin >> username;

    cout << "Enter Password : ";
    cin >> password;

    /*
       For demo, any username/password
       will work.
    */

    if(strlen(username) > 0 && strlen(password) > 0)
    {
        cout << "\nLogin Successful!";
        getch();
        return 1;
    }

    cout << "\nInvalid Login!";
    getch();

    return 0;
}


/* =========================
   FIND TRAIN
   ========================= */

Train* findTrain(int trainNo)
{
    Train *temp = trainHead;

    while(temp != NULL)
    {
        if(temp->trainNo == trainNo)
            return temp;

        temp = temp->next;
    }

    return NULL;
}


/* =========================
   CREATE TRAIN
   ========================= */

void addTrain()
{
    Train *newTrain;
    int i;

    newTrain = new Train;

    clrscr();

    cout << "\n====================================";
    cout << "\n             ADD TRAIN";
    cout << "\n====================================";

    cout << "\nEnter Train Number : ";
    cin >> newTrain->trainNo;

    if(findTrain(newTrain->trainNo) != NULL)
    {
        cout << "\nTrain already exists!";
        delete newTrain;
        getch();
        return;
    }

    cout << "Enter Train Name : ";
    cin >> newTrain->trainName;

    cout << "Enter Source : ";
    cin >> newTrain->source;

    cout << "Enter Destination : ";
    cin >> newTrain->destination;

    cout << "Enter Platform Number : ";
    cin >> newTrain->platform;

    cout << "Enter Total Seats (Maximum 20) : ";
    cin >> newTrain->totalSeats;

    if(newTrain->totalSeats > MAX_SEATS)
        newTrain->totalSeats = MAX_SEATS;

    newTrain->availableSeats = newTrain->totalSeats;

    /*
       Every train gets its OWN seat array.
    */

    for(i = 0; i < MAX_SEATS; i++)
        newTrain->seat[i] = 0;

    newTrain->passengerHead = NULL;

    newTrain->front = NULL;
    newTrain->rear = NULL;

    newTrain->next = NULL;

    if(trainHead == NULL)
    {
        trainHead = newTrain;
    }
    else
    {
        Train *temp = trainHead;

        while(temp->next != NULL)
            temp = temp->next;

        temp->next = newTrain;
    }

    cout << "\nTrain Added Successfully!";
    getch();
}


/* =========================
   DISPLAY ONE TRAIN
   ========================= */

void displayTrain(Train *t)
{
    cout << "\n------------------------------------";
    cout << "\nTrain Number    : " << t->trainNo;
    cout << "\nTrain Name      : " << t->trainName;
    cout << "\nSource          : " << t->source;
    cout << "\nDestination     : " << t->destination;
    cout << "\nPlatform        : " << t->platform;
    cout << "\nTotal Seats     : " << t->totalSeats;
    cout << "\nAvailable Seats : " << t->availableSeats;
    cout << "\n------------------------------------";
}


/* =========================
   DISPLAY ALL TRAINS
   ========================= */

void displayAllTrains()
{
    Train *temp = trainHead;

    clrscr();

    cout << "\n====================================";
    cout << "\n          ALL TRAIN DETAILS";
    cout << "\n====================================";

    if(temp == NULL)
    {
        cout << "\nNo trains available.";
        getch();
        return;
    }

    while(temp != NULL)
    {
        displayTrain(temp);
        temp = temp->next;
    }

    getch();
}


/* =========================
   SEARCH TRAIN BY NUMBER
   ========================= */

void searchTrain()
{
    int no;
    Train *t;

    clrscr();

    cout << "\nEnter Train Number : ";
    cin >> no;

    t = findTrain(no);

    if(t == NULL)
        cout << "\nTrain Not Found!";
    else
        displayTrain(t);

    getch();
}


/* =========================
   SEARCH SOURCE
   ========================= */

void searchSource()
{
    char source[30];
    Train *temp = trainHead;
    int found = 0;

    clrscr();

    cout << "\nEnter Source : ";
    cin >> source;

    while(temp != NULL)
    {
        if(strcmp(temp->source, source) == 0)
        {
            displayTrain(temp);
            found = 1;
        }

        temp = temp->next;
    }

    if(found == 0)
        cout << "\nNo train found from this source.";

    getch();
}


/* =========================
   SEARCH DESTINATION
   ========================= */

void searchDestination()
{
    char destination[30];
    Train *temp = trainHead;
    int found = 0;

    clrscr();

    cout << "\nEnter Destination : ";
    cin >> destination;

    while(temp != NULL)
    {
        if(strcmp(temp->destination, destination) == 0)
        {
            displayTrain(temp);
            found = 1;
        }

        temp = temp->next;
    }

    if(found == 0)
        cout << "\nNo train found for this destination.";

    getch();
}


/* =========================
   EDIT TRAIN
   ========================= */

void editTrain()
{
    int no;
    Train *t;

    clrscr();

    cout << "\nEnter Train Number : ";
    cin >> no;

    t = findTrain(no);

    if(t == NULL)
    {
        cout << "\nTrain Not Found!";
        getch();
        return;
    }

    cout << "\nEnter New Train Name : ";
    cin >> t->trainName;

    cout << "Enter New Source : ";
    cin >> t->source;

    cout << "Enter New Destination : ";
    cin >> t->destination;

    cout << "Enter New Platform : ";
    cin >> t->platform;

    cout << "\nTrain Updated Successfully!";

    getch();
}


/* =========================
   CHANGE PLATFORM
   ========================= */

void changePlatform()
{
    int no;
    int platform;

    Train *t;

    clrscr();

    cout << "\nEnter Train Number : ";
    cin >> no;

    t = findTrain(no);

    if(t == NULL)
    {
        cout << "\nTrain Not Found!";
        getch();
        return;
    }

    cout << "Current Platform : "
         << t->platform;

    cout << "\nEnter New Platform : ";
    cin >> platform;

    t->platform = platform;

    cout << "\nPlatform Updated Successfully!";

    getch();
}


/* =========================
   DELETE TRAIN
   ========================= */

void deleteTrain()
{
    int no;

    Train *temp = trainHead;
    Train *prev = NULL;

    clrscr();

    cout << "\nEnter Train Number : ";
    cin >> no;

    while(temp != NULL)
    {
        if(temp->trainNo == no)
        {
            if(prev == NULL)
                trainHead = temp->next;
            else
                prev->next = temp->next;

            delete temp;

            cout << "\nTrain Deleted Successfully!";
            getch();
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "\nTrain Not Found!";

    getch();
}


/* =========================
   DISPLAY SEATS
   ========================= */

void displaySeats()
{
    int no;
    int i;

    Train *t;

    clrscr();

    cout << "\nEnter Train Number : ";
    cin >> no;

    t = findTrain(no);

    if(t == NULL)
    {
        cout << "\nTrain Not Found!";
        getch();
        return;
    }

    cout << "\n====================================";
    cout << "\nTrain : " << t->trainName;
    cout << "\n====================================";

    for(i = 0; i < t->totalSeats; i++)
    {
        cout << "\nSeat " << i + 1;

        if(t->seat[i] == 0)
            cout << " : AVAILABLE";
        else
            cout << " : BOOKED";
    }

    getch();
}


/* =========================
   BOOK TICKET
   ========================= */

void bookTicket()
{
    int no;
    int i;
    int seatNo;

    Train *t;
    Passenger *p;

    clrscr();

    cout << "\n====================================";
    cout << "\n             BOOK TICKET";
    cout << "\n====================================";

    cout << "\nEnter Train Number : ";
    cin >> no;

    t = findTrain(no);

    if(t == NULL)
    {
        cout << "\nTrain Not Found!";
        getch();
        return;
    }

    if(t->availableSeats == 0)
    {
        cout << "\nAll seats are booked.";

        cout << "\nDo you want to join Waiting Queue?";
        cout << "\n1. Yes";
        cout << "\n2. No";

        int ch;
        cin >> ch;

        if(ch == 1)
        {
            WaitingPassenger *w;

            w = new WaitingPassenger;

            w->pnr = nextPNR++;

            cout << "\nEnter Passenger Name : ";
            cin >> w->name;

            cout << "Enter Age : ";
            cin >> w->age;

            cout << "Enter Gender (M/F) : ";
            cin >> w->gender;

            w->trainNo = no;
            w->next = NULL;

            if(t->front == NULL)
            {
                t->front = w;
                t->rear = w;
            }
            else
            {
                t->rear->next = w;
                t->rear = w;
            }

            cout << "\nAdded to Waiting Queue!";
            cout << "\nWaiting PNR : " << w->pnr;
        }

        getch();
        return;
    }

    cout << "\nAvailable Seats : "
         << t->availableSeats;

    cout << "\nEnter Seat Number : ";
    cin >> seatNo;

    if(seatNo < 1 || seatNo > t->totalSeats)
    {
        cout << "\nInvalid Seat Number!";
        getch();
        return;
    }

    if(t->seat[seatNo - 1] == 1)
    {
        cout << "\nThis Seat is Already Booked!";
        getch();
        return;
    }

    p = new Passenger;

    p->pnr = nextPNR++;

    cout << "\nEnter Passenger Name : ";
    cin >> p->name;

    cout << "Enter Age : ";
    cin >> p->age;

    cout << "Enter Gender (M/F) : ";
    cin >> p->gender;

    p->seatNo = seatNo;
    p->trainNo = no;

    p->next = t->passengerHead;

    t->passengerHead = p;

    /*
       THIS TRAIN'S SEAT ONLY
       becomes booked.
    */

    t->seat[seatNo - 1] = 1;

    t->availableSeats--;

    cout << "\n====================================";
    cout << "\n       TICKET BOOKED";
    cout << "\n====================================";

    cout << "\nPNR       : " << p->pnr;
    cout << "\nPassenger : " << p->name;
    cout << "\nTrain     : " << t->trainName;
    cout << "\nSeat      : " << p->seatNo;
    cout << "\nPlatform  : " << t->platform;

    getch();
}


/* =========================
   VIEW BOOKING
   ========================= */

void viewBooking()
{
    int pnr;

    Train *t;
    Passenger *p;

    clrscr();

    cout << "\nEnter PNR : ";
    cin >> pnr;

    t = trainHead;

    while(t != NULL)
    {
        p = t->passengerHead;

        while(p != NULL)
        {
            if(p->pnr == pnr)
            {
                cout << "\n====================================";
                cout << "\n             TICKET";
                cout << "\n====================================";

                cout << "\nPNR         : " << p->pnr;
                cout << "\nName        : " << p->name;
                cout << "\nAge         : " << p->age;
                cout << "\nTrain No    : " << t->trainNo;
                cout << "\nTrain Name  : " << t->trainName;
                cout << "\nSource      : " << t->source;
                cout << "\nDestination : " << t->destination;
                cout << "\nSeat No     : " << p->seatNo;
                cout << "\nPlatform    : " << t->platform;

                getch();
                return;
            }

            p = p->next;
        }

        t = t->next;
    }

    cout << "\nPNR Not Found!";

    getch();
}


/* =========================
   CANCEL TICKET
   ========================= */

void cancelTicket()
{
    int pnr;

    Train *t;
    Passenger *p;
    Passenger *prev;

    clrscr();

    cout << "\nEnter PNR : ";
    cin >> pnr;

    t = trainHead;

    while(t != NULL)
    {
        p = t->passengerHead;
        prev = NULL;

        while(p != NULL)
        {
            if(p->pnr == pnr)
            {
                /*
                   Make this train's seat available
                */

                t->seat[p->seatNo - 1] = 0;
                t->availableSeats++;

                if(prev == NULL)
                    t->passengerHead = p->next;
                else
                    prev->next = p->next;

                delete p;

                cout << "\nTicket Cancelled Successfully!";

                /*
                   Check waiting queue
                */

                if(t->front != NULL)
                {
                    WaitingPassenger *w;

                    w = t->front;

                    t->front = t->front->next;

                    if(t->front == NULL)
                        t->rear = NULL;

                    cout << "\nWaiting Passenger Available!";
                    cout << "\nPassenger: " << w->name;
                    cout << "\nPlease book the newly available seat.";

                    delete w;
                }

                getch();
                return;
            }

            prev = p;
            p = p->next;
        }

        t = t->next;
    }

    cout << "\nPNR Not Found!";

    getch();
}


/* =========================
   DISPLAY ALL BOOKINGS
   ========================= */

void displayBookings()
{
    Train *t;
    Passenger *p;

    clrscr();

    cout << "\n====================================";
    cout << "\n          ALL BOOKINGS";
    cout << "\n====================================";

    t = trainHead;

    while(t != NULL)
    {
        p = t->passengerHead;

        while(p != NULL)
        {
            cout << "\n--------------------------------";
            cout << "\nPNR       : " << p->pnr;
            cout << "\nName      : " << p->name;
            cout << "\nTrain No  : " << t->trainNo;
            cout << "\nSeat No   : " << p->seatNo;

            p = p->next;
        }

        t = t->next;
    }

    getch();
}


/* =========================
   SORT TRAINS
   BY TRAIN NUMBER
   ========================= */

void sortTrains()
{
    Train *i;
    Train *j;

    int tempNo;
    char tempName[30];
    char tempSource[30];
    char tempDestination[30];
    int tempPlatform;

    clrscr();

    /*
       Bubble Sort
    */

    for(i = trainHead; i != NULL; i = i->next)
    {
        for(j = i->next; j != NULL; j = j->next)
        {
            if(i->trainNo > j->trainNo)
            {
                tempNo = i->trainNo;
                i->trainNo = j->trainNo;
                j->trainNo = tempNo;

                strcpy(tempName, i->trainName);
                strcpy(i->trainName, j->trainName);
                strcpy(j->trainName, tempName);

                strcpy(tempSource, i->source);
                strcpy(i->source, j->source);
                strcpy(j->source, tempSource);

                strcpy(tempDestination, i->destination);
                strcpy(i->destination, j->destination);
                strcpy(j->destination, tempDestination);

                tempPlatform = i->platform;
                i->platform = j->platform;
                j->platform = tempPlatform;
            }
        }
    }

    cout << "\nTrains Sorted Successfully!";

    getch();
}


/* =========================
   ADMIN MENU
   ========================= */

void adminMenu()
{
    int choice;

    do
    {
        clrscr();

        cout << "\n====================================";
        cout << "\n            ADMIN MENU";
        cout << "\n====================================";

        cout << "\n1. Add Train";
        cout << "\n2. Display All Trains";
        cout << "\n3. Search Train";
        cout << "\n4. Edit Train";
        cout << "\n5. Delete Train";
        cout << "\n6. Change Platform";
        cout << "\n7. Display Seat Status";
        cout << "\n8. View All Bookings";
        cout << "\n9. Sort Trains";
        cout << "\n10. Logout";

        cout << "\n\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addTrain();
                break;

            case 2:
                displayAllTrains();
                break;

            case 3:
                searchTrain();
                break;

            case 4:
                editTrain();
                break;

            case 5:
                deleteTrain();
                break;

            case 6:
                changePlatform();
                break;

            case 7:
                displaySeats();
                break;

            case 8:
                displayBookings();
                break;

            case 9:
                sortTrains();
                break;

            case 10:
                cout << "\nAdmin Logout...";
                break;

            default:
                cout << "\nInvalid Choice!";
                getch();
        }

    }while(choice != 10);
}


/* =========================
   USER MENU
   ========================= */

void userMenu()
{
    int choice;

    do
    {
        clrscr();

        cout << "\n====================================";
        cout << "\n             USER MENU";
        cout << "\n====================================";

        cout << "\n1. View All Trains";
        cout << "\n2. Search Train by Number";
        cout << "\n3. Search Train by Source";
        cout << "\n4. Search Train by Destination";
        cout << "\n5. View Train Details";
        cout << "\n6. Check Available Seats";
        cout << "\n7. Book Ticket";
        cout << "\n8. View My Ticket / PNR";
        cout << "\n9. Cancel Ticket";
        cout << "\n10. Logout";

        cout << "\n\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayAllTrains();
                break;

            case 2:
                searchTrain();
                break;

            case 3:
                searchSource();
                break;

            case 4:
                searchDestination();
                break;

            case 5:
                searchTrain();
                break;

            case 6:
                displaySeats();
                break;

            case 7:
                bookTicket();
                break;

            case 8:
                viewBooking();
                break;

            case 9:
                cancelTicket();
                break;

            case 10:
                cout << "\nUser Logout...";
                break;

            default:
                cout << "\nInvalid Choice!";
                getch();
        }

    }while(choice != 10);
}


/* =========================
   MAIN FUNCTION
   ========================= */

void main()
{
    int choice;
    int login;

    /*
       Some default trains
       are added for testing.
    */

    Train *t;

    t = new Train;

    t->trainNo = 101;
    strcpy(t->trainName, "MumbaiExpress");
    strcpy(t->source, "Mumbai");
    strcpy(t->destination, "Delhi");
    t->platform = 1;
    t->totalSeats = 20;
    t->availableSeats = 20;

    for(int i = 0; i < MAX_SEATS; i++)
        t->seat[i] = 0;

    t->passengerHead = NULL;
    t->front = NULL;
    t->rear = NULL;
    t->next = NULL;

    trainHead = t;


    /*
       Second Train
       It has a completely separate seat array.
    */

    t = new Train;

    t->trainNo = 102;
    strcpy(t->trainName, "DelhiExpress");
    strcpy(t->source, "Delhi");
    strcpy(t->destination, "Mumbai");
    t->platform = 2;
    t->totalSeats = 20;
    t->availableSeats = 20;

    for(i = 0; i < MAX_SEATS; i++)
        t->seat[i] = 0;

    t->passengerHead = NULL;
    t->front = NULL;
    t->rear = NULL;
    t->next = NULL;

    trainHead->next = t;


    /*
       Main Menu
    */

    do
    {
        clrscr();

        cout << "\n====================================";
        cout << "\n      RAILWAY RESERVATION SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Admin Login";
        cout << "\n2. User Login";
        cout << "\n3. Exit";

        cout << "\n\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:

                login = adminLogin();

                if(login == 1)
                    adminMenu();

                break;


            case 2:

                login = userLogin();

                if(login == 1)
                    userMenu();

                break;


            case 3:

                cout << "\nThank You!";
                break;


            default:

                cout << "\nInvalid Choice!";
                getch();
        }

    }while(choice != 3);

    getch();
}