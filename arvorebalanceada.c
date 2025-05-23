#include "arvorebalanceada.h"

void inicializarArvore(ArvB *arv){
    arv->raiz = NULL;
}

No* insere(No *raiz, Prontuario p){
    if(raiz == NULL){ //se a raiz é NULL cria um novo nó que é a raiz da árvore
        return novoNo(p);
    }else{ //aqui adiciona abaixo da raiz, seguindo a ordem hierárquica

        //cpf é char e char segue uma regra chamada lexicografia que funciona como a ordem numérica, ou seja, compara se um número é maior que o outro pela ordem numérica, o que é o caso dos cpf, por isso a função abaixo compara os cpfs

        if (strcmp(p.cpf, raiz->dados.cpf) < 0){ //quando retorna negativo significa que o número é menor que o nó atual
            raiz->esquerda= insere(raiz->esquerda, p);
        }else if (strcmp(p.cpf, raiz->dados.cpf) > 0){ //quando retorna positivo significa que o número é maior que o nó atual
            raiz->direita = insere(raiz->direita, p);
        }

        raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

        raiz = balancear(raiz);
        return raiz;
    }
}

No* buscar(No *raiz, char* cpf){
    if (raiz == NULL){
        return NULL; //Ou a árvore não existe ou elemento não foi encontrado.
    }else{
         if(strcmp(cpf, raiz->dados.cpf)==0){ //se der 0 são iguais
             return raiz;
         }else{
             if (strcmp(cpf, raiz->dados.cpf) < 0){ //realiza busca na subarvore a esquerda
                 return buscar(raiz->esquerda, cpf);
             }else if (strcmp(cpf, raiz->dados.cpf) > 0){ //realiza busca na subarvore a direita
                 return buscar(raiz->direita, cpf);
             }
         }
    }   
}

No* remover(No *raiz, const char *cpf){
    if (raiz == NULL){
        return NULL; //Ou a árvore não existe ou elemento não foi encontrado para a remoção.
     }else{
         if(strcmp(cpf, raiz->dados.cpf)==0){
             if(raiz->esquerda == NULL && raiz->direita == NULL){ //remove nós folhas
                 free(raiz); //libera a memória da raiz
                 return NULL;
             }else{
                 //remove nos com um filho ↓
                 if(raiz->esquerda== NULL || raiz->direita == NULL){
                     No *aux;
                     if (raiz->esquerda != NULL){ //se tiver filho a esquerda armazena ele na variável auxiliar
                         aux = raiz->esquerda;
                     }else{
                         aux = raiz->direita; //se tiver filho a direita armazena ele na variável auxiliar
                     }
                     free(raiz); //libera a memória do nó a ser removido
                     return aux; //retorna o nó filho que vai para o lugar do pai
                 }else { //removerá nós com dois filhos
                     /*Ao remover um nó com dois filhos, se usar a subávore a esquerda (que é o caso), substituí pelo maior valor dela, ou seja, o nó mais a direita*/
                     No *aux = raiz->esquerda;
                     while (aux->direita != NULL){
                         aux = aux->direita; //percorre a direita até achar o mais à direita 
                     }
 
                     /*Após achar o nó mais a direita troca os valores do nó a ser removido e o que vai substituir para que ele seja um nó folha ou com um filho só, assim faz recursão de função e chamando o remover para o nó , ai cairá em uma das situações acima e removerá o nó*/
                     raiz->dados = aux->dados;
                     raiz->esquerda = remover(raiz->esquerda, aux->dados.cpf);
                     return raiz;
                 }
             }
        }else{
             if (strcmp(cpf, raiz->dados.cpf) < 0){ //realiza busca na subarvore a esquerda
                 raiz->esquerda= remover(raiz->esquerda, cpf);
            }else if (strcmp(cpf, raiz->dados.cpf) > 0){ //realiza busca na subarvore a direita
                 raiz->direita = remover(raiz->direita, cpf);
            }

            //recalcula a altura de todos os nós entre a raiz e o nó removido
            raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

            //verifica se há necessidade de balancear a arvore
            raiz = balancear(raiz);
    
            return raiz;
         }
     }  
}

No* novoNo(Prontuario p){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->dados = p;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }else{
        printf("Erro ao alocar nó em novo nó");
    }

    return novo;  
}

