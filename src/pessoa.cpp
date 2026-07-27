#include "pessoa.h"

//Contrutor
Pessoa::Pessoa(const std::string& nome, const std::string& genero, int anoNascimento, Pais* pais)
    : pais(pais), nome(nome), genero(genero), anoNascimento(anoNascimento)
{}

Pessoa::~Pessoa() {
    // Implementação do destrutor virtual
}

// Implementação dos Getters para as associações privadas
Pais* Pessoa::getPais() const {
    return pais;
}

const std::vector<Modalidade*>& Pessoa::getModalidades() const {
    return modalidades;
}

// Implementação dos Setters
//adicionar país
void Pessoa::setPais(Pais* p) {
    pais = p;
}

//adicionar modalidade
void Pessoa::setModalidade(Modalidade* m) {
    modalidades.push_back(m);
}