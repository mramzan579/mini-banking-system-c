/*
 * banking_system.c
 * Mini Banking System 
 * Add deposit_money() and withdraw_money() so the user
 * can add or remove funds from any account.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constants
#define MAX_ACCOUNTS  50
#define NAME_LEN      50
#define TYPE_LEN      20
#define FILE_NAME     "accounts.txt"

//Account struct
struct Account {
    int   accountNumber;
    char  name[NAME_LEN];
    char  type[TYPE_LEN];
    float balance;
};

/* ── Global account list 
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
================================================================ */
void create_account(void)
{
    int   i;
    int   new_number;
    float opening_balance;

    if (account_count >= MAX_ACCOUNTS) {
        printf("\n  Account limit reached! Cannot create more accounts.\n");
        return;
    }

    printf("\n--- Create New Account ---\n");

    printf("  Enter account number     : ");
    scanf("%d", &new_number);
    clear_input_buffer();

    if (new_number <= 0) {
        printf("\n  Invalid! Account number must be a positive number.\n");
        return;
    }

    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == new_number) {
            printf("\n  Account %d already exists!\n", new_number);
            return;
        }
    }

    accounts[account_count].accountNumber = new_number;

    printf("  Enter account holder name : ");
    fgets(accounts[account_count].name, NAME_LEN, stdin);
    accounts[account_count].name[strcspn(accounts[account_count].name, "\n")] = '\0';

    printf("  Account type (Savings / Current) : ");
    fgets(accounts[account_count].type, TYPE_LEN, stdin);
    accounts[account_count].type[strcspn(accounts[account_count].type, "\n")] = '\0';

    printf("  Enter opening balance    : ");
    scanf("%f", &opening_balance);
    clear_input_buffer();

    if (opening_balance < 0) {
        printf("\n  Invalid! Opening balance cannot be negative.\n");
        return;
    }

    accounts[account_count].balance = opening_balance;
    account_count++;

    printf("\n  Account created successfully!\n");
    printf("  Account Number : %d\n",   new_number);
    printf("  Account Holder : %s\n",   accounts[account_count - 1].name);
    printf("  Account Type   : %s\n",   accounts[account_count - 1].type);
    printf("  Opening Balance: %.2f\n", opening_balance);
    printf("  Total accounts : %d\n",   account_count);
}

/* ================================================================
   view_accounts()
   Prints all accounts in a clean formatted table.
================================================================ */
void view_accounts(void)
{
    int i;

    printf("\n--- All Accounts ---\n");

    if (account_count == 0) {
        printf("  No accounts found. Create an account first.\n");
        return;
    }

    printf("  Total accounts: %d\n\n", account_count);
    printf("  %-10s %-25s %-10s %s\n",
           "Acc No.", "Name", "Type", "Balance");
    printf("  --------------------------------------------------------\n");

    for (i = 0; i < account_count; i++) {
        printf("  %-10d %-25s %-10s %.2f\n",
               accounts[i].accountNumber,
               accounts[i].name,
               accounts[i].type,
               accounts[i].balance);
    }

    printf("  --------------------------------------------------------\n");
}

/* ================================================================
   search_account()
   Searches for a single account by its account number.
================================================================ */
void search_account(void)
{
    int i;
    int search_number;
    int found = 0;

    printf("\n--- Search Account ---\n");

    if (account_count == 0) {
        printf("  No accounts to search. Create an account first.\n");
        return;
    }

    printf("  Enter account number to search: ");
    scanf("%d", &search_number);
    clear_input_buffer();

    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == search_number) {
            printf("\n  Account found:\n");
            printf("  ----------------------------------------\n");
            printf("    Account Number : %d\n",   accounts[i].accountNumber);
            printf("    Name           : %s\n",   accounts[i].name);
            printf("    Type           : %s\n",   accounts[i].type);
            printf("    Balance        : %.2f\n", accounts[i].balance);
            printf("  ----------------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n  Account %d not found.\n", search_number);
    }
}

/* ================================================================
   deposit_money()
   Finds an account by number and adds the deposit amount
   directly to the current balance using +=
   Validates:
     — deposit amount must be greater than zero
     — account must exist before depositing
================================================================ */
void deposit_money(void)
{
    int   i;
    int   acc_number;
    float amount;
    int   found = 0;

    printf("\n--- Deposit Money ---\n");

    if (account_count == 0) {
        printf("  No accounts found. Create an account first.\n");
        return;
    }

    printf("  Enter account number : ");
    scanf("%d", &acc_number);
    clear_input_buffer();

    printf("  Enter deposit amount : ");
    scanf("%f", &amount);
    clear_input_buffer();

    /* Deposit amount must be greater than zero */
    if (amount <= 0) {
        printf("\n  Invalid! Deposit amount must be greater than zero.\n");
        return;
    }

    /* Find the account and update its balance */
    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == acc_number) {

            accounts[i].balance += amount;   /* add to existing balance */

            printf("\n  Deposit successful!\n");
            printf("  ----------------------------------------\n");
            printf("  Account Number : %d\n",   accounts[i].accountNumber);
            printf("  Account Holder : %s\n",   accounts[i].name);
            printf("  Amount Deposited: %.2f\n", amount);
            printf("  New Balance    : %.2f\n", accounts[i].balance);
            printf("  ----------------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n  Account %d not found.\n", acc_number);
    }
}

/* ================================================================
   withdraw_money()
   Finds an account by number and subtracts the withdrawal
   amount from the balance using -=
   Validates:
     — withdrawal amount must be greater than zero
     — account must have sufficient balance before withdrawing
     — account must exist
================================================================ */
void withdraw_money(void)
{
    int   i;
    int   acc_number;
    float amount;
    int   found = 0;

    printf("\n--- Withdraw Money ---\n");

    if (account_count == 0) {
        printf("  No accounts found. Create an account first.\n");
        return;
    }

    printf("  Enter account number    : ");
    scanf("%d", &acc_number);
    clear_input_buffer();

    printf("  Enter withdrawal amount : ");
    scanf("%f", &amount);
    clear_input_buffer();

    /* Withdrawal amount must be greater than zero */
    if (amount <= 0) {
        printf("\n  Invalid! Withdrawal amount must be greater than zero.\n");
        return;
    }

    /* Find the account */
    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == acc_number) {

            /* Check sufficient balance BEFORE subtracting */
            if (amount > accounts[i].balance) {
                printf("\n  Insufficient balance!\n");
                printf("  ----------------------------------------\n");
                printf("  Available Balance : %.2f\n", accounts[i].balance);
                printf("  Requested Amount  : %.2f\n", amount);
                printf("  ----------------------------------------\n");
            } else {
                accounts[i].balance -= amount;   /* subtract from balance */

                printf("\n  Withdrawal successful!\n");
                printf("  ----------------------------------------\n");
                printf("  Account Number  : %d\n",   accounts[i].accountNumber);
                printf("  Account Holder  : %s\n",   accounts[i].name);
                printf("  Amount Withdrawn: %.2f\n", amount);
                printf("  New Balance     : %.2f\n", accounts[i].balance);
                printf("  ----------------------------------------\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n  Account %d not found.\n", acc_number);
    }
}

/* ── Main ───────────────────────────────────────────────────── */
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
            case 1: create_account();  break;
            case 2: view_accounts();   break;
            case 3: search_account();  break;
            case 4: deposit_money();   break;
            case 5: withdraw_money();  break;
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