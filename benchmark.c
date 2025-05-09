#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "arvorebalanceada.h"

#define NUM_TESTES 1000000


No *raiz = NULL;
char cpfs[NUM_TESTES][12];  // Armazena os CPFs embaralhados

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

void gerarCPFsUnicos(char cpfs[][12], int total) {
    for (int i = 0; i < total; i++) {
        sprintf(cpfs[i], "%011d", 100000000 + i); //insere ordenado

        //  //insere aleatoriamente
    }

    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[12];
        strcpy(temp, cpfs[i]);
        strcpy(cpfs[i], cpfs[j]);
        strcpy(cpfs[j], temp);
    }
}

void testeInsercao(int total) {
    for (int i = 0; i < total; i++) {
        Prontuario p;
        strcpy(p.cpf, cpfs[i]);
        gerarNomeAleatorio(p.nome);
        p.dataNasc = gerarDataAleatoria();
        gerarHistoricoAleatorio(p.historico);
        raiz = insere(raiz, p);
    }
}

void testeBusca(int total) {
    for (int i = 0; i < total; i++) {
        buscar(raiz, cpfs[i]);
    }
}

void testeRemocao(int total) {
    for (int i = 0; i < total; i++) {
        raiz = remover(raiz, cpfs[i]);
    }
}

void testeAtualizacao(int total) {
    for (int i = 0; i < total; i++) {
        char novoNome[100];
        char novoHistorico[1000];
        sprintf(novoNome, "Nome_Atualizado_%d", i);
        sprintf(novoHistorico, "Histórico atualizado %d", i);
        atualizar(raiz, cpfs[i], novoNome, novoHistorico);
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
    gerarCPFsUnicos(cpfs, NUM_TESTES);

    printf("Iniciando benchmark...\n");

    printf("Inserindo %d elementos...\n", NUM_TESTES);
    double tempo_insercao = medirTempo(testeInsercao, NUM_TESTES);
    printf("Inserção concluída.\n");

    printf("Buscando %d elementos...\n", NUM_TESTES);
    double tempo_busca = medirTempo(testeBusca, NUM_TESTES);
    printf("Busca concluída.\n");

    printf("Atualizando %d elementos...\n", NUM_TESTES);
    double tempo_atualizacao = medirTempo(testeAtualizacao, NUM_TESTES);
    printf("Atualização concluída.\n");

    printf("Removendo %d elementos...\n", NUM_TESTES);
    double tempo_remocao = medirTempo(testeRemocao, NUM_TESTES);
    printf("Remoção concluída.\n");

    double tempo_total = tempo_insercao + tempo_busca + tempo_atualizacao + tempo_remocao;

    printf("\n--- Resultados do Benchmark ---\n");
    printf("Tempo de inserção:   %.6f segundos\n", tempo_insercao);
    printf("Tempo de busca:      %.6f segundos\n", tempo_busca);
    printf("Tempo de atualização:%.6f segundos\n", tempo_atualizacao);
    printf("Tempo de remoção:    %.6f segundos\n", tempo_remocao);
    printf("Tempo total:         %.6f segundos\n", tempo_total);

    return 0;
}