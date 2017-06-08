// tcp_client.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <time.h>
#define PORT 80


int sock;

void Error(char *mess)
{
  fprintf(stderr,"%s\n",mess);
  if (sock) close(sock);
  exit(-1);
}

char* recuperation(void) {
  struct sockaddr_in sin;
    char chemin[100];
    char domaine[32];
    char port[32];
    sprintf(chemin,"/v1/public/data/read/vberry/TESTVB_MONITORING/msg");
    strcpy(port,"80");
    strcpy(domaine,"api.beebotte.com");
    int port2=80;

  
    printf("-%s-\n", chemin);
    printf("-%s-\n", domaine);
    printf("%d\n", port2);
    
    struct hostent *hostinfo;
    hostinfo = gethostbyname(domaine);
    printf("ok");
    struct in_addr  **pptr;
    pptr = (struct in_addr **)hostinfo->h_addr_list;
    printf("Adresse IP de l'hote : %s\n",inet_ntoa(**(pptr)));
      //Creation de la socket
      sock = socket(AF_INET, SOCK_STREAM, 0);
      
      //Configuration de la connexion
      sin.sin_addr.s_addr = inet_addr(inet_ntoa(**(pptr)));
      sin.sin_family = AF_INET;
      sin.sin_port = htons(port2);
      
      //Tentative de connexion au serveur
      connect(sock, (struct sockaddr*)&sin, sizeof(sin));
      printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),htons(sin.sin_port));


      char buffer[100]="GET ";
      strcat(buffer, chemin);
      strcat(buffer, " HTTP/1.0\nHost: ");
      strcat(buffer, domaine);
      strcat(buffer, "\n\n");
      printf("%s", buffer);
      send(sock,buffer,strlen(buffer),0);

      char buffer2[1024]="";
      char buffer3[3000000]="";
      for(;;){
        int res = recv(sock, buffer2, sizeof buffer2 -1, 0);
        char * head;
        if((head=strstr(buffer2,"\r\n\r\n"))){
          strcat(buffer3, head+4);
        }

        else if(res > 0){
          buffer2[res]= '\0';
          strcat(buffer3, buffer2);
        }
        else{
          break;
        }
      }
      close(sock);

  return buffer3;

}

char* parsing(char text){
  
  
}


