#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int id_gen() // Used for generate ID
{
    time_t t = time(NULL);
    struct tm *curTime = localtime(&t);
    return (1900 + curTime->tm_year + curTime->tm_yday) * (curTime->tm_hour + curTime->tm_min + curTime->tm_sec);
}
typedef struct // define user
{
    int Order_ID, price;
    char name[100], gender[10], tailoreItm[1024 * 5];
    time_t ordered_date;
    time_t delivered_date;
    int wrktime_period;
} user;

typedef struct lnode *node;

struct lnode
{
    user u;
    node next;
};
typedef struct
{
    node head;
    node tail;
} list;

void initList(list *l)
{
    l->head = NULL;
    l->tail = NULL;
}

node initNode(user *u)
{
    node temp = (node)malloc(sizeof(struct lnode));
    temp->u.Order_ID = u->Order_ID;
    strcpy(temp->u.name, u->name);
    strcpy(temp->u.gender, u->gender);
    strcpy(temp->u.tailoreItm, u->tailoreItm);
    temp->u.wrktime_period = u->wrktime_period;
    temp->u.ordered_date = u->ordered_date;
    temp->u.delivered_date = u->delivered_date;
    temp->u.price = u->price;
    temp->next = NULL;
    return temp;
}

void inserFront(list *l, user *u)
{
    node temp = initNode(u);
    if (l->head == NULL)
    {
        l->head = l->tail = temp;
    }
    else
    {
        temp->next = l->head;
        l->head = temp;
    }
}

void insertRear(list *l, user *u)
{
    node temp = initNode(u);
    if (l->head == NULL)
    {
        l->head = l->tail = temp;
    }
    else
    {
        l->tail->next = temp;
        l->tail = temp;
    }
}

void insertNext(list *l, user *u, int UID)
{
    int found = 0;
    node search;
    node temp = initNode(u);

    if (l->head == NULL)
    {
        l->head = l->tail = temp;
    }
    else
    {
        search = l->head;
        while (search != NULL && !found)
        {
            if (search->u.Order_ID == UID)
            {
                found = 1;
            }
            else
            {
                search = search->next;
            }
        }
        if (found)
        {
            temp->next = search->next;
            search->next = temp;
        }
        else
        {
            printf("The entered User ID not found!!!");
        }
    }
}

void search(list *l, int UID)
{
    int found = 0;
    node search;
    if (l->head == NULL)
    {
        printf("The list is empty!!!\n");
    }
    else
    {
        search = l->head;
        while (search != NULL && !found)
        {
            if (search->u.Order_ID == UID)
            {
                found = 1;
            }
            else
            {
                search = search->next;
            }
        }
        if (found)
        {
            struct tm *ord = localtime(&search->u.ordered_date);
            char str1[100];
            strftime(str1, 100, "%d /%m /%Y |%I:%M %p", ord);
            struct tm *del = localtime(&search->u.delivered_date);
            char str2[100];
            strftime(str2, 100, "%d /%m /%Y |%I:%M %p", del);
            printf("+-----------+-----------------+-----------+-------------------------+-----------+-------------------------+-------------------------+\n");
            printf("|   ID      | Customer Name   |   Gender  |   Products              |   Price   |      Ordered Date       |     Delivered Date      |\n");
            printf("+-----------+-----------------+-----------+-------------------------+-----------+-------------------------+-------------------------+\n");
            printf("| %-9d | %-15s | %-9s | %-23s | %-9d | %-23s | %-23s |\n", search->u.Order_ID, search->u.name, search->u.gender, search->u.tailoreItm, search->u.price, str1, str2);
            printf("+-----------+-----------------+-----------+-------------------------+-----------+-------------------------+-------------------------+\n");
        }
        else
        {
            printf("The entered User ID not found!!!");
        }
    }
}

void delete(list *l, int UID)
{
    int found = 0;
    node search1;
    node search2;
    if (l->head == NULL)
    {
        printf("The list is empty!!!\n");
    }
    else
    {
        search1 = l->head;
        search2 = search1;
        while (search1 != NULL && !found)
        {
            if (search1->u.Order_ID == UID)
            {
                found = 1;
            }
            else
            {
                search2 = search1;
                search1 = search1->next;
            }
        }
        if (found)
        {
            if (search2 == search1)
            {
                l->head = search1->next;
            }
            else
            {
                search2->next = search1->next;
            }
            free(search1);
        }
        else
        {
            printf("The entered User ID not found!!!");
        }
    }
}

