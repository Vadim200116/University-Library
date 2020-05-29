#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include <time.h>
#include"structs.c"
#define S_STRING_SIZE 256
#define S_CASE_SIZE 64
#define S_MASSIVE_SIZE 4096

int ViewStudents(Anketa*Base, int size){
        printf("Таблица:\n");
        printf("________________________________________________________________________________________\n");
        printf("Номер зачетной книжки|    Фамилия    |    Имя   |    Отчество   |Факультет|Специальность|\n");
        for(int i=0;i<size;i++){
            if((strcmp(Base[i].RecBook, "del"))!=0){
                printf("________________________________________________________________________________________\n");
                printf("%21s|", Base[i].RecBook);
                printf("%15s|", Base[i].Surname);
                printf("%10s|", Base[i].Name);
                printf("%15s|", Base[i].Patron);
                printf("%9s|", Base[i].Faculty);
                printf("%13s|\n", Base[i].Spec);
            }
        }
        printf("________________________________________________________________________________________\n");
        printf("чтобы сохранить нажмите 8\n");
}

void WriteStudents(Anketa*Base, int size, char filename[S_CASE_SIZE]){
    FILE *Basefile=fopen(filename, "r");
    char Basket[S_STRING_SIZE];
    for(int i=0;i<size;i++){
        fgets(Basket, S_STRING_SIZE, Basefile);
        strcpy(Base[i].RecBook,strtok(Basket,";"));
        strcpy(Base[i].Surname,strtok(NULL,";"));
        strcpy(Base[i].Name,strtok(NULL,";"));
        strcpy(Base[i].Patron,strtok(NULL,";"));
        strcpy(Base[i].Faculty, strtok(NULL,";"));
        strcpy(Base[i].Spec, strtok(NULL,"\n"));
    }
    fclose(Basefile);
}

int AddStudent(Anketa*Base, int NumberLine){
        printf("ДОБАВЛЕНИЕ СТУДЕНТА\nНомер зачетной книжки:");
        char RecBook[S_CASE_SIZE];
        SetConsoleCP(1251);
        scanf("%s",&RecBook);
        SetConsoleCP(866);
        if((strcmp(RecBook,"Q"))==0){
            return 1;
        }
        int copy=0;
        for(int i=0; i<NumberLine; i++) {// Проверем есть если ли такая зачетка в базе
            if(strcmp(RecBook, Base[i].RecBook)==0){
                printf("Студент уже есть в базе.\n");
                copy=1;
                return 1;
            }
        }
        if(copy==1){ //если есть то возвращаемся в главное меню
            return 1;
        }
        if(copy==0){
            char Surname[S_CASE_SIZE];
            printf("Фамилия:");
            SetConsoleCP(1251);
            scanf("%s",&Surname);
            SetConsoleCP(866);
            if((strcmp(Surname,"Q"))==0){
                return 1;
            }
            char Name[S_CASE_SIZE];
            printf("Имя:");
            SetConsoleCP(1251);
            scanf("%s",&Name);
            SetConsoleCP(866);
            if((strcmp(Name,"Q"))==0){
                return 1;
            }
            char Patron[S_CASE_SIZE];
            printf("Отчество:");
            SetConsoleCP(1251);
            scanf("%s",&Patron);
            SetConsoleCP(866);
            if((strcmp(Patron,"Q"))==0){
                return 1;
            }
            char Faculty[S_CASE_SIZE];
            printf("Факультет:");
            SetConsoleCP(1251);
            scanf("%s",&Faculty);
            SetConsoleCP(866);
            if((strcmp(Faculty,"Q"))==0){
                return 1;
            }
            char Spec[S_CASE_SIZE];
            printf("специальность:");
            SetConsoleCP(1251);
            scanf("%s",&Spec);
            SetConsoleCP(866);
            if((strcmp(Spec,"Q"))==0){
                return 1;
            }
            strcpy(Base[NumberLine].RecBook,RecBook);
            strcpy(Base[NumberLine].Surname,Surname);
            strcpy(Base[NumberLine].Name,Name);
            strcpy(Base[NumberLine].Patron,Patron);
            strcpy(Base[NumberLine].Faculty,Faculty);
            strcpy(Base[NumberLine].Spec,Spec);
            printf("Студент добавлен\n");
            ViewStudents(Base, NumberLine+1);
            return 0;
        }
}

void DeleteStudent(Anketa*Base, int NumberLine){
                int del=0;
                printf("УДАЛЕНИЕ СТУДЕНТА\n");
                printf("введите номер зачетной книжки:");
                char RecBook[S_CASE_SIZE];
                SetConsoleCP(1251);
                scanf("%s",&RecBook);
                SetConsoleCP(866);
                if((strcmp(RecBook,"Q"))==0){
                    return;
                }
                for(int p=0; p<NumberLine; p++){
                    if(strcmp(Base[p].RecBook, RecBook)==0){
                        strcpy(Base[p].RecBook,"del");
                        del=1;
                        printf("Студент удален\n");
                        ViewStudents(Base, NumberLine);
                        break;
                    }
                }
                if(del==0){
                    printf("студент не найден\n");
                }
}

