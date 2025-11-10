// Shared memory
//Server.c
//touch shared_mem_file

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h> 
#define SHM_SIZE 1024  // Size of the shared memory segment 
int main() { 
key_t key; 
int shmid; 
char *shm_addr; 
const char *message = "Hello from the server!"; 
// Generate a unique key for the shared memory 
key = ftok("shared_mem_file", 'A'); 
if (key == -1) { 
perror("ftok"); 
exit(1); 
} 
// Create the shared memory segment 
shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666); 
if (shmid == -1) { 
perror("shmget"); 
exit(1); 
} 
// Attach the shared memory segment to the process's address space 
shm_addr = shmat(shmid, NULL, 0); 
if (shm_addr == (char *) -1) { 
perror("shmat"); 
exit(1); 
} 
// Write the message to the shared memory 
printf("Server: Writing message to shared memory...\n"); 
strcpy(shm_addr, message); 
// Keep the segment attached for a while so the client can read 
sleep(10); // Sleep for 10 seconds 
// Detach from the shared memory 
if (shmdt(shm_addr) == -1) { 
perror("shmdt"); 
} 
// Remove the shared memory segment 
if (shmctl(shmid, IPC_RMID, NULL) == -1) { 
perror("shmctl"); 
} 
printf("Server: Shared memory segment removed.\n"); 
return 0; 
} 



//Client.c

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h> 
#define SHM_SIZE 1024  // Size of the shared memory segment 
int main() { 
key_t key; 
int shmid; 
char *shm_addr; 
// Generate the same unique key as the server 
key = ftok("file", 'A'); 
if (key == -1) { 
perror("ftok"); 
exit(1); 
} 
// Get the shared memory segment created by the server 
shmid = shmget(key, SHM_SIZE, 0666); 
if (shmid == -1) { 
perror("shmget"); 
exit(1); 
} 
// Attach the shared memory segment to the process's address space 
shm_addr = shmat(shmid, NULL, 0); 
if (shm_addr == (char *) -1) { 
perror("shmat"); 
exit(1); 
} 
// Read the message from the shared memory 
printf("Client: Reading message from shared memory...\n"); 
printf("Message received: \"%s\"\n", shm_addr); 
// Detach from the shared memory 
if (shmdt(shm_addr) == -1) { 
perror("shmdt"); 
} 
return 0; 
}

