#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void room_booking();
void customer_record();
void delete_record();
void search();
int admin_login();
int customer_login();
void customer_register();

struct CustomerDetails {
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[15];
    char nationality[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
} s;

int main() {
    char choice;
    while (1) {
        system("cls");
        printf("\n\n\t\t\t\t===========>>>>> Hotel Management System <<<<<===========\n\n");
        printf("\t\t\t\t          =========>>>>> Main Menu <<<<<=========          \n");
        printf("\t\t\t\t             1) Admin Login                                  \n");
        printf("\t\t\t\t             2) Customer Login                               \n");
        printf("\t\t\t\t             3) Customer Register                            \n");
        printf("\t\t\t\t             4) Exit                                         \n");
        printf("\t\t\t\t             Enter your choice here: ");
        choice = getchar();
        getchar(); // to consume the newline character
        switch (choice) {
            case '1':
                if (admin_login()) {
                    while (1) {
                        system("cls");
                        printf("\n\n\t\t\t\t===========>>>>> Admin Menu <<<<<===========\n\n");
                        printf("\t\t\t\t             1) View Customer Record                         \n");
                        printf("\t\t\t\t             2) Delete Customer Record                       \n");
                        printf("\t\t\t\t             3) Search Customer Record                       \n");
                        printf("\t\t\t\t             4) Log Out                                      \n");
                        printf("\t\t\t\t             Enter your choice here: ");
                        choice = getchar();
                        getchar(); // to consume the newline character
                        switch (choice) {
                            case '1':
                                customer_record();
                                break;
                            case '2':
                                delete_record();
                                break;
                            case '3':
                                search();
                                break;
                            case '4':
                                goto main_menu; // Log out and return to main menu
                            default:
                                system("cls");
                                printf("\n\n\a\t\t\t\t\t\t    !!  Wrong Entry  !!");
                                printf("\n\n\n\t\t\t\t              Please re-enter correct option\n");
                                break;
                        }
                    }
                }
                break;
            case '2':
                if (customer_login()) {
                    room_booking();
                }
                break;
            case '3':
                customer_register();
                break;
            case '4':
                system("cls");
                printf("\n\n\t\t\t\t===========>>>>> Hotel Management System <<<<<===========\n\n");
                printf("\t\t\t\t==                                                       ==\n");
                printf("\t\t\t\t==                       Thank you                       ==\n");
                printf("\t\t\t\t==                          for                          ==\n");
                printf("\t\t\t\t==                  viewing our program                  ==\n");
                printf("\t\t\t\t==                                                       ==\n");
                exit(0);
            default:
                system("cls");
                printf("\n\n\a\t\t\t\t\t\t    !!  Wrong Entry  !!");
                printf("\n\n\n\t\t\t\t              Please re-enter correct option\n");
                break;
        }
    }
    main_menu:;
}

int admin_login() {
    char username[20], password[20];
    printf("\n\n\t\t\t\t===========>>>>> Admin Login <<<<<===========\n\n");
    printf("\t\t\t\tEnter Username: ");
    fgets(username, sizeof(username), stdin);
    printf("\t\t\t\tEnter Password: ");
    fgets(password, sizeof(password), stdin);

    // Removing newline characters from username and password
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("\n\t\t\t\tLogin successful! Press any key to continue.\n");
        getchar();
        return 1;
    } else {
        printf("\n\t\t\t\tInvalid credentials! Press any key to return to the main menu.\n");
        getchar();
        return 0;
    }
}

int customer_login() {
    char username[20], password[20];
    FILE *f = fopen("customers.txt", "r");
    if (f == NULL) {
        printf("\n\n\t\t\t\t\t\t!! No Customers Registered !!");
        printf("\n\n\t\t\t\t\t\tPress any key for main menu.\n");
        getchar();
        return 0;
    }

    printf("\n\n\t\t\t\t===========>>>>> Customer Login <<<<<===========\n\n");
    printf("\t\t\t\tEnter Username: ");
    fgets(username, sizeof(username), stdin);
    printf("\t\t\t\tEnter Password: ");
    fgets(password, sizeof(password), stdin);

    // Removing newline characters from username and password
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    struct {
        char username[20];
        char password[20];
    } customer;

    while (fread(&customer, sizeof(customer), 1, f)) {
        if (strcmp(customer.username, username) == 0 && strcmp(customer.password, password) == 0) {
            printf("\n\t\t\t\tLogin successful! Press any key to continue.\n");
            fclose(f);
            getchar();
            return 1;
        }
    }

    printf("\n\t\t\t\tInvalid credentials! Press any key to return to the main menu.\n");
    fclose(f);
    getchar();
    return 0;
}

