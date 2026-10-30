//Programa de arvores
#include <iostream>
#include <random>
using namespace std;

//Definindo a estrutura de um no usando struct
struct No {
    int valor;
    No* esquerda;
    No* direita;
    int altura;//Guardando a altura do no

    //Definindo os valores padroes de um no, no caso um ponteiro vazio
    No(int val) : valor(val), esquerda(nullptr), direita(nullptr), altura(1) {}
};

//Criando funcao que retorna a altura do meu no
int retornaAltura(No* no) {
    if (no == nullptr) return 0;
    return no->altura;
}
//Criando uma funcao que retorna o FB(fator de balanceamento)
//O fb diminui a altura do lado direito da altura do lado esquerdo
//(fb = AltEsquerda - AltDireita)
int FB(No* no) {
    if (no == nullptr) return 0;
    return retornaAltura(no->esquerda) - retornaAltura(no->direita);
}
//Funcao que compara 2 valores
int maior(int a, int b) {
    if (a > b) return a;
    else return b;
}
//Criando as rotacoes da arvore com base no peso
No* rotacaoDireita(No* noDesbalanceado) {
    No* x = noDesbalanceado->esquerda; //Instanciando a esquerda do meu no atual
    No* y = x->direita;//Salvando o valor da direita de X, para nao perdelo

    x->direita = noDesbalanceado; // O no menor que x se torna a inicial raiz
    noDesbalanceado->esquerda = y;// Na esquerda que esta vazia adicionamos o valor que tinhamos salvado

    //Como trocamos os ponteiros de posicao nos precisamos recalcular a alturas dessa nova configuracao
    //Vamos calcular a nova altura do no inicialmente dedsbalanceado
    //A nova altura e igual ao maior entre a a altura dos seus filhos +1
    noDesbalanceado->altura = maior(retornaAltura(noDesbalanceado->esquerda), retornaAltura(noDesbalanceado->direita)) + 1;
    //A nova altura e igual ao maior entre a a altura dos seus filhos +1
    x->altura = maior(retornaAltura(x->esquerda), retornaAltura(x->direita)) + 1;

    //Retorno o valor do No* X
    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* B = y->esquerda;

    // Executa a rotacao
    y->esquerda = x;
    x->direita = B;

    // Atualiza as alturas
    x->altura = maior(retornaAltura(x->esquerda), retornaAltura(x->direita)) + 1;
    y->altura = maior(retornaAltura(y->esquerda), retornaAltura(y->direita)) + 1;

    return y; // Nova raiz da subarvore
}

//Criando a funcao de inserir um valor na arvore
No* inserir(No* raiz, int valor) {
    //Verificando se o valor da minha raiz e nulo
    if (raiz == nullptr) {
        return new No(valor);
    }
    //Definindo a direcao da insercao com base no valor
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);//Chamando recursao e atualizando raiz
    }else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);//Chamando recursao e atualizando raiz
    }else {
        return raiz;
    }

    //Comecando a logica AVL para balancear a arvore
    //Atualizando a altura do no
    //A altura de um no especifico e a maior distancia de arestas entre ele e qualquer folha abaixo dele
    //Definimos a altura do no como 1 + a maior altura de seus filhos
    raiz->altura = 1 + maior(retornaAltura(raiz->esquerda), retornaAltura(raiz->direita));
    
    //Achando o fator de balanceamento
    int fb = FB(raiz);
    //Desbalanceado se fb > 1 ou fb < -1

    if (fb > 1 && valor < raiz->esquerda->valor) {
        return rotacaoDireita(raiz);
    }

    if (fb > -1 && valor > raiz->direita->valor) {
        return rotacaoEsquerda(raiz);
    }

    if (fb > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

//Criando a funcao de busca dentro da arvore
bool busca(No* raiz, int valor) {
    if (raiz == nullptr) return false;//Verificando a nulidade da raiz primaria
    if (valor == raiz->valor) return true;//Verificando se raiz primaria e o valor de busca

    //Definindo a direcao de busca com base no valor
    if (valor < raiz->valor) {
        return busca(raiz->esquerda, valor);//Chamando recursao e atualizando raiz
    }else {
        return busca(raiz->direita, valor);//Chamando recursao e atualizando raiz
    }
}

//Imprimindo minha arvore no modelo In-Order
void imprimir(No* raiz) {
    //Verificando se minha raiz existe
    if (raiz != nullptr) {
        imprimir(raiz->esquerda);
        cout << raiz->valor << " ";
        imprimir(raiz->direita);
    }
}

int main() {
    //Inicializando minha raiz como um ponteiro nulo
    No* raiz = nullptr;
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 43);
    raiz = inserir(raiz, 21);
    raiz = inserir(raiz, 11);
    raiz = inserir(raiz, 65);
    raiz = inserir(raiz, 87);
    raiz = inserir(raiz, 90);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 100);

    cout << "Elementos da arvore (In-Order) esquerda -> raiz -> direita : ";
    imprimir(raiz); cout << endl;

    return 0;
}
