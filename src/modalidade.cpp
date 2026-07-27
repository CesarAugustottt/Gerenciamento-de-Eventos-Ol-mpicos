#include "modalidade.h"
#include <algorithm> // Útil para futuros filtros

// Construtor
Modalidade::Modalidade(const std::string& codigo, const std::string& nome, const std::string& evento)
    : codigo(codigo), nome(nome), evento(evento) {}

//get de vetor de medalhas
const std::vector<Medalha*>& Modalidade:: getMedalhasAssociadas() const { 
    return medalhasAssociadas; 
}

// Implementação do Método de Associação (Requisito 7)
void Modalidade::adicionarMedalha(Medalha* medalha) {
    medalhasAssociadas.push_back(medalha); //adicionar medalhas
}

//retornar atletas associados
const std::vector<Atleta*>& Modalidade::getAtletasAssociados() const { 
    return atletasAssociados; 
}

// adicionar atletas associados a modalidade
void Modalidade::adicionarAtleta(Atleta* atleta) {
    if (atleta != nullptr) {
        atletasAssociados.push_back(atleta);
    }
}

// Método de Exibição
void Modalidade::exibirDados() const {
    std::cout << "\n--- DETALHES DA MODALIDADE ---" << std::endl;
    std::cout << "Código: " << codigo << std::endl;
    std::cout << "Nome: " << nome << std::endl;
    std::cout << "Evento: " << evento << std::endl;
    std::cout << "Total de Medalhas Concedidas: " << medalhasAssociadas.size() << std::endl;
    std::cout << "Total de Atletas Associados: " << atletasAssociados.size() << std::endl; // <--- DADO NOVO
}

/* * NOTA: O Requisito 8 ("Listagem de atletas: ao informar o código da modalidade, 
 * exibir o nome e medalhas dos atletas associados a ela") será implementado 
 * na classe controladora GestaoOlimpica, pois é ela quem detém o contêiner 
 * de todos os Atletas para fazer a busca eficiente. 
 */