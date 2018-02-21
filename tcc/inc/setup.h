#ifndef SETUP_H
#define SETUP_H

#include <stdio.h>

void Setup_ReadIniFile(char *);
void Setup_Output_Files();
void Setup_ReadBox(FILE *);
void Setup_Readxyz(int e, int write, int f, FILE *);  // output single float valued arrays in gopenmol xyz format
void Setup_InitStaticVars();    // Initialize bond detection
void Setup_ResetStaticVars();   // reset one frame of the variables (memory for which allocated in Bonds_Init())
void Setup_FreeStaticVars();    // Reset bond detection variables
int icell(int tix, int tiy, int tiz);
void Setup_Cell_List();

#endif