
#include <stdio.h> // Standard Input Output (scanf(), printf()...)
#include <stdlib.h> // Standard Library (malloc(), free()...)


void create(); // function declaration...
void display();
void insertBegin();
void insertEnd();
void insertPos();
void deleteBegin();
void deleteEnd();
void deletePos();
void deleteAll();
int scanValue();
int isEmpty();

struct Node { // declare the structure of the node
    int data; // declare data value
    struct Node * next; // declare pointer to the next node
};

typedef struct Node myNode; // the code is more clear now, we can type "myNode" instead of "struct Node"

myNode *head = NULL; // head is a pointer to the structure Node. Pointer to the structure will always represent first node from the linked list.

int main(){
    int choice;

    while(1){ // while(1) is an infinite loop in C (all integers except of (0) would give same effect)
        printf("\n****************MENU**************************\n");
        printf("|      1.Create first node.                  |\n");
        printf("|      2.Display.                            |\n");
        printf("|      3.Insert at the beginning.            |\n");
        printf("|      4.Insert at the end.                  |\n");
        printf("|      5.Insert at specified position.       |\n");
        printf("|      6.Delete from beginning.              |\n");
        printf("|      7.Delete from the end.                |\n");
        printf("|      8.Delete from specified position.     |\n");
        printf("|      9.Delete all.                         |\n");
        printf("|      10.Exit.                              |\n");
        printf("|____________________________________________|\n");
        printf("\nEnter your choice:");

        choice = scanValue();
        switch(choice){ // switch is a selection statement which lets user to select an output by keying specified int/char
            case 1:
                create(); // function call...
                break;
            case 2:
                display();
                break;
            case 3:
                insertBegin();
                break;
            case 4:
                insertEnd();
                break;
            case 5:
                insertPos();
                break;
            case 6:
                deleteBegin();
                break;
            case 7:
                deleteEnd();
                break;
            case 8:
                deletePos();
                break;
            case 9:
                deleteAll();
                break;
            case 10:
                printf("Goodbye.");
                exit(0);
                break;
            default: // 'default' is run when users type different integer than 1-10
                printf("ERROR: You can type integers between 1 and 10 only. Please try again.");
                break;
        }
    }
    return 0;
}

// function to create a first node
void create() {
    // initialize the nodes
    myNode * temp;

    // allocate memory to 'temp'
    temp=(myNode *)malloc(sizeof(myNode));

    if(temp==NULL) { // Check if the memory has been successfully allocated by malloc or not
        printf("\nOut of Memory Space:\n");
        return; // return to the main function
    }

    if(head==NULL) { // if list is empty
        head=temp; // temp is pointing to the head now
        printf("\nEnter the data value for the node:");
        scanf("%d",&temp->data); // assign scanned value to data
        temp->next=NULL; // the linked list terminates here
        printf("Element %d was added successfully\n", temp->data); // print data which is pointed by pointer temp
    }
    else {
        printf("First node is already created. Please choose another option\n");
        return; // return to the main function
    }
}

// function to display Linked List
void display() {
    // initialize the node, which will be used to print all nodes by sequentially passing by addresses of next nodes to the ptr using loop while
    myNode *ptr;

    if (isEmpty() == 1){
        return; // return to the main function
    }

    ptr=head; // pointer is pointing to the head now
    printf("\nThe List elements are:\n");

    while(ptr!=NULL){ // do until pointer does not exist (=NULL)
        printf("%d\n",ptr->data); // print data which is pointed by pointer ptr
        ptr=ptr->next; // go to the next node (ptr is pointing to the next node now)
    }
}

// function to instert node at the beginning of the list
void insertBegin() {
    // initialize the node
    myNode *temp;

    // allocate memory to 'temp'
    temp=(myNode *)malloc(sizeof(myNode));

    // check if the memory is allocated successfully. Malloc will return value '0' if memory was not allocated successfully in the Heap
    if(temp==NULL){
        printf("\nOut of Memory Space:\n");
        return; // return to the main function
    }

    printf("\nEnter the data value for the node:" );
    scanf("%d",&temp->data);
    temp->next =NULL; // end a node temp

    if(head==NULL) { // if list is empty
        head=temp; // temp is a new head (first element from the linked list)
    }
    else {
        temp->next=head; // connect nodes temp and head
        head=temp; // temp is a new head
    }
    printf("Element %d was added successfully\n", temp->data); // print data which is pointed by pointer temp
}

// function to insert node at the end of the list
void insertEnd() {
    // initialize the nodes
    myNode *temp;
    myNode *ptr;

    //allocate memory to the node
    temp=(myNode *)malloc(sizeof(myNode));

    if(temp==NULL) {
        printf("\nOut of Memory Space:\n");
        return; // return to the main function
    }

    printf("\nEnter the data value for the node:" );
    scanf("%d",&temp->data);
    temp->next =NULL; // end a temporary linked list here, which means you created single stand-alone temporary node

    if(head==NULL) {
        head=temp;
    }
    else {
        ptr=head; // ptr is pointing to the head now
        while(ptr->next !=NULL) { // this loop assigns sequentially the addresses of all nodes in the linked list to the node 'ptr' until
                //the next node does not exit. In result ptr stores address of the last node from linked list
            ptr=ptr->next; // go to the next node (ptr is pointing to the next node now)
        }
        ptr->next =temp; //connect nodes from addresses stored in ptr and temp. In result the last node in our linked stores data addressed by 'temp'.
    }
    printf("Element %d was added successfully\n", temp->data); // print data which is pointed by pointer temp
}

