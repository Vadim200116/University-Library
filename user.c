#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"structs.c"
#include "books.c"
#include"students.c"

#define STRING_SIZE 256  //длина строки файла
#define CASE_SIZE 32 //длина строки ввода
#define MASSIVE_SIZE 4096 // размер массива структур



int Writeusers(USER*Base,int size){
    FILE *Usersfile=fopen("users.csv", "r");
    char Basket[STRING_SIZE]; // содержимое userfile
    for(int i=0;i<size;i++){
        fgets(Basket, STRING_SIZE, Usersfile);
        strcpy(Base[i].login,strtok(Basket,";"));
        strcpy(Base[i].pass,strtok(NULL,";"));
        strcpy(Base[i].students,strtok(NULL,";"));
        strcpy(Base[i].books, strtok(NULL,"\n"));
    }
    fclose(Usersfile);
}

int main(){
    setlocale(LC_ALL,"Russian");
    FILE*Usersfile=fopen("users.csv","r");
    int NumberLine=0;
    if(Usersfile==NULL){
        printf("Ошибка, отсутствует файл с пользователями");
    }else{
        while(!feof(Usersfile)){  //считаем количество строк
            if((fgetc(Usersfile))=='\n'){
                NumberLine++;
            }
        }
        fclose(Usersfile);
        USER*Base;
        Base=calloc(MASSIVE_SIZE,sizeof(USER));
        Writeusers(Base, NumberLine);
        printf("Добро пожаловать!\n");
        char login[CASE_SIZE];
        char pass[CASE_SIZE];
        int found=0; // идентификатор логина
        int foundp=0;//идентфикатор пароля
        int NumUs=0;//номер пользователя
        int exit; //идентификатор выхода из программы
        int prog=0; //идентификатор присутствия в меню библиотек
         while(1){ //цикл авторизации
            exit=0;
            if(!found){
                printf("Введите логин(Q-чтобы выйти):");
                SetConsoleCP(1251);
                scanf("%s",&login);
                SetConsoleCP(866);
            }
            if(strcmp(login,"Q")==0){
                break;
            }
            if(!foundp){
                for(NumUs=0;NumUs<NumberLine;NumUs++){
                    if(strcmp(Base[NumUs].login,login)==0){
                        found=1;
                        printf("Введите пароль(Q-заново ввести логин):");
                        SetConsoleCP(1251);
                        scanf("%s",&pass);
                        SetConsoleCP(866);
                        if(strcmp(Base[NumUs].pass,pass)==0){
                            foundp=1;
                        }
                        if(!strcmp(pass,"Q")){
                            found=0;
                            foundp=0;
                            exit=1;
                        }
                        break;
                    }
                }
            }
            if(found==0&&exit==0){
                printf("Пользователь не найден\n");
            }
            if(foundp==0 && found==1){
                printf("Неверный пароль\n");
            }
            if(foundp==1 && found==1){
                if(prog==0){
                    printf("\nС возвращением, %s!\n",login);
                }
                if((strcmp(Base[NumUs].students,"1"))==0 && (strcmp(Base[NumUs].books,"1"))==0){
                    char UserButton[4];
                   if(prog==0){
                        printf("Вы можете выбрать библиотеку, которой хотите управлять:\nвведите 1 - чтобы открыть библиотеку students\nвведите 2 - чтобы открыть библиотеку books\n");
                        printf("(чтобы выйти, нажмите - Q)\n");
                   }
                    printf("admin:");
                    SetConsoleCP(1251);
                    scanf("%s",&UserButton);
                    SetConsoleCP(866);
                    if(!strcmp(UserButton,"1")){
                        students();
                        prog=1;
                    }else if(!strcmp(UserButton,"2")){
                        books();
                        prog=1;
                    }else if(!strcmp(UserButton,"Q")){
                        found=0;
                        foundp=0;
                        prog=0;
                    }else{
                        printf("Неопознанная команда\n");
                        prog=1;
                    }
                }
                if((strcmp(Base[NumUs].students,"1"))==0 && (strcmp(Base[NumUs].books,"0"))==0){
                    printf("Вы можете работать только с библиотекой студентов\n");
                    students();
                    found=0;
                    foundp=0;
                }
                if((strcmp(Base[NumUs].students,"0"))==0 && (strcmp(Base[NumUs].books,"1"))==0){
                    printf("Вы можете работать только с библиотекой книг\n");
                    books();
                    found=0;
                    foundp=0;
                }
            }
        }
    }
}
