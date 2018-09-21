#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <signal.h>

#define MAX_CHAR_READ 20500 //20KB
#define PORT 8080
#define HOST "127.0.0.1"

void readfile(char *filename, char *buffer) {
  char rows[MAX_CHAR_READ];
  FILE *file;
  file = fopen(filename, "r");
  if (!file) {
  	perror("Error reading file: ");
  	exit(1);
  } 
  else if (file) {
    while (fgets(rows, MAX_CHAR_READ, (FILE *)file)) {
       strcat(buffer, rows);
    }
  }
  fclose(file);
}

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getMemUsage(){ //Note: this value is in KB!
  FILE* file = fopen("/proc/self/status", "r");
  int result = -1;
  char line[128];

  while (fgets(line, 128, file) != NULL) {
    if (strncmp(line, "VmRSS:", 6) == 0){
        result = parseLine(line);
        break;
    }
  }
  fclose(file);
  return result;
}

void intHandler(int dummy) {
  printf("Memory usage: %d\n", getMemUsage());
  exit(0);
}

int main(int argc, char *argv[]) {
	char *filename = argv[1];
  char http_header[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";

  int server_fd, new_fd;
  struct sockaddr_in server_address;
  char request[MAX_CHAR_READ];
  char response[MAX_CHAR_READ];
  
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("Socket failed: ");
    exit(1);
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0) {
  	perror("Socket option failed: ");
  	exit(1);
  }

  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = inet_addr(HOST);
  server_address.sin_family = AF_INET;
  if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
    perror("Binding failed: ");
    close(server_fd);
    exit(1);
  }

  if (listen(server_fd, SOMAXCONN) < 0) {
    perror("Listen failed: ");
    close(server_fd);
    exit(1);
  }

  printf("Server is listening on port : %d\n", PORT);

  signal(SIGINT, intHandler);

  while (1) {
    socklen_t server_address_length = sizeof(server_address);
    if ((new_fd = accept(server_fd, (struct sockaddr *)&server_address, &server_address_length)) < 0) {
      perror("Request failed: ");
      close(server_fd);
		  exit(1);
    }

    read(new_fd, request, sizeof(request));
    // printf("%s\n", request);   logging is commented out for faster performance

    strcpy(response, http_header);
    
  	readfile(filename, response);

    write(new_fd, response, strlen(response));

    close(new_fd);
  }

  return 0;
}