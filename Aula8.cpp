#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARQUIVO "perguntas.csv"

/* ==============================
   ESTRUTURA DA PERGUNTA
   ============================== */

typedef struct {
    int id;
    char texto[250];
    char categoria[50];
    char curso[10];
    char resposta[4];
} Pergunta;


/* ==============================
   PROTÓTIPOS DAS FUNÇÕES
   ============================== */

void cadastrarPergunta();
void listarPerguntas();
void consultarPorCategoria();
void consultarPorCurso();
void atualizarPergunta();
void excluirPergunta();

int validarCurso(char curso[]);
int validarResposta(char resposta[]);
int obterProximoId();
void limparBuffer();
void removerQuebraLinha(char texto[]);
void converterMaiusculo(char texto[]);


/* ==============================
   FUNÇÃO PRINCIPAL
   ============================== */

int main() {

    int opcao;

    do {

        printf("\n");
        printf("=========================================\n");
        printf("     GERENCIADOR DE PERGUNTAS - QUIZ\n");
        printf("=========================================\n");
        printf("1 - Cadastrar pergunta\n");
        printf("2 - Listar todas as perguntas\n");
        printf("3 - Consultar perguntas por categoria\n");
        printf("4 - Consultar perguntas por curso\n");
        printf("5 - Atualizar pergunta\n");
        printf("6 - Excluir pergunta\n");
        printf("0 - Sair\n");
        printf("-----------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {

            printf("\nERRO: Digite apenas um numero.\n");

            limparBuffer();

            continue;
        }

        limparBuffer();

        switch (opcao) {

            case 1:
                cadastrarPergunta();
                break;

            case 2:
                listarPerguntas();
                break;

            case 3:
                consultarPorCategoria();
                break;

            case 4:
                consultarPorCurso();
                break;

            case 5:
                atualizarPergunta();
                break;

            case 6:
                excluirPergunta();
                break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nERRO: Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}


/* ==============================
   LIMPAR BUFFER
   ============================== */

void limparBuffer() {

    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        /* limpa o buffer */
    }
}


/* ==============================
   REMOVER QUEBRA DE LINHA
   ============================== */

void removerQuebraLinha(char texto[]) {

    texto[strcspn(texto, "\n")] = '\0';
}


/* ==============================
   CONVERTER PARA MAIUSCULO
   ============================== */

void converterMaiusculo(char texto[]) {

    int i;

    for (i = 0; texto[i] != '\0'; i++) {

        texto[i] = toupper((unsigned char) texto[i]);
    }
}


/* ==============================
   VALIDAR CURSO
   ============================== */

int validarCurso(char curso[]) {

    converterMaiusculo(curso);

    if (strcmp(curso, "CC") == 0) {
        return 1;
    }

    if (strcmp(curso, "ES") == 0) {
        return 1;
    }

    if (strcmp(curso, "ADS") == 0) {
        return 1;
    }

    return 0;
}


/* ==============================
   VALIDAR RESPOSTA
   ============================== */

int validarResposta(char resposta[]) {

    converterMaiusculo(resposta);

    if (strcmp(resposta, "SIM") == 0) {
        return 1;
    }

    if (strcmp(resposta, "NAO") == 0) {
        return 1;
    }

    return 0;
}


/* ==============================
   OBTER PROXIMO ID
   ============================== */

int obterProximoId() {

    FILE *arquivo;

    Pergunta p;

    int maiorId = 0;

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        return 1;
    }

    while (fgets(
        p.texto,
        sizeof(p.texto),
        arquivo
    ) != NULL) {

        char linha[400];

        char *campo;

        int id;

        strcpy(linha, p.texto);

        campo = strtok(linha, ";");

        if (campo != NULL) {

            id = atoi(campo);

            if (id > maiorId) {
                maiorId = id;
            }
        }
    }

    fclose(arquivo);

    return maiorId + 1;
}


/* ==============================
   CADASTRAR PERGUNTA
   ============================== */

