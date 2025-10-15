#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_TITULO 100
#define MAX_AUTOR 50
#define MAX_ISBN 14 // 13 dígitos + terminador nulo

struct Livro {
char isbn[MAX_ISBN];
char titulo[MAX_TITULO];
char autor[MAX_AUTOR];
int ano_publicacao;
int disponivel; // Usar 1 para true, 0 para false
};

int valid_isbn(char* isbn);
void cadastro_livros(struct Livro* cadlivros){
    printf("Titulo do Livro: ");
    scanf("%s", cadlivros->titulo);
    printf("Autor do Livro: ");
    scanf("%s", cadlivros->autor);
    getchar();
    printf("ISBN do Livro: ");
    scanf("%s", cadlivros->isbn);
    printf("Ano de Publicacao do Livro: ");
    scanf("%d", &cadlivros->ano_publicacao);
    printf("Disponivel[1-Sim/0-Nao]: ");
    scanf("%d", &cadlivros->disponivel);
    
    if(!valid_isbn(cadlivros->isbn)){
        return;
    }
}

void listar_livros(struct Livro* cadlivros){
    printf("Titulo: %s\n", cadlivros->titulo);
    printf("Autor: %s\n", cadlivros->autor);
    printf("ISBN: %s\n", cadlivros->isbn);
    printf("Ano: %d\n", cadlivros->ano_publicacao);
    printf("Disponivel: %d\n", cadlivros->disponivel);
}

int valid_isbn(char* isbn){
    int isbnValido = 1; 
    size_t tamIsbn = strlen(isbn);
    if (tamIsbn > 13) {
        isbnValido = 0;
    }

    if(!isbnValido){
    printf("ERRO: ISBN INVÁLIDO \n");
        return 0;
    }
    
    return 1;
}

int buscar_livros(struct Livro* livros, int n_livros){
    char busca_isbn[MAX_ISBN];
    int i;
    printf("Digite o ISBN do livro que deseje buscar: ");
    scanf("%s", busca_isbn);
    
    for(int i = 0; i<n_livros; i++){
        if(strcmp(livros[i].isbn, busca_isbn) == 0){
            printf("\nO ISBN digitado pertence ao Livro:\n");
            listar_livros(&livros[i]);
            return 1;
        }
    }
    for(int i = 0; i < n_livros; i++){
        if(strcmp(livros[i].isbn, busca_isbn) == 0){
            printf("\nDigite (1 para devolver, 0 para Emprestar): ");
            scanf("%d", &livros[i].disponivel);
            printf("Status atualizado com sucesso!\n");
            listar_livros(&livros[i]);  
            return 1;
        }
    }
    printf("\nNULL\n");
    return 0;

}

int livros_autor(struct Livro* livros, int n_livros){
    char busca_autor[MAX_AUTOR];
    int i;
    printf("Digite o Autor que deseje buscar: ");
    scanf("%s", busca_autor);
    
    for(int i = 0; i<n_livros;i++){
        if(strcmp(livros[i].autor, busca_autor) == 0){
            printf("Livros do Autor %s\n", busca_autor);
            listar_livros(&livros[i]);
            return 1;
        }
    }
    printf("\nNULL\n");
    return 0;
}
    

int main(){
    struct Livro* livros = NULL;
    int n_livros = 0;
    int i;
    int qtd_livros;
    printf("Quantos Livros deseja cadastrar? ");
    scanf("%d", &qtd_livros);
    
    n_livros += qtd_livros;
    livros = realloc(livros, n_livros * sizeof(struct Livro));
    for (int i = (n_livros-qtd_livros); i < n_livros; i++){
        getchar();
        printf("Livro %d\n", i+1);
        cadastro_livros(&livros[i]);
    }    
        
    buscar_livros(livros, n_livros);
    livros_autor(livros, n_livros);
    


    printf("\n\nListando Livros:\n");
    for (int i = 0; i<n_livros; i++){
        printf("\nLivro %d\n", i+1);
        listar_livros(&livros[i]);
    }
        
    
    
    free(livros);
    
    return 0;
}
