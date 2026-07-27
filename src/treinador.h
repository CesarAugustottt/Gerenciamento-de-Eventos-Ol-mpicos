#ifndef TREINADOR_H
#define TREINADOR_H

#include "pessoa.h" // Classe base
#include "pais.h"
#include <vector>

// já que Treinador armazena ponteiros de Atleta, deve declarar antes :
class Atleta; 

class Treinador : public Pessoa {
private:
    // Associação: Atletas vinculados (1..*) -> um treinador pode ter vários atletas para treinar
    std::vector<Atleta*> atletas;  //vetor de atletas

public:
    // Construtor: Chama o construtor da classe base 'Pessoa'
    Treinador(const std::string& nome, const std::string& genero, int anoNascimento, Pais* pais);
    
    // Destrutor sobrescrito
    ~Treinador() override;

    // metodo sobrescrito (polimorfismo)
    void exibirDados() override;

    // Getters
    const std::vector<Atleta*>& getAtletas() const;

    // Setters
    //adicionar atletas
    void setAtleta(Atleta* atleta);
};

#endif