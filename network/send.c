#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 

int main(void) {
    struct socketaddr_in peer; 
    int s, rc; 
    char buf[1]; 

    peer.sin_family = AF_INET; 
    peer.sin_port = htons(7500);
    peer.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    s = socket(AF_INET, SOCK_STREAM, 0); 
    if (s < 0) {
        perror("socket call failed"); 
        _Exit(1); 
    }
    rc = connect (s, (struct sockaddr *)&peer, sizeof (peer)); 
    if (rc) {
        perror("connect call failed"); 
        _Exit(1); 
    }
    rc = send(s, "1", 1, 0); 
    if (rc <= 0) {
        perror("recv call failed"); 
    } else {
        printf ("%c\n", buf[0]); 
    }
    _Exit(0); 
}
