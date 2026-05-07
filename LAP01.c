#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// ================================================================
//                        STRUCTURES
// ================================================================

struct Date {
    int day, month, year;
};

struct Client {
    int id;
    char name[30];
    char firstName[30];
    struct Date birthDate;
    char address[50];
    char tel[15];
};

struct Account {
    int clientId;
    char accountType;
    float balance;
    bool blocked;
};

struct Client clients[100];
struct Account accounts[100];
int clientCount = 0;

// ================================================================
//                  LAB 01 - Client Management
// ================================================================

void addClient() {
    printf("\n--- Add New Client ---\n");

    printf("Enter ID: ");
    scanf("%d", &clients[clientCount].id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == clients[clientCount].id) {
            printf("Error: ID already exists!\n");
            return;
        }
    }

    printf("Enter Last Name: ");
    scanf("%s", clients[clientCount].name);

    printf("Enter First Name: ");
    scanf("%s", clients[clientCount].firstName);

    printf("Enter Birth Date (dd mm yyyy): ");
    scanf("%d %d %d",
        &clients[clientCount].birthDate.day,
        &clients[clientCount].birthDate.month,
        &clients[clientCount].birthDate.year);

    printf("Enter Address: ");
    scanf(" %[^\n]", clients[clientCount].address);

    printf("Enter Phone: ");
    scanf("%s", clients[clientCount].tel);

    printf("Enter Account Type (P=Individual / M=Minor / C=Commercial): ");
    scanf(" %c", &accounts[clientCount].accountType);

    char type = accounts[clientCount].accountType;

    if (type == 'P') {
        int age = 2024 - clients[clientCount].birthDate.year;
        if (age < 18) {
            printf("Error: Individual account requires age 18+!\n");
            return;
        }
    }
    else if (type == 'M') {
        int guardianId;
        printf("Enter Guardian ID: ");
        scanf("%d", &guardianId);
        bool found = false;
        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == guardianId) {
                found = true;
                break;
            }
        }
        if (!found) {
            printf("Error: Guardian must have an account in this bank!\n");
            return;
        }
    }
    else if (type != 'C') {
        printf("Error: Invalid account type!\n");
        return;
    }

    accounts[clientCount].clientId = clients[clientCount].id;
    accounts[clientCount].balance = 0;
    accounts[clientCount].blocked = false;

    clientCount++;
    printf("Client added successfully!\n");
}

void searchClient() {
    printf("\n--- Search Client ---\n");
    int id;
    printf("Enter Client ID: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            printf("\n--- Client Found ---\n");
            printf("ID           : %d\n", clients[i].id);
            printf("Name         : %s %s\n", clients[i].name, clients[i].firstName);
            printf("Birth Date   : %02d/%02d/%d\n",
                clients[i].birthDate.day,
                clients[i].birthDate.month,
                clients[i].birthDate.year);
            printf("Address      : %s\n", clients[i].address);
            printf("Phone        : %s\n", clients[i].tel);
            printf("Account Type : %c\n", accounts[i].accountType);
            printf("Balance      : %.2f\n", accounts[i].balance);
            printf("Status       : %s\n", accounts[i].blocked ? "Blocked" : "Active");
            return;
        }
    }
    printf("Client not found!\n");
}

void modifyClient() {
    printf("\n--- Modify Client ---\n");
    int id;
    printf("Enter Client ID: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            printf("Enter New Last Name: ");
            scanf("%s", clients[i].name);
            printf("Enter New First Name: ");
            scanf("%s", clients[i].firstName);
            printf("Enter New Address: ");
            scanf(" %[^\n]", clients[i].address);
            printf("Enter New Phone: ");
            scanf("%s", clients[i].tel);
            printf("Client modified successfully!\n");
            return;
        }
    }
    printf("Client not found!\n");
}

void deleteClient() {
    printf("\n--- Delete Client ---\n");
    int id;
    printf("Enter Client ID: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            for (int j = i; j < clientCount - 1; j++) {
                clients[j] = clients[j + 1];
                accounts[j] = accounts[j + 1];
            }
            clientCount--;
            printf("Client deleted successfully!\n");
            return;
        }
    }
    printf("Client not found!\n");
}

// ================================================================
//               LAB 02 - Bank Account Operations
// ================================================================

void deposit() {
    printf("\n--- Deposit ---\n");
    int id;
    float amount;
    printf("Enter Client ID: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            if (accounts[i].blocked) {
                printf("Error: Account is blocked!\n");
                return;
            }
            printf("Enter Amount: ");
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("Error: Amount must be positive!\n");
                return;
            }
            accounts[i].balance += amount;
            printf("Deposit successful! New Balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Client not found!\n");
}

void withdraw() {
    printf("\n--- Withdraw ---\n");
    int id;
    float amount;
    printf("Enter Client ID: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            if (accounts[i].blocked) {
                printf("Error: Account is blocked!\n");
                return;
            }
            printf("Enter Amount: ");
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("Error: Amount must be positive!\n");
                return;
            }
            if (amount > accounts[i].balance) {
                printf("Error: Insufficient balance!\n");
                return;
            }
            accounts[i].balance -= amount;
            printf("Withdrawal successful! New Balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Client not found!\n");
}

