/*
 * banking_system.c
 *
 * A console-based Mini Banking System written in C.
 * Create accounts, deposit, withdraw, search, delete,
 * and save records to a file.
 *
 * Compile : gcc banking_system.c -o banking
 * Run     : ./banking
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Constants ─────────── */
#define MAX_ACCOUNTS  50
#define NAME_LEN      50
#define TYPE_LEN      20
#define FILE_NAME     "accounts.txt"
#define MIN_BALANCE   0.0f    /* minimum allowed opening balance  */
#define MIN_AMOUNT    0.01f   /* minimum allowed transaction amount */

/* ── Account struct ─────────────── */
struct Account {
    int   accountNumber;
    char  name[NAME_LEN];
    char  type[TYPE_LEN];
    float balance;
};

/* ── Global account list ────────── */
struct Account accounts[MAX_ACCOUNTS];
int account_count = 0;

/* ================================================================
   clear_input_buffer()
   Drains leftover characters from stdin after every scanf.
   Prevents input bugs when switching between numbers and strings.
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
   Called at the start of every loop in main().
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
   is_valid_type()
   Checks if the account type entered is either
   "Savings" or "Current" — case insensitive check
   using strcmp on both options.
   Returns 1 if valid, 0 if not.
================================================================ */
int is_valid_type(const char *type)
{
    if (strcmp(type, "Savings") == 0 || strcmp(type, "savings") == 0 ||
        strcmp(type, "Current") == 0 || strcmp(type, "current") == 0) {
        return 1;
    }
    return 0;
}

/* ================================================================
   create_account()
   Creates a new bank account and adds it to the array.
   Improved validation:
     — account number must be positive
     — no duplicate account numbers
     — name cannot be empty
     — type must be Savings or Current
     — opening balance cannot be negative
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

    /* Read and validate account number */
    printf("  Enter account number     : ");
    if (scanf("%d", &new_number) != 1 || new_number <= 0) {
        clear_input_buffer();
        printf("\n  Invalid! Account number must be a positive number.\n");
        return;
    }
    clear_input_buffer();

    /* Check for duplicate */
    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == new_number) {
            printf("\n  Account %d already exists!\n", new_number);
            return;
        }
    }

    accounts[account_count].accountNumber = new_number;

    /* Read and validate name — cannot be empty */
    printf("  Enter account holder name : ");
    fgets(accounts[account_count].name, NAME_LEN, stdin);
    accounts[account_count].name[strcspn(accounts[account_count].name, "\n")] = '\0';

    if (strlen(accounts[account_count].name) == 0) {
        printf("\n  Invalid! Name cannot be empty.\n");
        return;
    }

    /* Read and validate account type */
    printf("  Account type (Savings / Current) : ");
    fgets(accounts[account_count].type, TYPE_LEN, stdin);
    accounts[account_count].type[strcspn(accounts[account_count].type, "\n")] = '\0';

    if (!is_valid_type(accounts[account_count].type)) {
        printf("\n  Invalid type! Please enter Savings or Current.\n");
        return;
    }

    /* Read and validate opening balance */
    printf("  Enter opening balance    : ");
    if (scanf("%f", &opening_balance) != 1 || opening_balance < MIN_BALANCE) {
        clear_input_buffer();
        printf("\n  Invalid! Opening balance cannot be negative.\n");
        return;
    }
    clear_input_buffer();

    accounts[account_count].balance = opening_balance;
    account_count++;

    printf("\n  Account created successfully!\n");
    printf("  ----------------------------------------\n");
    printf("  Account Number : %d\n",   new_number);
    printf("  Account Holder : %s\n",   accounts[account_count - 1].name);
    printf("  Account Type   : %s\n",   accounts[account_count - 1].type);
    printf("  Opening Balance: %.2f\n", opening_balance);
    printf("  Total accounts : %d\n",   account_count);
    printf("  ----------------------------------------\n");
}

