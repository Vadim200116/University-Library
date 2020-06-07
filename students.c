#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include <time.h>
#include"structs.c"
#define S_STRING_SIZE 256 //длина строки файла
#define S_CASE_SIZE 64 //длина строки ввода
#define S_MASSIVE_SIZE 4096 // размер массива структур

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
}

void WriteStudents(Anketa*Base, int size,char filename[S_CASE_SIZE]){
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
        if(!strcmp(RecBook,"Q")){
            return 1;
        }
        int copy=0; // проверяет номер зачетки на совпадение
        for(int i=0; i<NumberLine; i++) {// Проверем есть если ли такая зачетка в базе
            if(!strcmp(RecBook, Base[i].RecBook)){
                printf("Студент уже есть в базе.\n");
                copy=1;
                return 1;
            }
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
            printf("Специальность:");
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
                int del=0;//идентификатор успешности удаления
                printf("УДАЛЕНИЕ СТУДЕНТА\n");
                printf("Введите номер зачетной книжки:");
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
                    printf("Студент не найден\n");
                }
}


void CreateBackUp(Anketa*Base, int NumberLine)
{
    printf("СОЗДАНИЕ БЭКАПА\n");    
    char date[S_STRING_SIZE];//массив для хранения даты
    long int s_time = time(NULL);
    struct tm *m_time = localtime(&s_time);
    strftime(date, S_STRING_SIZE, "%m_%d_(%H.%M)_%Y_", m_time);
    
    char filename[S_STRING_SIZE];//массив для хранения названия бэк-ап файла
    sprintf(filename, "students_%s.csv", date);
    
    FILE* Backup = fopen(filename, "w");
    if(Backup == NULL){
        printf("Не удалось создать бэк-ап файл %s\n", filename);
        return;
    }
     for (int i = 0; i < NumberLine; i++)
    {
       fprintf(Backup,"%s;%s;%s;%s;%s;%s\n",Base[i].RecBook,Base[i].Surname,Base[i].Name,Base[i].Patron,Base[i].Faculty,Base[i].Spec);
    }
    printf("Бэк-ап файл успешно создан %s\n", filename);

    fclose(Backup);
}


int CopyBackUp(Anketa*Base, int NumberLine){
    backdate date;// структура даты 
    char fname[S_STRING_SIZE]="students_";// название бэк-апа
    printf("ВОССТАНОВЛЕНИЕ ИЗ БЭКАПА\n");
    printf("введите дату и время\n");
    printf(" месяц:");
    scanf("%s",&date.month);
    if(!strcmp("Q",date.month)){
        return 0;
    }
    printf(" число:");
    scanf("%s",&date.number);
    if(!strcmp("Q",date.number)){
        return 0;
    }
    printf(" час:");
    scanf("%s",&date.hour);
    if(!strcmp("Q",date.hour)){
        return 0;
    }
    printf(" минуту:");
    scanf("%s",&date.minute);
    if(!strcmp("Q",date.minute)){
        return 0;
    }
    printf(" год:");
    scanf("%s",&date.year);
    if(!strcmp("Q",date.year)){
        return 0;
    }
    strcat(fname,date.month);
    strcat(fname,"_");
    strcat(fname,date.number);
    strcat(fname,"_(");
    strcat(fname,date.hour);
    strcat(fname,".");
    strcat(fname,date.minute);
    strcat(fname,")_");
    strcat(fname,date.year);
    strcat(fname,"_");
    strcat(fname,".csv");
    printf("%s",fname);

    FILE *Backupfile=fopen(fname, "r");
    if(Backupfile==NULL){
        printf(" - файл не найден.\n");
    }else{
        printf(" - файл успешно открыт\n");
        int BNumberLine=0;// количество строк в бэк-апе
        while(!feof(Backupfile)){  //считаем количество строк
            if((fgetc(Backupfile))=='\n'){
                BNumberLine++;
            }
        }
        fclose(Backupfile);
        printf("количество строк в файле бэкапа: %d\n",BNumberLine);
        Anketa *BackBase;             //массив данных бэк-апа
        BackBase=calloc(S_MASSIVE_SIZE,sizeof(Anketa));
        WriteStudents(BackBase,BNumberLine,fname); //записываем данные файла бэкапа в BackBase

        if(BNumberLine>0){ 
            printf("Таблица в файле бэкапа:\n");
            ViewStudents(BackBase,BNumberLine);
        }
        for(int i=0; i<BNumberLine;i++){
            strcpy(Base[i].RecBook,BackBase[i].RecBook);
            strcpy(Base[i].Surname,BackBase[i].Surname);
            strcpy(Base[i].Name,BackBase[i].Name);
            strcpy(Base[i].Patron,BackBase[i].Patron);
            strcpy(Base[i].Faculty,BackBase[i].Faculty);
            strcpy(Base[i].Spec,BackBase[i].Spec);
        }
        if(BNumberLine<NumberLine){
            for(int i=BNumberLine;i<NumberLine;i++){
                strcpy(Base[i].RecBook,"del");
            }
        }
    }
}




