
#include "main.h"


void revers_string(char *str);


int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in sock_serv, sock_client;
	char buf[BUFLEN];
	


	//create a TCP socket
	if ((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1){perror("can't open socket");return(-1);}
	puts("Socket created");
	/////////////////////////////////////////////////////
	// zero out the structure
	memset((char *) &sock_serv, 0, sizeof(sock_serv));
	// Prepare the sockaddr_in structure
	sock_serv.sin_family = AF_INET;
	sock_serv.sin_addr.s_addr = htonl(INADDR_ANY);
//    server.sin_addr.s_addr = INADDR_ANY;
    sock_serv.sin_port = htons(PORT);
	/////////////////////////////////////////////////////

	//Bind
	if( bind(socket_desc,(struct sockaddr *)&sock_serv , sizeof(sock_serv)) < 0){perror("bind failed. Error");return -1;}//print the error message
	puts("bind done");
	
	//Listen for connect with client
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&sock_client, (socklen_t*)&c);
	if (client_sock < 0){perror("accept failed");return -1;}
	puts("Connection accepted");
	
	//Receive a message from client
	while(1)
	{

		//try to receive some data, this is a blocking call
//        while( (read_size = recv(client_sock , buf , BUFLEN , 0)) > 0 )
		if ((read_size = recv(client_sock, buf, BUFLEN, 0)) == -1){perror("can't recv()");return(-1);}
        if(read_size == 0){puts("Client disconnected");break;}
		buf[read_size] = 0;
		
		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(sock_client.sin_addr), ntohs(sock_client.sin_port));
		printf("Data: %s\n" , buf);
		
		revers_string(buf);
		
		//Send the message back to client
		write(client_sock , buf , strlen(buf));
        if (strcmp (buf, "tixe")==0){break;}
	}
	

	close(socket_desc);
	return 0;
}


void revers_string(char *str)
{

	char temp_str[BUFLEN];
	int i = 0;
	int j = 0;
	while(0 != (*(str + i))){++i;}
	while(0 != i)
	{
	    --i;
	    temp_str[j] = (*(str + i));
	    ++j;
	}
	temp_str[j] = 0;
	strncpy (str, temp_str,BUFLEN);
}




