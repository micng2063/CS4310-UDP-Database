#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdbool.h>

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
	
	// declare a student struct
	struct student stuData[20] = {	{ 123 , "Michelle" , "McMichelle", 90 } , 
								{ 133 , "Michael" , "McMichael", 90 } ,   
								{ 143 , "Mitchell" , "McMitchel", 89 }	};
	int i = 3;
	printf("0. Starting communication...\n");
	int step = 1;
	
	while (num != 6){
		printf("%d. ", step);
		if (num == 1) {
			printf("Adding entry...\n");
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
			printf("Searching ID...\n");
			
			int searchID;
			recvfrom(s, &searchID, sizeof(searchID), 0, (struct sockaddr *)&client, &client_address_size);
			bool foundID = false;
			
			char msgSearch[50];
			int j; 
			for (j = 0; j < i; j++){
				if (stuData[j].id == searchID)
				{
					foundID = true;
					break;
				}
			}
			if (foundID == true){
				strcpy(msgSearch, stuData[j].fName);
				strcat(msgSearch, " ");
				strcat(msgSearch, stuData[j].lName);
				strcat(msgSearch, " is found with the matching ID.");
			}
			else{
				strcpy(msgSearch, "ID cannot be found in database.");
			}
			
			sendto(s, &msgSearch, sizeof(msgSearch), 0, (struct sockaddr *)&client, sizeof(client));
		}
		else if (num == 3){
			printf("Searching score...\n");
			
			int searchScore;
			recvfrom(s, &searchScore, sizeof(searchScore), 0, (struct sockaddr *)&client, &client_address_size);
			
			int j;
			int k = 0;
			char msgScore[200];
			strcpy(msgScore, "Student with this or greater than this score:\n");
			
			for (j = 0; j < i; j++){
				if (searchScore <= stuData[j].score)	{
					strcat(msgScore, "- ");
					strcat(msgScore, stuData[j].fName);
					strcat(msgScore, " ");
					strcat(msgScore, stuData[j].lName);
					if (j != (i-1)) {
						strcat(msgScore, "\n");
					}
					k++; 
				}
			}
			if (k == 0){
				strcpy(msgScore, "No students with this score can be found.");
			}
			
			sendto(s, &msgScore, sizeof(msgScore), 0, (struct sockaddr *)&client, sizeof(client));
			
		}
		else if (num == 4){
			printf("Displaying database...\n");
			
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
		else if (num == 5){
			printf("Deleting entry...\n");
			
			int deleteID;	
			recvfrom(s, &deleteID, sizeof(deleteID), 0, (struct sockaddr *)&client, &client_address_size);
			bool foundID = false;
			
			int j;
			int k;
			for (j = 0; j < i; j++){
				if (stuData[j].id == (deleteID)){
					foundID = true;
					break;
				}
			}
			if (foundID == true){
				for (k = j; k < i; k++){
					char fNameT[30];
					
					stuData[k].id = stuData[k+1].id;
					stuData[k].score = stuData[k+1].score;
					strcpy(stuData[k].fName, stuData[k+1].fName );
					strcpy(stuData[k].lName, stuData[k+1].lName );
				}
				i--;
			}
		}
		else if (num < 1 || num > 6 ) {
			break;
		}
		
		step++;
		recvfrom(s, &num, sizeof(num), 0, (struct sockaddr *)&client, &client_address_size);
	}
	
	printf("%d. Closing communication...\n", step);
	
	close(s);
}

