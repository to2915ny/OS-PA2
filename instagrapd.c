// Partly taken from https://www.geeksforgeeks.org/socket-programming-cc/

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
struct student{
	int id;
	char password[100];
	char targetc[4096];
	int result;
	struct student *p;
};

struct ioutc{
	char targetc[4096];

	struct {
	
	char input[100];


	}in[11];	

	struct {
	char output[1024];
	}out[11];
	int state;
}i;
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

void
child_proc(int conn)
{
	struct student new;
	int len = 0 ;
	int s ;
	int result = 1;
	struct student stu;
	
//	struct inoutc i;
	while((s= recv(conn,(void*)&stu,sizeof(struct student),0))>0){
	new.id = stu.id;
	strcpy(new.password,stu.password);
	strcpy(new.targetc,stu.targetc);

	}	
	printf("%s\n",new.password);
	strcpy(i.targetc,stu.targetc);

// copy .in files to struct 		

	strcpy(i.in[0].input,readFile("./testcase/1.in"));
	strcpy(i.in[1].input,readFile("./testcase/2.in"));
	strcpy(i.in[2].input,readFile("./testcase/3.in"));
        strcpy(i.in[3].input,readFile("./testcase/4.in"));
	strcpy(i.in[4].input,readFile("./testcase/5.in"));
        strcpy(i.in[5].input,readFile("./testcase/6.in"));
	strcpy(i.in[6].input,readFile("./testcase/7.in"));
        strcpy(i.in[7].input,readFile("./testcase/8.in"));
	strcpy(i.in[8].input,readFile("./testcase/9.in"));
        strcpy(i.in[9].input,readFile("./testcase/10.in"));

//	printf("%s\n",i.in[0].input);
//	printf("%s\n",i.targetc);
//=====================Worker Socket========================//
 	struct sockaddr_in serv_addr;
        int sock_fd ;
      //  int s, len ;
        char buffer[1024] = {0};
        char * data ;

        sock_fd = socket(AF_INET, SOCK_STREAM, 0) ;
        if (sock_fd <= 0) {
                perror("socket failed : ") ;
                exit(EXIT_FAILURE) ;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(9494);
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
               perror("inet_pton failed : ") ;
                exit(EXIT_FAILURE) ;
       }

        if (connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                perror("connect failed : ") ;
                exit(EXIT_FAILURE) ;
        }



	send(sock_fd,&i, sizeof(struct ioutc),0);

	shutdown(sock_fd,SHUT_WR);


	recv(sock_fd,(void*)&i,sizeof(struct ioutc),0);

	//state =0 complete, state = 1 error, state =2 time exceed
	int count =0;
	if(i.state == 0){
//	printf("%s\n",i.out[0].output);
	
	if(strcmp(i.out[0].output, readFile("./1.out")) ==0)
		count++;
	if(strcmp(i.out[1].output, readFile("./2.out")) ==0)
                count++;
	if(strcmp(i.out[9].output, readFile("./10.out")) ==0)
                count++;
	if(strcmp(i.out[2].output, readFile("./3.out")) ==0)
                count++;
        if(strcmp(i.out[3].output, readFile("./4.out")) ==0)
                count++;
	if(strcmp(i.out[4].output, readFile("./5.out")) ==0)
                count++;
        if(strcmp(i.out[5].output, readFile("./6.out")) ==0)
                count++;
	if(strcmp(i.out[6].output, readFile("./7.out")) ==0)
                count++;
	
        if(strcmp(i.out[7].output, readFile("./8.out")) ==0)
                count++;
	if(strcmp(i.out[8].output, readFile("./9.out")) ==0)
                count++;
	stu.result = count;

	printf("Number of test cases passed is : %d\n",stu.result);
	data = "It's complete, please type in password";
	len=strlen(data);
	send(conn,data,len,0);
	while(recv(conn,buffer,1024,0)>0){	
	
	printf("%s\n",buffer);
	}
//	strcpy(stu.result,"YOUHavePAssed");
	if(strcmp(buffer,stu.password)==0){
		send(conn,&i,sizeof(struct student),0);
		shutdown(conn,SHUT_WR);

		}			
	//send(conn,&i,sizeof(struct student),0);

	}
	else if(i.state ==1){
		printf("Compilation error\n");
	}
	else if(i.state ==2)
	{
		printf("Time takes too long\n");
	}
//	printf("%s\n",i.out[0].output);
	
//	strcpy(testtest, i.out[0].output);
/*	while ( (s = recv(conn, buf, 1023, 0)) > 0 ) {
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
	printf(">%s\n", data) ;
	
	orig = data ;
	while (len > 0 && (s = send(conn, data, len, 0)) > 0) {
		data += s ;
//		len -= s ;
	}
	data = orig;
//	len =0;
//	printf("%s\n",data);
	shutdown(conn, SHUT_WR) ;
//	if (orig != 0x0) 
//	free(orig) ;

//worker
 	struct sockaddr_in serv_addr;
        int sock_fd ;
      //  int s, len ;
        //char buffer[1024] = {0};
       // char * data ;

        sock_fd = socket(AF_INET, SOCK_STREAM, 0) ;
        if (sock_fd <= 0) {
                perror("socket failed : ") ;
                exit(EXIT_FAILURE) ;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(9293);
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
                perror("inet_pton failed : ") ;
                exit(EXIT_FAILURE) ;
        }

        if (connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                perror("connect failed : ") ;
                exit(EXIT_FAILURE) ;
        }

	//scanf("%s", buffer) ;

        //data = buffer ;
        //len = strlen(buffer) ;
//        s = 0 ;
	printf("%s\n",data);
        while (len > 0 && (s = send(sock_fd, data, len, 0)) > 0) {
                data += s ;
                len -= s ;
        }

        shutdown(sock_fd, SHUT_WR) ;

//        char buf[1024] ;
        data = 0x0 ;
        len = 0 ;
        while ( (s = recv(sock_fd, buf, 1023, 0)) > 0 ) {
                buf[s] = 0x0 ;
                if (data == 0x0) {
                        data = strdup(buf) ;
                        len = s ;
:                }
                else {
                        data = realloc(data, len + s + 1) ;
                        strncpy(data + len, buf, s) ;
                        data[len + s] = 0x0 ;
                        len += s ;
                }

        }
        printf("from worker >%s\n", data);
	if (orig != 0x0) 
	      free(orig) ;
*/
}

int 
main(int argc, char const *argv[]) 
{ 
	int listen_fd, new_socket ; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 

	char buffer[1024] = {0}; 

	listen_fd = socket(AF_INET /*IPv4*/, SOCK_STREAM /*TCP*/, 0 /*IP*/) ;
	if (listen_fd == 0)  { 
		perror("socket failed : "); 
		exit(EXIT_FAILURE); 
	}
	
	memset(&address, '0', sizeof(address)); 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY /* the localhost*/ ; 
	address.sin_port = htons(9393); 
	if (bind(listen_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed : "); 
		exit(EXIT_FAILURE); 
	} 

	while (1) {
		if (listen(listen_fd, 16 /* the size of waiting queue*/) < 0) { 
			perror("listen failed : "); 
			exit(EXIT_FAILURE); 
		} 

		new_socket = accept(listen_fd, (struct sockaddr *) &address, (socklen_t*)&addrlen) ;
		if (new_socket < 0) {
			perror("accept"); 
			exit(EXIT_FAILURE); 
		} 

		if (fork() > 0) {
			child_proc(new_socket) ;
		}
		else {
			close(new_socket) ;
		}
	}
} 