void update(list *l, int UID)
{
    int found = 0;
    node search;
    if (l->head == NULL)
    {
        printf("NO DATA!!!\n");
    }
    else
    {
        search = l->head;
        while (search != NULL && !found)
        {
            if (search->u.Order_ID == UID)
            {
                found = 1;
            }
            else
            {
                search = search->next;
            }
        }
        if (found)
        {
            int x, price, wrktime;
            char name[50], gender[10], product[5 * 1024];
            printf("Enter a following Number according to what you want to change...\n");
            printf("1: CHANGE NAME\t2: CHANGE GENDER\t3: CHANGE ORDERED ITEMS(Enter from the beginning)\n4: CHANGE PRICE\t5: CHANGE WORK TIME PERIOD\n");
            printf("which data do you want to be update(\t1\t2\t3\t4\t5): ");
            scanf("%d", &x);
            switch (x)
            {
            case 1:
                printf("ENTER Customer Name: ");
                getchar();
                scanf("%[^\n]", &name);
                strcpy(search->u.name, name);
                break;
            case 2:
                printf("ENTER gender: ");
                getchar();
                scanf("%[^\n]", &gender);
                strcpy(search->u.gender, gender);
                break;
            case 3:
                printf("Enter ordered Items (Again from the beginning):");
                getchar();
                scanf("%[^\n]", &product);
                strcpy(search->u.tailoreItm, product);
                break;
            case 4:
                printf("Enter price:");
                scanf("%d", &price);
                search->u.price = price;
                break;
            case 5:
                int hh, dd, mm;
                printf("ENTER Work time Period: (HOUR DAY MONTH)\n                         ");
                scanf("%d %d %d", &hh, &dd, &mm);
                wrktime = mm * 30 * 24 * 60 * 60 + dd * 24 * 60 * 60 + hh * 60 * 60;
                search->u.wrktime_period = wrktime;
                search->u.delivered_date += search->u.wrktime_period;
                break;
            default:
                printf("Wrong choice detected!!!\n");
                break;
            }
        }
        else
        {
            printf("The entered User ID not found!!!");
        }
    }
}

