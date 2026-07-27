#include "pais.h"
#include "medalha.h" // Necessário para acessar tipo e ano
#include "atleta.h"
#include "modalidade.h" // Necessário para o evento da Modalidade
#include <iostream>

// Implementação do Construtor
Pais::Pais(const std::string& codigo, const std::string& nome) 
    : codigo(codigo), nome(nome) {}

//GETTERS:
//retonar o codigo do pais
std::string Pais:: getCodigo() const { 
    return codigo; 
}
//retorna o vetor de atletas
const std::vector<Atleta*>& Pais:: getAtletas() const { 
    return atletas; 
}
//retorna o vetor de medalhas do país
const std::vector<Medalha*>& Pais:: getMedalhas() const { 
    return medalhas; 
}

//SETTERS
// Implementação dos Métodos de Associação

//adicionar atleta ao país
void Pais::adicionarAtleta(Atleta* atleta) {
    atletas.push_back(atleta); //adiciona elemento ao vetor de atletas
}
//Adicionar medalha ao país
void Pais::adicionarMedalha(Medalha* medalha) {
    medalhas.push_back(medalha); //adiciona elemento ao vetor de medalhas
}

// Implementação do Método de Exibição
void Pais::exibirDados() const {
    std::cout << "País: " << nome << " (" << codigo << ")" << std::endl;
    std::cout << "Total de Atletas Vinculados: " << atletas.size() << std::endl;
    std::cout << "Total de Medalhas Ganhas: " << medalhas.size() << std::endl;
}

// Implementação do Cálculo do Quadro de Medalhas (Requisito 9)
std::map<std::string, int> Pais::getQuadroMedalhas(int ano, const std::string& evento) const {
    std::map<std::string, int> quadro = {
        {"Ouro", 0},
        {"Prata", 0},
        {"Bronze", 0}
    }; //inicializando o map

    for (const auto& medalha : medalhas) { //percorre todas as medalhas e verifica
        // Verifica se o ano é igual ao ano dado
        if (medalha->anoObtencao == ano) {
            // Verifica o evento da Modalidade associada à medalha
            // Assume que Medalha tem getModalidade() e Modalidade tem getEvento()
            if (medalha->modalidade->evento == evento) { //se for igual o contador do map é incrementado
                quadro[medalha->tipo]++; // Assume que Medalha tem getTipo() retornando "Ouro", "Prata" ou "Bronze"
            }
        }
    }
    return quadro;
}

// Implementação do Cálculo de Pontuação (para Classificação Geral)
// Critério: Ouro=3, Prata=2, Bronze=1 (para ordem decrescente)
int Pais::calcularPontuacao(int ano, const std::string& evento) const {
    std::map<std::string, int> quadro = getQuadroMedalhas(ano, evento);
    
    // Pontuação usada para ordenação (Requisito 9)
    return (quadro["Ouro"] * 3) + (quadro["Prata"] * 2) + (quadro["Bronze"] * 1); //o valor retornado é usado para exibir o quadro de medalhas em gestao.
}