bool atualizar(No *raiz, const char *cpf, const char *novoNome, const char *novoHistorico){
    if(raiz == NULL){
        return false; //não encontrou cpf ou não há raiz
    }else{
        if(strcmp(cpf, raiz->dados.cpf)==0){ 
            strcpy(raiz->dados.nome, novoNome); //copia o novo nome na variavel da raiz, alterando o nome
            strcpy(raiz->dados.historico, novoHistorico);//copia o novo histórico na variavel da raiz, alterando o histórico
            return true;
        }else{
              if (strcmp(cpf, raiz->dados.cpf) < 0){ //atualiza na subarvore a esquerda
                return atualizar(raiz->esquerda, cpf, novoNome, novoHistorico );
            }else if (strcmp(cpf, raiz->dados.cpf) > 0){ //atualiza na subarvore a direita
                return atualizar(raiz->direita, cpf, novoNome, novoHistorico );
            }
        }
    }

}

void imprimeTodosInOrder(No *raiz){
    //imprime a arvore em ordem ou seja, Esquerda -> Raiz-> Direita
    if(raiz != NULL){
        imprimeTodosInOrder(raiz->esquerda);
        printf("\n------Prontário------\n");        
        printf("Nome: %s\n", raiz->dados.nome);
        printf("Cpf: %s\n", raiz->dados.cpf);
        printf("Data de Nascimento %02d/%02d/%04d\n", raiz->dados.dataNasc.dia,raiz->dados.dataNasc.mes, raiz->dados.dataNasc. ano );
        printf("Histórico: %s\n", raiz->dados.historico);
        printf("-----------------------\n");
        imprimeTodosInOrder(raiz->direita);    
    } 
}

void imprimeEspecifico(No *raiz, Prontuario p){
    //imprime um prontuario especifico a partir do cpf
    if (raiz != NULL){   
        if(strcmp(p.cpf, raiz->dados.cpf)==0){
            printf("\n------Prontário------\n");        
            printf("Nome: %s\n", raiz->dados.nome);
            printf("Cpf: %s\n", raiz->dados.cpf);
            printf("Data de Nascimento %02d/%02d/%04d\n", raiz->dados.dataNasc.dia,raiz->dados.dataNasc.mes, raiz->dados.dataNasc. ano );
            printf("Histórico: %s\n", raiz->dados.historico);
            printf("-----------------------\n");
        }else{
            if (strcmp(p.cpf, raiz->dados.cpf) < 0){ 
                imprimeEspecifico(raiz->esquerda, p);
            }else if (strcmp(p.cpf, raiz->dados.cpf) > 0){ 
                imprimeEspecifico(raiz->direita, p);
            }
        }
    }  
}

bool data_valida(int dia, int mes, int ano){
    if (ano < 1900 || ano > 2025) return false; // Anos válidos, para limitar se a data é valida, não há pessoas nascidas depois de 2025
    if (mes < 1 || mes > 12) return false; //como os meses vão de 1 a 12, se for maior que 12 ou menor que 1 é classificada inválida 
    
    // Verifica se os dias correspondem com os dias contidos nos meses, já que nem todos tem a mesma quantidade de dias
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // verificação para ano bissexto, ja que é o mes 2 e todo ano bissexto é divisivel por 
    if (mes == 2 && ((ano % 400 == 0) || (ano % 100 != 0 && ano % 4 == 0))) {
        dias_mes[1] = 29;
    }
    
    return (dia >= 1 && dia <= dias_mes[mes-1]); //dia só é valido se for entre 1 e o ultimo dia do do seu mês
}

bool inserirDataNascimento(Prontuario *prontuario){
    if (prontuario == NULL) {
        printf("Erro: Prontuário inexistente");
        return false;
    }

    int dia, mes, ano;
    
    printf("\n--- Inserção de Data de Nascimento ---\n");
    
    // Pede para inserir até dar uma data válida
    do {
        printf("Dia (1-31): ");
        scanf("%d", &dia);
        
        printf("Mês (1-12): ");
        scanf("%d", &mes);
        
        printf("Ano (1900-2025): ");
        scanf("%d", &ano);
        
        if (!data_valida(dia, mes, ano)) {
            printf("Data inválida! Por favor, insira novamente.\n");
        }
    } while (!data_valida(dia, mes, ano));
    
    // Atribui a data validada ao prontuário
    prontuario->dataNasc.dia = dia;
    prontuario->dataNasc.mes = mes;
    prontuario->dataNasc.ano = ano;
    
    printf("Data de nascimento inserida com sucesso: %02d/%02d/%04d\n", 
           dia, mes, ano); //imprime a data
    
    return true;
}

