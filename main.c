#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_PALAVRAS 10
#define MAX_TEMA 5
#define MAX_LINHA 200

// Definindo as estruturas
typedef struct {
    char palavra[201];
    char dica[201];
} Palavra;

typedef struct {
    char nome[50];
    Palavra palavras[MAX_PALAVRAS];
    int qtdPalavras;
} Categoria;

// Funcoes
void exibirMenu();
void jogar(Categoria categorias[MAX_TEMA]);
void adicionarPalavra(Categoria categorias[MAX_TEMA]);
void exibirCategorias(Categoria categorias[MAX_TEMA]);
int escolherCategoria(Categoria categorias[MAX_TEMA]);
void exibirBoneco(int membros);
bool processarLetra(char letra, char palavraEdit[201], char *esconde, char palavra[201]);
void resultado(char palavra[201], bool ganhou);
void removerAcentos(char *str);
void strToUpper(char *str);

int main() {
    srand(time(NULL));

    // Inicializando categorias e palavras
    Categoria categorias[MAX_TEMA] = {
        {"Animais", {{"GATO", "Animal domesticado"}, {"CACHORRO", "Melhor amigo do homem"}, {"LEAO", "Rei da selva"}}, 3},
        {"Lugares", {{"PARIS", "Cidade das luzes"}, {"LONDRES", "Capital inglesa"}}, 2},
        {"Comidas", {{"PIZZA", "Comida italiana"}, {"SUSHI", "Comida japonesa"}}, 2},
        {"Objetos", {{"LIVRO", "Objeto de leitura"}, {"CANETA", "Instrumento de escrita"}}, 2},
        {"Esportes", {{"FUTEBOL", "Esporte popular no Brasil"}, {"BASQUETE", "Esporte jogado com bola"}, {"TENIS", "Esporte de raquete"}}, 3}
    };

    exibirMenu(categorias);

    return 0;
}

void exibirMenu(Categoria categorias[MAX_TEMA]) {
    int opcao;
    do {
        printf("\n\t==================================="); 
        printf("\n\t|                                 |");
        printf("\n\t|         JOGO DA FORCA           |");
        printf("\n\t|                                 |");
        printf("\n\t==================================="); 
        printf("\n\t| [1] - INICIAR JOGO              |");
        printf("\n\t| [2] - ADICIONAR PALAVRA         |");
        printf("\n\t| [3] - SAIR                      |");
        printf("\n\t==================================="); 
        printf("\n\tDigite o numero de uma das opcoes: ");
        fflush(stdin);
        scanf("%d", &opcao);

        if (opcao == 1) {
            jogar(categorias);
        } else if (opcao == 2) {
            adicionarPalavra(categorias);
        }
    } while (opcao != 3);
}

void jogar(Categoria categorias[MAX_TEMA]) {
    int temaEscolhido = escolherCategoria(categorias);
    if (temaEscolhido == -1) {
        printf("\nNenhuma categoria v�lida foi selecionada. Voltando ao menu...\n");
        return;
    }

    Categoria categoriaSelecionada = categorias[temaEscolhido];
    int index = rand() % categoriaSelecionada.qtdPalavras; // Escolhendo uma palavra aleat�ria da categoria

    char palavra[201], palavraEdit[201], esconde[201];
    strcpy(palavra, categoriaSelecionada.palavras[index].palavra);
    strcpy(palavraEdit, palavra);
    strcpy(esconde, palavra);
    int i;
    for (i = 0; i < strlen(palavra); i++) {
        // Se o caractere for um espa�o, h�fen ou underline, mant�m ele no "esconde"
        if (palavra[i] == ' ' || palavra[i] == '-' || palavra[i] == '_') {
            esconde[i] = palavra[i];
        } else {
            esconde[i] = '_';  // Substitui os outros caracteres por "_"
        }
    }
    esconde[strlen(palavra)] = '\0';  // Certifique-se de finalizar a string com o caractere nulo.

    bool fim = false, ganhou = false;
    int qtdErro = 0;
    char letra;
    char letrasTentadas[MAX_LINHA];
    int j = 0;

    // Loop principal do jogo
    while (!fim) {
        system("cls");
        exibirBoneco(qtdErro);
        printf("\nPalavra: ");
        for (i = 0; i < strlen(esconde); i++) {
            printf("%c ", esconde[i]);
        }
        printf("\nLetras tentadas: ");
        for (i = 0; i < j; i++) {
            printf("%c ", letrasTentadas[i]);
        }

        printf("\nDica: %s", categoriaSelecionada.palavras[index].dica);
        printf("\nDigite uma letra: ");
        fflush(stdin);
        scanf(" %c", &letra);

        letra = toupper(letra);
        bool letraRepetida = false;
        for (i = 0; i < j; i++) {
            if (letrasTentadas[i] == letra) {
                letraRepetida = true;
                break;
            }
        }

        if (!letraRepetida) {
            letrasTentadas[j++] = letra;
            letrasTentadas[j] = '\0';

            bool erro = processarLetra(letra, palavraEdit, esconde, palavra);
            if (erro) {
                qtdErro++;
            }

            if (qtdErro >= 6) {
                fim = true;
                ganhou = false;
            } else if (strcmp(esconde, palavra) == 0) {
                fim = true;
                ganhou = true;
            }
        }
    }

    resultado(palavra, ganhou);
}

