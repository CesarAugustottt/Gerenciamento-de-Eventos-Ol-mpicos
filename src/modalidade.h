#ifndef MODALIDADE_H
#define MODALIDADE_H

#include <string>
#include <vector>
#include <iostream>

// Forward declaration para as associações
class Medalha; 
class Atleta;

class Modalidade {
private:
    // Associação: Todas as medalhas concedidas nesta modalidade
    std::vector<Medalha*> medalhasAssociadas;
    // NOVO: Associação: Todos os atletas associados a esta modalidade
    std::vector<Atleta*> atletasAssociados;

public:
    std::string codigo; // Código da modalidade
    std::string nome;   // Nome da modalidade
    std::string evento; // Olimpíadas, Olimpíadas de Inverno ou Paralimpíadas
    // Construtor
    Modalidade(const std::string& codigo, const std::string& nome, const std::string& evento);
    
    // Destrutor
    ~Modalidade() = default;

    // Métodos Getters (Encapsulamento)
    const std::vector<Medalha*>& getMedalhasAssociadas() const;
    const std::vector<Atleta*>& getAtletasAssociados() const;

    // Método de Associação (Requisito 7: Associação de medalhas a modalidades)
    void adicionarMedalha(Medalha* medalha);
    void adicionarAtleta(Atleta* atleta);

    // Método de Exibição
    void exibirDados() const;
};

#endif