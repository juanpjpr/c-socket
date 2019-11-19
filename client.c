#include <stdio.h>
#include <windows.h>

#define MAXBUFLEN 512
#define PORT 4950

char SendBuff[512]={
"Patricio Rey y Sus Redonditos de Ricota\n\n\
¡BANG! ¡BANG! ESTÁS LIQUIDADO (1989)\n\n\
Esa estrella era mi lujo\n\n\
¿Era todo? Pregunté.\n\
Soy un iluso.\n\
No nos dimos nada más,\n\
Sólo un buen gesto.\n\
Mordí el anzuelo una vez más.\n\
Siempre un iluso.\n\
Nuestra estrella se agotó\n\
Y era mi lujo.\n\
Ella fue por esa vez\n\
Mi héroe vivo, bah\n\
Fue mi único héroe\n\
En este lío.\n\
La más linda del amor\n\
Que un tonto ha visto soñar\n\
Metió mi rocanrol bajo este pulso.\n"
};

int main(int argc, char *argv[]){
  
  WSADATA wsaData;
  SOCKET conn_socket;
  struct sockaddr_in server;
  struct hostent *hp;
  int resp;
  
  //Inicializamos la DLL de sockets
  resp=WSAStartup(MAKEWORD(1,0),&wsaData);
  if(resp){
    printf("Error al inicializar socket\n");
    getchar();return -1;
  }

  //Obtenemos la IP del servidor... en este caso
  // localhost indica nuestra propia máquina...
  hp=(struct hostent *)gethostbyname("localhost");

  if(!hp){
    printf("No se ha encontrado servidor...\n");
    getchar();WSACleanup();return WSAGetLastError();
  }

  // Creamos el socket...
  conn_socket=socket(AF_INET,SOCK_DGRAM, 0);
  if(conn_socket==INVALID_SOCKET) {
    printf("Error al crear socket\n");
    getchar();WSACleanup();return WSAGetLastError();
  }
   
  memset(&server, 0, sizeof(server)) ;
  memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
  server.sin_family = hp->h_addrtype;
  server.sin_port = htons(PORT);

  // Se envían los datos
  resp=sendto(conn_socket, SendBuff, MAXBUFLEN, 0,(struct sockaddr *)&server,sizeof(struct sockaddr));
  if(resp==SOCKET_ERROR){ 
    printf("Error al enviar datos...\n");
    closesocket(conn_socket);WSACleanup();
    getchar();return WSAGetLastError();
  }
    
  // Visualizamos resultado...
  printf("Enviados %d bytes hacia %s\n",resp,inet_ntoa(server.sin_addr));
  getchar();
  
  // Cerramos el socket y liberamos la DLL de sockets
  closesocket(conn_socket);
  WSACleanup();
  return EXIT_SUCCESS;
} 
