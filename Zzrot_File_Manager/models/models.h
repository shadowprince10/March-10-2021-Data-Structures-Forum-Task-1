// double linked list
struct Node
{
    char name[255]; // file name ended with ".doc"
    int fileSize; // file size between 1 and 9999 kB
    Node *prev, *next;
}*first, *last; // global variable of first (head) and last (tail) in our file priority queue

/*
NOTE:
first: top priority / head of our priority queue
last: the lowest priority / tail of our priority queue
*/
