/*
 * banking_system.c
 * Mini Banking System
 * Set up the project structure, define the Account struct,
 * and build the main menu system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Constants ──────────────────────────────────────────────── */
#define MAX_ACCOUNTS  50     /* maximum number of accounts allowed */
#define NAME_LEN      50     /* maximum length of account holder   */
#define TYPE_LEN      20     /* maximum length of account type     */
#define FILE_NAME     "accounts.txt"   /* output file name         */

/* ── Account struct ─────────────────────────────────────────── */
/* Groups all information about one bank account in one unit.
   This is the core data structure of the entire program. */
struct Account {
    int   accountNumber;     /* unique account identifier          */
    char  name[NAME_LEN];    /* account holder full name           */
    char  type[TYPE_LEN];    /* Savings or Current                 */
    float balance;           /* current account balance            */
};

/* ── Global account list ────────────────────────────────────── */
struct Account accounts[MAX_ACCOUNTS];  /* holds all accounts     */
int account_count = 0;                  /* how many are stored    */

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

    /* Main loop — keeps running until user picks Exit */
    do {
        show_menu();
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1:
                printf("\n  [Coming soon] Create Account\n");
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