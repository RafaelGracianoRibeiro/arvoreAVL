# Guia Completo: Rotações e Balanceamento em Árvore AVL

Este guia explica de forma visual e intuitiva como funciona o auto-balanceamento em Árvores AVL, como identificar quando rotacionar e qual sentido escolher.

---

## 1. O que é o Fator de Balanceamento (FB)?

A Árvore AVL calcula para cada nó a diferença de altura entre os seus dois lados:

```text
FB = Altura(Subárvore Esquerda) - Altura(Subárvore Direita)
```

### Quando rotacionar ou NÃO rotacionar?

* **FB = 0**: As duas subárvores têm exatamente a mesma altura.
* **FB = +1**: O lado esquerdo é 1 nível mais fundo (Equilibrado).
* **FB = -1**: O lado direito é 1 nível mais fundo (Equilibrado).
* **FB = +2**: **DESBALANCEOU!** O lado esquerdo ficou pesado demais (Exige Rotação).
* **FB = -2**: **DESBALANCEOU!** O lado direito ficou pesado demais (Exige Rotação).

> **Regra de ouro:** Só existe rotação quando o FB atingir **+2** ou **-2**. Se estiver entre -1 e +1, nenhuma ação é necessária.

---

## 2. A Analogia da Gangorra (Qual sentido girar?)

Pense em uma balança ou gangorra:
* Se o lado **esquerdo** afundou com excesso de peso (FB = +2), você gira a árvore para a **DIREITA** para suspender o lado pesado.
* Se o lado **direito** afundou com excesso de peso (FB = -2), você gira a árvore para a **ESQUERDA** para suspender o lado pesado.

A forma do caminho (se desce em linha reta ou faz curva) determina se a rotação é **Simples** ou **Dupla**.

---

## 3. Os 4 Casos de Rotação

### Grupo 1: Rotações Simples (Caminho em Linha Reta)

#### Caso 1: Esquerda-Esquerda (EE) -> Formato `/`
* **Condição:** FB do nó é **+2** e o valor inserido entrou à **esquerda** do filho esquerdo.
* **Ação:** **Rotação Simples à Direita** (gira no sentido horário).

```text
       (C)  FB = +2
       /
     (B)              ===>           (B)
     /                              /   \
   (A)                            (A)   (C)
(Linha /)                     (Equilibrado)
```

---

#### Caso 2: Direita-Direita (DD) -> Formato `\`
* **Condição:** FB do nó é **-2** e o valor inserido entrou à **direita** do filho direito.
* **Ação:** **Rotação Simples à Esquerda** (gira no sentido anti-horário).

```text
   (A)  FB = -2
     \
     (B)              ===>           (B)
       \                            /   \
       (C)                        (A)   (C)
 (Linha \)                    (Equilibrado)
```

---

### Grupo 2: Rotações Duplas (Caminho em Curva / Cotovelo)

Quando o caminho faz um ziguezague, uma rotação simples não consegue equilibrar a árvore. Por isso, são necessários dois passos:
1. Desentortar o cotovelo para virar uma linha reta.
2. Fazer a rotação principal na raiz.

---

#### Caso 3: Esquerda-Direita (ED) -> Formato `<`
* **Condição:** FB do nó é **+2** (pesou à esquerda), mas o novo valor fez curva para a **direita** do filho esquerdo.
* **Ação:**
  1. Rotação à **Esquerda no filho esquerdo** (transforma `<` na linha reta `/`).
  2. Rotação à **Direita na raiz**.

```text
     (C)  FB = +2             (C)
     /                        /
   (A)           ===>       (B)          ===>       (B)
     \                      /                      /   \
     (B)                  (A)                    (A)   (C)
  (Curva <)           (Linha reta /)           (Equilibrado)
```

---

