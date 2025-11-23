# Jogo da Vida de Conway

Este projeto implementa o **Jogo da Vida de Conway** utilizando abordagens **sequencial** e **paralela** em **C**.

---

## Estrutura do projeto

```
.
├── doc/                          # Documentação e relatório do trabalho
│   └── TP.pdf
├── exemplo_de_entrada.txt        # Arquivo de entrada de exemplo
├── LICENSE                       # Licença do projeto
├── Makefile                      # Script de build
├── README.md                     # Este arquivo
└── src/                          # Código-fonte
    ├── Arquivo.c
    ├── Jogo_Vida_Conway.c
    ├── Jogo_Vida_Conway_Paralelo.c
    ├── Programa.c
    ├── Tabuleiro.c
    └── include/                  # Cabeçalhos
        ├── Arquivo.h
        ├── Jogo_Vida_Conway.h
        ├── Jogo_Vida_Conway_Paralelo.h
        └── Tabuleiro.h
```

---

## Requisitos

* GCC (compilador C)
* Make
* Biblioteca pthread (`-pthread`)

---

## Como compilar

No terminal, execute:

```bash
make
```

Isso irá gerar o executável `Programa` na raiz do projeto.

Para recompilar do zero:

```bash
make recompile
```

Para limpar arquivos compilados:

```bash
make clean
```

---

## Como executar

O programa lê um arquivo de entrada com os parâmetros da simulação:

```bash
./Programa <arquivo> <modo>
```

Onde:

* **<arquivo>**: caminho para o arquivo de entrada.
* **<modo>**: define o modo de execução:
    + **seq**: para sequencial.
    + **par**: para paralelo.


Exemplo:

```bash
./Programa exemplo_de_entrada.txt seq   # Modo sequencial
./Programa exemplo_de_entrada.txt par   # Modo paralelo
```

---


## Grupo

* Braian Melo
* Leonardo Ribeiro
