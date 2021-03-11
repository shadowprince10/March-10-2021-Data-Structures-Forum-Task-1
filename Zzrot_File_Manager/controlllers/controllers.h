#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../models/models.h"

// no cheating, mates ;)

// double linked list
Node *createNode(const char* name, int fileSize)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode -> name, name);
    newNode -> fileSize = fileSize;
    return newNode;
}

// push mid is used here since we always insert data based on priority (in this terms, it's file with the biggest size), henceforth with this, we can diplay all files in descending order by file size.
// user files can be deleted by inputting a file name, thus we have to use Pop Mid function. 
// Menu 4: Exit => Pop All function

void pushFirst(const char* name, int fileSize) // similar to push head function in double linked list
{
    Node *node = createNode(name, fileSize);

    if (!first)
    {
        first = last = node;
    }

    else
    {
        first -> prev = node;
        node -> next = first;
        first = node;
    }
}

void pushLast(const char* name, int fileSize) // similar to push tail function in double linked list
{
    Node* node = createNode(name, fileSize);

    if (!first)
    {
        first = last = node;
    }

    else
    {
        node -> prev = last;
        last -> next = node;
        last = node;
    }
}

/*
INSERT DOCUMENT LOGIC:
1. if the file size of our file node we want to insert is equal to the file size in our Priority Queue's top priority / head:
                            B  (the file node we want to insert)
NULL <-  B  ->  <-   B   ->  <-  A  -> NULL
                  current         

As it's stated in the Menu 1 explanation that if there are two or more files with same file size, the later file will be listed after the prior file, then we'll put our new file node after the previous file node with the equal file size.
the next pointer of our file node we want to insert will point to the current node and the previous pointer of our file node we want to insert will point to the node after the current node.

                            B  (the file node we want to insert)
                        /       \
NULL <-  B  ->  <-   B   ->  <-  A  -> NULL
                  current         

We also have to manage current node's and the node after the current node's pointer with directing their next or previous pointer into our file node we want to insert.
From the example above, current -> next currently is A. 
the node after the current node's previous pointer should point to the file node we want to insert and the current's node next pointer should point to the file node we want to insert.

current -> next -> prev = node;
current -> next = node;

We cannot exchange these two codes, however, as the meaning will be different.
If we assign the next pointer of the current node to point to the file node we want to insert, then the current -> next won't be anymore node A, but node B.


2. if the file size of our file we want to insert is equal to the file size in our Priority Queue's lowest priority / tail:

                                        A  (the file node we want to insert)
NULL <-  B  ->  <-   B   ->  <-  A  -> NULL  

We only need to push tail since if there are two or more files with same file size, the later file will be listed after the prior file.
So, when our file node we want to insert has the equal file size as the file node tail, then we'll just put it after the file node tail with the equal file size or in other words, push tail.


3. We put file nodes in descending order by file size as it's stated in the Menu 1 explanation.
Above are logic for cases if our file node we want to insert has the equal size to the file node head and the file node tail.

Case 3: What if the file node we want to insert is less or more a mid priority or the file node we want to insert has the less priority than our top priority file node, but bigger than our lowest priority file node?
Case 4: What if the file node we want to insert has the equal file size to the more or less mid priority file node?

First, we assign current to the first.
Then, we use while loop to make current move from the start to the next node and to the next node until the file size of the file node after the current node is smaller than the file size of the file node we want to insert.

CASE 3: 
                            B  (the file node we want to insert)
NULL <-  D  ->  <-   C   ->  <-  A  -> NULL
                  current

CASE 4: 
                            C  (the file node we want to insert)
NULL <-  D  ->  <-   C   ->  <-  A  -> NULL
                  current

                                       C  (the file node we want to insert)
NULL <-  D  ->  <-   C   ->  <-  C  ->  <-  A  ->  NULL
                  current

So, while the file node after the current file node exists and the file node after the current node has bigger or equal size than the file node we want to insert, then we will keep moving to the next node.
I use "bigger or equal" comparison here, not only bigger, since it's stated in Menu 1 explanations that a file will be put after prior files with the equal size.
So, when a file node has the equal size to the file node we want to insert, we have to keep moving, or otherwise it'll be very hard to manage the pointer.
Also, I add break; so that it'll be easier to manage the pointer of the current file node to the file node I want to insert since it'll stop right before the position where the file node will be inserted.
Try to make the current node stop right before or after the position where the current file node will be inserted so that it'll be easier to manage the current file node pointer and the next/previous pointer of node after/before the current file node pointer.

Imagine this:
                                       C  (the file node we want to insert)
NULL <-  D  ->  <-   C   ->  <-  C  ->  <-  C  ->  <-  C  ->  <-  A  ->  NULL
                  current

while (current -> next && current -> next -> fileSize > fileSize)
{

}

with this:
                                       C  (the file node we want to insert)
NULL <-  D  ->  <-   C   ->  <-  C  ->  <-  C  ->  <-  C  ->  <-  A  ->  NULL
                  current


When the file size of the file node after the current file node is already smaller than the file size of the file node we want to insert, I use break; to go out of the while loop so that the current will stop in its position and won't move to the next node.

the logic will be similar to the first case's logic where we shall make the node's previous pointer points to current node.
*/