void cadastrarPergunta() {

    FILE *arquivo;

    Pergunta p;

    p.id = obterProximoId();

    printf("\n=========================================\n");
    printf("          CADASTRAR PERGUNTA\n");
    printf("=========================================\n");

    printf("Codigo: %d\n", p.id);

    /* TEXTO DA PERGUNTA */

    do {

        printf("Pergunta: ");

        fgets(
            p.texto,
            sizeof(p.texto),
            stdin
        );

        removerQuebraLinha(p.texto);

        if (strlen(p.texto) == 0) {

            printf("ERRO: A pergunta nao pode ficar vazia.\n");
        }

    } while (strlen(p.texto) == 0);


    /* CATEGORIA */

    do {

        printf("Categoria: ");

        fgets(
            p.categoria,
            sizeof(p.categoria),
            stdin
        );

        removerQuebraLinha(p.categoria);

        if (strlen(p.categoria) == 0) {

            printf("ERRO: A categoria nao pode ficar vazia.\n");
        }

    } while (strlen(p.categoria) == 0);


    /* CURSO */

    do {

        printf("Curso (CC/ES/ADS): ");

        fgets(
            p.curso,
            sizeof(p.curso),
            stdin
        );

        removerQuebraLinha(p.curso);

        if (!validarCurso(p.curso)) {

            printf(
                "ERRO: O curso deve ser CC, ES ou ADS.\n"
            );
        }

    } while (!validarCurso(p.curso));


    /* RESPOSTA */

    do {

        printf("Resposta (SIM/NAO): ");

        fgets(
            p.resposta,
            sizeof(p.resposta),
            stdin
        );

        removerQuebraLinha(p.resposta);

        if (!validarResposta(p.resposta)) {

            printf(
                "ERRO: A resposta deve ser SIM ou NAO.\n"
            );
        }

    } while (!validarResposta(p.resposta));


    /* ABRIR ARQUIVO PARA ADICIONAR */

    arquivo = fopen(ARQUIVO, "a");

    if (arquivo == NULL) {

        printf(
            "\nERRO: Nao foi possivel abrir o arquivo.\n"
        );

        return;
    }


    /* GRAVAR NO CSV */

    fprintf(
        arquivo,
        "%d;%s;%s;%s;%s\n",
        p.id,
        p.texto,
        p.categoria,
        p.curso,
        p.resposta
    );


    fclose(arquivo);

    printf(
        "\nPergunta cadastrada com sucesso!\n"
    );
}


/* ==============================
   LISTAR PERGUNTAS
   ============================== */

void listarPerguntas() {

    FILE *arquivo;

    Pergunta p;

    char linha[400];

    int encontrou = 0;


    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {

        printf(
            "\nNenhuma pergunta cadastrada ainda.\n"
        );

        return;
    }


    printf("\n=========================================\n");
    printf("          TODAS AS PERGUNTAS\n");
    printf("=========================================\n");


    while (fgets(
        linha,
        sizeof(linha),
        arquivo
    ) != NULL) {

        char *campo;

        removerQuebraLinha(linha);


        /* ID */

        campo = strtok(linha, ";");

        if (campo == NULL) {
            continue;
        }

        p.id = atoi(campo);


        /* TEXTO */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(p.texto, campo);


        /* CATEGORIA */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(p.categoria, campo);


        /* CURSO */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(p.curso, campo);


        /* RESPOSTA */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(p.resposta, campo);


        printf("\nCodigo: %d\n", p.id);
        printf("Pergunta: %s\n", p.texto);
        printf("Categoria: %s\n", p.categoria);
        printf("Curso: %s\n", p.curso);
        printf("Resposta: %s\n", p.resposta);
        printf("-----------------------------------------\n");


        encontrou = 1;
    }


    fclose(arquivo);


    if (!encontrou) {

        printf(
            "\nNenhuma pergunta encontrada.\n"
        );
    }
}


/* ==============================
   CONSULTAR POR CATEGORIA
   ============================== */

void consultarPorCategoria() {

    FILE *arquivo;

    char linha[400];

    char categoriaBusca[50];

    int encontrou = 0;


    printf("\n=========================================\n");
    printf("       CONSULTAR POR CATEGORIA\n");
    printf("=========================================\n");

    printf("Categoria desejada: ");

    fgets(
        categoriaBusca,
        sizeof(categoriaBusca),
        stdin
    );

    removerQuebraLinha(categoriaBusca);


    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {

        printf(
            "\nERRO: Arquivo de perguntas nao encontrado.\n"
        );

        return;
    }


    printf("\nPerguntas encontradas:\n");


    while (fgets(
        linha,
        sizeof(linha),
        arquivo
    ) != NULL) {

        char copia[400];

        char *campo;

        int id;

        char texto[250];

        char categoria[50];

        char curso[10];

        char resposta[4];


        removerQuebraLinha(linha);

        strcpy(copia, linha);


        /* ID */

        campo = strtok(copia, ";");

        if (campo == NULL) {
            continue;
        }

        id = atoi(campo);


        /* TEXTO */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(texto, campo);


        /* CATEGORIA */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(categoria, campo);


        /* CURSO */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(curso, campo);


        /* RESPOSTA */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(resposta, campo);


        if (
            strcmp(categoria, categoriaBusca) == 0
        ) {

            printf(
                "[%d] %s - %s - %s\n",
                id,
                texto,
                curso,
                resposta
            );

            encontrou = 1;
        }
    }


    fclose(arquivo);


    if (!encontrou) {

        printf(
            "Nenhuma pergunta encontrada para essa categoria.\n"
        );
    }
}


