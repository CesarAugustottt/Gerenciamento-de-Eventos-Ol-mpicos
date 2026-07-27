#include "atleta.h"
#include "pais.h"      // Necessário para acessar getNome() do País
#include "modalidade.h" // Necessário para acessar getNome() da Modalidade
#include <iostream>

// Construtor: Chamada da base 'Pessoa'
Atleta::Atleta(const std::string& nome, const std::string& genero, int anoNascimento, Pais* pais, int participacoes)
    // Chamada ao construtor da classe base
    : Pessoa(nome, genero, anoNascimento, pais), 
      participacoes(participacoes) 
{}

// Destrutor
Atleta::~Atleta() {
    // Implementação do destrutor
}

// Implementação Polimórfica do método exibirDados()
void Atleta::exibirDados() {
    std::cout << "\n--- DETALHES DO ATLETA ---" << std::endl;
    
    // Acessa atributos públicos herdados diretamente
    std::cout << "Nome: " << nome << " (Gen.: " << genero << ", Nasc.: " << anoNascimento << ")" << std::endl;
    
    // Acessa atributo específico
    std::cout << "Participações: " << participacoes << std::endl;
    
    // Acessa associação herdada (País)
    if (getPais()) {
        std::cout << "País: " << getPais()->nome << std::endl;
    } else {
        std::cout << "País: [Não Associado]" << std::endl; // Boa prática defensiva
    }
    
    // Exibe modalidades (Herdado de Pessoa)
    std::cout << "Modalidades Associadas: ";
    if (getModalidades().empty()) { // verifica se o atleta tem modalidade
        std::cout << "Nenhuma";
    } else {
        for (const auto& m : getModalidades()) { 
            if (m != nullptr) {
                std::cout << m->nome << " ";
            } else {
                std::cout << "[Modalidade Inválida] ";
            }
        }
    }
    std::cout << std::endl;

    // Exibe medalhas (Associação própria de Atleta)
    std::cout << "Medalhas Conquistadas: " << medalhas.size() << std::endl;
}

//retorna numero de participações
int Atleta:: getParticipacoes() const { 
    return participacoes; 
}

//adiciona o numerod e participações
void Atleta:: setParticipacoes(int num) { 
    participacoes = num; 
}

//retorna vetor de medalhas
const std::vector<Medalha*>& Atleta:: getMedalhas() const { 
    return medalhas; 
}

// Implementação do Método de Associação (Requisito 6)
void Atleta::adicionarMedalha(Medalha* medalha) {
    medalhas.push_back(medalha); // adiciona medalhas
}