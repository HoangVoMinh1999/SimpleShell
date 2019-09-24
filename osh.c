#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LEN  128
#define HISTORY_BUFFER 20

int history(char hist[HISTORY_BUFFER][MAX_CMD_LEN], int current)
{
   //Dung bien check de kiem tra lich su co trong khong
   int check = 0;
   for (int i = 0; i < HISTORY_BUFFER; i++)
      if (hist[i][0] == '\0')
         check++;

   if (check == HISTORY_BUFFER - 1)
      printf("No commands in history!\n");
   else {
      int i = current;
      int hist_num = 1;
      do {
         if (hist[i][0] != '\0') {
            printf("%4d  %s\n", hist_num, hist[i]);
            hist_num++;
         }
         i = (i + 1) % HISTORY_BUFFER;
      } while (i != current);
   }
   return 0;
}

int clear_history(char hist[HISTORY_BUFFER][MAX_CMD_LEN])
{
   int i;
   for (i = 0; i < HISTORY_BUFFER; i++) {
      hist[i][0] = '\0';
   }
   return 0;
}

int main()
{
   char command[MAX_CMD_LEN];
   char hist[HISTORY_BUFFER][MAX_CMD_LEN] = {"\0"};
   int current = 0;

   while (1) {
      printf("osh>");
     
      fgets(command, MAX_CMD_LEN, stdin);

      //Truong hop 1: command trong (chi enter)
     
      if (strlen(command) == 1 && command[0] == '\n') {
         
         //Neu la command dau tien thi bat buoc phai nhap
         if (current == 0 && hist[HISTORY_BUFFER - 1] == NULL) {
            printf("Error! Please enter first command!\n");
            continue;
         }
         else {
            //free(hist[current]);
            if (current == 0) {
               strcpy(hist[current], hist[HISTORY_BUFFER - 1]);
               printf("%s\n", hist[current]);
            }
            else {
               strcpy(hist[current], hist[HISTORY_BUFFER - 1]);
               printf("%s\n", hist[current]);
            }
         }
      }
      
      //Truong hop 2: command binh thuong thi loai ki tu '\n' cuoi
      else {
         command[strlen(command) - 1] = '\0';
         //free(hist[current]);
         strcpy(hist[current], strdup(command));
      }

      strcpy(command, hist[current]);
      //Kiem tra lich su
      if (strcmp(command, "history") == 0)
         history(hist, current + 1);
      //Xoa buffer
      else if (strcmp(command, "clear") == 0) {
         clear_history(hist);
         printf("Removed history completed!\n");
      }
      //Thoat chuong trinh
      else if (strcmp(command, "exit") == 0)
      break;

      //Tang current sau moi lan chay
      current = (current + 1) % HISTORY_BUFFER;
   }
   
   //tra lai vung nho khi ket thuc chuong trinh
   clear_history(hist);

   return 0;
}
