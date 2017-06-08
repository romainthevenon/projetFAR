#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

void error(const char *msg) { perror(msg); exit(0); }


int sendToBeBotte(char *canal, char *clefCanal, char *ressource, char *data[])
{
    // data est un tableau de chaines (char[]), c-a-d un tableau de char a deux dimensions
    // printf("data[0] is %s\n",data[0]);
    //printf("data[3] is %s\n",data[3]);
 
    int i;
    char *host = "api.beebotte.com";
    /* !! TODO remplacer 'testVB' par le canal dans lequel publier (ex: partie12)
        (ici msg est la "ressource" que ce canal attend */
    char path[100] = "/v1/data/write/";
    strcat(path,canal);strcat(path,"/"); strcat(path,ressource);
    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, message_size;
    char *message, response[4096];

    // Necessaire pour envoyer des donnees sur beebottle.com (noter le token du canal a la fin) :
    char headers[300] ="Host: api.beebotte.com\r\nContent-Type: application/json\r\nX-Auth-Token: ";
    strcat(headers,clefCanal);strcat(headers,"\r\n"); 
    
    char donnees[4096] = "{\"data\":\""; // "data" est impose par beebotte.com
    for (i=0;i<3;i++) {
        strcat(donnees,data[i]);strcat(donnees,",");
    }
    strcat(donnees,data[3]);strcat(donnees,"\"}");

    /* How big is the whole HTTP message? (POST) */
    message_size=0;
    message_size+=strlen("%s %s HTTP/1.0\r\n")+strlen("POST")+strlen(path)+strlen(headers);
    message_size+=strlen("Content-Length: %d\r\n")+10+strlen("\r\n")+strlen(donnees); 
    /* allocate space for the message */
    message=malloc(message_size);

    /* Construit le message POST */
    sprintf(message,"POST %s HTTP/1.0\r\n",path); 
    sprintf(message+strlen(message), "%s",headers);
    sprintf(message+strlen(message),"Content-Length: %lu\r\n",strlen(donnees));
    strcat(message,"\r\n");              /* blank line     */
    strcat(message,donnees);             /* body           */

    /* What are we going to send? */
    printf("Request:\n%s\n-------------\n",message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");
    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");
    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80); // port 80
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0) error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total) error("ERROR storing complete response from socket");
    /* close the socket */
    close(sockfd); 

    /* process response */
    printf("Response:\n%s\n",response);

    free(message);
    return 0;
}


void sendData(void){
	
	char *infoApublier[5];
	infoApublier[0] = "type_msg=IP";
	infoApublier[1] = "type_ent=RJ";
	infoApublier[2] = "RFID=102030456";
	//infoApublier[3] = "couleur = rouge";         //en commentaire car maintenant on ne le publie plus
	infoApublier[4] = "data=162.38.111.119";
	
	char *channel = "partie0";

	char *ressource = "msg";

	char *channelKey = "1494771555601_SSGQdxJaJ801HBj4";

	sendToBeBotte(channel, channelKey, ressource, infoApublier);
}

