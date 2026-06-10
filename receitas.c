/*
 * LIVRO DE Receitas
 * AED Algoritmos
 * Grupo: Andre Almeida, Maycon Douglas, Ester Cardoso, João Paulo
 */
#include <stdio.h>
#include <string.h>

/* CASO VOCE USE SISTEMA DE PAGA PAU DE BILIONARIO (windows) TIRE O COMENTARIO ABAIXO*/
//#include <stdlib.h>

// variaveis globais 
char acao, acaoPrimaria;
char titulo[50];
char ingrediente[50][100], passo[50][200];

// contadoras
int qtdIngre, qtdPassos;


char feedback[6];

// declaracao de funcoes primarias
void adicionar();
void pesquisar();
void listar();
// declaracao de funcoes secundarias
void consultar(char *tituloBuscado);
void editar(char *tituloBuscado);
void deletar(char *tituloBuscado);
int buscar(char *tituloBuscado); // retorna 1 se achar
void salvar(); 


//  ===FUNCAO PRINCIPAL===
int main()
{
    printf("\n\n");
    printf("/=====================\\ \n");
    printf("|= LIVRO DE RECEITAS =|  \n");
    printf("\\=====================/ \n");

    do{
        printf("\nO que dejesa fazer ?\n");
        printf("<A> Adicionar receita\n<P> Pesquisar receita\n<L> Listar receitas\n<X> Sair\n");
        printf("Escolha: ");
        scanf("%c", &acaoPrimaria);
        getchar();
        while (acaoPrimaria != 'X' && acaoPrimaria != 'x' && acaoPrimaria != 'A' && acaoPrimaria != 'a' && acaoPrimaria != 'P' && acaoPrimaria != 'p' && acaoPrimaria != 'L' && acaoPrimaria != 'l'){
            printf("\nOpção Invalida!\n Escolha uma valida: ");
            scanf(" %c", &acaoPrimaria);
        }
        switch(acaoPrimaria){
            case 'A': case 'a':
                adicionar();
                break;
            case 'P': case 'p':
                pesquisar();
                break;
            case 'L': case 'l':
                listar();
                break;
            default:
                printf("\nSaindo...\n");
                break;
        }
    }while (acaoPrimaria != 'X' && acaoPrimaria != 'x');
    printf("\nO que achou do nosso software?\n(* * * * *):" );
    scanf("%s", feedback);
    return 0;
}


// =====FUNCOES AUXILIARES=====