void customer_register() {
    char username[20], password[20];
    FILE *f = fopen("customers.txt", "a+");
    if (f == NULL) {
        f = fopen("customers.txt", "w+");
        if (f == NULL) {
            perror("Unable to open file");
            exit(1);
        }
    }

    printf("\n\n\t\t\t\t===========>>>>> Customer Register <<<<<===========\n\n");
    printf("\t\t\t\tEnter Username: ");
    fgets(username, sizeof(username), stdin);
    printf("\t\t\t\tEnter Password: ");
    fgets(password, sizeof(password), stdin);

    // Removing newline characters from username and password
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    struct {
        char username[20];
        char password[20];
    } customer;

    int exists = 0;
    while (fread(&customer, sizeof(customer), 1, f)) {
        if (strcmp(customer.username, username) == 0) {
            exists = 1;
            break;
        }
    }

    if (exists) {
        printf("\n\t\t\t\tUsername already exists! Press any key to return to the main menu.\n");
    } else {
        strcpy(customer.username, username);
        strcpy(customer.password, password);
        fwrite(&customer, sizeof(customer), 1, f);
        printf("\n\t\t\t\tRegistration successful! Press any key to return to the main menu.\n");
    }

    fclose(f);
    getchar();
}

void room_booking() {
    FILE *f = fopen("add.txt", "a+");
    if (f == NULL) {
        f = fopen("add.txt", "w+");
        if (f == NULL) {
            perror("Unable to open file");
            exit(1);
        }
        system("cls");
        printf("Please hold on while we set our database in your computer!!");
        printf("\nProcess completed. Press any key to continue!! ");
        getchar();
    }

    while (1) {
        system("cls");
        printf("\n\n\t\t\t\t===========>>>>> Hotel Management System <<<<<===========\n\n");
        printf("\t\t\t\t          =========>>>>> Book A Room <<<<<=========          \n");
        printf("\t\t\t\t      ===============================================        \n");

        char roomnumber[10];
        printf("\n\t\t\t\t  Enter Room Number                : ");
        fgets(roomnumber, sizeof(roomnumber), stdin);

        int isBooked = 0;
        rewind(f);
        while (fread(&s, sizeof(s), 1, f)) {
            if (strcmp(s.roomnumber, roomnumber) == 0) {
                isBooked = 1;
                break;
            }
        }

        if (isBooked) {
            printf("\n\t\t\t\t\aRoom %s is already booked!", roomnumber);
            printf("\n\t\t\t\tPress any key to return to the main menu.\n");
            getchar();
            break;
        }

        strcpy(s.roomnumber, roomnumber);
        printf("\n\t\t\t\t  Enter Name                       : ");
        fgets(s.name, sizeof(s.name), stdin);
        printf("\n\t\t\t\t  Enter Address                    : ");
        fgets(s.address, sizeof(s.address), stdin);
        printf("\n\t\t\t\t  Enter Phone Number               : ");
        fgets(s.phonenumber, sizeof(s.phonenumber), stdin);
        printf("\n\t\t\t\t  Enter Nationality                : ");
        fgets(s.nationality, sizeof(s.nationality), stdin);
               printf("\n\t\t\t\t  Enter Email                      : ");
        fgets(s.email, sizeof(s.email), stdin);
        printf("\n\t\t\t\t  Enter Period ('x' days)          : ");
        fgets(s.period, sizeof(s.period), stdin);
        printf("\n\t\t\t\t  Enter Arrival date (dd/mm/yyyy)  : ");
        fgets(s.arrivaldate, sizeof(s.arrivaldate), stdin);

        fwrite(&s, sizeof(s), 1, f);
        fflush(stdin);

        printf("\n\n\t\t\t\t\aRoom successfully booked.");
        printf("\n\n\t\t\t\tWould you like to add more rooms? (Y/N): ");
        char choice = getchar();
        getchar(); // to consume the newline character
        if (choice != 'Y' && choice != 'y') {
            break;
        }
    }

    fclose(f);
}

