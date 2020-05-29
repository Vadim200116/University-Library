#ifndef STRUCTS_H
#define STRUCTS_H

// students
typedef struct Anketa{
	char RecBook[32];
	char Surname[64];
	char Name[64];
	char Patron[64];
	char Faculty[16];
	char Spec[64];
}Anketa;

typedef struct backdate{
    char month[3];
    int number[3];
    int hour[2];
    int minute[2];
    int year[4];
}backdate;

// books

typedef struct BOOK{
	long long int ISBN;
	char NameSP[32];
	char BookName[32];
	char Number[4];
	char Avail[4];
}BOOK;

//users

typedef struct USER{
    char login[16];
    char pass[16];
    char students[2];
    char books[2];
}USER;

#endif
