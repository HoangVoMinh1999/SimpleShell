#include "unistd.h"
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#define MAX_CMD_LEN  128
int data[100];
int len_of_data;
/* ---FUNCTION--- */
int Check_Command(char str[])
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
	if (count==3)
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
void Getter_Data_From_File(char *sign,char *file_name,int len_of_data,int data[])
{
	if (sign[0]==60) // dấu hiệu input
	{
		printf("Da chay ham nay\n");
		FILE *f=fopen(file_name,"r");
		if (f==NULL)
		{
			printf("FILE NOT EXIST");
			return NULL;
		}
		int i=0;
		fscanf(f,"%d",len_of_data);
		printf("%d\n",len_of_data);
		for (int i=0;i<len_of_data;i++)
		{
			fscanf(f,"%d",data[i]);
			printf("%d",data[i]);
		}
		fclose(f);
	}
	else if (sign[0]==62)
	{
		FILE *f=fopen(file_name,"w");
		if (f==NULL)
		{
			printf("No file output !!!");
			return NULL;
		}
		fprintf(f,"%d",len_of_data);
		for (int i=0;i<len_of_data;i++)
		{
			fprintf(f,"%s",data[i]);
		}
		fclose(f);
	}
}
/* ---MAIN--- */
int main() 
{ 
	char command[MAX_CMD_LEN];
	while(1)
	{
		printf("osh>");
		fgets(command,MAX_CMD_LEN, stdin);
		command[strlen(command)-1]=' ';
		command[strlen(command)]='\0';
		printf("%saa\n",command);
		if (Check_Command(command)==1) // Kiểm tra dòng code hợp lệ vs file
		{
			/* ---get function--- */
			char *token=strtok(command," "); 
			char *Redirect_File[4];
			Redirect_File[0]=token; // Redirect_File[0]=function
			/* ---get sign and file name--- */
			int i=1;
			while (token != NULL  && i<3)
			{
				token=strtok(NULL, " ");
				Redirect_File[i]=token; // Redirect_File[1]=sign,Redirect_File[2]=file_name
				i++;
			}
			for (int i=0;i<4;i++)
			{
				printf("vi tri thu [%d]=%saa\n",i,Redirect_File[i]);
			}
			if(Check_Sign(Redirect_File[1])==0)// nhập sai kí tự , khác < >
			{
				printf("Wrong command\n");
				continue;
			}
			else
			{
				Getter_Data_From_File(Redirect_File[1],Redirect_File[2],len_of_data,data);
				for (int i=0;i<10;i++)
				{
					printf("%d ",data[i]);
				}
			}
			
		}
	}
	return 0; 
} 
