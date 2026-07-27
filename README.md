# Sistema de Gerenciamento de Eventos Olímpicos

Este projeto é uma aplicação de console desenvolvida em C++ para gerenciar e analisar dados de eventos olímpicos, aplicando e demonstrando os conceitos fundamentais da **Programação Orientada a Objetos (POO)**, como Herança, Polimorfismo e Associações Bidirecionais.

## Objetivo do Projeto

O objetivo principal é simular um sistema de gestão de dados complexos, permitindo a **modelagem** correta das classes (Países, Atletas, Modalidades, Medalhas) e a geração de estatísticas analíticas.

## Como Compilar e Executar

O projeto utiliza um `Makefile` para automatizar a compilação e a limpeza dos arquivos gerados.

### 1. Pré-requisitos

Certifique-se de que o compilador **g++** (padrão C++17) e a ferramenta **make** estejam instalados e configurados em seu ambiente.

### 2. Compilação do Código

Para compilar todos os arquivos-fonte (`.cpp`) e gerar o executável final (`gestao_olimpica`), utilize o comando `make`:

```bash
make
```

### 3. Execução do Sistema

Após a compilação bem-sucedida, você pode iniciar o programa usando a regra run do Makefile:

```bash
make run
```

Alternativamente, você pode executar o arquivo diretamente:

```bash
./gestao_olimpica
```

Ao iniciar, o sistema carregará automaticamente todos os dados e exibirá o menu principal.

### 4. Limpeza do Projeto
Para remover todos os arquivos intermediários (.o) e o executável final utilize a regra clean:

```bash
make clean
```
