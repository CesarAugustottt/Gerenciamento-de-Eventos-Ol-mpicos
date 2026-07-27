#include "medalha.h"
#include "modalidade.h" // Para exibir detalhes na modalidade
#include "atleta.h"     // Para exibir detalhes do atleta
#include "pais.h"       // Para exibir detalhes do país

// Construtor
Medalha::Medalha(const std::string& tipo, int ano, Modalidade* mod)
    : tipo(tipo), anoObtencao(ano), modalidade(mod) {}


// Implementação do Método de Premiação/Associação
void Medalha::premiar(Atleta* atl, Pais* pais) {
    if (atletaGanhador != nullptr) {
        // Evita premiar a mesma medalha duas vezes, se necessário
        std::cerr << "AVISO: Esta medalha já foi associada a um atleta." << std::endl;
        return;
    }
    atletaGanhador = atl;
    paisGanhador = pais;
}

// Método de Exibição
void Medalha::exibirDados() const {
    std::cout << "\n--- DETALHES DA MEDALHA ---" << std::endl;
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Ano de Obtenção: " << anoObtencao << std::endl;
    
    // Associações
    if (modalidade) {
        std::cout << "Modalidade: " << modalidade->nome << " (" << modalidade->evento << ")" << std::endl;
    }
    if (atletaGanhador) {
        // Acessa o atributo público 'nome' do Atleta
        std::cout << "Atleta Ganhador: " << atletaGanhador->nome << std::endl; 
    }
    if (paisGanhador) {
        std::cout << "País Ganhador: " << paisGanhador->nome << std::endl;
    }
}