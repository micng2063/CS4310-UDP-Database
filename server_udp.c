#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

main(int argc, char **argv)	{
	int s, namelen, client_address_size;
	struct sockaddr_in server, client;
	
	int num;
	char msg[30];

	/* Create a datagram socket in the internet domain and 
	use the UDP protocol. */
	s = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_family = AF_INET; /* Server is in Internet Domain */
	server.sin_port = htons(8000); /* port */
	server.sin_addr.s_addr = INADDR_ANY; /* Server's Internet Address */
	bind(s, (struct sockaddr *)&server, sizeof(server));
	
	// communication starts from here
	
	client_address_size = sizeof(client);
	
	// receive an integer from the client
	recvfrom(s, &num, sizeof(num), 0, (struct sockaddr *)&client, &client_address_size);
	printf("Integer received: %d\n", num);   
	
	// send a reply message to the client
	if (num == 1) {
		strcpy(msg, "Adding entry...");
	}
	else if (num == 2){
		strcpy(msg, "Searching entry...");
	}
	sendto(s, msg, sizeof(msg), 0, (struct sockaddr *)&client, sizeof(client));
	
	close(s);
}

