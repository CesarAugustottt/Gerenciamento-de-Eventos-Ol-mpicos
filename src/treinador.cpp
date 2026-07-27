#include "treinador.h"
#include "atleta.h" 
#include <iostream>

// Construtor 
Treinador::Treinador(const std::string& nome, const std::string& genero, int anoNascimento, Pais* pais)
    : Pessoa(nome, genero, anoNascimento, pais) //chama o contrutor da classe base (Pessoa)
{}

// Destrutor
Treinador::~Treinador() {
    // Implementação do destrutor
}

// Implementação Polimórfica do método exibirDados() - Sobrescrevendo o metodo virtual puro de Pessoas
void Treinador::exibirDados() {
    std::cout << "\n--- DETALHES DO TREINADOR ---" << std::endl;
    // Acessa atributos públicos herdados
    std::cout << "Nome: " << nome << " (Gen.: " << genero << ", Nasc.: " << anoNascimento << ")" << std::endl;
    
    // Acessa associação herdada (País)
    if (getPais()) {
        std::cout << "País: " << getPais()->nome << std::endl;
    } else {
        std::cout << "País: [Não Associado]" << std::endl; // Adicionando fallback para robustez
    }
    
    // Exibe Modalidades (Herdado de Pessoa)
    std::cout << "Modalidades de Treinamento: ";

    if (getModalidades().empty()) { // Verifica se o treinador possui modalidades
        std::cout << "Nenhuma";
    } else {
        for (const auto& m : getModalidades()) { 
            // Adicionar verificação de nullptr aqui também é uma boa prática defensiva
            if (m != nullptr) { 
                std::cout << m->nome << " "; 
            }
        }
    }
    std::cout << std::endl;

    // Exibe Atletas Vinculados (Associação própria de Treinador)
    std::cout << "Atletas Vinculados (" << atletas.size() << "): ";
    if (atletas.empty()) { // Verifica se tem atletas
        std::cout << "Nenhum." << std::endl;
    } else {
        std::cout << std::endl;
        for (const auto& a : atletas) {
            if (a != nullptr) { 
                std::cout << "  - " << a->nome << std::endl; 
            } else {
                std::cout << "  - [Atleta nulo/inválido - Falha no Carregamento]" << std::endl;
            }
        }
    }
}

//getters:
const std::vector<Atleta*>& Treinador:: getAtletas() const { 
    return atletas;
}


// Implementação do Método de Associação
void Treinador::setAtleta(Atleta* atleta) {
    atletas.push_back(atleta); // Adiciona atletas ao treinador
}