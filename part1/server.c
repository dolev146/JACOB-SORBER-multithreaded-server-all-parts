#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>

#define SERVERPORT 5003
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 100

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
char client_message[1024];

void *handle_connection(void *p_client_socket);
int check(int exp, const char *msg);

int main(int argc, char **argv)
{

    int server_socket, client_socket, addr_size;
    SA_IN server_addr, client_addr;

    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to craete socket");

    // initialize the adress struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVERPORT);

    check(bind(server_socket, (SA *)&server_addr, sizeof(server_addr)), "Bind Failed!");
    check(listen(server_socket, SERVER_BACKLOG), "Listen Failed!");

    while (true)
    {
        printf("Waiting for connections... \n");
        // wait for and eventually accept an incomming connection

        addr_size = sizeof(SA_IN);
        check(client_socket = accept(server_socket, (SA *)&client_addr, (socklen_t *)&addr_size), "accept failed");
        printf("connected! on socket %d \n", client_socket);

        // do whatever we do with connections.
        // handle_connection(client_socket);
        pthread_t t;
        int *pclient = (int *)malloc(sizeof(int));
        *pclient = client_socket;
        pthread_create(&t, NULL, &handle_connection, pclient);
        
    }
    close(server_socket);
    printf("server socket finish  %d", server_socket);
}

int check(int exp, const char *msg)
{
    if (exp == SOCKETERROR)
    {
        perror(msg);
        exit(1);
    }
    return exp;
}

void *handle_connection(void *p_client_socket)
{
    int client_socket = *((int *)p_client_socket);
    free(p_client_socket);
    char buffer[BUFSIZE] = "hi from server ";
    recv(client_socket, client_message, 1024, 0);
    printf("%s", client_message);
    send(client_socket, buffer, 1024, 0);
    close(client_socket);
    return NULL;
    // Dzone
    // int newSocket = client_socket;
    // recv(newSocket, client_message, 1024, 0);

    // printf("%s", client_message);
    // char *firstcli = &client_message[0];

    // // Send message to the client socket

    // // pthread_mutex_lock(&lock);
    // char *message = malloc(sizeof(client_message) + 20);
    // strcpy(message, "Hello Client : ");
    // strcat(message, firstcli);
    // strcat(message, "\n");
    // strcpy(buffer, message);
    // free(message);
    // // pthread_mutex_unlock(&lock);
    // sleep(1);
    // send(newSocket, buffer, 1000, 0);
    // printf("Exit socket number %d \n", newSocket);
    // close(newSocket);
    // pthread_exit(NULL);
    // Dzone
}
