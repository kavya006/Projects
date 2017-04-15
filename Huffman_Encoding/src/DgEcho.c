/*-------------------------------------------------------------------------
 *  DgEcho.c - Reads a string from Client and writes it back to Client
 *  Version:	$Name:  $
 *  Module:	
 *
 *  Purpose:	
 *  See:	
 *
 *  Author:	Hema Murthy (hema@bhairavi.iitm.ernet.in)
 *
 *  Created:        Sat 17-Mar-2007 10:58:43
 *  Last modified:  Sat 17-Mar-2007 14:12:40 by hema
 *  $Id: DgEcho.c,v 1.1 2007/03/26 04:26:09 hema Exp hema $
 *
 *  Bugs:	
 *
 *  Change Log:	<Date> <Author>
 *  		<Changes>
 -------------------------------------------------------------------------*/

 
#include <stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include "string.h"
#include "stdlib.h"

#include "./assign2/Channel_Decoding.cpp"

#define  MAXMESG 2048


/*-------------------------------------------------------------------------
 *  DgEcho -- Reads a packet from client and sends it back to client
 *    Args:	
 *    Returns:	Nothing
 *    Throws:	
 *    See:	UNIX Network Programming - Richard Stevens: Vol I
 *    Bugs:	
 -------------------------------------------------------------------------*/
void DgEcho(int sockFd, struct sockaddr *pcliAddr, socklen_t  maxCliLen)
  {
    int       n;
    socklen_t cliLen;
  	
  	printf("entered dgecho\n");
    int i = 0;
  	for  ( ; ;)
	  {
      char mesg[MAXMESG] = "";
      printf("i ------ %d \t",i);
    		cliLen = maxCliLen;
        printf("kavya is a good girl\n");
        n = recvfrom(sockFd, mesg, MAXMESG, 0, pcliAddr, &cliLen);
  		  //printf("received string of size %d string is:%s\n",n, mesg);
        printf("Message -- %d\n",strlen(mesg));
    		if (n < 0) {
  		   printf("dg_echo : recvfrom error");
    		      // err_dump("dg_echo : recvfrom error");*/
    		   exit(-1);
  		  }
        if(ErrorDetection(mesg)==0)
        {
          cout << "print errirrrrrrrrrrrrrrrr" << endl;
          printf("\nRetransmit the Message\n");
          strcpy(mesg,"Retransmit");
        }
        else
        {
          cout << "successful" << endl;
          //printf("Message sent back to Client:%s\n", mesg);
          string filename;
          map<string, char> result;
          filename = "trail.txt";
          result = CodeMapping(filename);
          filename = "outtrail.txt";
          RegenerateSignal(result,filename,mesg); 
        }	
  		if (sendto (sockFd, mesg, n, 0, pcliAddr, cliLen) != n) {
  		   printf("dg_echo : sendto  error\n");
                     exit(-1);
  		  }
        i =i + 1;
  	}
  }	/*  End of DgEcho		End of DgEcho   */

	




/*-------------------------------------------------------------------------
 * $Log: DgEcho.c,v $
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
 *                        End of DgEcho.c
 -------------------------------------------------------------------------*/
