#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"structs.c"
#define STRING_SIZE 256  //длина строки файла
#define CASE_SIZE 32 //длина строки ввода
#define MASSIVE_SIZE 4096 // размер массива структур

void WriteBooks(BOOK*Base, int size){
    FILE *Basefile=fopen("books.csv", "r");
    char Basket[STRING_SIZE];
    for(int i=0;i<size;i++){
        fgets(Basket, STRING_SIZE, Basefile);
        Base[i].ISBN=atoll(strtok(Basket,";"));
        strcpy(Base[i].NameSP,strtok(NULL,";"));
        strcpy(Base[i].BookName,strtok(NULL,";"));
        strcpy(Base[i].Number,strtok(NULL,";"));
        strcpy(Base[i].Avail, strtok(NULL,"\n"));
    }
    fclose(Basefile);
}

int ViewBooks(BOOK*Base, int size){
        printf("Таблица:\n");
        printf("________________________________________________________________________________________\n");
        printf("   Номер ISBN  |    Ф И.О.автора    |            Название          |Кол-во|доступ.Кол-во|\n");
        for(int i=0;i<size;i++){
            if(Base[i].ISBN){
                printf("________________________________________________________________________________________\n");
                printf("%15lli|%20s|%30s|%6s|%13s|\n", Base[i].ISBN,Base[i].NameSP,Base[i].BookName,Base[i].Number,Base[i].Avail);
            }
        }
        printf("________________________________________________________________________________________\n");
        printf("чтобы сохранить нажмите 12\n");
}

void StrSwap(BOOK*Base,int left,int right){ 
    BOOK*Basket;
    Basket=calloc(MASSIVE_SIZE,sizeof(BOOK));
    Basket[left]=Base[left];
    Base[left]=Base[right];
    Base[right]=Basket[left];
}

void QuickSort(BOOK *Base, int left, int right){ 
  int startleft = left;
  int startright = right;
  long long int pivot = Base[left].ISBN;
  while (left < right){
    while (Base[right].ISBN >= pivot && left < right)
      right--;
        if(left != right){
            StrSwap(Base,left,right);
            left++;
        }
    while (Base[left].ISBN <= pivot && left < right)
        left++;
        if (left != right){
            StrSwap(Base,right,left);
            right--;
        }
  }
  pivot=left;
  left=startleft;
  right=startright;
  if (left<pivot)
    QuickSort(Base, left, pivot - 1);
  if (right>pivot)
    QuickSort(Base, pivot + 1, right);
}


int AddBook(BOOK*Base, int NumberLine){ 
        printf("ДОБАВЛЕНИЕ КНИГИ(вместо пробелов использовать запятые)\nНомер ISBN:");
        char StrISBN[CASE_SIZE];
        scanf("%s",&StrISBN);
        if((strcmp(StrISBN,"Q"))==0){
            return 1;
        }
        long long int ISBN=atoll(StrISBN);
        int copy=0;
        for(int i=0; i<NumberLine; i++) {
            if(Base[i].ISBN==ISBN){
                printf("Книга уже есть в базе.\n");
                copy=1;
                return 1;
            }
        }
        if(copy==1){ 
            return 1;
        }
        if(copy==0){
            char NameSP[CASE_SIZE];
            printf("Ф.И.О. автора:");
            SetConsoleCP(1251);
            scanf("%s",&NameSP);
            SetConsoleCP(866);
            if(!strcmp(NameSP,"Q")){
                return 1;
            }
            char BookName[CASE_SIZE];
            printf("Название:");
            SetConsoleCP(1251);
            scanf("%s",&BookName);
            SetConsoleCP(866);
            if(!strcmp(BookName,"Q")){
                return 1;
            }
            char Number[CASE_SIZE];
            printf("Количество:");
            SetConsoleCP(1251);
            scanf("%s",&Number);
            SetConsoleCP(866);
            if(!strcmp(Number,"Q")){
                return 1;
            }
            char Avail[CASE_SIZE];
            printf("Доступное количество:");
            SetConsoleCP(1251);
            scanf("%s",&Avail);
            SetConsoleCP(866);
            if(!strcmp(Avail,"Q")){
                return 1;
            }
            Base[NumberLine].ISBN = ISBN;                           
            strcpy(Base[NumberLine].NameSP,NameSP);
            strcpy(Base[NumberLine].BookName,BookName);
            strcpy(Base[NumberLine].Number,Number);
            strcpy(Base[NumberLine].Avail,Avail);
            printf("Книга добавлена\n");
            ViewBooks(Base, NumberLine+1);
            return 0;
    }
}

void DeleteBook(BOOK*Base, int NumberLine){
                int del=0;
                printf("УДАЛЕНИЕ КНИГИ\n");
                printf("Введите номер ISBN:");
                char StrISBN[CASE_SIZE];
                scanf("%s",&StrISBN);
                if(!strcmp(StrISBN,"Q")){
                    return;
                }
                long long int ISBN=atoll(StrISBN);
                for(int p=0; p<NumberLine; p++){
                    if(Base[p].ISBN == ISBN){
                        Base[p].ISBN=0;
                        del=1;
                        printf("Книга удалена\n");
                        ViewBooks(Base, NumberLine);
                        return;
                    }
                }
                if(del==0){
                    printf("Книга не найдена\n");
                }

}


