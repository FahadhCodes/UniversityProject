#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
//---------------------------------------------------------------------------PRODUCT DEFF------------------------------------------------------------------
void colour(int colour)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}
typedef struct pnode *product;
struct pnode
{
    char product_name[50];
    product next;
};

typedef struct
{
    product head;
    product tail;
} product_list;

void initPlist(product_list *pl)
{
    pl->head = NULL;
    pl->tail = NULL;
}

product initPnode(char pName[50])
{
    product ptemp = (product)malloc(sizeof(struct pnode));
    strcpy(ptemp->product_name, pName);
    ptemp->next = NULL;
    return ptemp;
}
void insertProduct_Rear(product_list *pl, char pName[50])
{
    product ptemp = initPnode(pName);
    if (pl->head == NULL)
    {
        pl->head = pl->tail = ptemp;
    }
    else
    {
        pl->tail->next = ptemp;
        pl->tail = ptemp;
    }
}

void pdelete(product_list *pl, char pName[50])
{
    int found = 0;
    product search1;
    product search2;
    if (pl->head == NULL)
    {
        printf("The list is empty!!!\n");
    }
    else
    {
        search1 = pl->head;
        search2 = search1;
        while (search1 != NULL && !found)
        {
            if (strcmp(search1->product_name, pName) == 0)
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
                pl->head = search1->next;
            }
            else
            {
                search2->next = search1->next;
            }
            free(search1);
        }
        else
        {
            printf("The entered Product not found!!!");
        }
    }
}

void pupdate(product_list *pl, char pName[50])
{
    printf("entered pupdate");
    int found = 0;
    product search;
    if (pl->head == NULL)
    {
        printf("NO PRODUCTS!!!\n");
    }
    else
    {
        search = pl->head;
        while (search != NULL && !found)
        {
            if (strcmp(search->product_name, pName) == 0)
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
            char Uproduct[50];
            printf("Enter the product Name:");
            getchar();
            scanf("%[^\n]", &Uproduct);
            strcpy(search->product_name, Uproduct);
        }
        else
        {
            printf("The entered product not found!!!");
        }
    }
}
void prod_Display(product_list *pl)
{
    product display;
    if (pl->head == NULL)
    {
        printf("NO PRODUCTS....!\n");
    }
    else
    {
        display = pl->head;
        // printf("+-------------------------+\n");
        // printf("|   Products              |\n");
        // printf("+-------------------------+\n");

        while (display != NULL)
        {
            printf("\n|           |                 |           |           |                         |                         | %23s |", display->product_name);
            display = display->next;
        }
    }
}
// link functions sub-list -> main-list

// link functions sub-list -> main-list
//---------------------------------------------------------------------------PRODUCT DEFF------------------------------------------------------------------

int id_gen() // Used for generate ID
{
    time_t t = time(NULL);
    struct tm *curTime = localtime(&t);
    return (1900 + curTime->tm_year + curTime->tm_yday) * (curTime->tm_hour + curTime->tm_min + curTime->tm_sec);
}
typedef struct // define user
{
    int Order_ID, price;
    char name[100], gender[10]; // tailoreItm[1024 * 5]
    product_list products;
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
    temp->u = *u;
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
        colour(96);
        if (found)
        {
            struct tm *ord = localtime(&search->u.ordered_date);
            char str1[100];
            strftime(str1, 100, "%d /%m /%Y |%I:%M %p", ord);
            struct tm *del = localtime(&search->u.delivered_date);
            char str2[100];
            strftime(str2, 100, "%d /%m /%Y |%I:%M %p", del);
            printf("+-----------+-----------------+-----------+-----------+-------------------------+-------------------------+-------------------------+\n");
            printf("|   ID      | Customer Name   |   Gender  |   Price   |      Ordered Date       |     Delivered Date      |   Products              |\n");
            printf("+-----------+-----------------+-----------+-----------+-------------------------+-------------------------+-------------------------+\n");
            colour(7);
            colour(14);
            printf("| %-9d | %-15s | %-9s | %-9d | %-23s | %-23s |-------------------------|", search->u.Order_ID, search->u.name, search->u.gender, search->u.price, str1, str2);
            prod_Display(&search->u.products);
            printf("\n");
            printf("+-----------+-----------------+-----------+-----------+-------------------------+-------------------------+-------------------------+\n");
        }
        else
        {
            printf("The entered User ID not found!!!");
        }
    }
}