/* ==============================
   CONSULTAR POR CURSO
   ============================== */

void consultarPorCurso() {

    FILE *arquivo;

    char linha[400];

    char cursoBusca[10];

    int encontrou = 0;


    printf("\n=========================================\n");
    printf("          CONSULTAR POR CURSO\n");
    printf("=========================================\n");

    do {

        printf("Curso (CC/ES/ADS): ");

        fgets(
            cursoBusca,
            sizeof(cursoBusca),
            stdin
        );

        removerQuebraLinha(cursoBusca);

        if (!validarCurso(cursoBusca)) {

            printf(
                "ERRO: Digite somente CC, ES ou ADS.\n"
            );
        }

    } while (!validarCurso(cursoBusca));


    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {

        printf(
            "\nERRO: Arquivo de perguntas nao encontrado.\n"
        );

        return;
    }


    printf("\nPerguntas relacionadas ao curso %s:\n",
           cursoBusca);


    while (fgets(
        linha,
        sizeof(linha),
        arquivo
    ) != NULL) {

        char copia[400];

        char *campo;

        int id;

        char texto[250];

        char categoria[50];

        char curso[10];

        char resposta[4];


        removerQuebraLinha(linha);

        strcpy(copia, linha);


        /* ID */

        campo = strtok(copia, ";");

        if (campo == NULL) {
            continue;
        }

        id = atoi(campo);


        /* TEXTO */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(texto, campo);


        /* CATEGORIA */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(categoria, campo);


        /* CURSO */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(curso, campo);


        /* RESPOSTA */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(resposta, campo);


        if (
            strcmp(curso, cursoBusca) == 0
        ) {

            printf(
                "[%d] %s - %s - %s\n",
                id,
                texto,
                categoria,
                resposta
            );

            encontrou = 1;
        }
    }


    fclose(arquivo);


    if (!encontrou) {

        printf(
            "Nenhuma pergunta encontrada para esse curso.\n"
        );
    }
}


/* ==============================
   ATUALIZAR PERGUNTA
   ============================== */