// function to instert a node in a specified position
void insertPos() {
    // initialize the nodes
    myNode *temp;
    myNode *ptr;

    // initialize variables
    int i,pos;

    // allocate memory to the node
    temp=(myNode *)malloc(sizeof(myNode));

    if(temp==NULL) {
        printf("\nOut of Memory Space:\n");
        return; // return to the main function
    }

    if (isEmpty() == 1){
        free(temp); // deallocate the memory
        return; // return to the main function
    }

    printf("\nEnter the position for the new node to be inserted:");
    scanf("%d",&pos); // scan integer that will be assigned to variable pos
    printf("\nEnter the data value of the node:");
    scanf("%d",&temp->data) ; // scan integer that will be stored in address pointed by temp in data.

    temp->next=NULL; // end a temporary linked list here, which means you created single stand-alone temporary node

    if(pos==0) {
        temp->next=head; // connect node temp to the head of linked list
        head=temp; // temp pointing to the head now
    }
    else {
        for(i=0,ptr=head;i<pos-1;i++) { // move pointer ptr to the (selected position - 1) place in our list
            ptr=ptr->next; // go to the next node
            if(ptr==NULL) { // if no data is stored in required position, function returns to the main function
                printf("\nPosition not found\n");
                return; // return to the main function
            }
        }
        temp->next = ptr->next; // store address from the node addressed by ptr in the node addressed by temp
        // (thanks to this move, data stored originally in selected position will be not overwritten)
        ptr->next = temp; // update link part stored in node ptr with address from temp
    }
    printf("Element %d was added successfully to the position:%d\n", temp->data, pos); // print data which is pointed by pointer temp

}

// function to delete first node
void deleteBegin() {
    // initialize the nodes
    myNode *ptr;

    if (isEmpty() == 1){
        return; // return to the main function
    }

    ptr=head; // ptr is pointing to the first element from the list now
    head=head->next; // head is pointing to the second node now
    printf("\nDeleted element:%d\n",ptr->data); // print data which is pointed by pointer ptr
    free(ptr); // deallocate memory for ptr as it is not needed anymore
}

// function to delete last node
void deleteEnd() {
    // initialize the nodes
    myNode *temp;
    myNode *ptr;

    if (isEmpty() == 1){
        return; // return to the main function
    }

    if(head->next ==NULL) { // if linked list has one element only
        ptr=head; // ptr points to the first element from the list
        head=NULL; // remove address of the first node (remove node)
        printf("\nDeleted element:%d\n",ptr->data); // print data which is pointed by pointer ptr
        free(ptr); // deallocate memory for ptr as it is not needed anymore
    }
    else { // if linked list has more than one element
        ptr=head; // ptr points to the first element from the list
        while(ptr->next!=NULL) { // while pointer is pointing to the existing node
            temp=ptr; // temp pointing to the same node as ptr now
            ptr=ptr->next; // ptr pointing to the next node now
        }
        temp->next=NULL; // temp is the last node now
        printf("\nDeleted element:%d\n",ptr->data); // print data which is pointed by pointer ptr
        free(ptr); // deallocate memory for ptr as it is not needed anymore
    }
}

// function to delete specified node
void deletePos() {
    //initialize the nodes
    myNode *temp;
    myNode *ptr;

    //initialize variables
    int i,pos;

    if (isEmpty() == 1){
        return; // return to the main function
    }

    printf("\nEnter the position of the node to be deleted:");
    scanf("%d",&pos);

    if(pos==0) {
        ptr=head; // ptr is pointing to the head now
        head=head->next; // head is pointing to the second node now (in result node pointed by ptr is not connected to the list)
        printf("\nDeleted element:%d from the position:0.",ptr->data); // print data which is pointed by pointer ptr
        free(ptr); // deallocate memory for ptr as it is not needed anymore
    }
    else {
        ptr=head;
        for(i=0;i<pos;i++) {
            temp=ptr; // temp is pointing to the same node as ptr
            ptr=ptr->next; // ptr is pointing to the second node now
            if(ptr==NULL) {
                printf("\nPosition %d not found.", pos);
                return; // return to the main function
            }
        }
        temp->next = ptr->next; // store address from the node addressed by ptr in the node addressed by temp
        printf("\nDeleted element:%d from the position:%d\n",ptr->data,pos);
        free(ptr);
    }
}

// function to delete all nodes
void deleteAll() {
    // initialize the nodes
    myNode *temp;

    if (isEmpty() == 1){
        return; // return to the main function
    }

    while(head != NULL) {
        temp=head;
        head=head->next; // head is pointing to the second node now
        printf("Deleted element:%d\n",temp->data);
        free(temp); // free temp as it is not needed anymore
    }
    printf("List is now empty.\n");

}

// function to scan the value (integer) and stop the program when incorrect data type is keyed. Otherwise, program would run infinitely.
int scanValue(){
    // initialize variable
    int myInteger;

    scanf("%d",&myInteger);

    // if data type is not an integer, value 0 will be assigned to the scanned value.
    if (myInteger==0){
        printf("\n******ERROR: You can key integers only.******\n");
        exit(0); // quit the program
    }
    return myInteger; // return value stored in variable myInteger
}

// if list is empty, return 1, if not, return 0
int isEmpty(){
    if(head==NULL) {
        printf("\nList is Empty.\n");
        return 1; // return value 1
    }

    return 0; // return value 0
}


