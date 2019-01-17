// ConsoleApplication23.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// 
//
// Кодегенератор         
// Абдулов Тимур 2019 год 
// 
 
#include <stdbool.h>       
#include <string.h> //
#include <stdlib.h> // Для СИ Компиляции 
#include <stdio.h>  // Для СИ Компиляции        

#include "generator.h"
#include "Intel.h"
#include "Utils.h"
#pragma warning(disable : 4996) //  Это для  VS си++
                                              
#pragma region ==================================== Переменные         .
                     
unsigned int  G_PLA=PL_I16;// Глобальаня переменая выбора платформы 
unsigned int  G_ADR=0;// Адрес где находимся в масиве G_MEM в данный момент 
unsigned int  L_ADR=0;// Базовый адрес 
// Адрес в ходе выполнения программы = L_ADR+G_ADR    
unsigned char G_MEM[Max_Siz_Mem];// Готовый код программы   

#pragma endregion 
#pragma region ==================================== Метки              .

typedef struct S_LAB { // Структура хранения метки 
	char *NAM;// Название метки 
	unsigned int ADR;// Адрес рапсоложения  
	S_LAB*NEX;// Следующая метка   
} S_LAB;
char*G_FUN;// Глобальная метка 
S_LAB*LABS;// Структура хранения всех меток 
unsigned int ADR_(const char*iNam) { // Возвращает адрес метки  

	 char*lLab=Tr_SumStr(G_FUN,strdup(iNam));
	 unsigned int res=0;
	 S_LAB *cur_lab = LABS; // начинаем с первой метки в списке  
	 bool ex=false;// Флаг выхода 
	 while ((cur_lab != NULL)&&(ex==false))// Перебираем метки 
	 if  (strcmp(lLab, cur_lab->NAM)==0) 
		  ex=true; else // Если имя совпадает завершаем цикл 
		  cur_lab = cur_lab->NEX;// Переходим к следующей переменной 
	 if (cur_lab!=NULL) res=cur_lab->ADR;
	 else { // Если локальной метки нету то ищим глобальную 
	 
	 char*lLab=strdup(iNam);
	 unsigned int res=0;
	 S_LAB *cur_lab = LABS; // начинаем с первой метки в списке  
	 bool ex=false;// Флаг выхода 
	 while ((cur_lab != NULL)&&(ex==false))// Перебираем метки 
	 if  (strcmp(lLab, cur_lab->NAM)==0) 
		  ex=true; else // Если имя совпадает завершаем цикл 
		  cur_lab = cur_lab->NEX;// Переходим к следующей переменной 
	 if (cur_lab!=NULL) res=cur_lab->ADR; 
	 
	 } 

 return res;
}     
void LAB_(const char*iStr) { // Создает Метку Label

	 char*lLab=Tr_SumStr(G_FUN,strdup(iStr));// Складываем Глобальную метку и локальную 
	 S_LAB *new_lab=(S_LAB*)malloc(sizeof(S_LAB));   
	 new_lab->NAM=lLab;// Запоминаем имя метки 
	 new_lab->ADR=G_ADR+L_ADR;// Запоминаем адрес метки 
	 new_lab->NEX=LABS;
	 LABS=new_lab;

}                   
void FUN_(const char*iStr) { // Создает глобальную метку 

	 G_FUN=strdup(iStr);
	 S_LAB *new_lab=(S_LAB*)malloc(sizeof(S_LAB));   
	 new_lab->NAM=strdup(iStr);// Запоминаем имя метки 
	 new_lab->ADR=G_ADR+L_ADR;// Запоминаем адрес метки 
	 new_lab->NEX=LABS;
	 LABS=new_lab;

}            
bool LAB_INIT()
{
	// Инициализация структуры для хранения меток 
	 S_LAB *LABS=(S_LAB*)malloc(sizeof(S_LAB));
	 LABS->ADR=0;// Создаем метку с адресом 0 
	 LABS->NAM=strdup("START");// Создаем метку с адресом 0 
	 LABS->NEX=NULL;//  
	 return true;
}

#pragma endregion 
#pragma region ==================================== Крос АСМ           .

// Универсальные для всех платформ =====================
                                                
void PLA_(int iPla) { // Выбор платформы 
    G_PLA=iPla;
}
void ORG_(unsigned int  iAdr) { // Устанавлвиает базовый адрес размещения кода 
     L_ADR=iAdr;
}
void ERR(const char*iStr){  // Это типа ошибка компидяции 
	char*lEr=(char*)strdup(iStr);
	//cp1251_cp866(lEr);
	printf("%s",iStr);
	exit(0);
}   
void STR_(const char*iStr) { // Распологает строку в памяти 
     
     int f=0;
     for (f=0;iStr[f]!=0;f++){
     G_MEM[G_ADR]=iStr[f];G_ADR=G_ADR+1;
     }
     G_MEM[G_ADR]=0;G_ADR=G_ADR+1;

}     
void STL_(const char*iStr){
	// Создает Метку и строку одинаковые 
	LAB_(iStr);
	STR_(iStr);
}
void DB_(unsigned char iNom){ // Размещает 1 байт 
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
}

#pragma endregion 
#pragma region ==================================== Инициализация      . 
bool Init()
{
     LAB_INIT();              
	 return true;
}
#pragma endregion 



 