int escolherCategoria(Categoria categorias[MAX_TEMA]) {
    exibirCategorias(categorias);
    int opcao;
    printf("\nEscolha uma categoria: ");
    fflush(stdin);
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > MAX_TEMA) {
        return -1;
    }

    return opcao - 1; // Ajustando �ndice para a categoria selecionada
}

void exibirCategorias(Categoria categorias[MAX_TEMA]) {
    printf("\nCategorias dispon�veis:");
    for (int i = 0; i < MAX_TEMA; i++) {
        printf("\n[%d] - %s (Palavras: %d)", i + 1, categorias[i].nome, categorias[i].qtdPalavras);
    }
}

void adicionarPalavra(Categoria categorias[MAX_TEMA]) {
    int temaEscolhido = escolherCategoria(categorias);
    if (temaEscolhido == -1) {
        printf("\nCategoria inv�lida. Voltando ao menu...\n");
        return;
    }

    Categoria *categoriaSelecionada = &categorias[temaEscolhido];

    if (categoriaSelecionada->qtdPalavras >= MAX_PALAVRAS) {
        printf("\nN�o � poss�vel adicionar mais palavras a esta categoria.\n");
        return;
    }

    Palavra novaPalavra;
    printf("\nDigite a nova palavra: ");
    fflush(stdin);
    scanf("%200[^\n]", novaPalavra.palavra);
    removerAcentos(novaPalavra.palavra);
    strToUpper(novaPalavra.palavra);

    printf("\nDigite a dica para a palavra: ");
    fflush(stdin);
    scanf("%200[^\n]", novaPalavra.dica);
    removerAcentos(novaPalavra.dica);
    strToUpper(novaPalavra.dica);

    categoriaSelecionada->palavras[categoriaSelecionada->qtdPalavras] = novaPalavra;
    categoriaSelecionada->qtdPalavras++;

    printf("\nPalavra adicionada com sucesso!\n");
}

void exibirBoneco(int membros) {
    printf("\n+---+");
    printf("\n|   |");
    switch (membros) {
        case 0:
            printf("\n|");
            break;
        case 1:
            printf("\n|   O");
            break;
        case 2:
            printf("\n|   O\n|   |");
            break;
        case 3:
            printf("\n|   O\n|  /|\\");
            break;
        case 4:
            printf("\n|   O\n|  /|\\\n|  /");
            break;
        case 5:
            printf("\n|   O\n|  /|\\\n|  / \\");
            break;
    }
    printf("\n=====");
}

bool processarLetra(char letra, char palavraEdit[201], char *esconde, char palavra[201]) {
    bool erro = true;
    for (int i = 0; i < strlen(palavraEdit); i++) {
        if (letra == palavraEdit[i]) {
            erro = false;
            esconde[i] = palavra[i];
        }
    }
    return erro;
}

void resultado(char palavra[201], bool ganhou) {
    printf("\n\n-------- RESULTADO --------\n");
    printf("Palavra: %s\n", palavra);
    if (ganhou) {
        printf("Voc� ganhou! Parab�ns!\n");
    } else {
        printf("Voc� perdeu. Tente novamente!\n");
    }
}

void removerAcentos(char *str) {
    char comAcento[] = "�����������������������";
    char semAcento[] = "aeiouaeiouaeaeaeaeiouaeiouac";

    for (int i = 0; str[i]; i++) {
        for (int j = 0; j < strlen(comAcento); j++) {
            if (str[i] == comAcento[j]) {
                str[i] = semAcento[j];
                break;
            }
        }
    }
}

void strToUpper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

