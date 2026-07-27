#ifndef GESTAO_OLIMPICA_H
#define GESTAO_OLIMPICA_H

#include <iostream>
#include <string>
#include <vector>    //conteiners vetor
#include <map>      //conteiners
#include <fstream> // Para manipulação de arquivos
#include <sstream> // Para manipulação de strings (CSV)

// Inclui todas as classes
#include "pais.h"
#include "pessoa.h" 
#include "atleta.h"
#include "treinador.h"
#include "modalidade.h"
#include "medalha.h"


// Estrutura auxiliar para o Quadro de Medalhas
struct DadosQuadro {
    std::string codigo;
    std::string nome;
    int ouro;
    int prata;
    int bronze;
    int pontuacao; // Ouro (3), Prata (2), Bronze (1)
};

class GestaoOlimpica {
private:
    // STL Map: Armazenamento centralizado com busca rápida por chave (código/nome)
    std::map<std::string, Pais*> paises;
    std::map<std::string, Pessoa*> pessoas; // Pode ser Atleta ou Treinador (Polimorfismo)
    std::map<std::string, Modalidade*> modalidades;
    std::vector<Medalha*> medalhas; // Vetor para manter a ordem de criação

public:
    GestaoOlimpica();
    ~GestaoOlimpica(); // Destrutor para liberar a memória dos ponteiros

    // --- Métodos de Interação (Menu) ---
    void executarMenu();
    void exibirMenu() const;
    
    // Requisitos de Cadastro
    void cadastrarPais(); 
    void cadastrarAtleta(); 
    void cadastrarTreinador();
    void criarModalidade();
    void criarMedalha();

    // Requisitos de Associação e Ações
    void premiarAtleta(); // Requisito 5, 6, 7 (Associação de atleta a medalha, medalha a modalidade)

    // --- Requisitos de Listagem e Relatórios ---
    void exibirQuadroMedalhas(); // Requisito 9
    void listarAtletasPorModalidade(); // Requisito 8

    //ATIVIDADE EXTRA: ESTATISTICA
    void gerarRelatoriosEstatisticas();
    void relatorioGeralPessoas();
    //estatisticas:
    void estatisticaMedalhasPorPais();
    void estatisticaClassificacaoPaises();
    void estatisticaAtletasMaisMedalhas();
    void estatisticaAtletasMaisParticipacoes();
    void estatisticaModalidadesMaisAtletas();
    void estatisticaAnosMaisMedalhasPais();

    // --- Métodos de Busca
    Pais* buscarPais(const std::string& codigo) const;
    Modalidade* buscarModalidade(const std::string& codigo) const;
    Atleta* buscarAtleta(const std::string& nome) const;
    
    // --- Requisitos de Persistência (Manipulação de Arquivos) ---
    void salvarDados();
    void carregarDados();
    

private:
    // Helper para salvar em CSV
    void salvarPessoasCSV(std::ofstream& arquivo);
    void salvarMedalhasCSV(std::ofstream& arquivo);
    void salvarPaisesCSV(std::ofstream& arquivo);
    void salvarModalidadesCSV(std::ofstream& arquivo);
    
    // Helper para carregar de CSV
    void carregarPessoasCSV(std::ifstream& arquivo);
    void carregarPaisesCSV(std::ifstream& arquivo);
    void carregarModalidadesCSV(std::ifstream& arquivo);
    void carregarMedalhasCSV(std::ifstream& arquivo);
};

#endif