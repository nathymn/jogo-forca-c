# 🎮 Jogo da Forca em C

Este é um jogo da forca desenvolvido em linguagem **C**, com suporte a múltiplas **categorias temáticas**, **dicas personalizadas** e a possibilidade de **adicionar novas palavras** durante a execução. O jogo roda no terminal e foi feito com foco em aprendizado e prática da linguagem C.

## 🔍 Visão Geral

- Interface no terminal  
- Categorias de palavras com dicas  
- Escolha aleatória de palavras  
- Permite adicionar novas palavras  
- Verificação de letras repetidas  
- Exibição do boneco da forca por partes  
- Tratamento de acentos e letras maiúsculas  

## 🛠️ Tecnologias Utilizadas

- Linguagem C (C99 ou superior)  
- Compilador GCC ou compatível  
- Bibliotecas padrão: `stdio.h`, `stdlib.h`, `string.h`, `stdbool.h`, `ctype.h`, `time.h`  

## 🚀 Como Compilar e Executar

1. **Compilar:**  
Use seu compilador C para compilar o arquivo `forca.c`.  

2. **Executar:**  
Após compilar, execute o programa resultante diretamente pelo terminal.  

> No Windows: `forca.exe`  
> No Linux/Mac: `./forca`  

## 📂 Estrutura de Arquivos

- `forca.c` — Código-fonte principal do jogo  

## 🎮 Funcionalidades

- Menu inicial com opções de jogo, adição de palavras e saída  
- Até 5 categorias temáticas com até 10 palavras cada  
- Cada palavra possui uma dica associada  
- Letras repetidas não são processadas duas vezes  
- Boneco da forca atualizado a cada erro  
- Finalização com vitória ou derrota  
