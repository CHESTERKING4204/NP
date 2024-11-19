#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // write, read, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h> // strlen, memset

const char message[] = "Hello sockets world\n";

int main(int argc, char const *argv[]) {

  int serverFd;
  struct sockaddr_in server;
  int len;
  int port = 1234;
  char *server_ip = "127.0.0.1";
  char buffer[1024];
  char recv[1024];
  
  serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFd < 0) {
    perror("Cannot create socket");
    exit(1);
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(server_ip);
  server.sin_port = htons(port);
  len = sizeof(server);
  if (connect(serverFd, (struct sockaddr *)&server, len) < 0) {
    perror("Cannot connect to server");
    exit(2);
  }

  while(1)
 {
  printf("Enter message for server: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
  if (write(serverFd, buffer, strlen(buffer)) < 0) {
    perror("Cannot write");
    exit(3);
  }
  if(strcmp(buffer,"bye")==0)
 {
  break;
 }
  memset(recv, 0, sizeof(recv));
  if (read(serverFd, recv, sizeof(recv)) < 0) {
    perror("cannot read");
    exit(4);
  }
  printf("Received %s from server\n", recv);
 }
  close(serverFd);
  return 0;
}