/* ================================================================
   view_accounts()
   Prints all accounts in a clean formatted table.
   Shows account number, name, type, and balance.
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
   Prints full account details if found.
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
    if (scanf("%d", &search_number) != 1) {
        clear_input_buffer();
        printf("\n  Invalid input! Please enter a number.\n");
        return;
    }
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
   Finds an account by number and adds the deposit amount.
   Improved: checks scanf return value for non-numeric input.
   Minimum deposit is MIN_AMOUNT (0.01).
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
    if (scanf("%d", &acc_number) != 1) {
        clear_input_buffer();
        printf("\n  Invalid input! Please enter a number.\n");
        return;
    }
    clear_input_buffer();

    printf("  Enter deposit amount : ");
    if (scanf("%f", &amount) != 1 || amount < MIN_AMOUNT) {
        clear_input_buffer();
        printf("\n  Invalid! Deposit must be at least %.2f.\n", MIN_AMOUNT);
        return;
    }
    clear_input_buffer();

    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == acc_number) {
            accounts[i].balance += amount;
            printf("\n  Deposit successful!\n");
            printf("  ----------------------------------------\n");
            printf("  Account Number  : %d\n",   accounts[i].accountNumber);
            printf("  Account Holder  : %s\n",   accounts[i].name);
            printf("  Amount Deposited: %.2f\n", amount);
            printf("  New Balance     : %.2f\n", accounts[i].balance);
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
   Finds an account by number and subtracts the withdrawal.
   Improved: checks scanf return value for non-numeric input.
   Minimum withdrawal is MIN_AMOUNT (0.01).
   Checks sufficient balance before withdrawing.
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
    if (scanf("%d", &acc_number) != 1) {
        clear_input_buffer();
        printf("\n  Invalid input! Please enter a number.\n");
        return;
    }
    clear_input_buffer();

    printf("  Enter withdrawal amount : ");
    if (scanf("%f", &amount) != 1 || amount < MIN_AMOUNT) {
        clear_input_buffer();
        printf("\n  Invalid! Withdrawal must be at least %.2f.\n", MIN_AMOUNT);
        return;
    }
    clear_input_buffer();

    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == acc_number) {
            if (amount > accounts[i].balance) {
                printf("\n  Insufficient balance!\n");
                printf("  ----------------------------------------\n");
                printf("  Available Balance : %.2f\n", accounts[i].balance);
                printf("  Requested Amount  : %.2f\n", amount);
                printf("  ----------------------------------------\n");
            } else {
                accounts[i].balance -= amount;
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

/* ================================================================
   delete_account()
   Deletes a bank account by its account number.
   Shows all accounts first, asks for confirmation
   before deleting, then uses shift technique.
================================================================ */
void delete_account(void)
{
    int  i, j;
    int  delete_number;
    int  found = 0;
    char confirm;

    printf("\n--- Delete Account ---\n");

    if (account_count == 0) {
        printf("  No accounts to delete. Create an account first.\n");
        return;
    }

    view_accounts();

    printf("\n  Enter account number to delete: ");
    if (scanf("%d", &delete_number) != 1) {
        clear_input_buffer();
        printf("\n  Invalid input! Please enter a number.\n");
        return;
    }
    clear_input_buffer();

    /* Confirmation step — prevents accidental deletion */
    printf("  Are you sure you want to delete account %d? (Y/N): ",
           delete_number);
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm != 'Y' && confirm != 'y') {
        printf("\n  Deletion cancelled.\n");
        return;
    }

    for (i = 0; i < account_count; i++) {
        if (accounts[i].accountNumber == delete_number) {
            for (j = i; j < account_count - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            account_count--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("\n  Account %d deleted successfully!\n", delete_number);
        printf("  Total accounts remaining: %d\n", account_count);
    } else {
        printf("\n  Account %d not found.\n", delete_number);
    }
}

/* ================================================================
   save_accounts()
   Writes all account records to accounts.txt.
   Uses fopen, fprintf, and fclose for file operations.
================================================================ */
void save_accounts(void)
{
    int   i;
    FILE *file;

    if (account_count == 0) {
        printf("\n  No accounts to save. Create an account first.\n");
        return;
    }

    file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        printf("\n  Error! Could not open file for writing.\n");
        return;
    }

    fprintf(file, "========================================\n");
    fprintf(file, "       BANK ACCOUNTS RECORD             \n");
    fprintf(file, "========================================\n");
    fprintf(file, "Total Accounts: %d\n\n", account_count);

    for (i = 0; i < account_count; i++) {
        fprintf(file, "Account %d:\n",              i + 1);
        fprintf(file, "  Account Number : %d\n",   accounts[i].accountNumber);
        fprintf(file, "  Name           : %s\n",   accounts[i].name);
        fprintf(file, "  Type           : %s\n",   accounts[i].type);
        fprintf(file, "  Balance        : %.2f\n", accounts[i].balance);
        fprintf(file, "----------------------------------------\n");
    }

    fclose(file);

    printf("\n  All accounts saved to '%s' successfully!\n", FILE_NAME);
    printf("  Open the file in your project folder to view it.\n");
}

/* ================================================================
   main()
   Entry point. Prints welcome banner and runs the program
   in a loop until the user selects Exit.
================================================================ */
int main(void)
{
    int choice;

    printf("========================================\n");
    printf("       MINI BANKING SYSTEM              \n");
    printf("========================================\n");
    printf("  Manage your bank accounts with ease.\n");
    printf("  Maximum accounts: %d\n", MAX_ACCOUNTS);
    printf("========================================\n");

    do {
        show_menu();

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("\n  Invalid input! Please enter a number.\n");
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: create_account(); break;
            case 2: view_accounts();  break;
            case 3: search_account(); break;
            case 4: deposit_money();  break;
            case 5: withdraw_money(); break;
            case 6: delete_account(); break;
            case 7: save_accounts();  break;
            case 8:
                printf("\n========================================\n");
                printf("  Thank you for using Mini Banking System\n");
                printf("  Goodbye!\n");
                printf("========================================\n\n");
                break;
            default:
                printf("\n  Invalid choice! Please enter 1 to 8.\n");
        }

    } while (choice != 8);

    return 0;
}