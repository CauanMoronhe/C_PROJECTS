#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10

typedef struct node_ht
{
    char word[30];
    int frequency;
    struct node_ht *next;
} node_ht;

node_ht *hash_table[TAM];

int hash_function(char *key)
{
    int sum = 0;
    for(int i = 0; key[i] != '\0'; i++)
    {
        sum += key[i];
    }
    return sum % TAM;
}

void init_ht()
{
    for(int i = 0; i < TAM; i++)
    {
        hash_table[i] = NULL;
    }
}

node_ht *search_word(char *word)
{
    int index = hash_function(word);
    node_ht *actual = hash_table[index];

    while (actual != NULL)
    {
        if(strcmp(actual->word, word) == 0)
            return actual;
        actual = actual->next;
    }

    return NULL;
}

void insert(char *word)
{
    node_ht *existing_node = search_word(word);

    if (existing_node != NULL)
    {
        existing_node->frequency++;
    }
    else
    {
        int index = hash_function(word);
        node_ht *new_node = (node_ht*) malloc(sizeof(node_ht));
        if(!new_node)
        {
            printf("Memory allocation error!\n");
            return;
        }

        strcpy(new_node->word, word);
        new_node->frequency = 1;
        new_node->next = hash_table[index];
        hash_table[index] = new_node;
    }
}

void print_table()
{
    printf("\nHash Table (TAM = %d):\n", TAM);
    for(int i = 0; i < TAM; i++)
    {
        node_ht *actual = hash_table[i];
        while(actual != NULL)
        {
            printf("Word: '%s' | Frequency: %d\n", actual->word, actual->frequency);
            actual = actual->next;
        }
        printf("NULL\n");
    }
}

void print_stats()
{
    int total_elements = 0;
    int stored_indices = 0;
    int max_chain = 0;

    for(int i = 0; i < TAM; i++)
    {
        node_ht *actual = hash_table[i];

        if(actual != NULL)
        {
            stored_indices++;
            int current_chain = 0;

            while(actual != NULL)
            {
                current_chain++;
                actual = actual->next;
            }

            total_elements += current_chain;

            if(current_chain > max_chain)
            {
                max_chain = current_chain;
            }
        }
    }

    printf("\n========== HASH TABLE STATICS ==========\n");
    printf("Size of the hash table: %d\n", TAM);
    printf("Total elements stored: %d\n", total_elements);
    printf("Stored indices: %d (%.2f%%)\n", stored_indices, (float)stored_indices/TAM * 100);
    printf("Empty indexes: %d\n", TAM - stored_indices);
    printf("Highest chain: %d\n", max_chain);
    printf("Load factor: %.2f\n", (float)total_elements / TAM);
    printf("========================================\n");
}

void destruct_table()
{
    for(int i = 0; i < TAM; i++)
    {
        node_ht *actual = hash_table[i];
        while (actual != NULL)
        {
            node_ht *aux = actual;
            actual = actual->next;
            free(aux);
        }
        hash_table[i] = NULL;
    }
}

int main()
{
    FILE *file_pointer;
    char line[30];
    char name_file[100];
    int menu, option = 9999999;

    printf("Hash Table Project\n\n");
    printf("Enter the file name or path: ");
    scanf("%s", &name_file);

    printf("\nTrying to open file: %s...\n\n", name_file);

    file_pointer = fopen(name_file, "r");

    if(file_pointer == NULL)
    {
        printf("Error: the file '%s' was not found!\n\n", name_file);
        printf("Please check that the name is correct and that the .txt file has been included.\n\n");
        exit(1);
    }

    while(option != 0)
    {
        printf("\n================= MENU =================\n\n");
        printf("1. Show hash table\n");
        printf("2. Show stats hash table\n");
        printf("3. Search name\n");
        printf("4. Destroy hash table\n");
        printf("0. Exit\n");
        printf("\n========================================\n\n");
    }


    /*fclose(file_pointer);

    switch(menu)
    {
        case(1)

    }*/

    return 0;
}
