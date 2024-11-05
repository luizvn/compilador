#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 
#include <stdbool.h> 
#include "analex.h" 
#define TAM_LEXEMA 50 
#define TAM_NUM 20 

void error(char msg[]) { 
	printf("%s Linha: %d\n", msg, contLinha);
	exit(1);
} 

 int main(int argc, char** argv)
 {
	 //proc
	 TOKEN AnaLex(FILE *fd){
		 int estado = 0;
		 char lexema[TAM_LEXEMA] = "";
		 int tamL = 0;
		 char digitos[TAM_NUM] = "";
		 int tamD = 0;
		 TOKEN t;
		 char c;
		 
		 while(1)
		 {
			 c = fgetc(fd);
			 switch(estado)
			 {
			 	 case 0:
			 	 	if(c == ' ' || c == '\t') estado = 0;
			 	 	else if(c == '_')
				    {
						estado = 2;
						lexema[tamL] = c;
						lexema[++tamL] = '\0';
					}
					else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
					{
						estado = 1;
						lexema[tamL] = c;
						lexema[++tamL] = '\0';
					}
					else if(c >= 0 || c <= 9)
					{
						estado = 4;
						digitos[tamD] = c;
						digitos[++tamL] = '\0';
					}
					else if(c == '\'')
					{
						estado = 8;
					}
					else if(c == '"')
					{
						estado = 14;
					}
					else if(c == '/')
					{
						estado = 20;
					}
					else if(c == '+')
					{
						estado = 22;
						t.cat = SN;
						t.codigo = ADI;
						return t;
					}
					else if(c == '-')
					{
						estado = 23;
						t.cat = SN;
						t.codigo = SUB;
						return t;
					}
					else if(c == '*')
					{
						estado = 24;
						t.cat = SN;
						t.codigo = MUL;
						return t;
					}
					else if(c == '&')
					{
						estado = 25;
					}
					else if(c == '|')
					{
						estado = 28;
					}
					else if(c == '>')
					{
						estado = 30;
					}
					else if(c == '<')
					{
						estado = 33;
					}
					else if(c == '=')
					{
						estado = 36;
					}
					else if(c == '!')
					{
						estado = 39;
					}
					else if(c == '(')
					{
						estado = 42;
						t.cat = SN;
						t.codigo = APAR;
						return t;
					}
					else if(c == ')')
					{
						estado = 43;
						t.cat = SN;
						t.codigo = FPAR;
						return t;
					}
					else if(c == '[')
					{
						estado = 44;
						t.cat = SN;
						t.codigo = ACOL;
						return t;
					}
					else if(c == ']')
					{
						estado = 45;
						t.cat = SN;
						t.codigo = FCOL;
						return t;
					}
					else if(c == ',')
					{
						estado = 46;
						t.cat = SN;
						t.codigo = VIRG;
						return t;
					}
					else if(c == '{')
					{
						estado = 5;
						t.cat = SN;
						t.codigo = ACH;
						return t;
					}
					else if(c == '}')
					{
						estado = 47;
						t.cat = SN;
						t.codigo = FCH;
						return t;
					}
					else if(c == '\n')
					{
						contLinha++;
					}
					else if(c == EOF)
					{
						t.cat = FA;
						return t;
					}
					else
					{
						error("caracter invalido!");
					}
				 break;
			 default:
				 break;
			 }
		 }
	 }
	 return 0;
 }