#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <vector>
#include <iostream>

// Classes uteis para Pessoa:
class Pais;
class Modalidade;

class Pessoa {
private:
    //ATRIBUTOS PRIVADOS
    Pais* pais; 
    std::vector<Modalidade*> modalidades; //vetor de modalidades da pessoa

public:
    // ATRIBUTOS PÚBLICOS
    std::string nome;
    std::string genero;
    int anoNascimento;

    //MÉTODOS
    // Construtor
    Pessoa(const std::string& nome, const std::string& genero, int anoNascimento, Pais* pais);
    
    // Destrutor virtual
    virtual ~Pessoa();
    
    // Polimorfismo: Método virtual puro
    virtual void exibirDados() = 0;

    // Métodos Getters
    Pais* getPais() const;
    const std::vector<Modalidade*>& getModalidades() const;
    
    // Métodos Setters
    void setPais(Pais* p);
    void setModalidade(Modalidade* m);
};

#endif