void SearchStudent(Anketa*Base,int NumberLine){
                printf("ПОИСК ИНФОРМАЦИИ ПО ФАМИЛИИ\nВведите фамилию:");
                char Surname[S_CASE_SIZE];
                SetConsoleCP(1251);
                scanf("%s",&Surname);
                SetConsoleCP(866);
                int found=0;//Существует ли студент с такой фамилией
                int d=0;//вывод шапки таблиц
                if(!strcmp(Surname,"Q")){
                    return;
                }
                for(int m=0;m<NumberLine;m++){
                    if(!strcmp(Base[m].Surname, Surname)){
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
                if(!found){
                    printf("студент с такой фамилией не найден\n");
                }
}

void ExitStudents(Anketa*Base, int NumberLine){
    FILE *Basefile=fopen("students.csv", "w");
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
        setlocale(LC_ALL,"Russian");
    unsigned int NumberLineStud=0;//количество срок
	FILE *StudFile=fopen("students.csv", "r");
	if(StudFile==NULL){
        printf("Файл не найден.");
    }else{
        printf("Файл прочитан\n");
        while(!feof(StudFile)){  //считаем количество строк
            if((fgetc(StudFile))=='\n'){
                NumberLineStud++;
            }
        }
        printf("Количество строк: %d\n",NumberLineStud);
        fclose(StudFile);
        Anketa*BaseStud;             //массив студентов
        BaseStud=calloc(S_MASSIVE_SIZE,sizeof(Anketa));
        char filename[S_CASE_SIZE]="students.csv";
        WriteStudents(BaseStud, NumberLineStud,filename); //считываем данные файла в BaseStud 
        if(NumberLineStud>0){ //выводим таблицу, если она не пустая
            ViewStudents(BaseStud,NumberLineStud);
        }
        printf("ВЫБЕРИТЕ ДЕЙСТВИЕ:(символ без пробела)\n");
		printf("1 - чтобы добавить нового студента\n2 - чтобы удалить студента\n5 - чтобы создать бэк-ап\n6 - чтобы загрузить бэк-ап\n7 - чтобы найти информацию о студенте по его фамилии\n8 - чтобы выйти с сохранением изменений\nQ - чтобы вернуться в предыдущее меню (работает во всех программах)\n");
        
         char StudButton[4]; // команда пользователя
        strcpy(StudButton,"0");
		while(!strcmp(StudButton,"0")){ //главный цикл
            printf("students:");
            SetConsoleCP(1251);
            scanf("%s",&StudButton);
            SetConsoleCP(866);
            printf("%s- ",StudButton);

            if((strcmp(StudButton,"0")) && (strcmp(StudButton,"1")) && (strcmp(StudButton,"2")) && (strcmp(StudButton,"5")) && (strcmp(StudButton,"6")) && (strcmp(StudButton,"7")) && (strcmp(StudButton,"8")) && (strcmp(StudButton,"Q"))){
                printf("Неопознанная команда\n");
                strcpy(StudButton,"0");
            }
// ПРОГРАММЫ:
            if(!strcmp(StudButton,"Q")){
                printf("Возврат в главное меню\n");
                return;
            }
            if (!strcmp(StudButton,"1")){    //добавление студента
                if(AddStudent(BaseStud,NumberLineStud)!=1){
                NumberLineStud++;
                }
                strcpy(StudButton,"0");
            }
           if(!strcmp(StudButton,"2")){ //удаление студента
                DeleteStudent(BaseStud, NumberLineStud);
                strcpy(StudButton,"0");
            }

            if(!strcmp(StudButton,"5")){ //создать бэкап
                CreateBackUp(BaseStud,NumberLineStud);
                strcpy(StudButton,"0");
            }
            if(!strcmp(StudButton,"6")){ //загрузить бэкап
                CopyBackUp(BaseStud, NumberLineStud);
                strcpy(StudButton,"0");
            }
            if(!strcmp(StudButton,"7")){  //найти информацию
                SearchStudent(BaseStud,NumberLineStud);
                strcpy(StudButton,"0");
            }
            if (!strcmp(StudButton,"8")){	//выход из программы с сохранением изменений
                ExitStudents(BaseStud, NumberLineStud);
                return;
            }
        }
    }
}    