#include <stdio.h>
#include <stdlib.h>

#include "File_IMA.h"
#include "Loader.h"
#include "generator.h"

int main(int argc, char *argv[]) {
  Init();
  // ����������� ���
  PC = 0;
  Loader(); // ������ ������
  printf("=====\r\n");
  PC = 0;
  Loader(); // ������ ������
  printf("Compile Ok Size of %d!\n", PC);
  Create_IMA(Program, MAX_SIZE_MEM, "TimOs.ima");
}
