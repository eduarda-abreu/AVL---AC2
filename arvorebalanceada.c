#include "arvorebalanceada.h"

void inicializarArvore(ArvB *arv){
    arv->raiz == NULL;
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

No* buscar(No *raiz, Prontuario p){
    if (raiz == NULL){
        return NULL; //Ou a árvore não existe ou elemento não foi encontrado.
    }else{
         if(strcmp(p.cpf, raiz->dados.cpf)==0){ //se der 0 são iguais
             return raiz;
         }else{
             if (strcmp(p.cpf, raiz->dados.cpf) < 0){ //realiza busca na subarvore a esquerda
                 return buscar(raiz->esquerda, p);
             }else if (strcmp(p.cpf, raiz->dados.cpf) > 0){ //realiza busca na subarvore a direita
                 return buscar(raiz->direita, p);
             }
         }
    }   
}

No* remover(No *raiz, Prontuario p){
    if (raiz == NULL){
        return NULL; //Ou a árvore não existe ou elemento não foi encontrado para a remoção.
     }else{
         if(strcmp(p.cpf, raiz->dados.cpf)==0){
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
                     while (aux->direita == NULL){
                         aux = aux->direita; //percorre a direita até achar o mais à direita 
                     }
 
                     /*Após achar o nó mais a direita troca os valores do nó a ser removido e o que vai substituir para que ele seja um nó folha ou com um filho só, assim faz recursão de função e chamando o remover para o nó , ai cairá em uma das situações acima e removerá o nó*/
                     raiz->dados = aux->dados;
                     aux->dados = p;
                     raiz->esquerda = remover(raiz->esquerda, p);
                     return raiz;
                 }
             }
        }else{
             if (strcmp(p.cpf, raiz->dados.cpf) < 0){ //realiza busca na subarvore a esquerda
                 raiz->esquerda= remover(raiz->esquerda, p);
            }else if (strcmp(p.cpf, raiz->dados.cpf) > 0){ //realiza busca na subarvore a direita
                 raiz->direita = remover(raiz->direita, p);
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
}

bool atualizar(No *raiz, const char cpf, const char *novoNome, const char *novoHistorico){

}

void imprimeTodosInOrder(No *raiz){

}

void imprimeEspecifico(No *raiz, Prontuario p){

}

bool data_valida(int dia, int mes, int ano){

}

bool inserirDataNascimento(Prontuario *prontuario){

}

short maior(short a, short b){
    return (a>b)? a:b; // se a for maior que b eu retorno a, se não retorna b 
}

short alturaDoNo(No* no){
    if(no== NULL){
        return -1;
    }else{ 
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

    y = r->direita; // raiz ficará a esquerda pois é menor do que o nó 
    f = y->esquerda; //filho (esquerda) do nó que será a raiz sendo armazenado para não perde-lo ao fazer a rotação, pois o nó raiz atual que se tornará filho em seu lugar para balancear a raiz e o no armazenado em f ficará a direita do nó que se tornará filho

    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) +1;
    y->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) +1;
   
    return y; //retorna a nova raiz
}

No* rotacaoDireita(No *r){
    No *y, *f;

    y= r->esquerda;
    f = y->direita;
    
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) +1;
    y->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) +1;
   
    return y; //retorna a nova raiz
}

No* rotacaoDireitaEsquerda(No *r){
    r->direita =  rotacaoDireita(r->direita);
    return rotacaoEsquerda(r);
}

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
    }
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda)< 0){
        raiz = rotacaoEsquerdaDireita(raiz);
    }
    else if(fb< -1 && fatorDeBalanceamento(raiz->direita)>0){
        raiz = rotacaoDireitaEsquerda(raiz);
    }
}