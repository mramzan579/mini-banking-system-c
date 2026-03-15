/*
 * banking_system.c
 * Mini Banking System
 * Add the create_account() function so the user can
 * open a new bank account with number, name, type, and balance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_ACCOUNTS  50
#define NAME_LEN      50
#define TYPE_LEN      20
#define FILE_NAME     "accounts.txt"

// Account struct 
struct Account {
    int   accountNumber;
    char  name[NAME_LEN];
    char  type[TYPE_LEN];
    float balance;
};

//Global account list
struct Account accounts[MAX_ACCOUNTS];
int account_count = 0;

/* ================================================================
   clear_input_buffer()
   Drains leftover characters from stdin after every scanf.
================================================================ */
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ================================================================
   show_menu()
   Prints the main menu options to the console.
================================================================ */
void show_menu(void)
{
    printf("\n========================================\n");
    printf("         MINI BANKING SYSTEM            \n");
    printf("========================================\n");
    printf("  1. Create Account\n");
    printf("  2. View All Accounts\n");
    printf("  3. Search Account\n");
    printf("  4. Deposit Money\n");
    printf("  5. Withdraw Money\n");
    printf("  6. Delete Account\n");
    printf("  7. Save Accounts to File\n");
    printf("  8. Exit\n");
    printf("========================================\n");
    printf("  Enter your choice: ");
}

/* ================================================================
   create_account()
   Creates a new bank account and adds it to the array.
   Reads account number, holder name, account type,
   and opening balance from the user.
   Validates:
     — account number must be a positive number
     — account number must not already exist
     — opening balance cannot be negative
================================================================ */
void create_account(void)
{
    int   i;
    int   new_number;
    float opening_balance;

    /* Stop if the account list is full */
    if (account_count >= MAX_ACCOUNTS) {
        printf("\n  Account limit reached! Cannot create more accounts.\n");
        return;
    }

    printf("\n--- Create New Account ---\n");

    /* Read and validate account number */
    printf("  Enter account number     : ");
    scanf("%d", &new_number);
    clear_input_buffer();

    /* Account number must be a positive integer */
    if (new_number <= 0) {
        printf("\n  Invalid! Account number must be a positive number.\n");
        return;
    }

    /* Check for duplicate account number */
    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == new_number) {
            printf("\n  Account %d already exists!\n", new_number);
            return;
        }
    }

    /* Save the account number — it passed all checks */
    accounts[account_count].accountNumber = new_number;

    /* Read account holder name */
    printf("  Enter account holder name : ");
    fgets(accounts[account_count].name, NAME_LEN, stdin);
    accounts[account_count].name[strcspn(accounts[account_count].name, "\n")] = '\0';

    /* Read account type — Savings or Current */
    printf("  Account type (Savings / Current) : ");
    fgets(accounts[account_count].type, TYPE_LEN, stdin);
    accounts[account_count].type[strcspn(accounts[account_count].type, "\n")] = '\0';

    /* Read and validate opening balance */
    printf("  Enter opening balance    : ");
    scanf("%f", &opening_balance);
    clear_input_buffer();

    /* Balance cannot be negative */
    if (opening_balance < 0) {
        printf("\n  Invalid! Opening balance cannot be negative.\n");
        return;
    }

    /* Save balance and register the account */
    accounts[account_count].balance = opening_balance;
    account_count++;

    printf("\n  Account created successfully!\n");
    printf("  Account Number : %d\n", new_number);
    printf("  Account Holder : %s\n", accounts[account_count - 1].name);
    printf("  Account Type   : %s\n", accounts[account_count - 1].type);
    printf("  Opening Balance: %.2f\n", opening_balance);
    printf("  Total accounts : %d\n", account_count);
}

//─ Main
int main(void)
{
    int choice;

    /* Welcome banner */
    printf("========================================\n");
    printf("       MINI BANKING SYSTEM              \n");
    printf("========================================\n");
    printf("  Manage your bank accounts with ease.\n");
    printf("  Maximum accounts: %d\n", MAX_ACCOUNTS);
    printf("========================================\n");

    /* Main loop */
    do {
        show_menu();
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                printf("\n  [Coming soon] View All Accounts\n");
                break;
            case 3:
                printf("\n  [Coming soon] Search Account\n");
                break;
            case 4:
                printf("\n  [Coming soon] Deposit Money\n");
                break;
            case 5:
                printf("\n  [Coming soon] Withdraw Money\n");
                break;
            case 6:
                printf("\n  [Coming soon] Delete Account\n");
                break;
            case 7:
                printf("\n  [Coming soon] Save to File\n");
                break;
            case 8:
                printf("\n  Goodbye!\n");
                break;
            default:
                printf("\n  Invalid choice! Please enter 1 to 8.\n");
        }

    } while (choice != 8);

    return 0;
}