void display(list *l)
{
    node display;
    if (l->head == NULL)
    {
        printf("NO DATA....!\n");
    }
    else
    {
        display = l->head;
        printf("+-----------+-----------------+-----------+-------------------------+-----------+-------------------------+-------------------------+\n");
        printf("|   ID      | Customer Name   |   Gender  |   Products              |   Price   |      Ordered Date       |     Delivered Date      |\n");
        printf("+-----------+-----------------+-----------+-------------------------+-----------+-------------------------+-------------------------+\n");

        while (display != NULL)
        {
            struct tm *ord = localtime(&display->u.ordered_date);
            char str1[100];
            strftime(str1, 100, "%d /%m /%Y |%I:%M %p", ord);
            struct tm *del = localtime(&display->u.delivered_date);
            char str2[100];
            strftime(str2, 100, "%d /%m /%Y |%I:%M %p", del);
            printf("| %-9d | %-15s | %-9s | %-23s | %-9d | %-23s | %-23s |\n", display->u.Order_ID, display->u.name, display->u.gender, display->u.tailoreItm, display->u.price, str1, str2);
            printf("+-----------+-----------------+-----------+-------------------------+-----------+-------------------------+-------------------------+\n");
            display = display->next;
        }
    }
}
void user_inp(user *u)
{
    printf("ENTER Customer Name: ");
    getchar();
    scanf("%49[^\n]", &u->name);
    printf("ENTER gender: ");
    getchar();
    scanf("%49[^\n]", &u->gender);
    printf("ENTER Ordered Items: ");
    getchar();
    scanf("%[^\n]", &u->tailoreItm);
    printf("ENTER Price: ");
    scanf("%d", &u->price);
    int hh, dd, mm;
    printf("ENTER Work time Period: (HOUR DAY MONTH)\n                         ");
    scanf("%d %d %d", &hh, &dd, &mm);
    u->wrktime_period = mm * 30 * 24 * 60 * 60 + dd * 24 * 60 * 60 + hh * 60 * 60;
    u->Order_ID = id_gen();
    u->ordered_date = time(NULL),
    u->delivered_date = u->ordered_date + u->wrktime_period;
}
int main()
{
    list *l = (list *)malloc(sizeof(list));
    int UID;
    initList(l);
    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                              MENU                                                                 |\n");
    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
    while (1) // INSERT FRONT LOOP
    {
        char CHOICE[10];
        printf("Enter what you want to change (INSERT\tUPDATE\tDELETE\tSEARCH\tDISPLAY): ");
        scanf("%s", &CHOICE);
        if (strcmp(CHOICE, "INSERT") == 0)
        {
            while (1) // INSERT LOOP
            {
                char ADD[10];
                printf("CHOOSE a Data Entering mehtod (FRONT\tREAR\tNEXT (to enter data next to a paricular data)): ");
                scanf("%s", &ADD);
                if (strcmp(ADD, "FRONT") == 0)
                {
                    while (1) // INSERT FRONT LOOP
                    {
                        user u;
                        user_inp(&u);
                        inserFront(l, &u);
                        int s;
                        printf("[1: ADD MORE DATA]   |   [0: EXIT DATA ENTERING (FRONT)]: ");
                        scanf("%d", &s);
                        if (s)
                        {
                            printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                        }
                        else
                        {
                            break;
                        }
                    }
                    display(l);
                }
                else if (strcmp(ADD, "REAR") == 0)
                {
                    while (1) // INSERT REAR LOOP
                    {
                        user u;
                        user_inp(&u);
                        insertRear(l, &u);
                        int s;
                        printf("[1: ADD MORE DATA]   |   [0: EXIT DATA ENTERING (REAR)]: ");
                        scanf("%d", &s);
                        if (s)
                        {
                            printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                        }
                        else
                        {
                            break;
                        }
                    }
                    display(l);
                }
                else if (strcmp(ADD, "NEXT") == 0)
                {
                    while (1) // INSERT NEXT LOOP
                    {
                        printf("Enter User ID to store data next to them: ");
                        scanf("%d", &UID);
                        user u;
                        user_inp(&u);
                        insertNext(l, &u, UID);
                        int s;
                        printf("[1: ADD MORE DATA]   |   [0: EXIT DATA ENTERING (NEXT)]: ");
                        scanf("%d", &s);
                        if (s)
                        {
                            printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                        }
                        else
                        {
                            break;
                        }
                    }
                    display(l);
                }
                else
                {
                    printf("INCORRECT CHOICE!!!");
                }
                int s;
                printf("[1: ADD MORE DATA USING OTHER DATA ENTERING METHOD]   |   [0: EXIT DATA ENTERING]: ");
                scanf("%d", &s);
                if (s)
                {
                    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<BACK TO THE MAIN INSERTING MENU<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
                    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                }
                else
                {
                    break;
                }
            }
        }
        else if (strcmp(CHOICE, "UPDATE") == 0)
        {
            while (1) // UPDATE LOOP
            {
                // CODE
                printf("Enter User ID that you want to update: ");
                scanf("%d", &UID);
                update(l, UID);
                int s;
                printf("[1: UPDATE MORE DATA]   |   [0: EXIT FROM UPDATING]: \n");
                scanf("%d", &s);
                if (s)
                {
                    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("+.............................................................UPDATING..............................................................+\n");
                }
                else
                {
                    break;
                }
            }
            display(l);
        }
        else if (strcmp(CHOICE, "DELETE") == 0)
        {
            while (1) // UPDATE LOOP
            {
                // CODE
                printf("Enter User ID that you want to delete: ");
                scanf("%d", &UID);
                delete (l, UID);
                int s;
                printf("[1: DELETE MORE DATA]   |   [0: EXIT FROM DELETE]: \n");
                scanf("%d", &s);
                if (s)
                {
                    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("+.............................................................DELETING..............................................................+\n");
                }
                else
                {
                    break;
                }
            }
            display(l);
        }
        else if (strcmp(CHOICE, "SEARCH") == 0)
        {
            while (1) // SEARCH LOOP
            {
                // CODE
                printf("Enter User ID that you want to find: ");
                scanf("%d", &UID);
                search(l, UID);
                int s;
                printf("[1: SEARCH AGAIN]   |   [0: EXIT FROM SEARCH]: \n");
                scanf("%d", &s);
                if (s)
                {
                    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("+.............................................................SEARCHING.............................................................+\n");
                }
                else
                {
                    break;
                }
            }
        }
        else if (strcmp(CHOICE, "DISPLAY") == 0)
        {
            while (1) // DISPLAYING LOOP
            {
                display(l);
                int s;
                printf("[1: DISPLAY AGAIN]   |   [0: EXIT FROM DISPLAYING]: \n");
                scanf("%d", &s);
                if (s)
                {
                    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("+........................................................DISPLAYING.........................................................+\n");
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            while (1) // DEFAULT LOOP
            {
                // CODE
                printf("INCORRECT CHOICE!!!");
                int s;
                printf("[1: TRY AGAIN]   |   [0: EXIT TO MAIN MENU]: \n");
                scanf("%d", &s);
                if (s)
                {
                    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
                    printf("+...................................................................................................................................+\n");
                }
                else
                {
                    break;
                }
            }
        }

        int s;
        printf("[1: EDIT ENTERED DATA]   |   [0: EXIT]: \n");
        scanf("%d", &s);
        if (s)
        {
            printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
            printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<BACK TO THE MAIN MENU<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
            printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
        }
        else
        {
            break;
        }
    }
    getchar();
    return 0;
}