// FUNCAO BUSCAR (pro pesquisar, editar e tals)
int buscar(char *tituloBuscado) {
    FILE *file = fopen("receitas.txt", "r");
    if (file == NULL) return 0;
    char linha[300];
    while (fgets(linha, sizeof(linha), file)) {
        if (strncmp(linha, "Titulo:", 7) == 0) {
            char *titu = linha + 7;
            titu[strcspn(titu, "\n")] = '\0';
            if (strcmp(titu, tituloBuscado) == 0) {
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

// FUNCAO SALVAR
void salvar(){
    FILE *file = fopen("receitas.txt", "a"); // "a" adicionar
    if (file == NULL){
        printf("\nErro ao abrir arquivo!\n");
        return;
    }
    // salvar receita 
    fprintf(file, "-= RECEITA =-\n");
    fprintf(file, "Titulo:%s\n",titulo);
    // salvar ingredientes
    fprintf(file, "Ingredientes:\n");
    for (int c = 0; c < qtdIngre; c++){
        fprintf(file, "* %s\n", ingrediente[c]);
    }
    fprintf(file,"==FIM DOS INGREDIENTES==\n");
    // salvar preparo
    fprintf(file, "Preparo:\n");
    for (int c = 0; c < qtdPassos; c++){
        fprintf(file, "* %s\n", passo[c]);
    }
    fprintf(file, "--== FIM DA RECEITA ==--\n\n");
    // fechar arquivo
    fclose(file);
}

// =====FUNCOES PRIMARIAS=====

// FUNCAO ADICIONAR
void adicionar() {
    printf("\nAdicionar Receita\n");
    //titulo
    printf("Titulo: ");
    fgets(titulo, 50, stdin);
    titulo[strcspn(titulo, "\n")] = '\0'; // ler espacos

    //ingredientes
    int fim = 0,c;
    printf("\nDigite os ingredientes separados por ENTER.\nDigite \"fim\" para parar.\n");
    for (c = 0; c < 50 && fim == 0; c++){
        printf("\nIngrediente [%d]: ", c + 1);
        fgets (ingrediente[c], 100, stdin); // leitura
        ingrediente[c][strcspn(ingrediente[c], "\n")] = '\0';
        if (strcmp(ingrediente[c], "fim") == 0){ // fim das entradas
            fim = 1;
            c--;
        }
    }
    qtdIngre = c;

    // passo a passo 
    fim = 0;
    printf("\nDigite passo a passo do modo de preparo de sua receita.\nDigite cada passo então pressione ENTER.");
    printf("\nDigite \"fim\" para parar.\n");
    for (c = 0; c < 50 && fim == 0; c++){
        printf("\nPasso[%d]: ", c + 1);
        fgets(passo[c], 200, stdin); // leitura
        passo[c][strcspn(passo[c], "\n")] = '\0';
        if (strcmp(passo[c], "fim") == 0){ // fim das entradas
            fim = 1;
            c--;
        }
    }
    qtdPassos = c;

    //salvar no arquivo
    salvar();
    printf("\nReceita Salva com sucesso!\n");
}

//FUNCAO PESQUISAR

void pesquisar() {
    char busca[50];
    printf("\nDigite o título da receita: ");
    fgets(busca, 50, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    if (!buscar(busca)) {
        printf("\nReceita não encontrada!\n");
        printf("\nO que deseja fazer?\n");
        printf("<A> Adicionar nova receita\n");
        printf("<L> Listar receitas existentes\n");
        printf("<X> Sair da pesquisa\n");
        printf("Escolha: ");
        scanf(" %c", &acao);
        getchar();
        switch (acao) {
            case 'A': case 'a':
                adicionar();
                break;
            case 'L': case 'l':
                listar();
                break;
            default:
                printf("Voltando...\n");
        }
        return; // sai da função após tratar as opções
    }

    // Se encontrou a receita, oferece as opções normais
    printf("\nOpções: \n");
    printf("<C> Consultar\n<E> Editar\n<D> Deletar\n<X> Sair\nEscolha: ");
    scanf(" %c", &acao);
    getchar();

    switch (acao) {
        case 'C': case 'c':
            consultar(busca);
            break;
        case 'E': case 'e':
            editar(busca);   // título já digitado
            break;
        case 'D': case 'd':
            deletar(busca);
            break;
        default:
            printf("\nVoltando...\n");
            break;
    }
}

// FUNCAO LISTAR
void listar(){
    FILE *file = fopen("receitas.txt", "r");
    if ( file == NULL){
        printf("\nNenhuma receita cadastrada.\n");
        return;
    }

    char linha[300];
    int cont = 1;
    printf("\n--===Suas Receitas===--\n");
    while(fgets(linha, sizeof(linha), file)) {
        if (strncmp(linha, "Titulo:", 7) == 0){
            char *titu = linha + 7;
            titu[strcspn(titu, "\n")] = '\0';
            printf("%d. %s.\n",cont++,titu);
        }
    }
    fclose(file);

    if (cont == 1)
        printf("\nNenhuma receita encontrada.\n");
}

// =====FUNCOES SECUNDARIAS=====

// FUNCAO CONSULTAR
void consultar(char *tituloBuscado){
    FILE *file = fopen("receitas.txt", "r");
    if (file == NULL){
        printf("\nNenhuma receita cadastrada.\n");
        return;
    }

    char linha[300];
    int achou = 0;
    int lendoIngre = 0, lendoPrep = 0;

    while (fgets(linha, sizeof(linha), file)){
        linha[strcspn(linha, "\n")] = '\0';
        if (!achou && strncmp(linha, "Titulo:", 7) == 0){
            if (strcmp(linha + 7, tituloBuscado) == 0){
            achou = 1;
            printf("\n========= %s =========\n", tituloBuscado);
            }
            continue;
        }

        if (achou == 1){
            if (strcmp(linha, "Ingredientes:") == 0){
                lendoIngre = 1;
                printf("Ingredientes:\n");
                continue;
            }
            if (strcmp(linha, "==FIM DOS INGREDIENTES==") == 0){
                lendoIngre = 0;
                continue;
            }
            if (strcmp(linha, "Preparo:") == 0){
                lendoPrep = 1;
                printf("\nModo de Preparo:\n");
                continue;
            }
            if (strcmp(linha, "--== FIM DA RECEITA ==--") == 0){
                break;
            }
            if (lendoIngre && linha[0] == '*')
                printf(" %s\n", linha + 2); // para pular os contadores * 
            if(lendoPrep && linha[0] == '*')
                printf(" %s\n",linha + 2);
            
        }
    }
    fclose(file);
    if (!achou) 
        printf("\nReceita não encontrada.\n");
}

// FUNCAO EDITAR (apaga e cria uma nova)

void editar(char *velho) {
    // Não pede o título novamente
    if (!buscar(velho)) {
        printf("\nReceita não encontrada!\n");
        return;
    }

    printf("Digite os dados atualizados: \n");
    adicionar();   // cria nova receita (será salva ao final do arquivo)

    // Remove a receita antiga (lógica corrigida igual a deletar, mas sem perguntar)
    FILE *og = fopen("receitas.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (og == NULL || temp == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    char linha[300];
    int dentroReceita = 0, deletarEsta = 0;
    char tituloLido[50];

    while (fgets(linha, sizeof(linha), og)) {
        linha[strcspn(linha, "\n")] = '\0';

        if (strcmp(linha, "-= RECEITA =-") == 0) {
            if (fgets(linha, sizeof(linha), og)) {
                linha[strcspn(linha, "\n")] = '\0';
                if (strncmp(linha, "Titulo:", 7) == 0) {
                    strcpy(tituloLido, linha + 7);
                    deletarEsta = (strcmp(tituloLido, velho) == 0);
                }
            }
            if (!deletarEsta) {
                fprintf(temp, "-= RECEITA =-\n");
                fprintf(temp, "Titulo:%s\n", tituloLido);
                dentroReceita = 1;
            } else {
                dentroReceita = 1;
            }
            continue;
        }

        if (dentroReceita) {
            if (strcmp(linha, "--== FIM DA RECEITA ==--") == 0) {
                if (!deletarEsta) {
                    fprintf(temp, "--== FIM DA RECEITA ==--\n");
                }
                dentroReceita = 0;
                deletarEsta = 0;
                continue;
            }
            if (!deletarEsta) {
                fprintf(temp, "%s\n", linha);
            }
            continue;
        }

        fprintf(temp, "%s\n", linha);
    }

    fclose(og);
    fclose(temp);
    remove("receitas.txt");
    rename("temp.txt", "receitas.txt");
    printf("\nEdição concluída (antiga removida, nova adicionada).\n");
}
// FUNCAO DELETAR RECEITA

void deletar(char *delTitulo) {
    if (!buscar(delTitulo)) {
        printf("\nReceita não encontrada!\n");
        return;
    }

    // Mesma lógica de exclusão da editar, mas sem adicionar nada novo
    FILE *og = fopen("receitas.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (og == NULL || temp == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    char linha[300];
    int dentroReceita = 0, deletarEsta = 0;
    char tituloLido[50];

    while (fgets(linha, sizeof(linha), og)) {
        linha[strcspn(linha, "\n")] = '\0';

        if (strcmp(linha, "-= RECEITA =-") == 0) {
            if (fgets(linha, sizeof(linha), og)) {
                linha[strcspn(linha, "\n")] = '\0';
                if (strncmp(linha, "Titulo:", 7) == 0) {
                    strcpy(tituloLido, linha + 7);
                    deletarEsta = (strcmp(tituloLido, delTitulo) == 0);
                }
            }
            if (!deletarEsta) {
                fprintf(temp, "-= RECEITA =-\n");
                fprintf(temp, "Titulo:%s\n", tituloLido);
                dentroReceita = 1;
            } else {
                dentroReceita = 1;
            }
            continue;
        }

        if (dentroReceita) {
            if (strcmp(linha, "--== FIM DA RECEITA ==--") == 0) {
                if (!deletarEsta) {
                    fprintf(temp, "--== FIM DA RECEITA ==--\n");
                }
                dentroReceita = 0;
                deletarEsta = 0;
                continue;
            }
            if (!deletarEsta) {
                fprintf(temp, "%s\n", linha);
            }
            continue;
        }

        fprintf(temp, "%s\n", linha);
    }

    fclose(og);
    fclose(temp);
    remove("receitas.txt");
    rename("temp.txt", "receitas.txt");
    printf("\nReceita deletada com sucesso!\n");
}
