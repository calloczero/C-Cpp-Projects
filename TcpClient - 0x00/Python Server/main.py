from sys import stdout, stderr, argv

import socket
import os

def routine(host: str, port: int) -> None:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        # assign port to process
        sock.bind((host, port))
        # listen for client
        print("Waiting for client!!!")
        sock.listen(1)
        # accept
        client, addr = sock.accept()
        # debug message
        print(f"New Client>>> {client} is connected!!!")
        # while loop
        # receive data
        data = client.recv(4096)
        # decode data
        data = data.decode("utf8")
        # print received data
        print(f"[{client}] >>> {data}")

def main():
    # check commandline arguments
    if len(argv) < 2:
        stderr.write(f"<host> <port>")
        stderr.flush()
    routine(argv[1], int(argv[2]))

if __name__=="__main__":
    main()
