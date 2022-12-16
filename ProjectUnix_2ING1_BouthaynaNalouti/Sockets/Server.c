#include "Server_Client.h"

int main()
{
	// Seed the random number generator with the current time
	srand(time(NULL));
	// Initialize variables
	int serverSocket, client_sockfd;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
			
	// Bind the socket to the address and port number.
	bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	// open file in previous directory named server_output.txt
	FILE *fp = fopen("../server_output.txt", "w");
	// Listen on the socket, with 100 max connection requests queued
	if (listen(serverSocket, 100) == 0){
		printf("Serveur à l'écoute au port %d...\n", PORT);
		fprintf(fp, "Serveur à l'écoute au port %d...\n", PORT);
	}else{
		printf("Error\n");
		fprintf(fp, "Error\n");
	}
	fflush(stdout);
	fflush(fp);
	while (1) {
		addr_size = sizeof(serverStorage);

		// Extract the first connection in the queue
		client_sockfd = accept(serverSocket, 
								(struct sockaddr*)&serverStorage,
								&addr_size);

		char client_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(((struct sockaddr_in *)&serverStorage)->sin_addr), client_ip, INET_ADDRSTRLEN);
		printf("Client connecté à partir de l'ip %s\n", client_ip);
		fprintf(fp, "Client connecté à partir de l'ip %s\n", client_ip);
		fflush(stdout);
		fflush(fp);
		if(fork() == 0){
			fflush(stdout);
			int num_client;
            /* lecture d’une question */
			recv(client_sockfd, &num_client, sizeof(num_client), 0);

            /* construction de la réponse */
			int num_gen[num_client];
			for (int i = 0; i < num_client; i++){
				num_gen[i] = rand() % NMAX + 1;
			}

            /* envoi de la réponse */
			send(client_sockfd, num_gen, sizeof(num_gen), 0);

			// Close the connection
			close(client_sockfd);
			exit(0);
		}else{
			close(client_sockfd);
		}
	}
	return 0;
}
