#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"structs.c"
#define STRING_SIZE 256
#define CASE_SIZE 32
#define MASSIVE_SIZE 4096


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
        printf("   Номер ISBN  |    Ф И.О.автора    |            Название          |кол-во|доступ.кол-во|\n");
        for(int i=0;i<size;i++){
            if(Base[i].ISBN!=0){
                printf("________________________________________________________________________________________\n");
                printf("%15lli|%20s|%30s|%6s|%13s|\n", Base[i].ISBN,Base[i].NameSP,Base[i].BookName,Base[i].Number,Base[i].Avail);
            }
        }
        printf("________________________________________________________________________________________\n");
        printf("чтобы сохранить нажмите 12\n");
}

void StrSwap(BOOK*Base,int left,int right){ //функция замены строк для быстрой сортировки
    BOOK*Basket;
    Basket=calloc(MASSIVE_SIZE,sizeof(BOOK));
    Basket[left]=Base[left];
    Base[left]=Base[right];
    Base[right]=Basket[left];
}

void QuickSort(BOOK *Base, int left, int right){ //используем быструю сортировку, т.к. предполагается большой объем данных + числа ISBM весьма большие
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
        for(int i=0; i<NumberLine; i++) {// Проверем есть если ли такая книга в базе
            if(Base[i].ISBN==ISBN){
                printf("Книга уже есть в базе.\n");
                copy=1;
                return 1;
            }
        }
        if(copy==1){ //если есть то возвращаемся в главное меню
            return 1;
        }
        if(copy==0){
            char NameSP[CASE_SIZE];
            printf("Ф.И.О. автора:");
            SetConsoleCP(1251);
            scanf("%s",&NameSP);
            SetConsoleCP(866);
            if((strcmp(NameSP,"Q"))==0){
                return 1;
            }
            char BookName[CASE_SIZE];
            printf("Название:");
            SetConsoleCP(1251);
            scanf("%s",&BookName);
            SetConsoleCP(866);
            if((strcmp(BookName,"Q"))==0){
                return 1;
            }
            char Number[CASE_SIZE];
            printf("Количество:");
            SetConsoleCP(1251);
            scanf("%s",&Number);
            SetConsoleCP(866);
            if((strcmp(Number,"Q"))==0){
                return 1;
            }
            char Avail[CASE_SIZE];
            printf("Доступное количество:");
            SetConsoleCP(1251);
            scanf("%s",&Avail);
            SetConsoleCP(866);
            if((strcmp(Avail,"Q"))==0){
                return 1;
            }
            Base[NumberLine].ISBN = ISBN;
                            //printf("%s",Base[NumberLine].ISBN);
            strcpy(Base[NumberLine].NameSP,NameSP);
                            //printf("%s",Base[NumberLine].NameSP);
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
                printf("введите номер ISBN:");
                char StrISBN[CASE_SIZE];
                scanf("%s",&StrISBN);
                if((strcmp(StrISBN,"Q"))==0){
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
                //printf("%lli",ISBN);
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
                FILE *Basefile=fopen("books.csv", "w"); // открываем файл для записи(при этом все данные удаляются)
                for(int i=0;i<NumberLine;i++){
                    if(Base[i].ISBN!=0){
                        fprintf(Basefile,"%lli;%s;%s;%s;%s\n",Base[i].ISBN,Base[i].NameSP,Base[i].BookName,Base[i].Number,Base[i].Avail);
                    }
                }
                printf("файл сохранен\n");
                fclose(Basefile);
                free(Base);
}


void books(){
    setlocale(LC_ALL,".1251");
    int NumberLineBooks=0;
	FILE *BooksFile=fopen("books.csv", "r");
	if(BooksFile==NULL){
        printf("Файл не найден.");
    }else{
        printf("файл прочитан\n");
        while(!feof(BooksFile)){  //считаем количество строк
            if((fgetc(BooksFile))=='\n'){
                NumberLineBooks++;
            }
        }
        printf("количество строк: %d\n",NumberLineBooks);
        fclose(BooksFile);
        BOOK*Basebooks;             //создаем массив Basebooks
        Basebooks=calloc(MASSIVE_SIZE,sizeof(BOOK));
        WriteBooks(Basebooks, NumberLineBooks); //записываем данные файла в Basebooks (по структуре в файле structanketa.h
        if(NumberLineBooks>0){ //выводим таблицу, если она не пустая
            ViewBooks(Basebooks,NumberLineBooks);
        }


        printf("ВЫБЕРИТЕ ДЕЙСТВИЕ:(нельзя вводить пробелы)\n");
		printf("1 - чтобы добавить новую книгу\n2 - чтобы удалить книгу\n3 - чтобы найти книгу по ISBN\n4 - чтобы отсортировать таблицу по возрастанию ISBN\n12 - чтобы выйти с сохранением изменений\nQ - чтобы вернуться в предыдущее меню (работает во всех программах)\n");

        char BooksButton[4];
        strcpy(BooksButton,"-1");
		while((strcmp(BooksButton,"-1"))==0){ //главный цикл
            printf("books:");
            SetConsoleCP(1251);
            scanf("%s",&BooksButton);
            SetConsoleCP(866);
            printf("%s- ",BooksButton);

            if((strcmp(BooksButton,"Q"))!=0 && (strcmp(BooksButton,"0"))!=0 && (strcmp(BooksButton,"1"))!=0 && (strcmp(BooksButton,"2"))!=0 && (strcmp(BooksButton,"3"))!=0 && (strcmp(BooksButton,"4"))!=0 && (strcmp(BooksButton,"12"))!=0){
                printf("Неопознанная команда\n");
                strcpy(BooksButton,"-1");
            }
            // ПРОГРАММЫ:
            if((strcmp(BooksButton,"Q"))==0){
                printf("Возврат в главное меню\n");
                return;
            }
            if ((strcmp(BooksButton,"1"))==0){    //добавление книги
                if(AddBook(Basebooks,NumberLineBooks)!=1){
                NumberLineBooks++;}
                strcpy(BooksButton,"-1");
            }
            if((strcmp(BooksButton,"2"))==0){ //удаление книги
                DeleteBook(Basebooks, NumberLineBooks);
                strcpy(BooksButton,"-1");
            }

            if((strcmp(BooksButton,"3"))==0){  //найти информацию
                SearchBook(Basebooks,NumberLineBooks);
                strcpy(BooksButton,"-1");
            }

            if((strcmp(BooksButton,"4"))==0){  //сортировка по ISBN
                QuickSort(Basebooks,0,NumberLineBooks-1);
                ViewBooks(Basebooks,NumberLineBooks);
                strcpy(BooksButton,"-1");
            }
            if ((strcmp(BooksButton,"12"))==0){	//выход из программы с сохранением изменений
                ExitBooks(Basebooks, NumberLineBooks);
                strcpy(BooksButton,"0");;
            }

        }
    }
}    