short maior(short a, short b){
    return (a>b)? a:b; // se a for maior que b eu retorno a, se não retorna b 
}

//Função que retorna a altura de um nó na árvore 
short alturaDoNo(No* no){
    if(no== NULL){
        // se o nó for nulo (arvore vazia ou filho inexistente), a altura é -1
        return -1;
    }else{ 
        //caso contrário, retorna a altura armazenada no nó
        return no->altura;
    }
}

short fatorDeBalanceamento(No *no){
    if(no){
        return (alturaDoNo(no->esquerda) - alturaDoNo(no->direita)); // se o resultado for -2 ou 2 está desbalanceada a árvore 
    }else{
        return 0;
    }
}

No* rotacaoEsquerda(No *r){
    No *y, *f; //y nó que se tornará raiz e f é o filho desse nó que não pode ser perdido

    y = r->direita; // y é o filho à direita de r e se tornará a nova raiz da subárvore
    f = y->esquerda; //f é o filho esquerdo de y, que será realocado como filho direito de r

    y->esquerda = r; // r se torna filho esquerdo de y
    r->direita = f; // f se torna o filho direito de r

    //Atualizando alturas após a rotação
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) +1;
    y->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) +1;
   
    return y; //retorna a nova raiz
}

No* rotacaoDireita(No *r){
    No *y, *f;//y nó que se tornará raiz e f é o filho desse nó que não pode ser perdido

    y= r->esquerda; //y é filho à esquerda de r e se tornará a nova raiz da subárvore
    f = y->direita;//f é o filho à direita de y, que será realocado como filho esquerdo de r

    y->direita =r;//r se torna filho direito de y
    r->esquerda = f;// f se torna o filho esquerdo de r
    
    //atualiza as alturas após a rotação
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) +1;
    y->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) +1;
   
    return y; //retorna a nova raiz
}

/*Rotação dupla a esquerda -> é necessário fazer primeiro uma rotação à direita no filho a direita e depois uma rotação à esquerda no nó atual */
No* rotacaoDireitaEsquerda(No *r){
    r->direita =  rotacaoDireita(r->direita);
    return rotacaoEsquerda(r);
}

/*Rotação dupla à direita -> é necessário fazer primeiro uma rotação a esquerda no filho à esquerda e depois uma rotação à direita no nó atual*/
No* rotacaoEsquerdaDireita(No *r){
    r->esquerda = rotacaoEsquerda(r->esquerda);
    return rotacaoDireita(r);
}

No* balancear(No *raiz){
    short fb = fatorDeBalanceamento(raiz);
    
    //se está pendendo para direita (fator de balanceamento < -1) e o nó a direita também tem um filho a direita ou dois filhos faz rotação a esquerda 
    if(fb < -1 && fatorDeBalanceamento(raiz->direita) <= 0){
        raiz = rotacaoEsquerda(raiz);
    }//se está pendendo para esquerda (fator de balanceamento > 1) e o nó a esquerda também tem um filho a esquerda ou dois filhos faz rotação a direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda)>= 0){
        raiz =  rotacaoDireita(raiz);
    }/*Caso de rotação dupla a direita: se o filho está pendendo pra esquerda fb > 1, mas o filho à esquerda está pendendo para a direita fator de balanceamento < 0 é necessário fazer a rotação esquerda direita*/
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda)< 0){
        raiz = rotacaoEsquerdaDireita(raiz);
    }
    else if(fb< -1 && fatorDeBalanceamento(raiz->direita)>0){
        raiz = rotacaoDireitaEsquerda(raiz);
    }

    return raiz;
}

Prontuario lerProntuarioDoUsuario() {
    Prontuario p;
    printf("Digite o nome: ");
    getchar(); // Limpa buffer
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;

    printf("Digite o CPF (somente números): ");
    fgets(p.cpf, sizeof(p.cpf), stdin);
    p.cpf[strcspn(p.cpf, "\n")] = 0;

    printf("Digite a data de nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &p.dataNasc.dia, &p.dataNasc.mes, &p.dataNasc.ano);

    printf("Digite o histórico médico: ");
    getchar(); // Limpa buffer
    fgets(p.historico, sizeof(p.historico), stdin);
    p.historico[strcspn(p.historico, "\n")] = 0;

    return p;
}