#### Caso 4: Direita-Esquerda (DE) -> Formato `>`
* **Condição:** FB do nó é **-2** (pesou à direita), mas o novo valor fez curva para a **esquerda** do filho direito.
* **Ação:**
  1. Rotação à **Direita no filho direito** (transforma `>` na linha reta `\`).
  2. Rotação à **Esquerda na raiz**.

```text
   (A)  FB = -2             (A)
     \                        \
     (C)         ===>         (B)        ===>       (B)
     /                          \                  /   \
   (B)                          (C)              (A)   (C)
  (Curva >)           (Linha reta \)           (Equilibrado)
```

---

## 4. Tabela Resumo Rápida

| Fator do Nó (FB) | Onde o valor entrou? | Formato visual | Ação a tomar |
| :--- | :--- | :--- | :--- |
| **FB > 1 (+2)** | Esquerda do filho esquerdo | Linha reta `/` | Rotação Simples à **Direita** |
| **FB < -1 (-2)** | Direita do filho direito | Linha reta `\` | Rotação Simples à **Esquerda** |
| **FB > 1 (+2)** | Direita do filho esquerdo | Cotovelo `<` | Rotação Dupla: **Esquerda no filho, depois Direita na raiz** |
| **FB < -1 (-2)** | Esquerda do filho direito | Cotovelo `>` | Rotação Dupla: **Direita no filho, depois Esquerda na raiz** |

---

## 5. Implementação no Código C++

```cpp
// 1. Atualizar a altura
raiz->altura = 1 + maior(retornaAltura(raiz->esquerda), retornaAltura(raiz->direita));

// 2. Obter o Fator de Balanceamento
int fb = FB(raiz);

// 3. Casos de balanceamento:

// Caso 1: Esquerda-Esquerda
if (fb > 1 && valor < raiz->esquerda->valor) {
    return rotacaoDireita(raiz);
}

// Caso 2: Direita-Direita
if (fb < -1 && valor > raiz->direita->valor) {
    return rotacaoEsquerda(raiz);
}

// Caso 3: Esquerda-Direita
if (fb > 1 && valor > raiz->esquerda->valor) {
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
}

// Caso 4: Direita-Esquerda
if (fb < -1 && valor < raiz->direita->valor) {
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
}
```

---

## 6. Como Funciona a Função `inserir` e o Processo de Recursão

A função `inserir` opera em duas fases graças à recursão: uma **fase de descida** (busca binária) e uma **fase de subida/desempilhamento** (pós-ordem: atualização de alturas e balanceamento).

### 6.1. As 3 Fases da Recursão no Código

```cpp
No* inserir(No* raiz, int valor) {
    // FASE 1: CASO BASE
    // Quando encontra um ponteiro nulo (folha vazia), aloca o novo nó
    if (raiz == nullptr) {
        return new No(valor);
    }

    // FASE 2: DESCIDA RECURSIVA (Busca Binária)
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    } else {
        return raiz; // Valor duplicado (não insere repetido)
    }

    // FASE 3: SUBIDA DO DESEMPILHAMENTO (Pós-Ordem)
    // 1. Atualiza a altura do nó atual
    raiz->altura = 1 + maior(retornaAltura(raiz->esquerda), retornaAltura(raiz->direita));

    // 2. Calcula o Fator de Balanceamento
    int fb = FB(raiz);

    // 3. Verifica e aplica rotações se necessário (EE, DD, ED, DE)
    if (fb > 1 && valor < raiz->esquerda->valor) {
        return rotacaoDireita(raiz);
    }
    if (fb < -1 && valor > raiz->direita->valor) {
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

    // Retorna o nó atual (ou a nova raiz da subárvore após rotação)
    return raiz;
}
```

### 6.2. Rastreamento Passo a Passo em uma Árvore Real

Considere uma árvore inicial com os nós **30** e **20**:
```text
    (30)
    /
  (20)
```
Ao executar `raiz = inserir(raiz, 10);`:

1. **1ª Chamada (Descida): `inserir(nó 30, 10)`**
   * `10 < 30` $\rightarrow$ Chama `inserir(30->esquerda, 10)`, ou seja, `inserir(nó 20, 10)`.
   * A execução do nó 30 fica pausada na pilha de chamadas aguardando o retorno.

2. **2ª Chamada (Descida): `inserir(nó 20, 10)`**
   * `10 < 20` $\rightarrow$ Chama `inserir(20->esquerda, 10)`, ou seja, `inserir(nullptr, 10)`.
   * A execução do nó 20 fica pausada na pilha de chamadas aguardando o retorno.

3. **3ª Chamada (Caso Base): `inserir(nullptr, 10)`**
   * Encontra `raiz == nullptr`.
   * Executa `return new No(10);` (nó criado com altura 1).
   * Retorna o endereço do novo nó para quem o chamou (nó 20).

4. **Retomada da 2ª Chamada (Subida - Nó 20):**
   * `raiz->esquerda = [endereço do nó 10];` (conecta o nó 10 como filho esquerdo).
   * Atualiza altura: `1 + maior(1, 0) = 2`.
   * Calcula FB: `1 - 0 = +1` (balanceado).
   * `return raiz;` (retorna o próprio nó 20 para o nó 30).

5. **Retomada da 1ª Chamada (Subida - Nó 30):**
   * `raiz->esquerda = [endereço do nó 20];` (reconfirma o ponteiro).
   * Atualiza altura: `1 + maior(2, 0) = 3`.
   * Calcula FB: `2 - 0 = +2` (**DESBALANCEOU!**).
   * Avalia as condições: `fb > 1 && 10 < 20` é **Verdadeiro** (Caso Esquerda-Esquerda).
   * Executa `return rotacaoDireita(raiz);`:
     * O nó **20** é promovido a nova raiz da subárvore.
     * O nó **30** se torna o filho direito de 20.
     * As alturas de 30 e 20 são recalculadas.
     * Retorna o nó **20**.

6. **Finalização na `main`:**
   * A variável `raiz` da função `main` recebe o retorno final: o nó **20**.
   * Árvore resultante perfeitamente equilibrada:
```text
        (20)
       /    \
     (10)   (30)
```

### 6.3. Por que a atribuição `raiz->esquerda = inserir(...)` é essencial?
* **Costura de novos nós:** Conecta os nós criados no caso base (`new No`) aos seus respectivos pais.
* **Propagação de rotações:** Quando ocorre uma rotação em uma subárvore filha, a raiz dessa subárvore muda. Essa atribuição atualiza automaticamente o ponteiro do nó pai para apontar para a nova raiz da subárvore rotacionada.
