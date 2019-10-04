#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
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
   for (int i = 0; i < HISTORY_BUFFER; i++) {
      hist[i][0] = '\0';
   }
   return 0;
}

int main()
{
   char command[MAX_CMD_LEN];
   char hist[HISTORY_BUFFER][MAX_CMD_LEN] = {"\0"};
   int current = 0;
   char* args[20];
   char* rest = command;
   int i = 0;
   int copy_desc;
   int check;

   while (1) {
      printf("osh>");
      fflush(stdout);
      fgets(command, MAX_CMD_LEN, stdin);

      //Truong hop 1: command trong (chi enter)
      if (strlen(command) == 1 && command[0] == '\n') {
         //Truong hop la vi tri dau tien
         if (current == 0){
            //Mang chua lap day HISTORY_BUFFER
            if (hist[HISTORY_BUFFER - 1][0] == '\0')
               printf("Error! Please enter first command!\n");
            //Truong hop buffer da day va quay lai vi tri dau tien
            else {
               strcpy(hist[current], hist[HISTORY_BUFFER - 1]);
               strcpy(command, hist[HISTORY_BUFFER - 1]);
               printf("%s\n", hist[current]);
            }
         }
         //Truong hop khong phai la vi tri dau tien
         else {
            strcpy(hist[current], hist[current - 1]);
            strcpy(command, hist[current - 1]);
            printf("%s\n", hist[current]);
         }
      }

      //Truong hop 2: command binh thuong thi loai ki tu '\n' cuoi
      else {
         command[strlen(command) - 1] = '\0';
         strcpy(hist[current], command);
      }

      //Goi fork() de chia tien trinh
      pid_t pid = fork();

      //Kiem tra tien trinh
         //Tien trinh con
      if (pid == 0) {
            //Tach command thanh tung chuoi vao args
            while(args[i] = strtok_r(rest, " ", &rest)){
               i++;
            }
            args[i] = NULL;

            //Command yeu cau ghi ra file
            if (args[i-2][0] == '>') {
               int fd = open(args[i-1], O_WRONLY | O_APPEND | O_CREAT);

               if (fd < 0)
                  printf("Error opening the file!\n");

               copy_desc = dup(1);
               dup2(fd, 1);
               args[i-2] = NULL;
               check = 1;
            }

            //Command yeu cau thuc thi lenh voi file input
            if (args[i-2][0] == '<') {
               int fd = open(args[i-1], O_RDONLY);

               if (fd < 0)
                  printf("Error opening the file!\n");

               copy_desc = dup(0);
               dup2(fd, 0);
               args[i-2] = NULL;
               check = 0;
            }

            //Xu li pipe()
            if (args[i-2][0] == '|') {
               pid_t pid_c;
               pid_c = fork();
            }

            execvp(args[0], args);
            exit(1);
         }
         //Tien trinh cha
      else if (pid > 0) {
         wait(NULL);
         if (check == 1)
            dup2(copy_desc, 1);
         if (check == 0)
            dup2(copy_desc, 0);
      }
      else {
         printf("Failed to create new process!\n");
      }

      strcpy(command, hist[current]);
      //Kiem tra lich su
      if (strcmp(command, "history") == 0)
         history(hist, current + 1);
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
