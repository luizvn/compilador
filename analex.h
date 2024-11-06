#ifndef ANALEX
#define ANALEX 
#define TAM_MAX_LEXEMA 50


	enum categoria{PVR=1, CT_I, SN, CT_R, CT_C, ID, FA, LT, FE
	};
	//pvr: palavra reservada || ct_i: constante inteira || sn: sinal || ct_r: constante real
	//ct_c: constante char || id: identificador || FA: fim do arquivo || LT: literal
	//fe: fim da expressão ------duvida-------
	

	enum sinal{DIV=1, ADI, SUB, MUL, AND, EN, OU, MAQ, MAIQ, MEQ, MEIQ, COMP, ATRIB, DIF, NEG,
	APAR, FPAR, ACOL, FCOL, ACH, FCH, VIRG
	};
	

	enum palavra_reservada{CONST=1, PR, INIT, ENDP, CHAR, INT, REAL, BOOL, DO, WHILE, ENDW, VAR, FROM,
	TO, DT, BY, IF, ENDV, ELIF, ELSE, ENDI, GETOUT, GETINT, GETREAL, GETCHAR, PUTINT, 
	PUTCHAR, PUTREAL
	};
	
typedef 
	struct{  
		enum categoria cat;						// deve receber uma das constantes de enum TOKEN_CAT 
		union {								// parte variável do registro 
			int codigo;						// para tokens das categorias SN 
		   	char lexema[TAM_MAX_LEXEMA];	// cadeia de caracteres que corresponde ao nome do token da cat. ID 
		   	int valInt;						// valor da constante inteira em tokens da cat. CT_I 
			float valReal;
			char c;
		}; 
	} TOKEN;   // Tipo TOKEN 

 

#endif 

/* Contador de linhas do código fonte */ 

int contLinha = 1; 