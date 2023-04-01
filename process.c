#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define SHARED_MEMORY_SIZE 32 
#define SHARED_MEMORY_KEY "secret"


void show_shared_memory_menu();

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Programm takes 1 mandatory argument.\n");
        printf("Template: %s <name>\n", argv[0]);
        printf("Example: %s A\n", argv[0]);
        return 1;
    }
    
    // generate unique shared memory key
    key_t key = ftok(SHARED_MEMORY_KEY, 0);

    // get shared memory
    int shmid = shmget(key, SHARED_MEMORY_SIZE, 0666);

    // attach shared memory to the process
    char *shmaddr = shmat(shmid, NULL, 0);

    // work with shared memory
    for (;;) {
        printf("Program %s\n", argv[1]);
        show_shared_memory_menu();
        char choice; 
        choice = getchar();
        getchar(); // for \n

        if (choice == '1') {
            // show shared memory value
            printf("Current shared memory value: '%s'\n", shmaddr);
        } else if (choice == '2') {
            // change shared memory value
            printf("Type shared memory value.\n");
            printf("New value: ");
            fgets(shmaddr, SHARED_MEMORY_SIZE, stdin);
            shmaddr[strcspn(shmaddr, "\n")] = 0; // remove \n
        } else if (choice == '3') {
            // exit
            break;
        }
        printf("===\n");
    }

    // detach shared memory from the process
    shmdt(shmaddr);

    return 0;
}

void show_shared_memory_menu() {
    printf("1. Show shared memory value.\n");
    printf("2. Change shared memory value.\n");
    printf("3. Exit.\n");
}
