// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[102] = {0};
    char *hello = "Hello from server";

    //****** Write a code somewhere here which can help to do privilege separation *********//

    printf("**** Server is now started **** \n");
    // printf("execve=0x%p\n", execve); // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    } // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    
    printf("Line 55 - I am Parent with id: %d\n", getpid());
    printf("Line 56 - My uid is: %d \n", getuid());
                              //******************* Separate part that processes the data from the client ***********//////////
    // ->> Creating a child process using fork
    pid_t forkedProcess;
    forkedProcess = fork();

    // If fork is unsuccessful, exit
    if (forkedProcess < 0)
    {
        printf("FATAL ERROR");
        exit(EXIT_FAILURE);
    }

    // --> If fork is successful, process the data from the client
    else if (forkedProcess == 0)
    {
        setuid(99999);
        printf("Line 73 - I am Child with id: %d of parent with id: %d \n", getpid(), getppid());
        printf("Line 74 - My uid is: %d \n", getuid());
        valread = read(new_socket, buffer, 1024);
        printf("%s\n", buffer);
        send(new_socket, hello, strlen(hello), 0);
        printf("Hello message sent\n");
    }
    else
    {
        int *stat_loc;
        printf("Line 83 - I am Child with id: %d of parent with id: %d \n", getpid(), getppid());
        waitpid(forkedProcess, stat_loc, 0);
        printf("Line 85 - I am Child with id: %d of parent with id: %d \n", getpid(), getppid());
    }

    //****** Write a code somewhere here which can help to do privilege separation *********//

    return 0;
}
