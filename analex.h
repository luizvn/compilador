#ifndef ANALEX
#define ANALEX 
#define TAM_MAX_LEXEMA 31

typedef
	enum{PR=1, CT_I, SN, CT_R, CT_L, ID}
	categoria;
	
typedef 
	struct{  
		categoria cat;						// deve receber uma das constantes de enum TOKEN_CAT 
		union {								// parte variável do registro 
			int codigo;						// para tokens das categorias SN 
		   	char lexema[TAM_MAX_LEXEMA];	// cadeia de caracteres que corresponde ao nome do token da cat. ID 
		   	int valInt;						// valor da constante inteira em tokens da cat. CT_I 
			float valor_r;
			char c;
		}; 
	} TOKEN;   // Tipo TOKEN 

 

#endif 

/* Contador de linhas do código fonte */ 

int contLinha = 1; 