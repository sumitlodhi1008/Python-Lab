#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090
#define MAXLEN 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[MAXLEN];
    FILE *fp;
    int bytes;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(server_fd, 5);

    printf("TCP Server waiting for connection on port %d\n", PORT);

    len = sizeof(cliaddr);
    client_fd = accept(server_fd, (struct sockaddr *)&cliaddr, &len);
    printf("Client connected.\n");

    fp = fopen("received_file.txt", "wb");

    while ((bytes = recv(client_fd, buffer, MAXLEN, 0)) > 0) {
        fwrite(buffer, 1, bytes, fp);
    }

    printf("File received successfully.\n");

    fclose(fp);
    close(client_fd);
    close(server_fd);
    return 0;
}
