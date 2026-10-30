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
