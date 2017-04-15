/*-------------------------------------------------------------------------
 *  Server.c - Server Program - receives FOREVER messages for client
 *  Version:	$Name:  $
 *  Module:	
 *
 *  Purpose:	
 *  See:	
 *
 *  Author:	Hema Murthy (hema@bhairavi.iitm.ernet.in)
 *
 *  Created:        Fri 16-Mar-2007 13:46:26
 *  Last modified:  Mon 26-Mar-2007 10:04:02 by hema
 *  $Id: Server.c,v 1.1 2007/03/26 04:26:09 hema Exp hema $
 *
 *  Bugs:	
 *
 *  Change Log:	<Date> <Author>
 *  		<Changes>
 -------------------------------------------------------------------------*/

/* 
 * Example of server using UDP protocol
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include "./include/DgFunctions.h"  
/*-------------------------------------------------------------------------
 *  Usage -- Prints the usage for the program
 *    Args:	
 *    Returns:	Nothing
 *    Throws:	
 *    See:	
 *    Bugs:	
 -------------------------------------------------------------------------*/
void Usage()

{
  printf ("Server IPAddress PortNumber\n");
}	/*  End of Usage		End of Usage   */



/*-------------------------------------------------------------------------
 *  main -- Server Main Program - receives packets from client and echoes them back
 *    Args:	ServerIP, ServerPort
 *    Returns:	Nothing
 *    Throws:	
 *    See:	Unix Network Programming: Richard Stevens Vol I
 *    Bugs:	
 -------------------------------------------------------------------------*/
int  main(int argc, char **argv)
  {
    int                   sockFd;
    int                   serverPortNumber;
    struct sockaddr_in    serverAddr, clientAddr;

        /*
     * OPEN A UDP socket
     */
    if (argc != 3) {
      Usage();
      exit (-1);
    }
    sscanf(argv[2], "%d", &serverPortNumber);
    if (( sockFd = socket(AF_INET,SOCK_DGRAM ,0)) < 0) {
       printf( "server : can't bind local address \n");
       exit (-1);
    }
    bzero(( char *) &serverAddr , sizeof (serverAddr));
    serverAddr.sin_family   = AF_INET;
    serverAddr.sin_addr.s_addr  = inet_addr(argv[1]);
    serverAddr.sin_port  = htons(serverPortNumber);


    if (bind(sockFd,(struct sockaddr *) &serverAddr , sizeof (serverAddr))<0) {
      printf( "server : can't bind local addres\n");
       exit(-1);
    }
    
    DgEcho((int)sockFd, (struct sockaddr *) &clientAddr , (socklen_t)sizeof(clientAddr));
    printf("kavya is a good girl\n");
    return(0);
 }	/*  End of main		End of main   */





/*-------------------------------------------------------------------------
 * $Log: Server.c,v $
 * Revision 1.1  2007/03/26 04:26:09  hema
 * Initial revision
 *
 *
 * Local Variables:
 * time-stamp-active: t
 * time-stamp-line-limit: 20
 * time-stamp-start: "Last modified:[ 	]+"
 * time-stamp-format: "%3a %02d-%3b-%:y %02H:%02M:%02S by %u"
 * time-stamp-end: "$"
 * End:
 *                        End of Server.c
 -------------------------------------------------------------------------*/
