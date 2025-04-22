/* Name    : Osaid Hasan Nur
 * ID      : 1210733
 * Section : 1
 * Instructor : Ahmad Abusnaina
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tnode *BST;
typedef struct nodell *linked_list;

// Function Prototype
// Binary Search tree Functions
BST makeEmpty(BST);
BST Find(int,BST);
BST insert(int, char [], char [], int , char [], BST );
BST Min(BST );
BST Max(BST );
BST delete(int , BST );
void Save_To_File(BST );
void copy(linked_list , BST );

// linked list functions
linked_list new_linked_list(linked_list);
void insert_First(int , char[], char [], int , char [], linked_list);
void insert_Last(int , char [], char [], int , char [], linked_list);
void deleteList(linked_list);
void print_List(linked_list);
linked_list split(linked_list );
linked_list Sort_Name(linked_list );
linked_list Sort_Class(linked_list );
linked_list merge_Name(linked_list , linked_list);
linked_list merge_Class(linked_list , linked_list );

// define the nodes for both BST and linked list
struct tnode
{
    int ID;
    char name[1000];
    char address[1000];
    int classID;
    char date_of_enrollment[15];
    BST right;
    BST left;
};
struct nodell
{
    int ID;
    char name[1000];
    char address[1000];
    int classID;
    char date_of_enrollment[15];
    linked_list next;
    linked_list prev;
};

FILE *input, *output;
int main()
{
    printf("***************** Welcome to the School system ***********************\n");
    input = fopen("students.txt", "r");

    //construct an empty BST
    BST students = NULL;
    // define linked lists to store the sorted data , "byName" stores the data sorted by name
    // "byCity" stores the data of student who lives in specific city (have the same address)
    // "classes"
    linked_list byName = new_linked_list(byName);
    linked_list byCity = new_linked_list(byCity);
    linked_list classes = new_linked_list(classes);

    // load the content of the file named students.txt to the tree
    int count = 0;
    while (!feof(input) && count <= 1)
    {
        int id = 0, class_id = 0;
        char name[1000] = {0}, date[15] = {0}, address[1000] = {0};
        fscanf(input, "%d", &id);
        // id = 0 means that the character is something not int , so I will skip this character
        // by moving the file pointer and increase a counter , if the counter become more than 2
        // so we reach the end of file
        if (id == 0)
        {
            // fseek function is used here to move the file pointer one character
            // this is to skip any spaces after last data or any spaces
            fseek(input, 1, SEEK_CUR);
            count++;
            continue;
        }
        count = 0;
        fscanf(input, "%s", &name);
        fscanf(input, "%d", &class_id);
        fscanf(input, "%s", &address);
        fscanf(input, "%s", &date);
        students = insert(id, name, address, class_id, date, students);
    }

    while (1)
    {
        int sel;

        // display the menu
        printf("choose the operation (1-8) \n");
        printf("1- Insert a Student  \n");
        printf("2- Search / Update Info. For a student \n");
        printf("3- list all Students sorted by name \n");
        printf("4- list Students that lives a specific city  \n");
        printf("5- list all Students by their classes \n");
        printf("6- Delete A student \n");
        printf("7- Save all data to the file \n");
        printf("8- Exit\n");
        scanf("%d", &sel);

        // insert new student with his associated data
        if (sel == 1)
        {
            int id = 0, class_id = 0;
            char name[1000] = {0}, date[15] = {0}, address[1000] = {0};
            // Fill the fields for the new student
            printf("ID >>> ");
            scanf("%d", &id);
            printf("Name >>> ");
            scanf("%s", &name);
            printf("Class ID >>> ");
            scanf("%d", &class_id);
            printf("Address >>> ");
            scanf("%s", &address);
            printf("Date of Enrollment >>> ");
            scanf("%s", &date);

            // insert the data into the BST
            students = insert(id, name, address, class_id, date, students);
        }

            // search for a student by ID , and be able to edit his data
        else if (sel == 2)
        {
            printf("Enter the ID : ");
            int id;
            scanf("%d", &id);
            BST elem = Find(id, students);
            if (elem == NULL)
                printf("Student not found ! \n");
            else
            {
                int selection = 0, flag = 0;

                //show all data for the student that his data will be edited
                printf("{ ID: %d }  ", elem->ID);
                printf("{ Name: %s }  ", elem->name);
                printf("{ Class ID: %d }  ", elem->classID);
                printf("{ Address: %s }  ", elem->address);
                printf("{ Date of Enrollment: %s }\n", elem->date_of_enrollment);

                // the flag here is to break from the loop if the user finished editing
                while (!flag)
                {
                    printf("choose the field you want to update :\n");
                    printf("[1] ID      [2] Name      [3] Class ID      [4] Address      [5] Date of Enrollment      [6] Finish edit\n");
                    scanf("%d", &selection);
                    switch (selection)
                    {
                        case 1:
                            printf("new ID >>> ");
                            scanf("%d", &elem->ID);
                            break;
                        case 2:
                            printf("new Name >>> ");
                            scanf("%s", &elem->name);
                            break;
                        case 3:
                            printf("new Class ID >>> ");
                            scanf("%d", &elem->classID);
                            break;
                        case 4:
                            printf("new Address >>> ");
                            scanf("%s", &elem->address);
                            break;
                        case 5:
                            printf("new Date of Enrollment >>> ");
                            scanf("%s", &elem->date_of_enrollment);
                            break;
                        case 6:
                            flag = 1;
                            break;
                        default:
                            printf("Invalid Input ! try again ... \n");
                            break;
                    }
                }
            }
        }

            // print the data orderd depending on the name of student in lexicographic order
        else if (sel == 3)
        {
            copy(byName, students);

            //sort the linked list that contains the data from the BST
            byName = Sort_Name(byName);

            // print the data to the display
            print_List(byName);

            // delete the ordered list to apply any possible updates in other operations
            deleteList(byName);
        }

            // search for a city , if exists , print all students living in this city
        else if (sel == 4)
        {
            char city[1000] = {0};
            copy(byName, students);
            byName = Sort_Name(byName);
            printf("Enter the city name >>> ");
            scanf("%s", city);
            linked_list ptr = byName->next;

            // iterate over all nodes in the ordered list and insert the student who lives
            // in the entered city into another linked list
            while (ptr != NULL)
            {
                if (strcmp(ptr->address, city) == 0)
                    insert_Last(ptr->ID, ptr->name, ptr->address, ptr->classID, ptr->date_of_enrollment, byCity);
                ptr = ptr->next;
            }
            if (byCity->next == NULL)
            {
                printf("None of Students lives in this city !\n");
            }
            else
            {
                // the data here is automatically sorted because i iterated on the sorted list called byName
                print_List(byCity);
            }
            // delete the used lists to apply any possible updates in other operations
            deleteList(byName);
            deleteList(byCity);
        }

            // print each class and all students existing in
        else if (sel == 5)
        {
            copy(byName, students);
            byName = Sort_Name(byName);
            linked_list ptr = byName->next;

            // iterate over all nodes in byName and insert data in another list called classes
            while (ptr != NULL)
            {
                insert_Last(ptr->ID, ptr->name, ptr->address, ptr->classID, ptr->date_of_enrollment, classes);
                ptr = ptr->next;
            }

            // sort the list by class ID
            classes = Sort_Class(classes);

            linked_list head = classes->next;
            int temp = -1000; // to avoid the error if the id is zero

            // this nested loop iterates over the two lists , one that containing data with sorted classes , and the other
            // containing data with sorted names , I will iterate over each class ID , and print each student in it ,
            // the names will be automatically sorted in this case , if there are more than one student in some class
            // so we have repeated class ID , in this case, the loop will print the data once , it will skip the repeated
            // class IDs , also , the data will be printed directly without storing it in a linked list
            while (head != NULL)
            {
                if (temp == head->classID)
                {
                    temp = head->classID;
                    head = head->next;
                    continue;
                }
                printf("** Class %d :\n",head->classID);
                linked_list list = byName->next;
                while (list != NULL)
                {
                    if (list->classID == head->classID)
                    {
                        printf("  %-10d  ", list->ID);
                        printf("   %-20s   ", list->name);
                        printf("   %-10d   ", list->classID);
                        printf("  %-15s   ", list->address);
                        printf("  %-10s \n", list->date_of_enrollment);
                    }
                    list = list->next;
                }
                temp = head->classID;
                head = head->next;
            }

            // delete the used lists to apply any possible changes in other operations
            deleteList(byName);
            deleteList(classes);
        }

            // delete a student by his ID
        else if (sel == 6)
        {
            printf("Enter the ID of student you want to remove : ");
            int id = 0;
            scanf("%d", &id);
            delete (id, students);
            printf("Student with ID %d have been removed ... \n", id);
        }

            // save all data to the file named "students.txt", data is the file will be stored ordered by ID
        else if (sel == 7)
        {
            fclose(input);
            output = fopen("students.txt", "w");
            Save_To_File(students);
            printf("Data Saved to the file ... \n");
            fclose(output);
        }

            // Exit the program
        else if (sel == 8)
        {
            printf("********** Thank you for using Our Program  ************ \n");
            printf("-------------------- Good By -------------------------");
            break;
        }

            // invalid input
        else
        {
            printf("Invalid Input ! try again \n");
        }
    }
    makeEmpty(students);
    return 0;
}

// BST Functions *************************************************************************************************

// delete the whole BST
BST makeEmpty(BST t)
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        free(t);
    }
    return NULL;
}

// returns the node with minimum ID
BST Min(BST t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return Min(t->left);
}

// returns the node with maximum ID
BST Max(BST t)
{
    if (t == NULL)
        return NULL;
    else if (t->right == NULL)
        return t;
    else
        return Max(t->right);
}

// Find a node depending on the value of the ID , if it is not exist, returns null
BST Find(int x, BST t)
{
    if (t == NULL) // in case the element is not exist
        return NULL;
    else if (x < t->ID)
    {
        return Find(x, t->left);
    }
    else if (x > t->ID)
    {
        return Find(x, t->right);
    }
    else
        return t;
}

// save all data of the tree to the file , by making in order traversal on the BST
void Save_To_File(BST t)
{
    if (t == NULL)
        return;
    Save_To_File(t->left);
    fprintf(output,"  %-10d  ", t->ID);
    fprintf(output,"   %-20s   ", t->name);
    fprintf(output,"   %-10d   ", t->classID);
    fprintf(output,"  %-15s   ", t->address);
    fprintf(output,"  %-10s \n", t->date_of_enrollment);
    Save_To_File(t->right);
}

// insert a student to the BST
BST insert(int id, char name[], char address[], int class_id, char date[], BST t)
{
    if (t == NULL)
    {
        t = (BST)malloc(sizeof(struct tnode));
        if (t == NULL)
            printf("out of space !\n");
        else
        {
            t->ID = id;
            strcpy(t->name, name);
            strcpy(t->address, address);
            t->classID = class_id;
            strcpy(t->date_of_enrollment, date);
            t->left = t->right = NULL;
        }
    }
    else if (id < t->ID)
        t->left = insert(id, name, address, class_id, date, t->left);
    else if (id > t->ID)
        t->right = insert(id, name, address, class_id, date, t->right);
    return t;
}

// delete a student from BST depending on the value of ID
BST delete(int id, BST t)
{
    BST tempcell;
    if (t == NULL)
        printf("Element not found !\n");
    else if (id < t->ID)
    {
        t->left = delete (id, t->left);
    }
    else if (id > t->ID)
    {
        t->right = delete (id, t->right);
    }
    else
    {
        tempcell = t;
        if (t->left && t->right)
        {
            tempcell = Min(t->right);
            t->ID = tempcell->ID;
            t->right = delete (t->ID, t->right);
        }

        else if (t->left == NULL)
        {
            t = t->right;
            free(tempcell);
        }

        else if (t->right == NULL)
        {
            t = t->left;
            free(tempcell);
        }
    }

    return t;
}

// copy the data from BST to linked list by making in order traversal on the BST
void copy(linked_list L, BST T)
{
    if (T == NULL)
        return;
    copy(L, T->left);
    insert_First(T->ID, T->name, T->address, T->classID, T->date_of_enrollment, L);
    copy(L, T->right);
}


// linked list Functions **************************************************************************************

// construct a new linked list
linked_list new_linked_list(linked_list L)
{
    L = (linked_list)malloc(sizeof(struct nodell));
    L->ID = 0;
    L->classID = 0;
    memset(L->name, 0, sizeof(L->name));
    memset(L->address, 0, sizeof(L->address));
    memset(L->date_of_enrollment, 0, sizeof(L->date_of_enrollment));
    L->next = NULL;
    L->prev = NULL;
    return L;
}

// insert node at the first of linked list
void insert_First(int id, char name[], char address[], int class_id, char date[], linked_list L)
{
    linked_list newlist = new_linked_list(newlist);
    newlist->ID = id;
    strcpy(newlist->name, name);
    strcpy(newlist->address, address);
    newlist->classID = class_id;
    strcpy(newlist->date_of_enrollment, date);
    newlist->next = L->next;
    newlist->prev = L;
    L->next = newlist;
    L->next->prev = newlist;
}

// insert node at the last of linked list
void insert_Last(int id, char name[], char address[], int class_id, char date[], linked_list L)
{
    linked_list newlist = new_linked_list(newlist);
    newlist->ID = id;
    strcpy(newlist->name, name);
    strcpy(newlist->address, address);
    newlist->classID = class_id;
    strcpy(newlist->date_of_enrollment, date);
    linked_list lst = L;
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    lst->next = newlist;
    newlist->prev = lst;
    newlist->next = NULL;
}

// Delete the linked list and free all linked_lists except the head
void deleteList(linked_list L)
{
    linked_list p, temp;
    p = L->next;
    L->next = NULL;
    while (p != NULL)
    {
        temp = p->next;
        free(p);
        p = temp;
    }
}

// print the data stored in linked list to the screen (terminal)
void print_List(linked_list L)
{
    linked_list p = L->next;
    printf(" {    ID    }  ");
    printf(" {        Name         }  ");
    printf(" { Class ID }  ");
    printf(" {    Address    }  ");
    printf(" { Date of Enrollment }\n");
    while (p != NULL)
    {
        printf("  %-10d  ", p->ID);
        printf("   %-20s   ", p->name);
        printf("   %-10d   ", p->classID);
        printf("  %-15s   ", p->address);
        printf("  %-10s \n", p->date_of_enrollment);
        p = p->next;
    }
    printf("\n");
}

// the following functions are for the merge sort
// Merge sort is a sort algorithm depending on divide and conquer technique, I use it in my program
// because it's the best algorithm in time complexity , worst case O(nlog(n)) , and this is the minimum
// time compared to the other teqniques like (Radix sort, Quich sort )

// to split the linked list into two equal parts to sort every part alone
linked_list split(linked_list L)
{
    linked_list fast = L, slow = L;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    linked_list temp = slow->next;
    slow->next = NULL;
    return temp;
}

// the main function for merge sort depending on the name of student
linked_list Sort_Name(linked_list L)
{
    // if the list is empty or contains one node return the same list
    if (!L || !L->next)
        return L;

    // points to the seconde part of splitted list , so till now , i have two lists
    // L and second , and each list , it has the same number of nodes
    linked_list second = split(L);

    // take every list and make recursion to split it more and more till we reach every node in a single list
    L = Sort_Name(L);
    second = Sort_Name(second);

    // merge the two sorted parts , the sort algorithm is depeding on the name of student
    return merge_Name(L, second);
}

// the main function for merge sort depending on the class id of the student
linked_list Sort_Class(linked_list L)
{
    // if the list is empty or contains one node return the same list
    if (!L || !L->next)
        return L;
    linked_list second = split(L);

    // take every list and make recursion to split it more and more till we reach every node in a single list
    L = Sort_Class(L);
    second = Sort_Class(second);

    // merge the two sorted parts , the sort algorithm compares the class id of students
    return merge_Class(L, second);
}

// sort the different parts and merge them into one linked list using recursion
// sort and merge by comparing the names of students
linked_list merge_Name(linked_list first, linked_list second)
{
    // If first list is empty
    if (!first)
        return second;

    // If second list is empty
    if (!second)
        return first;

    // Pick the smaller value by comparing the name of first student and second student using strcmp
    if (strcmp(first->name, second->name) < 0)
    {
        // compare all elements of first part with the second part
        first->next = merge_Name(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
        // this else if first >= second
    else
    {
        // here , the second name is smaller than the first name
        second->next = merge_Name(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

// sort and merge by comparing the class id's of students
linked_list merge_Class(linked_list first, linked_list second)
{
    // If first  list is empty
    if (!first)
        return second;

    // If second  list is empty
    if (!second)
        return first;

    // Pick the smaller value by comparing the class ID for first student and class ID for second student
    if (first->classID < second->classID)
    {
        first->next = merge_Class(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        // here , the class ID for second student is smaller than class ID for first student
        second->next = merge_Class(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}