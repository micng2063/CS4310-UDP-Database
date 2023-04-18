#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
void printMenu(){
	printf( "-------------------------\n");
	printf( "- Student Database Menu -\n");
	printf( "-------------------------\n");
	printf( "1. Add Entry\n");
	printf( "2. Search with ID\n");
	printf( "4. Display Database\n");
	printf( "-------------------------\n");
}

int main(int argc, char **argv) {
	int s, server_address_size;
	unsigned short port;
	struct sockaddr_in server;
	char buf[32];
	struct hostent *hostnm;
	
	int num; 
	char msg[30];
	
	if ((s = socket(AF_INET, SOCK_DGRAM, 0))<0){
		printf("socket creation error");
	}
	
	server.sin_family = AF_INET; // Internet domain
	server.sin_port = htons(8000); // port
	hostnm = gethostbyname(argv[1]);  //get server's name
	server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr); 
	
	// communication starts from here
	
	server_address_size = sizeof(server);
	
	// send an integer to the server
	printMenu();
	printf("Enter choice: ");
	scanf("%d", &num);
	sendto(s, &num, sizeof(num), 0, (struct sockaddr *)&server, server_address_size);
	
	if (num == 4){
		int size;
		recvfrom(s, &size, sizeof(size), 0, (struct sockaddr *)&server, &server_address_size);
		int j;
		for (j = 0; j < size; j++){
			int id; 
			int score;
			char msgfName[50];
			char msglName[50];
			int order = j + 1;
			
			recvfrom(s, &id, sizeof(id), 0, (struct sockaddr *)&server, &server_address_size);
			recvfrom(s, msgfName, sizeof(msgfName), 0, (struct sockaddr *)&server, &server_address_size);
			recvfrom(s, msglName, sizeof(msglName), 0, (struct sockaddr *)&server, &server_address_size);
			recvfrom(s, &score, sizeof(score), 0, (struct sockaddr *)&server, &server_address_size);
			
			printf("%d .", order);
			printf("%s ", msgfName);
			printf("%s \t", msglName);
			printf(" - %d\t", id);   
			printf(" - %d\n", score);   // new data send as address
		}
	}
	// receive a message from the server
	recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr *)&server, &server_address_size);
	printf("%s\n", msg);
	
	close(s);
}
