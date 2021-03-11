// no cheating, mates ;)

#include <stdio.h>
// for input and output
#include <stdlib.h>
#include <string.h>
// to access string function to be able to use strcmp() and strcpy() function
#include <stdbool.h>
// for boolean
#include "../controllers/controllers.h"
// to access controllers or functions related to the data structure model (e.g., Priority Queue functions)
#include "../controllers/utils.h"
// to access addition functions ,such as printTitle and clearScreen functions

void initialContent()
{
    insertDocument("Queue.doc", 345);
    insertDocument("Linked List.doc", 580);
    insertDocument("Array.doc", 230);
    insertDocument("Stack.doc", 580);
    insertDocument("Tree.doc", 230);
}

void registerNewDocument() // Menu 1: Register New Document Function
{
    char docName[255];
    // char docDomain[255];
    int docSize;

    clearScreen();
    puts("Register New Document");
    puts("--------------------------------------------");
    puts("");

    do
    {
        printf("Input document name [*.doc]: ");
        scanf("%s", docName); getchar();
        // int len = strlen(docName);
    } while (docName[strlen(docName) - 4] != '.' || docName[strlen(docName) - 3] != 'd' || docName[strlen(docName) - 2] != 'o' || docName[strlen(docName) - 1] != 'c');

    do
    {
        printf("Input document size [1-9999 kB]: ");
        scanf("%d", &docSize); getchar();
    } while (docSize < 1 || docSize > 9999);

    insertDocument(docName, docSize);
    puts("Success registered new document!");
    puts("");
    printf("Press enter to continue...");
    getchar(); // to catch one enter key from user
}

void removeDocument() // Menu 2: Remove Document Function
{
    char deletedFileName[255];
        
    clearScreen();
    printf("Input document name: ");
    scanf("%[^\n]", deletedFileName); getchar(); // if I don't add getchar(), it won't show any error messages
    deleteDocument(deletedFileName);
    puts("");
    printf("Press enter to continue...");
    getchar(); // to catch one enter key from user
}

/*
void viewExistingFile() // Menu 3: View Existing File Function
{
    clearScreen();
    puts("View Existing File");
    puts("--------------------------------------------");
    view();
    // getchar(); // to catch one enter key
}
*/

void exitFileManager() // Menu 4: Exit Function
{
    clearScreen();
    popAll(); // remove all stored file data from memory
}


void mainMenu()
{
    int option;
    printTitle();
    bool isValid = true;

    while (isValid) // this is taught by a lab assistant when I join pretraining. What I understand from him is that it's used to display or run the program as long as it's still valid. Whenever we exit every menu, the main menu option screen will still be displayed because it's still valid.
    {
        clearScreen();
        puts("1. Register New Document");
        puts("2. Remove Document");
        puts("3. View Existing File");
        puts("4. Exit");
        // printf("Choose: ");
        do
        {
            printf("Choose: ");
            scanf("%d", &option);
            getchar(); // we shall put this getchar() or otherwise, when I test, it can't display Menu 3 (View Existing Files)
        } while (option < 1 || option > 4);

        // MENUS
        if (option == 1) // Menu 1: Register New Document
        {
            registerNewDocument();
        }

        else if (option == 2) // Menu 2: Remove Document
        {
            removeDocument();
        }

        else if (option == 3) // Menu 3: View Existing File (Error: cannot display Menu 3)
        {
            // viewExistingFile();
            view();
        }

        else // Menu 4: Exit
        {
            exitFileManager();
            isValid = false; // so that the program won't be runned or displayed anymore
            getchar(); // to catch one enter key from user
            exit(0); // exit with no error
        }
    }
}


int main()
{
    initialContent();
    mainMenu();
    // view();
    /*
    view();
    popDocument("Alark.doc");
    view();
    popAll();
    view();
    */

    return 0;
}

// no cheating, mates ;)
