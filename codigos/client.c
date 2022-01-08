/*
Alumno:Anaya Ruiz Yair Alejandro
Profesor: Ing. Carlos Alberto Román Zamitiz
Materia: Arquitectura Cliente Servidor

PROYECTO FINAL
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include<string.h>

int main(int argc, char * argv[]){

    char cadena[1024];
    char sendLine[1024];
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd  = socket(AF_INET,SOCK_STREAM,0);
    //limpiar variables
    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));

    //argv[1] = IP , argv[2] = PUERTO

    inet_pton(AF_INET,argv[1],&(servaddr.sin_addr)); //recibe direccion del servidor

    connect(sockfd,(struct sockaddr * )&servaddr,sizeof(servaddr));

    printf("Se inicio el cliente!\n");

    while(!strstr(cadena,"adios") && !strstr(sendLine,"adios")){

        //limpiamos buffer
        bzero(cadena,1024);
        //leemos mensaje
        fgets(sendLine,1024,stdin);
        //mandamos el mensaje
        write(sockfd,sendLine, strlen(sendLine)+1);

        if(!strstr(cadena,"adios")){

            //leemos

            read(sockfd,cadena,1024);
            printf("Server : %s\n",cadena);

        }


    }


    printf("finalizacion de programa\n");
    close(sockfd);





 return 0;
}