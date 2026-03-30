#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_WORK_TIME 20
#define MAX_WORK_AGE 65

typedef struct nodeL
{
    int data_line;
    struct nodeL *next_line;
} node_line;

typedef struct
{
    node_line *begin;
    node_line *end;
    int size_line;
} line;

typedef struct nodeP
{
    int data_pile;
    struct nodeP *next_pile;
} node_pile;

typedef struct
{
    node_pile *top;
    int size_pile;
} pile;

//Line functions
void create_line(line *q);
int insert(line *q, int data_line);
int remove_line(line *q, int *data_line);
int is_empty_line(line q);
int get_begin(line q);
int get_end(line q);
int get_size_line(line q);
void show_line(line q);


//Pile functions
void create_pile(pile *s);
int stack_pile(pile *s, int data_pile);
int unstack_pile(pile *s, int *data_pile);
int is_empty_pile(pile s);
int get_top_pile(pile s);
int get_size_pile(pile s);
void show_pile(pile s);

int main()
{
    line working;
    pile retired;
    int workT[10];
    int workA[10];
    int i = 0, select_menu = -1, sucessP, sucessL, dataP = 0, dataL = 0;

    printf("Creating a stack and queue...\n\n");
    create_line(&working);
    if(is_empty_line(working))
        printf("The created queue is empty!\n");
    else
        printf("The created queue is not empty!\n");

    create_pile(&retired);
    if(is_empty_pile(retired))
        printf("The created stack is empty!\n");
    else
        printf("The stack isn't empty!\n");

    Sleep(2000);
    system("cls");

    printf("Generating and stacking data...\n\n");

    Sleep(2000);

    srand(time(NULL));

    for(i = 0; i < 10; i++)
    {
        workT[i] = rand() % 21 + 20;
        workA[i] = rand() % 63 + 18;
        printf("Storing working time: %d\n", workT[i]);
        printf("Storing worker age: %d\n", workA[i]);
    }

    Sleep(6000);
    system("cls");

    for(i = 0; i < 10; i++)
    {
        if(workT[i] >= MAX_WORK_TIME && workA[i] >= MAX_WORK_AGE)
        {
            printf("Storing the %d age of the worker with %d working time in the retired stack\n", workA[i], workT[i]);
            dataP = workA[i];
            sucessP = stack_pile(&retired, dataP);
            if(!sucessP)
                printf("Error storing on stack!");
        }
        else
        {
            printf("Storing the %d age of the worker with %d working time in the working queue\n", workA[i], workT[i]);
            dataL = workA[i];
            sucessL = insert(&working, dataL);
            if(!sucessL)
                printf("Error storing in queue!");
        }
    }

    Sleep(6000);
    system("cls");

    show_pile(retired);
    show_line(working);

    system("cls");

    while (select_menu != 0)
    {
        show_pile(retired);
        printf("\n");
        show_line(working);
        printf("\n");

        printf("1. Remove from pile\n");
        printf("2. Remove from queue\n");
        printf("3. Get the size of pile\n");
        printf("4. Get the size of the queue\n");
        printf("5. Get the top of the pile\n");
        printf("6. Get the begin of the queue\n");
        printf("7. Get the end of the queue\n");
        printf("0. Exit\n");
        printf("Choose one of the options: ");
        scanf("%d", &select_menu);
        printf("\n");

        switch(select_menu)
        {
            case 1:
                unstack_pile(&retired, &dataP);
                printf("\n");
                system("cls");
                break;

            case 2:
                remove_line(&working, &dataL);
                printf("\n");
                system("cls");
                break;

            case 3:
                system("cls");
                printf("Size of the pile = %d\n\n", get_size_pile(retired));
                break;

            case 4:
                system("cls");
                printf("Size of the queue = %d\n\n", get_size_line(working));
                break;

            case 5:
                if (is_empty_pile(retired))
                {
                    printf("The stack is empty...\n\n");
                }
                else
                {
                    system("cls");
                    printf("Data on top of the pile = %d\n\n", get_top_pile(retired));
                }
                break;

            case 6:
                if (is_empty_line(working))
                {
                    printf("The queue is empty...\n\n");
                }
                else
                {
                    system("cls");
                    printf("Begin of the queue = %d\n\n", get_begin(working));
                }
                break;

            case 7:
                if (is_empty_line(working))
                {
                    printf("The queue is empty...\n\n");
                }
                else
                {
                    system("cls");
                    printf("End of the queue = %d\n\n", get_end(working));
                }
                break;

            case 0:
                return 0;
                break;

            default:
                printf("Invalid option! Try again\n");
                break;
        }
    }
    return 0;
}

void create_pile(pile *s)
{
    s->top = NULL;
    s->size_pile = 0;
}

int stack_pile(pile *s, int dataP)
{
    node_pile *aux;
    aux = (node_pile *) malloc(sizeof(node_pile));
    if(aux == NULL)
        return 0;

    aux->data_pile = dataP;
    aux->next_pile = s->top;
    s->top = aux;
    s->size_pile++;

    return 1;
}

int unstack_pile(pile *s, int *dataP)
{
    node_pile *aux = s->top;
    if(aux == NULL)
        return 0;

    *dataP = aux->data_pile;
    s->top = aux->next_pile;
    s->size_pile--;
    free(aux);

    return 1;
}

int is_empty_pile(pile s)
{
    if(s.top == NULL)
        return 1;
    return 0;
}

int get_top_pile(pile s)
{
    return s.top->data_pile;
}

int get_size_pile(pile s)
{
    return s.size_pile;
}

void show_pile(pile s)
{
    node_pile *aux = s.top;
    if(aux == NULL)
        printf("The pile is empty...\n");
    else
    {
        while(aux != NULL)
        {
            printf("Retired pile: %d years\n", aux->data_pile);
            aux = aux->next_pile;
        }
    }
}

void create_line(line *q)
{
    q->begin = NULL;
    q->end = NULL;
    q->size_line = 0;
}

int insert(line *q, int data_line)
{
    node_line *aux;
    aux = (node_line*) malloc(sizeof(node_line));
    if(aux == NULL)
        return 0;

    aux->data_line = data_line;
    aux->next_line = NULL;
    q->size_line++;

    if(q->begin == NULL)
    {
        q->begin = aux;
        q->end = aux;
        return 1;
    }

    q->end->next_line = aux;
    q->end = aux;
    return 1;
}

int remove_line(line *q, int *data_line)
{
    node_line *aux;
    aux = q->begin;
    if(aux == NULL)
        return 0;

    *data_line =aux->data_line;
    q->size_line--;
    q->begin = aux->next_line;

    if(q->begin == NULL)
        q->end = NULL;

    free(aux);
    return 1;
}

int is_empty_line(line q)
{
    if(q.begin == NULL)
        return 1;
    return 0;
}

int get_begin(line q)
{
    return q.begin->data_line;
}

int get_end(line q)
{
    return q.end->data_line;
}

int get_size_line(line q)
{
    return q.size_line;
}

void show_line(line q)
{
    node_line *aux;
    aux = q.begin;
    if(aux == NULL)
    {
        printf("The queue is empty...\n");
    }

    while(aux != NULL)
    {
        printf("Working queue: %d years\n", aux->data_line);
        aux = aux->next_line;
    }
}
