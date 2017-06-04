#include <stdio.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

#define	BUF_SIZE	256
#define	PROJ_ID		32
#define	PATH_NAME	"."
#define	SERVER_MSG	1
#define	CLIENT_MSG	2

void error_handler(char *s)
{
	printf("%s\n",s );
	exit(1);
}
int main(int argc, char const *argv[])
{
	struct mymsgbuf
	{
		long	msgtype;
		char 	ctrlstring[BUF_SIZE];
	}msgbuffer;

	int 	qid;
	int 	msglen;
	key_t	msgkey;

	msgkey = ftok(PATH_NAME,PROJ_ID);
	if (msgkey == -1)
	{
			error_handler("ftok error\n");	
	}

	qid = msgget(msgkey,IPC_CREAT|0660);
	if (qid == -1)
	{
		error_handler("mssget error\n");
	}
	while(1)
	{
		printf("server:");
		fgets(msgbuffer.ctrlstring,BUF_SIZE,stdin);
		if(!strncmp("exit"),msgbuffer.ctrlstring,4)
		{
			msgctl(qid,IPC_RMID,NULL);
			break;
		}
		msgbuffer.ctrlstring[strlen(msgbuffer.ctrlstring)-1] = '\0';
		msgbuffer.msgtype = SERVER_MSG;

	}
	if(msgsnd(qid,&msgbuffer,strlen()))

	return 0;
}
