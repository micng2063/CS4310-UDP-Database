#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

struct student {
   int id;
   char fName[20];
   char lName[20];
   int score;
};

int main(int argc, char **argv)	{
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
	
	// declare a student struct
	struct student stuData[20] = {	{ 123 , "Michelle" , "McMichelle", 90 } , 
								{ 133 , "Michael" , "McMichael", 90 } ,   
								{ 143 , "Mitchell" , "McMitchel", 89 }	};
	int i = 3;
	
	// send a reply message to the client

	if (num == 1) {
		strcpy(msg, "Adding entry...");
		int numID;
		int score;
		char fName[30];
		char lName[30];
		
		recvfrom(s, &numID, sizeof(numID), 0, (struct sockaddr *)&client, &client_address_size);
		recvfrom(s, fName, sizeof(fName), 0, (struct sockaddr *)&client, &client_address_size);
		recvfrom(s, lName, sizeof(lName), 0, (struct sockaddr *)&client, &client_address_size);
		recvfrom(s, &score, sizeof(score), 0, (struct sockaddr *)&client, &client_address_size);
			
		stuData[i].id = numID; // if not set ntohl, num = address
		strcpy(stuData[i].fName, fName);
		strcpy(stuData[i].lName, lName);
		stuData[i].score = score; 
		i++;
	}
	else if (num == 2){
		strcpy(msg, "Searching entry...");
	}
	else if (num == 4){
		strcpy(msg, "Displaying database...");
		
		int j;
		
		int size;
		size = i;
		sendto(s, &size, sizeof(size), 0, (struct sockaddr *)&client, sizeof(client));

		for (j = 0; j < i; j++){
			int numID;
			int score;
			char msgfName[50];
			char msglName[50];
			
			strcpy(msgfName, stuData[j].fName);
			strcpy(msglName, stuData[j].lName);
			numID = stuData[j].id;
			score = stuData[j].score;
			
			sendto(s, &numID, sizeof(numID), 0, (struct sockaddr *)&client, sizeof(client));
			sendto(s, msgfName, sizeof(msgfName), 0, (struct sockaddr *)&client, sizeof(client));
			sendto(s, msglName, sizeof(msglName), 0, (struct sockaddr *)&client, sizeof(client));
			sendto(s, &score, sizeof(score), 0, (struct sockaddr *)&client, sizeof(client));
		}
	}

	close(s);
}

