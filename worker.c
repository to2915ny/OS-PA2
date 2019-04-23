#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <signal.h>
#include <sys/time.h>


char cmd[100];
char buf[10];
int filenum=1;

pid_t child_pid;

struct student{
	int id;
	char password[100];
	char targetc[4096];
	char result[2048];
	struct student *p;
};

struct inoutc{
	char targetc[4096];
	struct {
		char input[100];
	}in[11];

	struct {
		char output[1024];
	}out[11];
	int state;	//0 for complete, 1 for compile error, 2 for time exceed
};

char *readFile(char *filename){
	FILE *f = fopen(filename, "r");
	
	fseek(f,0, SEEK_END);
	long length = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *buffer = (char *) malloc(length +1);
	buffer[length] = '\0';
	fread(buffer, 1, length, f);
	fclose(f);
	return buffer;
}

int compilation(){
	if(system("gcc -o test test.c")!=0)
                return -1;
	else
		return 0;
}

int alrm_handler(int sig)
{
	child_pid = getpid();
	sprintf(buf,"%d",child_pid);
	printf("%s\n",buf);
//	strcpy(cmd,"kill -9 ");
//	strcat(cmd, buf);
//	system(cmd);
//	signal(SIGINT, SIG_DFL);
	
	return -1;
}
void sig_handler(int sig)
{
	signal(SIGALRM, SIG_DFL);
	void sig_handler(int sig);    /// reestablishing signal
	exit(-1);
}

int execution(char *in){
	FILE *fp;
	struct itimerval t ;

//        signal(SIGALRM, alrm_handler) ;

//        t.it_value.tv_sec = 3 ;
//        t.it_value.tv_usec = 0 ; // 3.0sec
//        t.it_interval = t.it_value ;
	
        strcpy(cmd, "./test ");
	strcat(cmd,in);
        cmd[strlen(cmd)-1] = 0;
        strcat(cmd, " > ./");
	sprintf(buf,"%d",filenum);
	strcat(cmd, buf);
	strcat(cmd, ".out");
	
//	setitimer(ITIMER_REAL, &t, 0x0);

//	child_pid = getpid();
//	signal(SIGALRM, sig_handler);
        system(cmd);
	printf("testcase %d executed\n",filenum);
//	while(1){
//		if(alrm_handler == -1 || system(cmd) != 0)
//			return -1;
//		else if(i != 0){
//			return 0;
//		}
//	}

//	alarm(3);
	

	return 0;
}

void
child_proc(int conn)
{
	struct inoutc new;
	FILE *cp;
	int i, s ;
	char filename[15];
	
	while ( (s = recv(conn, (void*)&new, sizeof(struct inoutc), 0)) > 0 ) { }

	cp = fopen("./test.c","w");
	
	for(i = 0; (i<sizeof(new.targetc)) && (fputc(new.targetc[i], cp)!=EOF) ; i++);

	fclose(cp);
	
	if(compilation() == -1){
		new.state = 1;
		send(conn, (void*)&new, sizeof(struct inoutc), 0);
		printf("compilation error\n");
		return;
	} // passing the state of compilation error
	for(filenum = 1; filenum < 11; filenum++){
		if(execution(new.in[filenum-1].input) == -1){
			new.state = 2;
			printf("time over\n");
        	        send(conn, (void*)&new, sizeof(struct inoutc), 0);
                	return;
		} // passing the state of time exceed
		strcpy(filename, "./");
		sprintf(buf,"%d",filenum);
		strcat(filename, buf);
		strcat(filename, ".out");
		strcpy(new.out[filenum-1].output,readFile(filename));
		printf("testcase %d stored\n", filenum);
//		strcpy(cmd,"rm ");
//		strcat(cmd, buf);
//		strcat(cmd, ".out");
//		system(cmd);
	}
	system("rm test");
	system("rm test.c");
//	strcpy(new.out[index].output,readFile("./1.out"));

	s = send(conn, (void*)&new, sizeof(struct inoutc), 0);
	printf("test result sent\n");
	shutdown(conn, SHUT_WR) ;
	
	return;
}

int 
main(int argc, char const *argv[]) 
{ 
	int listen_fd, new_socket ; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0};
	FILE *fp;
	pthread_t thread1, thread2;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0) ;
	if (listen_fd == 0)  { 
		perror("socket failed : "); 
		exit(EXIT_FAILURE); 
	}
	
	memset(&address, '0', sizeof(address)); 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY ; 
	address.sin_port = htons(9494); 
	if (bind(listen_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed : "); 
		exit(EXIT_FAILURE); 
	} 

	while (1) {
		if (listen(listen_fd, 16 ) < 0) { 
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
	return 0;
} 