void delete(list *l, int UID)
{
    printf("1: DELETE ENTIRE DATA\n");
    printf("2: DELETE A PRODUCT\n\n");
    int cho;
    printf("Enter what you want to Delete (\t1\t2\t): ");
    scanf("%d", &cho);

    if (cho == 1)
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
                printf("The entered User ID not found!!!\n");
            }
        }
    }
    else if (cho == 2)
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
                char pName[50];
                printf("Enter the product name you want to delete: ");
                getchar();
                scanf("%[^\n]", pName);
                pdelete(&search->u.products, pName);
            }
            else
            {
                printf("The entered User ID not found!!!\n");
            }
        }
    }
    else
    {
        printf("Invalid choice!!!\n");
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
            char name[50], gender[10], product[50];
            colour(7);
            printf("Enter a following Number according to what you want to change...\n");
            colour(82);
            printf("1: CHANGE NAME\t2: CHANGE GENDER\t3: CHANGE ORDERED ITEMS(Enter from the beginning)\n");
            colour(13);
            printf("4: CHANGE PRICE\t5: CHANGE WORK TIME PERIOD\n");
            printf("which data do you want to be update(");
            colour(82);
            printf(" 1 ");
            colour(13);
            printf(" 2 ");
            colour(82);
            printf(" 3 ");
            colour(13);
            printf(" 4 ");
            colour(82);
            printf(" 5 ");
            colour(13);
            printf(" ): ");
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
                printf("Enter the product name you want to update: ");
                getchar();
                scanf("%[^\n]", product);
                pupdate(&search->u.products, product);
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
    colour(96);
    if (l->head == NULL)
    {
        printf("NO DATA....!\n");
    }
    else
    {
        display = l->head;
        printf("+-----------+-----------------+-----------+-----------+-------------------------+-------------------------+-------------------------+\n");
        printf("|   ID      | Customer Name   |   Gender  |   Price   |      Ordered Date       |     Delivered Date      |   Products              |\n");
        printf("+-----------+-----------------+-----------+-----------+-------------------------+-------------------------+-------------------------+\n");
        colour(7);
        colour(14);
        while (display != NULL)
        {
            struct tm *ord = localtime(&display->u.ordered_date);
            char str1[100];
            strftime(str1, 100, "%d /%m /%Y |%I:%M %p", ord);
            struct tm *del = localtime(&display->u.delivered_date);
            char str2[100];
            strftime(str2, 100, "%d /%m /%Y |%I:%M %p", del);
            printf("| %-9d | %-15s | %-9s | %-9d | %-23s | %-23s |-------------------------|", display->u.Order_ID, display->u.name, display->u.gender, display->u.price, str1, str2);
            prod_Display(&display->u.products);
            printf("\n");
            printf("+-----------+-----------------+-----------+-----------+-------------------------+-------------------------+-------------------------+\n");
            display = display->next;
        }
        colour(7);
    }
}

