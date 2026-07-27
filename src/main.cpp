#include "gestaoOlimpica.h"

int main() {
    // 1. Instancia o objeto gestor.
    // O construtor chama automaticamente carregarDados().
    GestaoOlimpica gestor; 

    // 2. Inicia o loop do menu e a interação.
    gestor.executarMenu(); 

    // 3. O destrutor da 'gestor' é chamado automaticamente ao sair,
    // liberando toda a memória alocada.
    
    return 0;
}