void SearchBook(BOOK*Base,int NumberLine){
                printf("ПОИСК ИНФОРМАЦИИ ПО ISBN\nВведите ISBN:");
                int d=0;
                char StrISBN[CASE_SIZE];
                scanf("%s",&StrISBN);
                if((strcmp(StrISBN,"Q"))==0){
                    return;
                }
                long long int ISBN=atoll(StrISBN);
                int found=0;
                for(int i=0;i<NumberLine;i++){
                    if(Base[i].ISBN==ISBN){
                        if(d==0){
                        printf("________________________________________________________________________________________\n");
                        printf("   Номер ISBN  |    Ф И.О.автора    |            Название          |кол-во|доступ.кол-во|\n");
                        printf("________________________________________________________________________________________\n");
                        }
                        d=1;
                        printf("%15lli|%20s|%30s|%6s|%13s|\n", Base[i].ISBN,Base[i].NameSP,Base[i].BookName,Base[i].Number,Base[i].Avail);
                        printf("________________________________________________________________________________________\n");
                        found=1;
                    }
                }
                if(found==0){
                    printf("книга с таким номером ISBN не найдена\n");
                }
}

float ExitBooks(BOOK*Base, int NumberLine){
                FILE *Basefile=fopen("books.csv", "w");
                for(int i=0;i<NumberLine;i++){
                    if(Base[i].ISBN){
                        fprintf(Basefile,"%lli;%s;%s;%s;%s\n",Base[i].ISBN,Base[i].NameSP,Base[i].BookName,Base[i].Number,Base[i].Avail);
                    }
                }
                printf("файл сохранен\n");
                fclose(Basefile);
                free(Base);
}


void books(){
    setlocale(LC_ALL,".1251");
    int NumberLineBooks=0;// количество строчек
	FILE *BooksFile=fopen("books.csv", "r");
	if(BooksFile==NULL){
        printf("Файл не найден.");
    }else{
        printf("файл прочитан\n");
        while(!feof(BooksFile)){  
            if((fgetc(BooksFile))=='\n'){
                NumberLineBooks++;
            }
        }
        printf("количество строк: %d\n",NumberLineBooks);
        fclose(BooksFile);
        BOOK*Basebooks;             //массив книг 
        Basebooks=calloc(MASSIVE_SIZE,sizeof(BOOK));
        WriteBooks(Basebooks, NumberLineBooks); //записываем данные файла в Basebooks 
        if(NumberLineBooks>0){ 
            ViewBooks(Basebooks,NumberLineBooks);
        }


        printf("ВЫБЕРИТЕ ДЕЙСТВИЕ:(нельзя вводить пробелы)\n");
		printf("1 - чтобы добавить новую книгу\n2 - чтобы удалить книгу\n3 - чтобы найти книгу по ISBN\n4 - чтобы отсортировать таблицу по возрастанию ISBN\n12 - чтобы выйти с сохранением изменений\nQ - чтобы вернуться в предыдущее меню (работает во всех программах)\n");

        char BooksButton[4];
        strcpy(BooksButton,"-1");
		while(!strcmp(BooksButton,"-1")){ //главный цикл
            printf("books:");
            SetConsoleCP(1251);
            scanf("%s",&BooksButton);
            SetConsoleCP(866);
            printf("%s- ",BooksButton);

            if((strcmp(BooksButton,"Q")) && (strcmp(BooksButton,"0")) && (strcmp(BooksButton,"1")) && (strcmp(BooksButton,"2")) && (strcmp(BooksButton,"3")) && (strcmp(BooksButton,"4")) && (strcmp(BooksButton,"12"))){
                printf("Неопознанная команда\n");
                strcpy(BooksButton,"-1");
            }
            // ПРОГРАММЫ:
            if(!strcmp(BooksButton,"Q")){
                printf("Возврат в главное меню\n");
                return;
            }
            if (!strcmp(BooksButton,"1")){    //добавление книги
                if(AddBook(Basebooks,NumberLineBooks)!=1){
                NumberLineBooks++;
                }
                strcpy(BooksButton,"-1");
            }
            if(!strcmp(BooksButton,"2")){ //удаление книги
                DeleteBook(Basebooks, NumberLineBooks);
                strcpy(BooksButton,"-1");
            }

            if(!strcmp(BooksButton,"3")){  //найти информацию
                SearchBook(Basebooks,NumberLineBooks);
                strcpy(BooksButton,"-1");
            }

            if(!strcmp(BooksButton,"4")){  //сортировка по ISBN
                QuickSort(Basebooks,0,NumberLineBooks-1);
                ViewBooks(Basebooks,NumberLineBooks);
                strcpy(BooksButton,"-1");
            }
            if (!strcmp(BooksButton,"12")){	//выход из программы с сохранением изменений
                ExitBooks(Basebooks, NumberLineBooks);
                strcpy(BooksButton,"0");
            }

        }
    }
}    