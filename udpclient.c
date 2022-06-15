#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main() {
  int sockfd;
  char send_data[1024];
  struct sockaddr_in server_addr;
  struct hostent *host;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    return 1;
  }

  host = gethostbyname((char *)"127.0.0.1");
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5000);
  server_addr.sin_addr = *((struct in_addr *)host->h_addr);
  memset(&server_addr.sin_zero, '\0', 8);

  while (1) {
    printf("Type Something (q or Q to quit): ");
    fgets(send_data, 1024, stdin);

    if (strcmp(send_data, "q\n") == 0 || strcmp(send_data, "Q\n") == 0)
      break;
    else
      sendto(sockfd, send_data, strlen(send_data), 0,
             (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
  }

  return 0;
}