void transfer() {
    printf("\n--- Transfer ---\n");
    int id_sender, id_receiver;
    float amount;
    int idx_sender = -1, idx_receiver = -1;

    printf("Enter Sender ID: ");
    scanf("%d", &id_sender);
    printf("Enter Receiver ID: ");
    scanf("%d", &id_receiver);
    printf("Enter Amount: ");
    scanf("%f", &amount);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id_sender)   idx_sender = i;
        if (clients[i].id == id_receiver) idx_receiver = i;
    }

    if (idx_sender == -1 || idx_receiver == -1) {
        printf("Error: One or both clients not found!\n");
        return;
    }
    if (accounts[idx_sender].blocked) {
        printf("Error: Sender account is blocked!\n");
        return;
    }
    if (amount <= 0) {
        printf("Error: Amount must be positive!\n");
        return;
    }
    if (amount > accounts[idx_sender].balance) {
        printf("Error: Insufficient balance!\n");
        return;
    }

    accounts[idx_sender].balance -= amount;
    accounts[idx_receiver].balance += amount;
    printf("Transfer successful!\n");
    printf("Sender New Balance   : %.2f\n", accounts[idx_sender].balance);
    printf("Receiver New Balance : %.2f\n", accounts[idx_receiver].balance);
}

void modifyAccountType() {
    printf("\n--- Modify Account Type ---\n");
    int id;
    printf("Enter Client ID: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            printf("Current Account Type: %c\n", accounts[i].accountType);
            printf("Enter New Account Type (P/M/C): ");
            scanf(" %c", &accounts[i].accountType);
            printf("Account type modified successfully!\n");
            return;
        }
    }
    printf("Client not found!\n");
}

void accountInquiry() {
    printf("\n--- Account Inquiry ---\n");
    int id;
    printf("Enter Client ID: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            printf("\n=== Account Details ===\n");
            printf("Client ID    : %d\n", clients[i].id);
            printf("Name         : %s %s\n", clients[i].name, clients[i].firstName);
            printf("Account Type : %c\n", accounts[i].accountType);
            printf("Balance      : %.2f\n", accounts[i].balance);
            printf("Status       : %s\n", accounts[i].blocked ? "Blocked" : "Active");
            return;
        }
    }
    printf("Client not found!\n");
}

// ================================================================
//               LAB 03 - File Integration
// ================================================================

void saveToFile() {
    FILE *f = fopen("bank_data.txt", "w");
    if (f == NULL) {
        printf("Error: Cannot open file!\n");
        return;
    }
    fprintf(f, "%d\n", clientCount);
    for (int i = 0; i < clientCount; i++) {
        fprintf(f, "%d %s %s %d %d %d %s %s %c %.2f %d\n",
            clients[i].id,
            clients[i].name,
            clients[i].firstName,
            clients[i].birthDate.day,
            clients[i].birthDate.month,
            clients[i].birthDate.year,
            clients[i].address,
            clients[i].tel,
            accounts[i].accountType,
            accounts[i].balance,
            accounts[i].blocked);
    }
    fclose(f);
    printf("Data saved successfully!\n");
}

void loadFromFile() {
    FILE *f = fopen("bank_data.txt", "r");
    if (f == NULL) return;

    fscanf(f, "%d", &clientCount);
    for (int i = 0; i < clientCount; i++) {
        fscanf(f, "%d %s %s %d %d %d %s %s %c %f %d",
            &clients[i].id,
            clients[i].name,
            clients[i].firstName,
            &clients[i].birthDate.day,
            &clients[i].birthDate.month,
            &clients[i].birthDate.year,
            clients[i].address,
            clients[i].tel,
            &accounts[i].accountType,
            &accounts[i].balance,
            (int*)&accounts[i].blocked);
        accounts[i].clientId = clients[i].id;
    }
    fclose(f);
    printf("Data loaded successfully!\n");
}

// ================================================================
//                        MAIN
// ================================================================

int main() {
    int choice;

    loadFromFile(); // تحميل البيانات عند بداية البرنامج

    while (1) {
        printf("\n==============================\n");
        printf("      BANK MANAGEMENT\n");
        printf("==============================\n");
        printf("--- LAB 01 ---\n");
        printf("1. Add Client\n");
        printf("2. Search Client\n");
        printf("3. Modify Client\n");
        printf("4. Delete Client\n");
        printf("--- LAB 02 ---\n");
        printf("5. Deposit\n");
        printf("6. Withdraw\n");
        printf("7. Transfer\n");
        printf("8. Modify Account Type\n");
        printf("9. Account Inquiry\n");
        printf("--- LAB 03 ---\n");
        printf("10. Save Data to File\n");
        printf("11. Load Data from File\n");
        printf("==============================\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  addClient();         saveToFile(); break;
            case 2:  searchClient();                    break;
            case 3:  modifyClient();      saveToFile(); break;
            case 4:  deleteClient();      saveToFile(); break;
            case 5:  deposit();           saveToFile(); break;
            case 6:  withdraw();          saveToFile(); break;
            case 7:  transfer();          saveToFile(); break;
            case 8:  modifyAccountType(); saveToFile(); break;
            case 9:  accountInquiry();                  break;
            case 10: saveToFile();                      break;
            case 11: loadFromFile();                    break;
            case 0:
                saveToFile();
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}