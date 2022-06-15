#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main() {
  int sockfd, addr_len, bytes_read;
  char recv_data[1024];
  struct sockaddr_in server_addr, client_addr;
  addr_len = sizeof(struct sockaddr);

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    return 1;
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5000);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  memset(&server_addr.sin_zero, '\0', 8);

  if (bind(sockfd, (struct sockaddr *)&server_addr, addr_len) == -1) {
    perror("bind");
    return 1;
  }

  printf("UDPServer Waiting for client on port 5000\n");
  while (1) {
    bytes_read =
        recvfrom(sockfd, recv_data, 1024, 0, (struct sockaddr *)&client_addr,
                 (socklen_t *)&addr_len);
    recv_data[bytes_read] = '\0';
    printf("(%s , %d) said : %s", inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port), recv_data);
  }

  return 0;
}
