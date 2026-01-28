"""
Server receiver buffer is char[256]
If correct, the server will send a message back to you saying "I got your message"
Write your socket client code here in python
Establish a socket connection -> send a short message -> get a message back -> ternimate
use python "input->" function, enter a line of a few letters, such as "abcd"
"""
import socket

def main():
    # TODO: Create a socket and connect it to the server at the designated IP and port
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('127.0.0.1', 6666))
    # TODO: Get user input and send it to the server using your TCP socket
    message = input("Enter a message: ")
    s.send(message.encode())
    # TODO: Receive a response from the server and close the TCP connection
    response = s.recv(1024)
    print(response.decode())
    s.close()




if __name__ == '__main__':
    main()