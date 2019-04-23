#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
struct student{
	int id;
	char password[100];
	char targetc[4096];
	int result;

};
char *readFile(char *filename) {
    FILE *f = fopen(filename, "r");
 //   assert(f);
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char *) malloc(length + 1);
    buffer[length] = '\0';
    fread(buffer, 1, length, f);
    fclose(f);
    return buffer;
}
int 
main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in serv_addr; 
	int sock_fd ;
	int s, len ;
	char buffer[1024] = {0}; 
	char * data ;
	int listen_fd, new_socket ;
        struct sockaddr_in address;
        int addrlen = sizeof(address);
	
	sock_fd = socket(AF_INET, SOCK_STREAM, 0) ;
	
	if (sock_fd <= 0) {
		perror("socket failed : ") ;
		exit(EXIT_FAILURE) ;
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(9059); 
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		perror("inet_pton failed : ") ; 
		exit(EXIT_FAILURE) ;
	} 

	if (connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("connect failed : ") ;
		exit(EXIT_FAILURE) ;
	}
	
	struct student stud;

	stud.id =21400547;
	strcpy(stud.password,"thisismypass");
	strcpy(stud.targetc,readFile(argv[1]));

	send(sock_fd,&stud, sizeof(struct student),0);
//	scanf("%s", buffer) ;
	shutdown(sock_fd,SHUT_WR);	
//	data = buffer ;
//	len = strlen(buffer) ;
//	s = 0 ;
//	while (len > 0 && (s = send(sock_fd, data, len, 0)) > 0) {
//		data += s ;
//		len -= s ;
//	}

	while(recv(sock_fd,buffer,1024,0)>0){
		printf("%s\n",buffer);
		
	
	}
	close(sock_fd);
//	create a new socket

	sock_fd = socket(AF_INET, SOCK_STREAM, 0) ;

        if (sock_fd <= 0) {
                perror("socket failed : ") ;
                exit(EXIT_FAILURE) ;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(9119);
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
                perror("inet_pton failed : ") ;
                exit(EXIT_FAILURE) ;
        }

        if (connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                perror("connect failed : ") ;
                exit(EXIT_FAILURE) ;
        }



	scanf("%s",buffer);
	
	send(sock_fd,buffer,1024,0);
	shutdown(sock_fd,SHUT_WR);
	printf("%s\n",buffer);
	printf("sent!\n");
//	recv(sock_fd,(void*)&stud,sizeof(struct student),0);
	printf("buck\n");
	
	while(recv(sock_fd,(void*)&stud,sizeof(struct student),0)>0)
	{}
	
	printf("%d cases passed!\n",stud.result);
		
	
//	printf("Please type);
/*

	
	char buf[1024] ;
	data = 0x0 ;
	len = 0 ;
	while ( (s = recv(sock_fd, buf, 1023, 0)) > 0 ) {
		buf[s] = 0x0 ;
		if (data == 0x0) {
			data = strdup(buf) ;
			len = s ;
		}
		else {
			data = realloc(data, len + s + 1) ;
			strncpy(data + len, buf, s) ;
			data[len + s] = 0x0 ;
			len += s ;
		}

	}
	printf(">%s\n", data); 
*/
} 

