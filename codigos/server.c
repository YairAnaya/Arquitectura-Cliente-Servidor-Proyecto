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
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
    char *tmp;
    
    //ARGV[1] = puerto
    int puerto = atoi(argv[1]);
    //abrimos nuestro socket
    listen_fd = socket(AF_INET,SOCK_STREAM,0);

    //limpiando los datos
    bzero(&servaddr,sizeof(servaddr));
    
    //AF_INET : nos sirve para indicar que el socket se podra conectar con otros ordenadores
    servaddr.sin_family = AF_INET;
    //direccion del cliente que queremos atender
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);  //cualquier cliente
    //puerto que utilizaremos
    servaddr.sin_port = htons(puerto);

    //bind indica al sistema que tenemos abierto el socket y vamos a atender al servicio

    bind(listen_fd,(struct  sockaddr *)&servaddr,sizeof(servaddr));

    //listen indica que vamos a empezar a atender la llamada de los clientes
    //recibe la lista de clientes que vamos a soportar
    listen(listen_fd,10);
   //recoger los clientes de la lista de espera
   //si no hay ningun cliente la llamada quedara bloqueada hasta que haya
    comm_fd = accept(listen_fd,(struct sockaddr *)NULL,NULL);

    //mensaje de inicio

    printf(" - - - - Se inicio el servidor - - - -\n");

    //mientras no se escriba la palabra adios, se seguira con la comunicacion

    while(!strstr(cadena,"adios") && !strstr(sendLine,"adios")){
        
        //vacemos la cadena recibida , llenandola de zeros
        bzero(cadena,1024);

        //socket del que quemos leer
        read(comm_fd,cadena,1024);
        printf("Cliente : %s\n",cadena);

        FILE * pipe = popen(cadena,"r");

        //si la cadena no dice adios, hay que contestar el mensaje
        if(!strstr(cadena,"adios")){
            //escribimos nuestro mensaje
            //que será la llamada 
            //gets(sendLine);
            fgets(sendLine,1024,pipe);

            //enviamos mensaje
            write(comm_fd,sendLine,strlen(sendLine)+1);
        }
    }


    close(listen_fd);


}