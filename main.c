#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} Arvore;

int buscar (Arvore *a, int v) {
  if (a == NULL) { return 0; } /*Nao achou*/
  else if (v < a->info) {
    return buscar (a->esq, v);
  }
  else if (v > a->info) {
    return buscar (a->dir, v);
  }
  else { return 1; } /*Achou*/
}

Arvore* inserir (Arvore *a, int v) {
  if (a == NULL) {
    a = (Arvore*)malloc(sizeof(Arvore));
    a->info = v;
    a->esq = a->dir = NULL;
  }
  else if (v < a->info) {
    a->esq = inserir (a->esq, v);
  }
  else { a->dir = inserir (a->dir, v); }
  return a;
}

void in_order(Arvore *a){
  if(!a)
    return;
  in_order(a->esq);
  printf("%d ",a->info);
  in_order(a->dir);
}

Arvore* remover(Arvore *a, int x){
  Arvore * aux, * pai_aux;
  int filhos = 0,tmp;

  if(!a)
    return(NULL);

  if(a->info < x)
    a->dir = remover(a->dir,x);
  else if(a->info > x)
    a->esq = remover(a->esq,x);
  else{
    if(a->esq)
      filhos++;
    if(a->dir)
      filhos++;

    if(filhos == 0){
      free(a);
      return(NULL);
    }
    else if(filhos == 1){
      aux = a->esq ? a->esq : a->dir;
      free(a);
      return(aux);
    }
    else{
      aux = a->esq;
      pai_aux = a;
      while(aux->dir){ pai_aux = aux; aux = aux->dir; }
      tmp = a->info;
      a->info = aux->info;
      aux->info = tmp;
      pai_aux->dir = remover(aux,tmp);
      return(a);
    }
  }

  return(a);
}

void print(Arvore * a,int spaces){
  int i;
  for(i=0;i<spaces;i++) printf(" ");
  if(!a){
    printf("//\n");
    return;
  }

  printf("%d\n", a->info);
  print(a->esq,spaces+2);
  print(a->dir,spaces+2);
}

int minValue(Arvore *a){
    Arvore *aux = a;
    while(aux->esq != NULL)
        aux = aux->esq;
    
    return aux->info;
}

int maxValue(Arvore *a){
    Arvore *aux = a;
    while(aux->dir != NULL)
        aux = aux->dir;
    
    return aux->info;
}

int arv_bina_check(Arvore *a){
    if(a == NULL) return 1;

// checa se o valor da esquerda eh maior que a raiz(node que esta sendo verificado)
    if(a->esq != NULL && maxValue(a->esq) > a->info)
        return 0;
        // checa se o valor da direita eh menor que a raiz(node que esta sendo verificado)
    if(a->dir != NULL && minValue(a->dir)<= a->info)
        return 0;
    // continua percorrendo a arvore
    if(!arv_bina_check(a->esq) || !arv_bina_check(a->dir))
        return 0;
    
    
    return 1;
}

int main(){
  Arvore * a;

  a = inserir(NULL,50);
  a = inserir(a,30);
  a = inserir(a,90);
  a = inserir(a,20);
  a = inserir(a,40);
  a = inserir(a,95);
  a = inserir(a,10);
  a = inserir(a,35);
  a = inserir(a,45);
  a = inserir(a,37);

  printf("\n");

    printf("arvore eh binaria: %d\n", arv_bina_check(a));

}