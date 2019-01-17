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
char *Labs[Max_Siz_Mem];// Списко меток 

#pragma endregion 
#pragma region ==================================== Метки              .



unsigned int ADR_(const char*iNam) { // Возвращает адрес метки  

     int res=-1;

     // ПОиск локальной метки =================================================
     // Двигаемся вниз по коду пока не встретим глобальную метку
     // либо конец программы либо не найдем 
     int f=G_ADR;
     while (  (res==-1) // ПОка не нашли метку 
            &&(f<Max_Siz_Mem) // Пока не дошли до конца программы 
            &&((Labs[f]==NULL)||(Labs[f][0]=='@'))) // пока это локальная метка 
            if ((Labs[f]!=NULL)&&(strcmp(iNam,(char*)&(Labs[f][1]))==0)) res=f;else f=f+1;
     // Двигаемся верх по коду пока не встретим глобальную метку
     // либо начало программы либо не найдем 
    f=G_ADR;
     while (  (res==-1) // ПОка не нашли метку 
            &&(f>=0) // Пока не дошли до конца программы 
            &&((Labs[f]==NULL)||(Labs[f][0]=='@'))) // пока это локальная метка 
            if ((Labs[f]!=NULL)&&(strcmp(iNam,(char*)&(Labs[f][1]))==0)) res=f;else f=f-1; 
     // ПОиск Глобальной метки =================================================
     // Двигаемся вниз по коду пока не встретим  
     // конец программы либо не найдем метку 
     f=G_ADR;
     while (  (res==-1) // ПОка не нашли метку 
            &&(f<Max_Siz_Mem)) // Пока не дошли до конца программы 
            if ((Labs[f]!=NULL)&&(strcmp(iNam,Labs[f])==0)) res=f;else f=f+1;
     // Двигаемся верх по коду пока не встретим  
     // начало программы либо не найдем метку 
     f=G_ADR;
     while (  (res==-1) // ПОка не нашли метку 
            &&(f>=0)) // Пока не дошли до конца программы 
            if ((Labs[f]!=NULL)&&(strcmp(iNam,Labs[f])==0)) res=f;else f=f-1;
        
 printf(" %s %d \r\n",iNam,res);
 return res+L_ADR;
}     
void LAB_(const char*iStr) { // Создает ЛОкальную Метку    

     Labs[G_ADR]=Tr_SumStr(strdup("@"),strdup(iStr)); 
     
}                   
void FUN_(const char*iStr) { // Создает глобальную метку 
                     
     Labs[G_ADR]=strdup(iStr); 
	 
}            
bool LAB_INIT()
{
     int f=0; 
	 for (f=0;f<Max_Siz_Mem;f++)Labs[f]=NULL;  
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



 