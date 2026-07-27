#ifndef MEDALHA_H
#define MEDALHA_H

#include <string>
#include <iostream>

// Forward declarations para as associações
class Modalidade; 
class Atleta;
class Pais;

class Medalha {
public:
    std::string tipo;      // Requisito 3: "Ouro", "Prata" ou "Bronze"
    int anoObtencao;       // Ano de obtenção
    
    // Associações (Requisitos 6, 7 e 9)
    Modalidade* modalidade; // A qual modalidade está vinculada (1..1)
    Atleta* atletaGanhador = nullptr;  // Qual atleta a ganhou (1..1)
    Pais* paisGanhador= nullptr;     // Qual país a ganhou (implícito via Atleta, mas útil para consulta)



    // Construtor
    Medalha(const std::string& tipo, int ano, Modalidade* mod);
    
    // Destrutor
    ~Medalha() = default;

    //atribuir atleta e pais a medalha
    void premiar(Atleta* atl, Pais* pais);

    // Método de Exibição
    void exibirDados() const;
};

#endif // MEDALHA_H