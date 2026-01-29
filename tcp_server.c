/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h> 
 #include <sys/socket.h>
 #include <netinet/in.h>
 
 void error(const char *msg)
 {
     perror(msg);
     exit(1);
 }
 
 int main(int argc, char *argv[])
 {
     /* 1. What is argc and *argv[]?
      * argc is the number of arguments passed to the program
      * argv[] is an array of strings that contains the arguments passed to the program
      */
     int sockfd, newsockfd, portno;
     /* 2. What is a UNIX file descriptor and file descriptor table?
      * A file descriptor is a small integer that uniquely identifies an open file in the system.
      * A file descriptor table is a data structure that maps file descriptors to the files they represent.
      */
     socklen_t clilen;
 
     struct sockaddr_in serv_addr, cli_addr;
     /* 3. What is a struct? What's the structure of sockaddr_in?
      * A struct is a collection of variables of different types that are grouped together under a single name.
      * The structure of sockaddr_in is:
      * sin_family: The address family of the socket.
      * sin_port: The port number of the socket.
      * sin_addr: The IP address of the socket.
      * sin_zero: A padding field to make the structure the same size as sockaddr.
      */
     
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     /* 4. What are the input parameters and return value of socket()
      * The input parameters are the address family, socket type, and protocol.
      * The return value is a file descriptor for the socket.
      */
     
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     /* 5. What are the input parameters of bind() and listen()?
      *
      * The input parameters are the socket file descriptor, the address of the server, and the length of the address.
      * The return value is 0 if the binding is successful, -1 if it fails.
        */
     
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     
     while(1) {
         /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
         *
         * The while loop is used to handle multiple connections to the server.
         * If there are multiple simultaneous connections, the server can handle them all by using the fork() system call.
         * Fork() creates a new process that is a copy of the current process.
         * The new process will handle the new connection, while the current process will continue to listen for new connections.
         */
         
     char buffer[256];
         newsockfd = accept(sockfd, 
                     (struct sockaddr *) &cli_addr, 
                     &clilen);
     /* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
    * 
    * Fork() is a system call that creates a new process that is a copy of the current process.
    * The new process will handle the new connection, while the current process will continue to listen for new connections.
    * This is useful because it allows the server to handle multiple connections at the same time.
    */
         
     if (newsockfd < 0) 
              error("ERROR on accept");
     bzero(buffer,256);
         
     n = read(newsockfd,buffer,255);
         if (n < 0) 
             error("ERROR reading from socket");
         //printf("Here is the message: %s\n",buffer);
         n = write(newsockfd,"I got your message",18);
         if (n < 0) 
             error("ERROR writing to socket");
         close(newsockfd);
     }
     close(sockfd);
     return 0; 
 }
   
 /* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 * It asks the operating system to do something that it can't do on its own.
 */