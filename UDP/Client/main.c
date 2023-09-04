
#include "main.h"


void get_input_string(char *str_in);


int main(void)
{
	struct sockaddr_in sock_client;		// initilaize struct of socket
	int fd;					// deskriptor socket
	int slen;				// len structure socket
	char buf[BUFLEN];
	char temp_buf[BUFLEN];
	int recv_len;				// len received mesage

	if ( (fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){perror("can't socket");return -1;}

	/////////////////////////////////////////////////////
	// zero out the structure
	memset((char *) &sock_client, 0, sizeof(sock_client));
	slen = sizeof(sock_client);				// len structure socket
	// init structure
	sock_client.sin_family = AF_INET;
	sock_client.sin_port = htons(PORT);
	/////////////////////////////////////////////////////
	if (inet_aton(SERVER , &sock_client.sin_addr) == 0){fprintf(stderr, "inet_aton() failed\n");return -1;}

	while(1)
	{
		printf("Enter message : ");
		get_input_string(buf);
		
		//send the message
		if (sendto(fd, buf, strlen(buf) , 0 , (struct sockaddr *) &sock_client, slen)==-1){perror("can't sendto");return -1;}//receive a reply and print it
		strncpy (temp_buf, buf,BUFLEN);
		
		memset(buf,'\0', BUFLEN);//clear the buffer by filling null, it might have previously received data
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *) &sock_client, &slen)) == -1){perror("can't recvfrom()");return -1;}
		buf[recv_len] = 0;
		printf("Data: %s\n" , buf);
		if (strcmp (temp_buf, "exit")==0){break;}
	}

	close(fd);
	return 0;
}



void get_input_string(char *str_in)
{
    int ch = 0;
    int temp_count = 0;
    while ((ch = getchar()) != '\n')
    {
        (*(str_in + temp_count)) = ch;
        ++temp_count;
        if(temp_count > (BUFLEN - 2 ))
        {
//          (*(str_in + temp_count)) = '\n';
//          ++temp_count;
          break;
        }
    }
//    (*(str_in + temp_count)) = '\n';
    (*(str_in + temp_count)) = 0;    
}




