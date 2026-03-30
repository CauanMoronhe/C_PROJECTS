#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

typedef struct node_music{
    int music_id;
    char music_name[MAX_NAME];
    char artist_name[MAX_NAME];

    struct node_music *next;
    struct node_music *prev;
}music;

music* create_music(int id, const char* name, const char* artist){
    music* new_music = (music*) malloc(sizeof(music));
    if(new_music == NULL){
        printf("Memory allocation error!\n");
        exit(1);
    }

    new_music->music_id = id;

    strcpy(new_music->music_name, name);
    strcpy(new_music->artist_name, artist);

    new_music->music_name[MAX_NAME - 1] = '\0';
    new_music->artist_name[MAX_NAME - 1] = '\0';

    new_music->next = NULL;
    new_music->prev = NULL;

    return new_music;
}

void clear_buffer_entry(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void insert_music_end(music** playlist, int id, const char* name, const char* artist){
    music* new_music = create_music(id, name, artist);

    if(*playlist == NULL){
        new_music->next = new_music;
        new_music->prev = new_music;
        *playlist = new_music;
        printf("Music added: %s\n", name);
        return;
    }

    music* begin = *playlist;
    music* end = begin->prev;

    new_music->next = begin;
    new_music->prev = end;

    end->next = new_music;
    begin->prev = new_music;

    printf("Music added: %s\n", name);
}

void remove_music(music** playlist, int id){
    if(*playlist == NULL){
        printf("The playlist is empty! Nothing to remove.\n");
        return;
    }

    music* current = *playlist;
    music* node_to_remove = NULL;

    do{
        if(current->music_id == id){
            node_to_remove = current;
            break;
        }
        current = current->next;
    } while(current != *playlist);

    if(node_to_remove == NULL){
        printf("ID music %d not found", id);
        return;
    }

    if(node_to_remove->next == node_to_remove){
        *playlist = NULL;
    } else {
        music* def_prev = node_to_remove->prev;
        music* def_next = node_to_remove->next;

        def_prev->next = def_next;
        def_next->prev = def_prev;

        if(node_to_remove == *playlist){
            *playlist = def_next;
        }
    }

    printf("Removing: ID %d | Music: %s\n", node_to_remove->music_id, node_to_remove->music_name);
    free(node_to_remove);
}

void print_playlist(music* playlist){
    if(playlist == NULL){
        printf("The playlist is empty!\n");
        return;
    }

    printf("\n================= YOUR PLAYLIST(Circular) =================\n");

    music* current = playlist;

    do{
        printf("ID: %d | Music: %-20s | Artist: %s\n", current->music_id, current->music_name, current->artist_name);

        current = current->next;

    } while(current != playlist);

    printf("===========================================================\n");
}

void play_playlist(music* playlist){
    if(playlist == NULL){
        printf("The playlist is empty! Impossible to play music");
        return;
    }

    music* current = playlist;
    char command = '\0';

    printf("\n=============== STARTING INTERACTIVE PLAYER ===============\n");

    // e = exit;
    // n = next;
    // p = previous;

    while(command != 'e'){
        printf("\n===========================================================\n");
        printf("Playing now:\n");
        printf("ID: %d | Music: %s | Artist: %s\n", current->music_id, current->music_name, current->artist_name);
        printf("===========================================================\n");

        printf("Commands: [n] Next | [p] Previous | [e] Exit player\n");
        printf("Type your command: ");
        scanf(" %c", &command);
        clear_buffer_entry();

        switch(command){
            case 'n':
            case 'N':
                current = current->next;
                break;
            case 'p':
            case 'P':
                current = current->prev;
                break;
            case 'e':
            case 'E':
                printf("...Stopping the player and backing to menu.\n");
                break;
            default:
                printf("Invalid command. Try 'n', 'p' or 'e'.\n");
                break;
        }
    }
}

void release_playlist(music** playlist){
    if(*playlist == NULL){
        return;
    }

    music* begin = *playlist;
    music* current = begin;

    begin->prev->next = NULL;

    while(current != NULL){
        music* def_next = current->next;
        printf("Releasing memory: %s\n", current->music_name);
        free(current);
        current = def_next;
    }

    *playlist = NULL;
}

int main(){

    music* my_playlist = NULL;
    int option;
    int id;
    char name[MAX_NAME];
    char artist[MAX_NAME];

    do{
        printf("\n====================== PLAYLIST MENU ======================\n");
        printf("1. ADD MUSIC (at the end)\n");
        printf("2. REMOVE MUSIC (by ID)\n");
        printf("3. SHOW COMPLETE PLAYLIST\n");
        printf("4. PLAY PLAYLIST (interactive)\n");
        printf("0. EXIT PROGRAM\n");
        printf("===========================================================\n");

        if(scanf("%d", &option) != 1){
            printf("Invalid entry! Please, type one number.\n");
            clear_buffer_entry();
            option = -1;
            continue;
        }

        clear_buffer_entry();

        switch(option){
            case 1:
                printf("\n======================== ADD MUSIC ========================\n");
                printf("TYPE THE ID: ");
                scanf("%d", &id);
                clear_buffer_entry();

                printf("TYPE THE NAME OF THE MUSIC: ");
                fgets(name, MAX_NAME, stdin);
                name[strcspn(name, "\n")] = 0;

                printf("TYPE THE NAME OF THE ARTIST: ");
                fgets(artist, MAX_NAME, stdin);
                artist[strcspn(artist, "\n")] = 0;

                insert_music_end(&my_playlist, id, name, artist);
                break;

            case 2:
                printf("\n===================== REMOVE A MUSIC ======================\n");
                printf("TYPE THE ID OF THE MUSIC YOU WANT REMOVE: ");
                scanf("%d", &id);
                clear_buffer_entry();

                remove_music(&my_playlist, id);
                break;

            case 3:
                print_playlist(my_playlist);
                break;

            case 4:
                play_playlist(my_playlist);
                break;

            case 0:
                printf("EXITING AND RELEASING MEMORY...\n");
                release_playlist(&my_playlist);
                printf("MEMORY FREED!\n");
                break;

            case 99:
                printf("\n===========================================================\n");
                printf("COMPLETE NAME: CAUAN MORONHE LOPES\n");
                printf("DELIVERY DATE: 26/10/2025\n");
                printf("===========================================================\n");
                break;

            default:
                printf("INVALID OPTION! PLEASE, TRY AGAIN.\n");
                break;
        }
    } while(option != 0);

    return 0;
}

