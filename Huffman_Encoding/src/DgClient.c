/*-------------------------------------------------------------------------
 *  DgClient.c - Sends a string to the Server
 *  Version:	$Name:  $
 *  Module:	
 *
 *  Purpose:	
 *  See:	
 *
 *  Author:	Hema Murthy (hema@bhairavi.iitm.ernet.in)
 *
 *  Created:        Sat 17-Mar-2007 10:57:59
 *  Last modified:  Sat 17-Mar-2007 14:14:24 by hema
 *  $Id: DgClient.c,v 1.1 2007/03/26 04:26:09 hema Exp hema $
 *
 *  Bugs:	
 *
 *  Change Log:	<Date> <Author>
 *  		<Changes>
 -------------------------------------------------------------------------*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

#define MAXLINE 512


/*-------------------------------------------------------------------------
 *  DgClient -- Sends packets to server and receives packets from server
 *    Args:	
 *    Returns:	Nothing
 *    Throws:	
 *    See:	Unix Network Programming: Richard Stevens Vol I
 *    Bugs:	
 -------------------------------------------------------------------------*/
 
 void DgClient(char *sendMsg, int sockFd , struct sockaddr *servAddr , socklen_t servlen, char *tempMsg)
   {
     int n;
     char recvMsg[MAXLINE];
       {
	 n = strlen(sendMsg);
	 printf("Kavya Was not here %d\n",strlen(sendMsg));
	 if(sendto(sockFd, sendMsg , n, 0 , servAddr , servlen) != n)
	   printf("DgClient : sendto error on socket \n");
	 printf ("Message Sent = %s\n", sendMsg);
        fflush(stdout);
	 /*
	  * Now read a message from the socket and write it to 
	  * standard output.
	  */
	 n = recvfrom(sockFd, recvMsg, MAXLINE, 0, 
	     (struct sockaddr *) 0 , ( socklen_t *) 0);

	 if(n < 0) {

	    printf("DgClient : recvfrom error \n");
            exit (-1) ;
	 }

	 recvMsg[n] = '\0';
	 printf("recvMsg -- %d\n",n );
	 printf("Received Message %s\n", recvMsg);
	 char *temp = "Retransmit";
	 if(strcmp(recvMsg,temp) == 0)
	 {
	 	n = strlen(tempMsg);
	 	if(sendto(sockFd, tempMsg , n, 0 , servAddr , servlen) != n)
	   	printf("DgClient : sendto error on socket \n");
	 	printf ("temp Message Sent = %s\n", tempMsg);
	 }
       }
   }	/*  End of DgClient		End of DgClient   */

/*-------------------------------------------------------------------------
 * $Log: DgClient.c,v $
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
 *                        End of DgClient.c
 -------------------------------------------------------------------------*/
