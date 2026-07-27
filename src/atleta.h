#ifndef ATLETA_H
#define ATLETA_H

#include "pessoa.h" // Classe base
#include "medalha.h" // Associação
#include "modalidade.h" // Associação (também herdada, mas é bom incluir)
#include <vector>
class Medalha;

class Atleta : public Pessoa {
private:
    int participacoes; //número de participações do atleta nas olimpiadas
    std::vector<Medalha*> medalhas; //vetor de medalhas do atleta

public:
    // Construtor: Deve chamar o construtor da classe base 'Pessoa'
    Atleta(const std::string& nome, const std::string& genero, int anoNascimento, Pais* pais, int participacoes);
    
    // Destrutor
    ~Atleta() override;//sobrescrito

    // Polimorfismo: Implementa o método virtual puro de Pessoa
    void exibirDados() override;

    // Getters e Setters Específicos de Atleta
    int getParticipacoes() const;
    void setParticipacoes(int num);
    const std::vector<Medalha*>& getMedalhas() const;

    // Método de Associação (Requisito 6) : Associação de atletas e medalhas
    void adicionarMedalha(Medalha* medalha);
};

#endif