void SearchStudent(Anketa*Base,int NumberLine){
                printf("ПОИСК ИНФОРМАЦИИ ПО ФАМИЛИИ\nВведите фамилию:");
                char Surname[S_CASE_SIZE];
                SetConsoleCP(1251);
                scanf("%s",&Surname);
                SetConsoleCP(866);
                int found=0;
                int d=0;
                if((strcmp(Surname,"Q"))==0){
                    return;
                }
                for(int m=0;m<NumberLine;m++){
                    if((strcmp(Base[m].Surname, Surname))==0){
                        if(d==0){printf("________________________________________________________________________________________\n");
                        printf("Номер зачетной книжки|    Фамилия    |    Имя   |    Отчество   |Факультет|Специальность|\n");
                        printf("________________________________________________________________________________________\n");
                        }
                        d=1;
                        printf("%21s|%15s|%10s|%15s|%9s|%13s|\n",Base[m].RecBook,Base[m].Surname,Base[m].Name,Base[m].Patron,Base[m].Faculty,Base[m].Spec);
                        printf("________________________________________________________________________________________\n");
                        found=1;
                    }
                }
                if(found==0){
                    printf("студент с такой фамилией не найден\n");
                }
}

void ExitStudents(Anketa*Base, int NumberLine){
    FILE *Basefile=fopen("students.csv", "w"); // открываем файл для записи(при этом все данные удаляются)
    for(int i=0;i<NumberLine;i++){
        if((strcmp(Base[i].RecBook, "del"))!=0){
            fprintf(Basefile,"%s;%s;%s;%s;%s;%s\n",Base[i].RecBook,Base[i].Surname,Base[i].Name,Base[i].Patron,Base[i].Faculty,Base[i].Spec);
        }
    }
    printf("файл сохранен\n");
    fclose(Basefile);
    free(Base);
}















void students(){
    int NumberLineStud=0;
	FILE *StudFile=fopen("students.csv", "r");
	if(StudFile==NULL){
        printf("Файл не найден.");
    }else{
        printf("файл прочитан\n");
        while(!feof(StudFile)){  //считаем количество строк
            if((fgetc(StudFile))=='\n'){
                NumberLineStud++;
            }
        }
        printf("количество строк: %d\n",NumberLineStud);
        fclose(StudFile);
        Anketa*BaseStud;             //создаем массив BaseStud
        BaseStud=calloc(S_MASSIVE_SIZE,sizeof(Anketa));
        char filename[S_CASE_SIZE]="students.csv";
        WriteStudents(BaseStud, NumberLineStud, filename); //записываем данные файла в BaseStud (по структуре в файле structanketa.h
        if(NumberLineStud>0){ //выводим таблицу, если она не пустая
            ViewStudents(BaseStud,NumberLineStud);
        }
        printf("ВЫБЕРИТЕ ДЕЙСТВИЕ:(нельзя вводить пробелы)\n");
		printf("1 - чтобы добавить нового студента\n2 - чтобы удалить студента\n5 - чтобы создать бэкап\n6 - чтобы загрузить бэкап\n7 - чтобы найти информацию о студенте по его фамили\n8 - чтобы выйти с сохранением изменений\nQ - чтобы вернуться в предыдущее меню (работает во всех программах)\n");
        
         char StudButton[4];
        strcpy(StudButton,"0");
		while((strcmp(StudButton,"0"))==0){ //главный цикл
            printf("students:");
            SetConsoleCP(1251);
            scanf("%s",&StudButton);
            SetConsoleCP(866);
            printf("%s- ",StudButton);

            if((strcmp(StudButton,"0"))!=0 && (strcmp(StudButton,"1"))!=0 && (strcmp(StudButton,"2"))!=0 && (strcmp(StudButton,"5"))!=0 && (strcmp(StudButton,"6"))!=0 && (strcmp(StudButton,"7"))!=0 && (strcmp(StudButton,"8"))!=0 && (strcmp(StudButton,"Q"))!=0){
                printf("неопознанная команда\n");
                strcpy(StudButton,"0");
            }
// ПРОГРАММЫ:
            if((strcmp(StudButton,"Q"))==0){
                printf("Возврат в главное меню\n");
                return;
            }
            if ((strcmp(StudButton,"1"))==0){    //добавление студента
                if(AddStudent(BaseStud,NumberLineStud)!=1){
                NumberLineStud++;}
                strcpy(StudButton,"0");
            }
           if((strcmp(StudButton,"2"))==0){ //удаление студента
                DeleteStudent(BaseStud, NumberLineStud);
                strcpy(StudButton,"0");
            }

            if((strcmp(StudButton,"5"))==0){ 
                printf("Пока в разработке");
                 strcpy(StudButton,"0");
            }
            if((strcmp(StudButton,"6"))==0){ //загрузить бэкап
                printf("Пока в разработке");
                strcpy(StudButton,"0");
            }
            if((strcmp(StudButton,"7"))==0){  //найти информацию
                SearchStudent(BaseStud,NumberLineStud);
                strcpy(StudButton,"0");
            }
            if ((strcmp(StudButton,"8"))==0){	//выход из программы с сохранением изменений
                ExitStudents(BaseStud, NumberLineStud);
                strcpy(StudButton,"-1");
            }
        }
    }
}    