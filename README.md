![Language](https://img.shields.io/badge/language-C-blue)
![Status](https://img.shields.io/badge/status-Finalizado-brightgreen)
![Parser](https://img.shields.io/badge/Analisador-Léxico%20%2F%20Sintático-orange)
![Grammar](https://img.shields.io/badge/Gramática-MicroPascal-red)
![Last Commit](https://img.shields.io/badge/github-last--commit-lightgrey)
![License](https://img.shields.io/badge/license-MIT-green)
![Repo Size](https://img.shields.io/badge/repo--size-auto-blue)

# 📘 Analisador Léxico e Sintático — MicroPascal

Implementação em C usando **Recursive Descent Parsing**

Este projeto apresenta a construção completa das etapas de **Análise Léxica** e **Análise Sintática** de um compilador para a linguagem **MicroPascal**, desenvolvido como parte da disciplina de *Linguagens Formais, Autômatos e Compiladores* da UCB.

---

## 📌 Visão Geral

O sistema é dividido em duas etapas principais:

### 🔹 Analisador Léxico

Responsável por ler o código-fonte e convertê-lo em uma sequência organizada de **tokens**, removendo espaços, comentários e identificando:

* Identificadores
* Palavras reservadas
* Símbolos simples e duplos
* Números inteiros e reais
* Delimitadores

Cada token é armazenado com:

* Tipo (enum)
* Lexema
* Linha e coluna no código

### 🔹 Analisador Sintático

Valida se a sequência de tokens segue as regras da **Gramática Livre de Contexto (GLC)** da linguagem MicroPascal.
A implementação utiliza **descida recursiva**, mapeando cada não-terminal da gramática para uma função em C.

---

# 🔍 Detalhamento dos Principais Componentes

## ✴️ 1. Analisador Léxico

### ✔ Função `recuperarTipoDado`

Classifica símbolos individuais (+, -, ;, (, ), :=, etc).
Retorna o tipo do token ou ERRO caso o símbolo não exista na linguagem.

### ✔ Função `separaSimbolos`

* Isola símbolos compostos (`:=`, `<=`, `>=`, `==`)
* Separa símbolos simples
* Preserva números reais como `2.5` sem quebrar o ponto
* Usa `strtok_s` para gerar tokens organizados

### ✔ Função `NovoArquivo`

Gera `leitura.lex`, contendo todos os tokens reconhecidos pelo léxico.

### ✔ Função `AbrirArquivo`

Lê o código-fonte linha a linha, separa tokens e envia para o analisador léxico.

---

# ✴️ 2. Analisador Sintático (Recursive Descent)

### 📌 Função 1 — `ProgramaEBloco`

Valida:

```
program <id> ;
<bloco>
..
```

É o ponto de entrada do compilador.

### 📌 Função 2 — `bloco`

Contém:

* Declaração de variáveis (`var`)
* Comando composto (`begin ... end`)

### 📌 Função 3 — `comando`

Reconhece:

* Atribuições
* Comandos compostos
* Estruturas `if … then … else`
* Estruturas `while … do`

### 📌 Função 4 — `expressao`

Analisa termos, fatores, operadores aritméticos e operadores relacionais.
Garante precedência correta e estrutura válida.

---

# 🧪 Testes do Sistema

O analisador foi testado com múltiplos arquivos válidos e inválidos.

## ✔ Testes com Programas Corretos

Os testes incluem:

* Declarações de variáveis
* Comandos compostos
* `if/then/else`
* `while/do`
* Operações aritméticas envolvendo inteiros e reais

Resultados:

* Todos os programas corretos foram **aceitos**
* Árvores de derivação completas registradas nos logs

## ❌ Testes com Erros Sintáticos

Casos avaliados:

### 🔸 Erro 1 — Estrutura incorreta de `if/then/else`

`else` sem bloco delimitado → erro capturado.

### 🔸 Erro 2 — Variável não declarada

Uso de identificador fora da seção `var`.

### 🔸 Erro 3 — Operador inválido

Uso de `%` ao invés de `mod`.

Resultados:

* Todos os erros foram detectados com precisão
* Mensagens exibem linha, lexema, token encontrado e token esperado

---

# 📄 Considerações Finais

O sistema final atende **100% dos requisitos**:

* ✔ Validação estrutural completa
* ✔ Geração de árvore de derivação
* ✔ Tratamento robusto de erros
* ✔ Léxico e sintático funcionando em conjunto

### 🧩 Desafio Resolvido

Reconhecimento correto de números reais seguidos de delimitadores:
`2.5;` → token REAL + token `;`
Problema solucionado ajustando regras do léxico.

---

# 🚀 Como Compilar e Executar

```bash
gcc main.c -o analisador
./analisador
```

---

# 👨‍💻 Autor

* Luiz Rocha

TRABALHO DA MATERIA LINGUAGENS FORMAIS, AUTÔMATOS E COMPILADORES
           Universidade Católica de Brasília — UCB