void customer_record() {
    system("cls");
    FILE *f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("\n\n\t\t\t\t\t\t!! File Not Found !!");
        printf("\n\n\t\t\t\t\t\tPress any key for main menu.\n");
        getchar();
        return;
    }

    system("cls");
    printf("\n\n\t\t\t\t===========>>>>> Hotel Management System <<<<<===========\n\n");
    printf("\t\t\t\t      =========>>>>> View Customer Record <<<<<=========       \n");
    printf("\t\t\t\t   ======================================================    \n\n");

    while (fread(&s, sizeof(s), 1, f)) {
        printf("\t\t\t\t\tRoom = %s    ", s.roomnumber);
        printf("--------> Name        = %s", s.name);
        printf("\n\t\t\t\t\t\t    --------> Address      = %s", s.address);
        printf("\n\t\t\t\t\t\t    --------> Phone number = %s", s.phonenumber);
        printf("\n\t\t\t\t\t\t    --------> Nationality  = %s", s.nationality);
        printf("\n\t\t\t\t\t\t    --------> Email        = %s", s.email);
        printf("\n\t\t\t\t\t\t    --------> Period       = %s", s.period);
        printf("\n\t\t\t\t\t\t    --------> Arrival date = %s", s.arrivaldate);
        printf("\n\n");
    }

    fclose(f);
    getchar();
}

void delete_record() {
    system("cls");
    FILE *f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("\n\n\t\t\t\t\t\t!! File Not Found !!");
        printf("\n\n\t\t\t\t\t\tPress any key for main menu.\n");
        getchar();
        return;
    }

    FILE *t = fopen("temp.txt", "w");
    if (t == NULL) {
        printf("\n\n\t\t\t\t\t\t!! File Not Found !!");
        fclose(f);
        printf("\n\n\t\t\t\t\t\tPress any key for main menu.\n");
        getchar();
        return;
    }

    printf("\n\n\t\t\t\t===========>>>>> Hotel Management System <<<<<===========\n\n");
    printf("\t\t\t\t         =========>>>>> Delete Record <<<<<=========          \n");
    printf("\t\t\t\t    ==================================================       \n");
    printf("\n\n\t\t\t\tEnter the Room Number to be deleted from the database: ");
    char roomnumber[20];
    fgets(roomnumber, sizeof(roomnumber), stdin);

    int found = 0;
    while (fread(&s, sizeof(s), 1, f)) {
        if (strcmp(s.roomnumber, roomnumber) != 0) {
            fwrite(&s, sizeof(s), 1, t);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(t);

    remove("add.txt");
    rename("temp.txt", "add.txt");

    if (found) {
        printf("\n\n\t\t\t\tThe Customer is successfully removed....");
    } else {
        printf("\n\n\t\t\tRecords of Customer in this Room not found!");
    }

    printf("\n\n\t\t\t\tPress any key to return to main menu.\n");
    getchar();
}

void search() {
    system("cls");
    printf("\n\n\t\t\t\t===========>>>>> Hotel Management System <<<<<===========\n\n");
    printf("\t\t\t\t         =========>>>>> Search Record <<<<<=========          \n");
    printf("\t\t\t\t===========================================================        \n");

    FILE *f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("\n\n\t\t\t\t\t\t!! File Not Found !!");
        printf("\n\n\t\t\t\t\t\tPress any key for main menu.\n");
        getchar();
        return;
    }

    char roomnumber[20];
    printf("\n\n\t\t\t\tEnter Room number: ");
    fgets(roomnumber, sizeof(roomnumber), stdin);

    int flag = 0;
    while (fread(&s, sizeof(s), 1, f)) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            flag = 1;
            printf("\n\t\t\t\t\a  Record Found\n");
            printf("\n\t\t\t\t  Name         = %s", s.name);
            printf("\n\t\t\t\t  Address      = %s", s.address);
            printf("\n\t\t\t\t  Phone number = %s", s.phonenumber);
            printf("\n\t\t\t\t  Nationality  = %s", s.nationality);
            printf("\n\t\t\t\t  Email        = %s", s.email);
            printf("\n\t\t\t\t  Period       = %s", s.period);
            printf("\n\t\t\t\t  Arrival date = %s", s.arrivaldate);
            printf("\n\n");
            break;
        }
    }

    if (!flag) {
        printf("\n\t\t\t\tNo customer record found for Room %s", roomnumber);
    }

    fclose(f);
    printf("\n\n\t\t\t\tPress any key to return to main menu.\n");
    getchar();
}
