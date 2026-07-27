#ifndef PAIS_H
#define PAIS_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

// Declarações uteis para País
class Atleta;
class Medalha;
class Modalidade;

class Pais {
private:
    std::string codigo;  //código do pais, ex: BRA
    std::vector<Atleta*> atletas; //vetor de atletas do país
    std::vector<Medalha*> medalhas;  //vetor de medalhas do país

public:
    std::string nome; //nome do país que é um atributo público
    // Construtor
    Pais(const std::string& codigo, const std::string& nome);
    
    // Destrutor
    ~Pais() = default;

    // Métodos Getters (Encapsulamento)
    std::string getCodigo() const;
    const std::vector<Atleta*>& getAtletas() const;
    const std::vector<Medalha*>& getMedalhas() const;
    
    // Métodos Setters/Associação
    void adicionarAtleta(Atleta* atleta);
    void adicionarMedalha(Medalha* medalha);

    // Requisito 9: Obtém o quadro de medalhas por tipo
    // Retorna um mapa (Ouro, Prata, Bronze) para um dado ano/evento
    std::map<std::string, int> getQuadroMedalhas(int ano, const std::string& evento) const;
    
    // Calcula a pontuação geral para a classificação
    int calcularPontuacao(int ano, const std::string& evento) const;
    
    // Método de Exibição
    void exibirDados() const;
};

#endif