void insertDocument(const char* name, int fileSize) // similar to push mid function in double linked list
{
    Node *node = createNode(name, fileSize);

    if (!first) // if there's no node in our file priority queue
    {
        first = last = node; // put the file node immediately in our file priority queue as first (head) and last (tail) 
    }

    else if (fileSize > first -> fileSize)
    {
        pushFirst(name, fileSize);
    }

    /*
    else if (fileSize == first -> fileSize)
    {
        Node *current = first;

        while (current -> next && current -> next -> fileSize == fileSize)
        {
            current = current -> next;
        }

        node -> prev = current;
        node -> next = current -> next;
        current -> next -> prev = node;
        current -> next = node;
    }
    */

    else if (fileSize <= last -> fileSize)
    {
        pushLast(name, fileSize); // when the file node we want to insert has the smaller or equal size to our priority queue's lowest file node priority, then we use push tail function. This will help to print file datas in descending order as the smallest will always be put behind as our lowest priority file node
    }

    else
    {
        Node *current = first;

        while (current -> next && current -> next -> fileSize >= fileSize)
        {
            if (current -> next -> fileSize < fileSize)
            {
                break;
            }

            current = current -> next;
        }

        /*
        node -> prev = current -> prev;
        node -> next = current;
        current -> prev -> next = node;
        current -> prev = node;
        */

        node -> prev = current;
        node -> next = current -> next;
        current -> next -> prev = node;
        current -> next = node;
    }
}

/*
POP DOCUMENT LOGIC

free first, then we make the node NULL
if we make the node NULL first, then it'll be useless to free NULL node

for pop mid function:
similar to push mid function, I use while loop to move current starting from the first node or head in the priority queue.

while current exists and the file name in the current node isn't equal to the file name we want to delete, we'll keep moving current to the next node.
when the file name of the current node is equal to the file name we want to delete, we go out of the while loop

but if till the end of the priority queue, we don't find any file node that we want to delete, then we'll print an error message out and do nothing (return)

B  (the file node we want to delete)
NULL <-  D  ->  <-   C   ->  <-  B  ->  <-  A  ->  NULL
                              current

## Explanation on this coding based on the example I imagined above:
current -> prev -> next = current -> next;
// currently, current -> prev is C since the previous pointer of B points to C. Then, we redirect the next pointer of C (current -> prev -> next) into A, which is a node after the current node which B's next pointer points to (current -> next or B -> next).
current -> next -> prev = current -> prev;
// next, we redirect previous pointer of current -> next (node A) (current -> next -> prev) to point to currently node which previous pointer of node B points to (current -> prev).
current -> prev = current -> next = NULL;
// after we reassign/redirect the pointer of the node before and after the current node (node B), we assign both previous and next pointer of node B to NULL.
free(current);
// then, we delete / free memory of the current node.
*/

void popFirst() // similar to pop head function in double linked list
{
    if (!first)
    {
        return; // do nothing
    }

    else if (first == last) // if there's only one node in our file priority queue,
    {
        // immediately free the node
        free(first);
        first = last = NULL;
    }

    else // if there's one or more node in our file priority queue
    {
        Node *firstCandidate = first -> next; // I make a new pointer variable for the node after our file priority queue's top priority / head as a head replacement
        firstCandidate -> prev = first -> next = NULL;
        free(first);
        // first = NULL;
        first = firstCandidate;
    }
}

void popLast() // similar to pop tail function in double linked list
{
    if (!first) // if there's no file node in our file Priority Queue, which means we have no file node to remove
    {
        return; // do nothing
    }

    else if (first == last) // if there's only one node in our file Priority Queue
    {
        // immediately free the node
        free(first);
        first = last = NULL;
    }

    else
    {
        Node *lastCandidate = last -> prev; // I make a new pointer variable for the node after our file priority queue's lowest priority / tail as a tail replacement
        last -> prev = lastCandidate -> next = NULL;
        free(last);
        // last = NULL;
        last = lastCandidate;
    }
}

void deleteDocument(const char* name) // similar to pop mid function in double linked list
{
    if (!first)
    {
        puts("Data is empty!");
        return;
    }

    else if (strcmp(name, first -> name) == 0)
    {
        popFirst();
        printf("Document: %s is succesfully removed!\n", name);
    }

    else if (strcmp(name, last -> name) == 0)
    {
        popLast();
        printf("Document: %s is succesfully removed!\n", name);
    }

    else
    {
        Node *current = first;

        while (current && strcmp(current -> name, name) != 0)
        {
            current = current -> next;
        }

        if (!current) // if we find no node to remove till the end of our file double linked list
        {
            printf("There is no match document with name: %s\n", name); // show error message as it's stated in details information about Menu 2
            return; // do nothing
        }

        current -> prev -> next = current -> next;
        current -> next -> prev = current -> prev;
        current -> prev = current -> next = NULL;
        free(current);
        // current = NULL;
        printf("Document: %s is succesfully removed!\n", name);
    }
}

void popAll()
{
    while (first) // as long as our file double linked list has head,
    {
        popFirst(); // we push head till our double linked list has no file node anymore
    }
    printf("All data has been succesfully removed!");
}


void view() // Menu 3: View Existing File Function
{
    Node *current = first;
    int number = 1;

    system("clear");
    puts("View Existing File");
    puts("--------------------------------------------");
    puts("");

    while (current)
    {
        printf(" %d. %-30s\t\t%d kB\n", number, current -> name, current -> fileSize);
        // -%30s to print files left aligned
        number++;
        current = current -> next;
    }
    puts("");
    printf("Press enter to continue...");
    getchar(); // to catch one enter key from user
}

// no cheating, mates ;)
