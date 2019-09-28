#include "unistd.h"
#include <stdio.h> 
#include <string.h> 

#define MAX_CMD_LEN  128
char data[100]={0};
/* ---FUNCTION--- */
int Check_File(char str[])
{
	int i=0,count=0;
	while (str[i]!='\0')
	{
		if (str[i]==' ')
		{
			count++;
		}
		i++;
	}
	if (count==2)
	{
		return 1;
	}
	return 0;
}
int Check_Sign(char str[])
{
	if (str[0]!=60 && str[0]!=62)
	{
		return 0;
	}
	return 1;
}

/* ---MAIN--- */
int main() 
{ 
	char command[MAX_CMD_LEN];
	while(1)
	{
		printf("osh>");
		fgets(command,MAX_CMD_LEN, stdin);
		printf("%s\n",command);
		if (Check_File(command)==1)
		{
			/* ---get function--- */
			char *token=strtok(command," "); 
			char *Redirect_File[3];
			Redirect_File[0]=token; // Redirect_File[0]=function
			 Redirect_File[0][strlen(Redirect_File[0])]='\0';
			printf("%s",Redirect_File[0]);
			/* ---get sign and file name--- */
			int i=1;
			while (token != NULL)
			{
				token=strtok(NULL, " ");
				strcpy(Redirect_File[i],token); // Redirect_File[1]=sign,Redirect_File[2]=file_name
				// Redirect_File[i][strlen(Redirect_File[i])]='\0';
				printf("%s\n",Redirect_File[i]);
				i++;
			}
		}
	}

	return 0; 
} 