void user_inp(user *u)
{
    colour(10);
    printf("ENTER Customer Name: ");
    getchar();
    scanf("%49[^\n]", &u->name);
    printf("ENTER gender: ");
    getchar();
    scanf("%49[^\n]", &u->gender);
    initPlist(&u->products);
    while (1) // INSERT REAR LOOP
    {
        colour(3);
        char pName[50];
        printf("ENTER Ordered Items: ");
        getchar();
        scanf("%[^\n]", pName);
        insertProduct_Rear(&u->products, pName);
        int s;
        printf("[1: ADD MORE PRODUCTS]   |   [0: EXIT FROM PRODUCT ENTERING (REAR) SECTION]: ");
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
    colour(350);
    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                              MENU                                                                 |\n");
    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("+-----------------------------------------------------------------------------------------------------------------------------------+\n");
    colour(7);
    while (1) // INSERT FRONT LOOP
    {
        char CHOICE[10];
        printf("Enter what you want to change ");
        colour(30);
        printf(" INSERT ");
        colour(100);
        printf(" UPDATE ");
        colour(334);
        printf(" DELETE ");
        colour(288);
        printf(" SEARCH ");
        colour(113);
        printf(" DISPLAY :");
        colour(7);
        scanf("%s", &CHOICE);
        if (strcmp(CHOICE, "INSERT") == 0)
        {
            while (1) // INSERT LOOP
            {
                char ADD[10];
                colour(7);
                printf("CHOOSE a Data Entering mehtod ");
                colour(30);
                printf("FRONT");
                colour(100);
                printf("REAR");
                colour(113);
                printf("NEXT");
                colour(7);
                printf("(to enter data next to a paricular data)): ");
                scanf("%s", &ADD);
                if (strcmp(ADD, "FRONT") == 0)
                {
                    while (1) // INSERT FRONT LOOP
                    {
                        colour(11);
                        user u;
                        user_inp(&u);
                        inserFront(l, &u);
                        int s;
                        printf("[1: ADD MORE DATA]   |   [0: EXIT DATA ENTERING (FRONT)]: ");
                        scanf("%d", &s);
                        if (s)
                        {
                            colour(6);
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
                        colour(12);
                        user u;
                        user_inp(&u);
                        insertRear(l, &u);
                        int s;
                        printf("[1: ADD MORE DATA]   |   [0: EXIT DATA ENTERING (REAR)]: ");
                        scanf("%d", &s);
                        if (s)
                        {
                            colour(6);
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
                        colour(3);
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
                            colour(6);
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
                colour(13);
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
                colour(7);
            }
        }
        else if (strcmp(CHOICE, "UPDATE") == 0)
        {
            while (1) // UPDATE LOOP
            {
                // CODE
                colour(13);
                printf("Enter User ID that you want to update: ");
                scanf("%d", &UID);
                update(l, UID);
                int s;
                printf("[1: UPDATE MORE DATA]   |   [0: EXIT FROM UPDATING]: ");
                scanf("%d", &s);
                if (s)
                {
                    colour(10);
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
            while (1) // DELETE LOOP
            {
                // CODE
                colour(12);
                printf("Enter User ID that you want to delete: ");
                scanf("%d", &UID);
                delete (l, UID);
                int s;
                printf("[1: DELETE MORE DATA]   |   [0: EXIT FROM DELETE]: ");
                scanf("%d", &s);
                if (s)
                {
                    colour(10);
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
                colour(14);
                printf("Enter User ID that you want to find: ");
                scanf("%d", &UID);
                search(l, UID);
                int s;
                printf("[1: SEARCH AGAIN]   |   [0: EXIT FROM SEARCH]: ");
                scanf("%d", &s);
                if (s)
                {
                    colour(6);
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
                printf("[1: DISPLAY AGAIN]   |   [0: EXIT FROM DISPLAYING]: ");
                scanf("%d", &s);
                if (s)
                {
                    colour(6);
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
                colour(4);
                printf("INCORRECT CHOICE!!!");
                int s;
                printf("[1: TRY AGAIN]   |   [0: EXIT TO MAIN MENU]: ");
                scanf("%d", &s);
                if (s)
                {
                    colour(6);
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
        colour(7);
        printf("[1: EDIT ENTERED DATA]   |   [0: EXIT]: ");
        scanf("%d", &s);
        colour(13);
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
        colour(7);
    }
    getchar();
    return 0;
}