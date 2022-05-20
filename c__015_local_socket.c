#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/un.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <errno.h>

#define SERVER "/tmp/test_socket"

/* Open socket from local socket */
int openMsgSocket(){
  int fd;
    struct sockaddr_un name;
    int fd_flags; 

    fd = socket(PF_LOCAL, SOCK_STREAM, 0);

    //Set socket to non-block mode
    fd_flags = fcntl(fd, F_GETFL, 0); 
    fcntl(fd, F_SETFL, fd_flags | O_NONBLOCK);

    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, SERVER);
    bind(fd, &name, SUN_LEN(&name));
    listen(fd, 5);
    
    return fd;
}

/* Send message to local socket */
void sendMsg(char *msg_string){
    int socket_fd;
    struct sockaddr_un name;

    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    name.sun_family = AF_LOCAL;
    strcpy(name.sun_path, SERVER);

    connect(socket_fd, &name, SUN_LEN(&name));


    int i = write(socket_fd, msg_string, strlen(msg_string)+1);
    if(i < 0){
        printf("write error\n");    
    }

    close(socket_fd);
}

/* Format string and call send message */
int debug(const char * __restrict format, ...){
  char buf[512];
    va_list arg;
    int rv;

    va_start(arg, format);
    rv = vsprintf(buf, format, arg);
    va_end(arg);
    
    sendMsg(buf);

    return rv;
}


int main (void){
    unlink(SERVER);
    pid_t chpid;
    
    if ( (chpid = fork()) == (pid_t) -1 ) {
        fprintf(stderr, "%s: fork(2)\n", strerror(errno));

        exit(1);

   } else if ( chpid == 0 ){
      /* child */
      printf("child start...\n");

      sleep(5);

      printf("child send msg 55555\n");
      debug("show cable modem");
      printf("child send msg 666\n");
      debug("show cmc version");
   }else{
      /* parent */
      printf("parent start...\n");           
      int fd = openMsgSocket();
      //int fd=5;

      printf("parent open socket\n");    
        
      while(1){
  
         int client_socket_fd;
         struct sockaddr_un client_name;
         int client_name_len;
         int i;
         char msg[512];

         client_socket_fd = accept(fd, &client_name, &client_name_len);

         if(client_socket_fd != -1){

            if(i = read(client_socket_fd, &msg, sizeof(msg)) > 0){
               printf("parent get msg %s\n", msg);
            }
            close(client_socket_fd);
         }   

      }
   }
   return 0;
}
