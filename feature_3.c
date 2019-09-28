#include "unistd.h"
#include <stdio.h> 
#include <string.h> 

#define MAX_CMD_LEN  128
int data[100];
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
void Getter_Data_From_File(char *sign,char *file_name,char data[])
{
	printf("Da chay ham nay\n");
	int len_of_data=0;
	if (sign==60) // dấu hiệu input
	{
		FILE *f=fopen(file_name,"rt");
		if (f==NULL)
		{
			printf("No file for getting data");
			return NULL;
		}
		fscanf(f,"%d",&len_of_data);
		printf("da chay cho nay\n");
		printf("%d\n",len_of_data);
		for (int i=0;i<len_of_data;i++)
		{
			fscanf(f,"%d",&data[i]);
		}
		fclose(f);
	}
	else if (sign==61)
	{
		FILE *f=fopen(file_name,"r");
		if (f==NULL)
		{
			printf("No file for getting data");
			return NULL;
		}
		fscanf(f,"%d",data);
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
		strncat(command," ",sizeof(char));
		if (Check_File(command)==1) // Kiểm tra dòng code hợp lệ vs file
		{
			/* ---get function--- */
			char *token=strtok(command," "); 
			char *Redirect_File[4];
			Redirect_File[0]=token; // Redirect_File[0]=function
			/* ---get sign and file name--- */
			int i=1;
			while (token != NULL)
			{
				token=strtok(NULL, " ");
				Redirect_File[i]=token; // Redirect_File[1]=sign,Redirect_File[2]=file_name
				i++;
			}
			if(Check_Sign(Redirect_File[1])==0)// nhập sai kí tự , khác < >
			{
				printf("Wrong command\n");
				continue;
			}
			else
			{
				Getter_Data_From_File(Redirect_File[1],Redirect_File[2],data);
				for (int i=0;i<10;i++)
				{
					printf("%d ",data[i]);
				}
			}
			
		}
	}
	return 0; 
} 