void atualizarPergunta() {

    FILE *arquivo;

    FILE *temporario;

    Pergunta p;

    char linha[400];

    int idBusca;

    int encontrou = 0;


    printf("\n=========================================\n");
    printf("           ATUALIZAR PERGUNTA\n");
    printf("=========================================\n");

    printf("Codigo da pergunta: ");

    if (scanf("%d", &idBusca) != 1) {

        printf(
            "ERRO: Codigo invalido.\n"
        );

        limparBuffer();

        return;
    }

    limparBuffer();


    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {

        printf(
            "\nERRO: Arquivo de perguntas nao encontrado.\n"
        );

        return;
    }


    temporario = fopen("temporario.csv", "w");

    if (temporario == NULL) {

        printf(
            "\nERRO: Nao foi possivel criar arquivo temporario.\n"
        );

        fclose(arquivo);

        return;
    }


    while (fgets(
        linha,
        sizeof(linha),
        arquivo
    ) != NULL) {

        char copia[400];

        char *campo;


        removerQuebraLinha(linha);

        strcpy(copia, linha);


        /* ID */

        campo = strtok(copia, ";");

        if (campo == NULL) {
            continue;
        }

        p.id = atoi(campo);


        /* TEXTO */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(p.texto, campo);


        /* CATEGORIA */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(p.categoria, campo);


        /* CURSO */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(p.curso, campo);


        /* RESPOSTA */

        campo = strtok(NULL, ";");

        if (campo == NULL) {
            continue;
        }

        strcpy(p.resposta, campo);


        if (p.id == idBusca) {

            encontrou = 1;


            printf("\nPergunta encontrada!\n");

            printf(
                "Pergunta atual: %s\n",
                p.texto
            );


            /* NOVO TEXTO */

            do {

                printf("Novo texto: ");

                fgets(
                    p.texto,
                    sizeof(p.texto),
                    stdin
                );

                removerQuebraLinha(p.texto);

                if (strlen(p.texto) == 0) {

                    printf(
                        "ERRO: A pergunta nao pode ficar vazia.\n"
                    );
                }

            } while (strlen(p.texto) == 0);


            /* NOVA CATEGORIA */

            do {

                printf("Nova categoria: ");

                fgets(
                    p.categoria,
                    sizeof(p.categoria),
                    stdin
                );

                removerQuebraLinha(p.categoria);

                if (strlen(p.categoria) == 0) {

                    printf(
                        "ERRO: A categoria nao pode ficar vazia.\n"
                    );
                }

            } while (strlen(p.categoria) == 0);


            /* NOVO CURSO */

            do {

                printf("Novo curso (CC/ES/ADS): ");

                fgets(
                    p.curso,
                    sizeof(p.curso),
                    stdin
                );

                removerQuebraLinha(p.curso);

                if (!validarCurso(p.curso)) {

                    printf(
                        "ERRO: O curso deve ser CC, ES ou ADS.\n"
                    );
                }

            } while (!validarCurso(p.curso));


            /* NOVA RESPOSTA */

            do {

                printf("Nova resposta (SIM/NAO): ");

                fgets(
                    p.resposta,
                    sizeof(p.resposta),
                    stdin
                );

                removerQuebraLinha(p.resposta);

                if (!validarResposta(p.resposta)) {

                    printf(
                        "ERRO: A resposta deve ser SIM ou NAO.\n"
                    );
                }

            } while (!validarResposta(p.resposta));


            printf(
                "Pergunta atualizada com sucesso!\n"
            );
        }


        /* GRAVA A PERGUNTA NO TEMPORARIO */

        fprintf(
            temporario,
            "%d;%s;%s;%s;%s\n",
            p.id,
            p.texto,
            p.categoria,
            p.curso,
            p.resposta
        );
    }


    fclose(arquivo);

    fclose(temporario);


    if (!encontrou) {

        remove("temporario.csv");

        printf(
            "\nNenhuma pergunta encontrada com o codigo %d.\n",
            idBusca
        );

        return;
    }


    /* SUBSTITUI O ARQUIVO ORIGINAL */

    remove(ARQUIVO);

    rename("temporario.csv", ARQUIVO);
}


/* ==============================
   EXCLUIR PERGUNTA
   ============================== */

void excluirPergunta() {

    FILE *arquivo;

    FILE *temporario;

    char linha[400];

    int idBusca;

    int encontrou = 0;


    printf("\n=========================================\n");
    printf("            EXCLUIR PERGUNTA\n");
    printf("=========================================\n");

    printf("Codigo da pergunta: ");


    if (scanf("%d", &idBusca) != 1) {

        printf(
            "ERRO: Codigo invalido.\n"
        );

        limparBuffer();

        return;
    }

    limparBuffer();


    arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {

        printf(
            "\nERRO: Arquivo de perguntas nao encontrado.\n"
        );

        return;
    }


    temporario = fopen("temporario.csv", "w");

    if (temporario == NULL) {

        printf(
            "\nERRO: Nao foi possivel criar arquivo temporario.\n"
        );

        fclose(arquivo);

        return;
    }


    while (fgets(
        linha,
        sizeof(linha),
        arquivo
    ) != NULL) {

        char copia[400];

        char *campo;

        int id;


        removerQuebraLinha(linha);

        strcpy(copia, linha);


        campo = strtok(copia, ";");

        if (campo == NULL) {
            continue;
        }

        id = atoi(campo);


        if (id == idBusca) {

            encontrou = 1;

            /* NAO COPIA A PERGUNTA PARA O TEMPORARIO */

            continue;
        }


        /* COPIA AS DEMAIS PERGUNTAS */

        fprintf(
            temporario,
            "%s\n",
            linha
        );
    }


    fclose(arquivo);

    fclose(temporario);


    if (!encontrou) {

        remove("temporario.csv");

        printf(
            "\nNenhuma pergunta encontrada com o codigo %d.\n",
            idBusca
        );

        return;
    }


    /* SUBSTITUI O ARQUIVO ORIGINAL */

    remove(ARQUIVO);

    rename("temporario.csv", ARQUIVO);


    printf(
        "\nPergunta excluida com sucesso!\n"
    );
}