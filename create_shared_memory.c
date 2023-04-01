#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>

#define SHARED_MEMORY_SIZE 32 
#define SHARED_MEMORY_KEY "secret"

int main(int argc, char **argv) {
    // generate unique shared memory key
    key_t key = ftok(SHARED_MEMORY_KEY, 0);

    // create shared memory
    int shmid = shmget(key, SHARED_MEMORY_SIZE, 0666 | IPC_CREAT | IPC_EXCL);

    printf("Enter any key to delete shared memory...");
    getchar();

    // delete shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
