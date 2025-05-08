/* #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvorebalanceada.h"  

#define NUM_TESTES 100

No *raiz = NULL;

void gerarNomeAleatorio(char *nome) {
    sprintf(nome, "Paciente_%d\n", rand() % 100000);
}

void gerarHistoricoAleatorio(char *historico) {
    sprintf(historico, "Histórico médico gerado automaticamente.\n");
}

Data gerarDataAleatoria() {
    Data d;
    d.dia = rand() % 28 + 1;
    d.mes = rand() % 12 + 1;
    d.ano = rand() % 50 + 1950;
    return d;
}

void testeInsercao(int total) {
    for (int i = 0; i < total; i++) {
        Prontuario p;
        sprintf(p.cpf, "%011d", 100000000 + i);
        gerarNomeAleatorio(p.nome);
        p.dataNasc = gerarDataAleatoria();
        gerarHistoricoAleatorio(p.historico);

        raiz = insere(raiz, p); // função da ABB ou AVL
    }
}

void testeBusca(int total) {
    for (int i = 0; i < total; i++) {
        char cpf[12];  // CPF como string
        sprintf(cpf, "%011d", 100000000 + i);  // Gerando o CPF como string com 11 dígitos
        buscar(raiz, cpf); // função da ABB ou AVL
    }
}

void testeRemocao(int total) {
    for (int i = 0; i < total; i++) {
        char cpf[12];  // CPF como string
        sprintf(cpf, "%011d", 100000000 + i);  // Gerando o CPF como string com 11 dígitos
        raiz = remover(raiz, cpf); // função da ABB ou AVL
    }
}

int main() {
    srand(time(NULL));
    raiz = NULL;

    clock_t t_inicio, t_fim;
    double tempo_insercao, tempo_busca, tempo_remocao, tempo_total;

    printf("Iniciando benchmark...\n");
    fflush(stdout);

    t_inicio = clock();

    printf("Inserindo %d elementos...\n", NUM_TESTES);
    fflush(stdout);
    clock_t t0 = clock();
    testeInsercao(NUM_TESTES);
    clock_t t1 = clock();
    tempo_insercao = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("Inserção concluída.\n");
    fflush(stdout);

    printf("Buscando %d elementos...\n", NUM_TESTES);
    fflush(stdout);
    t0 = clock();
    testeBusca(NUM_TESTES);
    t1 = clock();
    tempo_busca = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("Busca concluída.\n");
    fflush(stdout);

    printf("Removendo %d elementos...\n", NUM_TESTES);
    fflush(stdout);
    t0 = clock();
    testeRemocao(NUM_TESTES);
    t1 = clock();
    tempo_remocao = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("Remoção concluída.\n");
    fflush(stdout);

    t_fim = clock();
    tempo_total = (double)(t_fim - t_inicio) / CLOCKS_PER_SEC;

    printf("\n--- Resultados do Benchmark ---\n");
    printf("Tempo de inserção: %.6f segundos\n", tempo_insercao);
    printf("Tempo de busca:    %.6f segundos\n", tempo_busca);
    printf("Tempo de remoção:  %.6f segundos\n", tempo_remocao);
    printf("Tempo total:       %.6f segundos\n", tempo_total);
    fflush(stdout);

    return 0;
}

*/

#include <windows.h>  // Para QueryPerformanceCounter
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvorebalanceada.h"

#define NUM_TESTES 1000000

No *raiz = NULL;

// Funções geradoras (sem mudanças)
void gerarNomeAleatorio(char *nome) {
    sprintf(nome, "Paciente_%d", rand() % 100000);
}

void gerarHistoricoAleatorio(char *historico) {
    sprintf(historico, "Histórico médico gerado automaticamente.");
}

Data gerarDataAleatoria() {
    Data d;
    d.dia = rand() % 28 + 1;
    d.mes = rand() % 12 + 1;
    d.ano = rand() % 50 + 1950;
    return d;
}

void testeInsercao(int total) {
    for (int i = 0; i < total; i++) {
        Prontuario p;
        sprintf(p.cpf, "%011d", 100000000 + i);
        gerarNomeAleatorio(p.nome);
        p.dataNasc = gerarDataAleatoria();
        gerarHistoricoAleatorio(p.historico);
        raiz = insere(raiz, p);
    }
}

void testeBusca(int total) {
    for (int i = 0; i < total; i++) {
        char cpf[12];
        sprintf(cpf, "%011d", 100000000 + i);
        buscar(raiz, cpf);
    }
}

void testeRemocao(int total) {
    for (int i = 0; i < total; i++) {
        char cpf[12];
        sprintf(cpf, "%011d", 100000000 + i);
        raiz = remover(raiz, cpf);
    }
}

double medirTempo(void (*funcao)(int), int total) {
    LARGE_INTEGER inicio, fim, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&inicio);

    funcao(total);

    QueryPerformanceCounter(&fim);

    return (double)(fim.QuadPart - inicio.QuadPart) / freq.QuadPart;
}

int main() {
    srand(time(NULL));
    raiz = NULL;

    printf("Iniciando benchmark...\n");
    fflush(stdout);

    printf("Inserindo %d elementos...\n", NUM_TESTES);
    fflush(stdout);
    double tempo_insercao = medirTempo(testeInsercao, NUM_TESTES);
    printf("Inserção concluída.\n");

    printf("Buscando %d elementos...\n", NUM_TESTES);
    fflush(stdout);
    double tempo_busca = medirTempo(testeBusca, NUM_TESTES);
    printf("Busca concluída.\n");

    printf("Removendo %d elementos...\n", NUM_TESTES);
    fflush(stdout);
    double tempo_remocao = medirTempo(testeRemocao, NUM_TESTES);
    printf("Remoção concluída.\n");

    double tempo_total = tempo_insercao + tempo_busca + tempo_remocao;

    printf("\n--- Resultados do Benchmark ---\n");
    printf("Tempo de inserção: %.6f segundos\n", tempo_insercao);
    printf("Tempo de busca:    %.6f segundos\n", tempo_busca);
    printf("Tempo de remoção:  %.6f segundos\n", tempo_remocao);
    printf("Tempo total:       %.6f segundos\n", tempo_total);

    return 0;
}