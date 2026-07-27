#include "gestaoOlimpica.h"

// STL para Entrada/Saída e Manipulação de Strings
#include <iostream> // Para std::cout, std::cin
#include <fstream>  // Para manipulação de arquivos (std::ifstream, std::ofstream)
#include <sstream>  // Para std::stringstream (Essencial para leitura/escrita em formato CSV)
#include <string>   // Para manipulação de strings
#include <limits>   // Para std::numeric_limits (limpeza de buffer)

// STL para Lógica e Algoritmos
#include <algorithm> // Para std::sort (necessário para o Quadro de Medalhas)
#include <cctype>
#include <map>
#include <iomanip> // Para formatação de saída

// CONSTRUTOR: Prepara o sistema
GestaoOlimpica::GestaoOlimpica()
{
    // Carrega os dados automaticamente ao iniciar
    carregarDados();
}
//-------------------------------------------------------------------------------------------------------------------------

// DESTRUTOR: Libera a memória de todos os ponteiros criados (Polimorfismo)
GestaoOlimpica::~GestaoOlimpica()
{
    for (auto &par : paises)
        delete par.second;
    for (auto &par : pessoas)
        delete par.second; // Destrutor virtual de Pessoa é chamado
    for (auto &par : modalidades)
        delete par.second;
    for (auto &m : medalhas)
        delete m; // Libera todas as medalhas
    // Os contêineres da STL (map, vector) são automaticamente destruídos
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Exibir Menu
void GestaoOlimpica::exibirMenu() const
{
    std::cout << "\n====== SISTEMA DE GESTÃO DE EVENTOS OLÍMPICOS ======" << std::endl;
    std::cout << "1. Cadastrar país" << std::endl;
    std::cout << "2. Cadastrar atleta" << std::endl;
    std::cout << "3. Cadastrar treinador" << std::endl;
    std::cout << "4. Criar medalha" << std::endl;
    std::cout << "5. Criar modalidade" << std::endl;
    std::cout << "6. Premiar atleta com medalha" << std::endl;
    std::cout << "7. Exibir quadro de medalhas" << std::endl;
    std::cout << "8. Listar atletas de uma modalidade" << std::endl;
    std::cout << "9. Gerar relatórios e estatísticas" << std::endl;
    std::cout << "10. Salvar dados e sair" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Executar Menu (Loop Principal)
void GestaoOlimpica::executarMenu()
{
    int opcao;
    do
    {
        exibirMenu();
        if (!(std::cin >> opcao))
        {
            // Lidar com entrada não numérica
            std::cout << "Entrada inválida. Por favor, digite um número." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (opcao)
        {
        case 1:
            cadastrarPais();
            break;
        case 2:
            cadastrarAtleta();
            break;
        case 3:
            cadastrarTreinador();
            break;
        case 4:
            criarMedalha();
            break;
        case 5:
            criarModalidade();
            break;
        case 6:
            premiarAtleta();
            break;
        case 7:
            exibirQuadroMedalhas();
            break;
        case 8:
            listarAtletasPorModalidade();
            break;
        case 9:
            gerarRelatoriosEstatisticas();
            break;
        case 10:
            salvarDados();
            std::cout << "Dados salvos. Encerrando o sistema." << std::endl;
            break;
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    } while (opcao != 10);
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO : BUSCAS
Pais *GestaoOlimpica::buscarPais(const std::string &codigo) const
{
    auto it = paises.find(codigo);
    if (it != paises.end())
    {
        return it->second;
    }
    return nullptr; // Retorna nulo se não encontrar
}

Modalidade *GestaoOlimpica::buscarModalidade(const std::string &codigo) const
{
    auto it = modalidades.find(codigo);
    if (it != modalidades.end())
    {
        return it->second;
    }
    return nullptr; // se não encontrar retorna nulo
}

// Implementação necessária do buscarAtleta:
Atleta *GestaoOlimpica::buscarAtleta(const std::string &nome) const
{
    auto it = pessoas.find(nome);
    if (it != pessoas.end())
    {
        // Tenta fazer o downcast para Atleta (Polimorfismo)
        return dynamic_cast<Atleta *>(it->second);
    }
    return nullptr;
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Cadastrar País (Opção 1)
void GestaoOlimpica::cadastrarPais()
{
    std::string nome, codigo;
    std::cout << "\n--- CADASTRO DE PAÍS ---" << std::endl;

    // 1. Coleta de dados
    std::cout << "Código do País: ";
    std::cin >> codigo;

    // Converte o código para maiúsculas para padronização e busca
    std::transform(codigo.begin(), codigo.end(), codigo.begin(), ::toupper);

    // Verifica unicidade
    if (paises.count(codigo) > 0)
    {
        std::cout << "ERRO: País com código '" << codigo << "' já está cadastrado." << std::endl;
        return;
    }

    std::cout << "Nome do País: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nome);

    // 2. Criação e Armazenamento (STL: std::map)
    Pais *novoPais = new Pais(nome, codigo);
    paises[codigo] = novoPais;

    std::cout << "\n País '" << nome << "' cadastrado com sucesso!" << std::endl;
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Cadastrar Atleta (opção 2)
void GestaoOlimpica::cadastrarAtleta()
{
    std::string nome, genero, codPais, codModalidade;
    int anoNascimento, participacoes;

    std::cout << "\n--- CADASTRO DE ATLETA ---" << std::endl;

    // 1. Coleta de dados básicos
    std::cout << "Nome do Atleta: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nome);

    // Verifica se já existe uma Pessoa com esse nome
    if (pessoas.count(nome) > 0)
    {
        std::cout << "ERRO: Uma pessoa com o nome '" << nome << "' já está cadastrada." << std::endl;
        return;
    }

    std::cout << "Gênero (M/F): ";
    std::cin >> genero;
    std::cout << "Ano de Nascimento: ";
    std::cin >> anoNascimento;
    std::cout << "Número de participações nas Olimpíadas: ";
    std::cin >> participacoes;

    // 2. Associação com País (Requisito 1, 5)
    std::cout << "Código do País: ";
    std::cin >> codPais;

    Pais *pais = buscarPais(codPais);
    if (!pais)
    {
        std::cout << "ERRO: País com código '" << codPais << "' não encontrado. Cadastre-o primeiro." << std::endl;
        return;
    }

    // 3. Criação do objeto
    Atleta *novoAtleta = new Atleta(nome, genero, anoNascimento, pais, participacoes);
    pessoas[nome] = novoAtleta; // Armazena na coleção central (Polimorfismo: Pessoa*)

    // 4. Associação com Modalidades (1..*)
    std::cout << "\n--- ASSOCIAÇÃO DE MODALIDADES ---" << std::endl;
    std::cout << "Digite o código de uma modalidade ou 'fim' para terminar:" << std::endl;

    // so para de pedir a modalidade se o usuario digitar fim
    while (std::cin >> codModalidade && codModalidade != "fim")
    {
        Modalidade *modalidade = buscarModalidade(codModalidade);

        if (modalidade)
        {
            novoAtleta->setModalidade(modalidade);
            std::cout << "Modalidade " << modalidade->nome << " adicionada." << std::endl;
        }
        else
        {
            std::cout << "AVISO: Modalidade com código '" << codModalidade << "' não encontrada." << std::endl;
        }
        std::cout << "Próximo código (ou 'fim'): ";
    }

    // 5. Associação País -> Atleta
    pais->adicionarAtleta(novoAtleta);

    std::cout << "\n Atleta '" << nome << "' cadastrado e associado com sucesso ao País e Modalidade(s)." << std::endl;
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Cadastrar Treinador (Requisito 2 - opção 3)
void GestaoOlimpica::cadastrarTreinador()
{
    std::string nome, genero, codPais, codModalidade;
    int anoNascimento;

    std::cout << "\n--- CADASTRO DE TREINADOR ---" << std::endl;

    // 1. Coleta de dados básicos
    std::cout << "Nome do Treinador: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nome);

    if (pessoas.count(nome) > 0)
    {
        std::cout << "ERRO: Uma pessoa com o nome '" << nome << "' já está cadastrada." << std::endl;
        return;
    }

    std::cout << "Gênero (M/F): ";
    std::cin >> genero;
    std::cout << "Ano de Nascimento: ";
    std::cin >> anoNascimento;

    // 2. Associação com País
    std::cout << "Código do País: ";
    std::cin >> codPais;

    Pais *pais = buscarPais(codPais);
    if (!pais)
    {
        std::cout << "ERRO: País com código '" << codPais << "' não encontrado. Cadastre-o primeiro." << std::endl;
        return;
    }

    // 3. Criação do objeto
    // Usa o construtor da subclasse Treinador, que chama a base Pessoa
    Treinador *novoTreinador = new Treinador(nome, genero, anoNascimento, pais);
    pessoas[nome] = novoTreinador; // Armazena na coleção central (Polimorfismo: Pessoa*)

    // 4. Associação com Modalidades (Modalidades treinadas)
    std::cout << "\n--- ASSOCIAÇÃO DE MODALIDADES DE TREINAMENTO ---" << std::endl;
    std::cout << "Digite o código de uma modalidade ou 'fim' para terminar:" << std::endl;

    while (std::cin >> codModalidade && codModalidade != "fim")
    {
        Modalidade *modalidade = buscarModalidade(codModalidade);

        if (modalidade)
        {
            novoTreinador->setModalidade(modalidade);
            std::cout << "Modalidade " << modalidade->nome << " adicionada." << std::endl;
        }
        else
        {
            std::cout << "AVISO: Modalidade com código '" << codModalidade << "' não encontrada." << std::endl;
        }
        std::cout << "Próximo código (ou 'fim'): ";
    }

    std::cout << "\n Treinador '" << nome << "' cadastrado e associado com sucesso ao País e Modalidade(s)!" << std::endl;
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Criar medalha (Opção 4)
void GestaoOlimpica::criarMedalha()
{
    std::string codModalidade, tipoMedalha;
    int ano;

    std::cout << "\n--- CRIAÇÃO DA MEDALHA ---" << std::endl;

    // 1. Coleta da Modalidade
    std::cout << "Código da Modalidade: ";
    std::cin >> codModalidade;
    Modalidade *modalidade = buscarModalidade(codModalidade);
    if (!modalidade)
    {
        std::cout << "ERRO: Modalidade '" << codModalidade << "' não encontrada." << std::endl;
        return;
    }

    // 2. Coleta dos detalhes da Medalha
    std::cout << "Tipo da Medalha (Ouro, Prata, Bronze): ";
    std::cin >> tipoMedalha;

    std::cout << "Ano de obtenção: ";
    std::cin >> ano;

    // 3. CRIAÇÃO: Cria o objeto Medalha sem o Atleta
    Medalha *novaMedalha = new Medalha(tipoMedalha, ano, modalidade);

    // Adiciona ao vetor central de gestão
    medalhas.push_back(novaMedalha);

    // Associações Bidirecionais Iniciais (Modalidade -> Medalha)
    modalidade->adicionarMedalha(novaMedalha);

    std::cout << "\n Medalha de " << tipoMedalha << " (Ano: " << ano << ") criada e associada à Modalidade." << std::endl;
    std::cout << "Use a Opção 6 para associá-la a um Atleta." << std::endl;
}

//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Criar Modalidade (Opção 5)
void GestaoOlimpica::criarModalidade()
{
    std::string codigo, nome, evento;

    std::cout << "\n--- CRIAÇÃO DE MODALIDADE ---" << std::endl;

    // 1. Coleta de dados
    std::cout << "Código da Modalidade (ex: BAS): ";
    std::cin >> codigo;

    // Verifica unicidade
    if (modalidades.count(codigo) > 0)
    {
        std::cout << "ERRO: Modalidade com código '" << codigo << "' já existe." << std::endl;
        return;
    }

    std::cout << "Nome da Modalidade (ex: Basquetebol): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nome);

    std::cout << "Evento (Olimpíadas, Olímpiadas de Inverno ou Paralimpíadas): ";
    std::getline(std::cin, evento);

    // 2. Criação e Armazenamento (STL: std::map)
    Modalidade *novaModalidade = new Modalidade(codigo, nome, evento);
    modalidades[codigo] = novaModalidade;

    std::cout << "\n✅ Modalidade '" << nome << "' cadastrada com sucesso!" << std::endl;
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Premiar Atleta com Medalha (Opção 6)
void GestaoOlimpica::premiarAtleta()
{
    std::string nomeAtleta, tipoMedalha, codModalidade;
    int anoBusca;

    std::cout << "\n--- PREMIAÇÃO / ASSOCIAÇÃO DA MEDALHA ---" << std::endl;

    // 1. Busca da Medalha (Poderia ser um ID, mas usaremos os dados de identificação)
    std::cout << "Digite o Tipo da Medalha (Ouro, Prata, Bronze): ";
    std::cin >> tipoMedalha;

    std::cout << "Digite o Ano de obtenção: ";
    std::cin >> anoBusca;

    std::cout << "Digite o Código da Modalidade: ";
    std::cin >> codModalidade;

    // 2. Busca do Atleta
    std::cout << "Nome completo do Atleta ganhador: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nomeAtleta);

    Atleta *atleta = buscarAtleta(nomeAtleta);
    if (!atleta)
    {
        std::cout << "ERRO: Atleta '" << nomeAtleta << "' não encontrado." << std::endl;
        return;
    }

    // 3. Localizar a Medalha PENDENTE na coleção central
    Medalha *medalhaParaPremiar = nullptr;
    for (Medalha *m : medalhas)
    {
        // Verifica se a medalha é a correta E se ainda não foi premiada (atletaGanhador == nullptr)
        if (m->tipo == tipoMedalha &&
            m->anoObtencao == anoBusca &&
            m->modalidade->codigo == codModalidade &&
            m->atletaGanhador == nullptr)
        {

            medalhaParaPremiar = m;
            break;
        }
    }

    if (!medalhaParaPremiar)
    {
        std::cout << "ERRO: Medalha pendente não encontrada ou já foi premiada." << std::endl;
        return;
    }

    // 4. PREMIAR: Associa Atleta e País (Método da classe Medalha)
    Pais *paisGanhador = atleta->getPais();
    medalhaParaPremiar->premiar(atleta, paisGanhador);

    // 5. Associações Bidirecionais Finais
    atleta->adicionarMedalha(medalhaParaPremiar);       // Atleta -> Medalha
    paisGanhador->adicionarMedalha(medalhaParaPremiar); // País -> Medalha

    std::cout << "\n Medalha de " << tipoMedalha << " (Ano: " << anoBusca << ") associada com sucesso ao atleta " << atleta->nome << "!" << std::endl;
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Exibir Quadro de Medalhas (Opção 7)
void GestaoOlimpica::exibirQuadroMedalhas()
{
    int ano;
    std::string evento;

    std::cout << "\n--- QUADRO GERAL DE MEDALHAS ---" << std::endl;
    std::cout << "Informe o Ano: ";
    if (!(std::cin >> ano))
    { // garantir q o usuario digitou um número
        std::cout << "Entrada inválida." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cout << "Informe o Evento (ex: Olimpíadas, Paralimpíadas, Inverno): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, evento);

    std::vector<DadosQuadro> quadro;

    // 1. Coleta e Cálculo dos Dados
    for (const auto &par : paises)
    {
        Pais *p = par.second;

        // Usa o método da classe Pais para obter a contagem (Associação)
        std::map<std::string, int> contagem = p->getQuadroMedalhas(ano, evento);

        // Usa o método da classe Pais para obter a pontuação (Associação)
        int pontuacao = p->calcularPontuacao(ano, evento);

        // Se houver medalhas, adiciona ao quadro
        if (contagem["Ouro"] > 0 || contagem["Prata"] > 0 || contagem["Bronze"] > 0)
        {
            quadro.push_back({p->getCodigo(),
                              p->nome,
                              contagem["Ouro"],
                              contagem["Prata"],
                              contagem["Bronze"],
                              pontuacao});
        }
    }

    // 2. Ordenação (Requisito: Ordem decrescente de pontos)
    // Se a pontuação for igual, o desempate segue a regra Ouro > Prata > Bronze
    std::sort(quadro.begin(), quadro.end(), [](const DadosQuadro &a, const DadosQuadro &b)
              {
        // Primário: Pontuação
        if (a.pontuacao != b.pontuacao) {
            return a.pontuacao > b.pontuacao;
        }
        // Secundário: Ouro
        if (a.ouro != b.ouro) {
            return a.ouro > b.ouro;
        }
        // Terciário: Prata
        if (a.prata != b.prata) {
            return a.prata > b.prata;
        }
        // Quaternário: Bronze
        return a.bronze > b.bronze; });

    // 3. Exibição Formatada
    std::cout << "\n====== QUADRO DE MEDALHAS: " << evento << " (" << ano << ") ======" << std::endl;
    // O comando setw formata a largura minima do campo
    std::cout << std::setw(5) << "Rank"
              << std::setw(8) << "Código"
              << std::setw(25) << "País"
              << std::setw(7) << "Ouro"
              << std::setw(7) << "Prata"
              << std::setw(7) << "Bronze"
              << std::setw(7) << "Total"
              << std::endl;
    std::cout << std::string(66, '=') << std::endl;

    for (size_t i = 0; i < quadro.size(); ++i)
    {
        const DadosQuadro &item = quadro[i];
        int total = item.ouro + item.prata + item.bronze;
        // O comando setw formata a largura minima do campo
        std::cout << std::setw(5) << (i + 1) // Classificação
                  << std::setw(8) << item.codigo
                  << std::setw(25) << std::left << item.nome
                  << std::setw(7) << std::right << item.ouro
                  << std::setw(7) << item.prata
                  << std::setw(7) << item.bronze
                  << std::setw(7) << total
                  << std::endl;
    }
    std::cout << std::string(66, '=') << std::endl;
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: Listar Atletas por Modalidade (opção 8)
void GestaoOlimpica::listarAtletasPorModalidade()
{
    std::string codModalidade;
    std::cout << "\n--- LISTAGEM DE ATLETAS POR MODALIDADE ---" << std::endl;
    std::cout << "Digite o código da modalidade (ex: NAT): ";
    std::cin >> codModalidade;

    // 1. Busca pela Modalidade
    Modalidade *modalidade = buscarModalidade(codModalidade);

    if (!modalidade)
    {
        std::cout << "ERRO: Modalidade com código '" << codModalidade << "' não encontrada." << std::endl;
        return;
    }

    std::cout << "\nModalidade: " << modalidade->nome << " (" << modalidade->evento << ")" << std::endl;
    std::cout << "Atletas associados:" << std::endl;
    std::cout << std::setw(30) << std::left << "Nome do Atleta"
              << " | Ouro | Prata | Bronze" << std::endl;
    std::cout << std::string(55, '-') << std::endl;

    int atletasEncontrados = 0;

    // 2. Itera sobre todas as Pessoas cadastradas
    for (const auto &par : pessoas)
    {
        Pessoa *p = par.second;

        // Usa dynamic_cast para verificar se a Pessoa é um Atleta (Polimorfismo/Herança)
        Atleta *atleta = dynamic_cast<Atleta *>(p);

        if (atleta)
        {
            // 3. Verifica se o Atleta está associado à Modalidade
            bool associado = false;
            for (const auto &mod : atleta->getModalidades())
            {
                if (mod == modalidade)
                { // Compara os ponteiros da modalidade
                    associado = true;
                    break;
                }
            }

            if (associado)
            {
                atletasEncontrados++;

                // 4. Conta as medalhas do atleta
                int ouro = 0, prata = 0, bronze = 0;
                for (const auto &medalha : atleta->getMedalhas())
                {
                    // Verifica se a medalha foi ganha NESSA MODALIDADE e conta o tipo
                    if (medalha->modalidade == modalidade)
                    {
                        if (medalha->tipo == "Ouro")
                            ouro++;
                        else if (medalha->tipo == "Prata")
                            prata++;
                        else if (medalha->tipo == "Bronze")
                            bronze++;
                    }
                }

                // 5. Exibe os dados
                std::cout << std::setw(30) << std::left << atleta->nome << " | "
                          << std::setw(4) << std::right << ouro << " | "
                          << std::setw(5) << std::right << prata << " | "
                          << std::setw(6) << std::right << bronze << std::endl;
            }
        }
    }

    if (atletasEncontrados == 0)
    {
        std::cout << "Nenhum atleta associado a esta modalidade foi encontrado." << std::endl;
    }
}
//-------------------------------------------------------------------------------------------------------------------------

// IMPLEMENTAÇÃO: SALVAR DADOS (opção 10)
void GestaoOlimpica::salvarDados()
{
    std::cout << "\nSalvando dados para arquivos CSV..." << std::endl;

    // Salvando PAÍSES (paises.csv)
    std::ofstream arqPais("paises.csv");
    if (arqPais.is_open())
    {
        for (const auto &par : paises)
        {
            Pais *p = par.second;
            // Formato: CODIGO,NOME
            arqPais << p->getCodigo() << "," << p->nome << "\n";
        }
        arqPais.close();
        std::cout << "  - Países salvos." << std::endl;
    }
    else
    {
        std::cerr << "ERRO: Não foi possível abrir paises.csv para escrita." << std::endl;
    }

    // Salvando MODALIDADES (modalidades.csv)
    std::ofstream arqMod("modalidades.csv");
    if (arqMod.is_open())
    {
        for (const auto &par : modalidades)
        {
            Modalidade *m = par.second;
            // Formato: CODIGO,NOME,EVENTO
            arqMod << m->codigo << "," << m->nome << "," << m->evento << "\n";
        }
        arqMod.close();
        std::cout << "  - Modalidades salvas." << std::endl;
    }
    else
    {
        std::cerr << "ERRO: Não foi possível abrir modalidades.csv para escrita." << std::endl;
    }

    // Salvando PESSOAS (pessoas.csv)
    std::ofstream arqPess("pessoas.csv");
    if (arqPess.is_open())
    {
        for (const auto &par : pessoas)
        {
            Pessoa *p = par.second;

            // 1. Dados básicos
            arqPess << p->nome << "," << p->genero << "," << p->anoNascimento << ","
                    << p->getPais()->getCodigo(); // Associa País

            // 2. Associações de Modalidades (separadas por ponto e vírgula)
            arqPess << ",";
            for (const auto &mod : p->getModalidades())
            {
                arqPess << mod->codigo << ";";
            }

            // 3. Dados específicos de subclasses
            Atleta *atl = dynamic_cast<Atleta *>(p);
            Treinador *tre = dynamic_cast<Treinador *>(p);

            if (atl)
            {
                // Formato ATLETA: NOME,GENERO,ANONASC,PAIS_COD,MODS,PARTICIPACOES,TIPO
                arqPess << "," << atl->getParticipacoes() << "," << "ATLETA\n";
            }
            else if (tre)
            {
                // Formato TREINADOR: NOME,GENERO,ANONASC,PAIS_COD,MODS,ATLETAS_VINCULADOS,TIPO
                arqPess << ",";
                for (const auto &a : tre->getAtletas())
                {
                    arqPess << a->nome << ";"; // Associa Atletas vinculados
                }
                arqPess << "," << "TREINADOR\n";
            }
        }
        arqPess.close();
        std::cout << "  - Pessoas (Atletas/Treinadores) salvas." << std::endl;
    }
    else
    {
        std::cerr << "ERRO: Não foi possível abrir pessoas.csv para escrita." << std::endl;
    }

    // Salvando MEDALHAS (medalhas.csv)
    std::ofstream arqMed("medalhas.csv");
    if (arqMed.is_open())
    {
        for (const auto &m : medalhas)
        {
            // Formato: TIPO,ANO,MODALIDADE_COD,ATLETA_NOME,PAIS_COD
            arqMed << m->tipo << "," << m->anoObtencao << ","
                   << m->modalidade->codigo << ","
                   << m->atletaGanhador->nome << ","
                   << m->paisGanhador->getCodigo() << "\n";
        }
        arqMed.close();
        std::cout << "  - Medalhas salvas." << std::endl;
    }
    else
    {
        std::cerr << "ERRO: Não foi possível abrir medalhas.csv para escrita." << std::endl;
    }
    std::cout << "Dados salvos com sucesso." << std::endl;
}
//-------------------------------------------------------------------------------------------------------------------------

// CARREGAR DADOS:
// FUNÇÃO AUXILIAR para tokenizar strings CSV
// (Deve estar implementada no gestaoOlimpica.cpp)
std::vector<std::string> tokenizar(const std::string &linha, char delimitador)
{
    std::vector<std::string> tokens;
    std::stringstream ss(linha);
    std::string token;
    while (std::getline(ss, token, delimitador))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// IMPLEMENTAÇÃO: Carregar Dados (Reconstrói o grafo de objetos)
void GestaoOlimpica::carregarDados()
{
    std::cout << "\nCarregando dados dos arquivos CSV..." << std::endl;
    std::string linha;

    // FASE 1: ENTIDADES INDEPENDENTES (Países e Modalidades)
    // 1. CARREGAR PAÍSES
    std::ifstream arqPais("paises.csv");
    if (arqPais.is_open())
    {
        while (std::getline(arqPais, linha))
        {
            if (linha.empty())
                continue; // Ignora linhas vazias
            std::vector<std::string> tokens = tokenizar(linha, ',');
            if (tokens.size() >= 2)
            {
                Pais *p = new Pais(tokens[1], tokens[0]); // NOME, CODIGO
                paises[tokens[0]] = p;
            }
        }
        arqPais.close();
        std::cout << "  - Países carregados: " << paises.size() << std::endl;
    }

    // 2. CARREGAR MODALIDADES
    std::ifstream arqMod("modalidades.csv");
    if (arqMod.is_open())
    {
        while (std::getline(arqMod, linha))
        {
            if (linha.empty())
                continue; // Ignora linhas vazias
            std::vector<std::string> tokens = tokenizar(linha, ',');
            if (tokens.size() >= 3)
            {
                Modalidade *m = new Modalidade(tokens[0], tokens[1], tokens[2]); // CODIGO, NOME, EVENTO
                modalidades[tokens[0]] = m;
            }
        }
        arqMod.close();
        std::cout << "  - Modalidades carregadas: " << modalidades.size() << std::endl;
    }

    // FASE 2: PESSOAS E MEDALHAS (Criação de Objetos e Associações Simples
    // 3. CARREGAR PESSOAS - FASE I: Criação de Objetos e Vínculo Pessoa -> Modalidade/País
    std::ifstream arqPess("pessoas.csv");
    if (arqPess.is_open())
    {
        while (std::getline(arqPess, linha))
        {
            if (linha.empty())
                continue; // Ignora linhas vazias
            std::vector<std::string> tokens = tokenizar(linha, ',');

            // Assume um formato mínimo (NOME, GENERO, ANONASC, PAIS_COD, MODS, DADOS_ESP, TIPO)
            if (tokens.size() >= 5)
            {
                std::string nome = tokens[0];
                std::string genero = tokens[1];
                int anoNascimento = std::stoi(tokens[2]); // Já é o ano, sempre na posição 2
                std::string codPais = tokens[3];
                std::string tipo = tokens.back(); // O último token é o tipo

                Pais *pais = buscarPais(codPais);
                if (!pais)
                    continue;

                Pessoa *novaPessoa = nullptr;

                // Lógica de Atleta: Espera 7 tokens (índices 0 a 6). Participações está em tokens[5]
                if (tipo == "ATLETA" && tokens.size() == 7)
                {
                    int participacoes = std::stoi(tokens[5]);
                    novaPessoa = new Atleta(nome, genero, anoNascimento, pais, participacoes);

                    // Lógica de Treinador: Espera 6 tokens (índices 0 a 5).
                }
                else if (tipo == "TREINADOR" && tokens.size() >= 6)
                {
                    novaPessoa = new Treinador(nome, genero, anoNascimento, pais);
                }

                if (novaPessoa)
                {
                    // Associa Modalidades (tokens[4])
                    std::vector<std::string> mods = tokenizar(tokens[4], ';');
                    for (const auto &codMod : mods)
                    {
                        Modalidade *mod = buscarModalidade(codMod);
                        if (mod)
                        {
                            novaPessoa->setModalidade(mod); // 1. Pessoa -> Modalidade (Mão Simples)

                            // INSERÇÃO DA ASSOCIAÇÃO BIDIRECIONAL AQUI
                            Atleta *atl = dynamic_cast<Atleta *>(novaPessoa);
                            if (atl)
                            {
                                mod->adicionarAtleta(atl); // 2. Modalidade -> Atleta (Mão Inversa, Essencial para estatística)
                            }
                        }
                    }
                    pessoas[nome] = novaPessoa;
                    pais->adicionarAtleta(dynamic_cast<Atleta *>(novaPessoa));
                }
            }
        }
        arqPess.close();
        std::cout << "  - Pessoas (Fase I) carregadas: " << pessoas.size() << std::endl;
    }

    // 4. CARREGAR MEDALHAS: Criação e Associações Bidirecionais
    std::ifstream arqMed("medalhas.csv");
    if (arqMed.is_open())
    {
        while (std::getline(arqMed, linha))
        {
            if (linha.empty())
                continue; // Ignora linhas vazias
            std::vector<std::string> tokens = tokenizar(linha, ',');
            if (tokens.size() == 5)
            {
                std::string tipo = tokens[0];
                int ano = std::stoi(tokens[1]);
                Modalidade *mod = buscarModalidade(tokens[2]);

                Atleta *atl = dynamic_cast<Atleta *>(pessoas.count(tokens[3]) ? pessoas[tokens[3]] : nullptr);
                Pais *pais = buscarPais(tokens[4]);

                if (mod && atl && pais)
                {
                    // 1. Criação com construtor simplificado
                    Medalha *m = new Medalha(tipo, ano, mod);

                    // 2. Associação (simulando a premiação)
                    m->premiar(atl, pais);

                    medalhas.push_back(m);

                    // 3. Associações Bidirecionais Finais
                    atl->adicionarMedalha(m);
                    mod->adicionarMedalha(m);
                    pais->adicionarMedalha(m);
                }
            }
        }
        arqMed.close();
        std::cout << "  - Medalhas carregadas: " << medalhas.size() << std::endl;
    }

    // --- FASE 3: RECONSTRUÇÃO DE VÍNCULOS COMPLEXOS (Treinador -> Atleta) ---
    // 5. CARREGAR PESSOAS - FASE II: Reconstrução do Vínculo Treinador -> Atleta
    std::ifstream arqPessFase2("pessoas.csv");
    if (arqPessFase2.is_open())
    {
        while (std::getline(arqPessFase2, linha))
        {
            if (linha.empty())
                continue; // Ignora linhas vazias
            std::vector<std::string> tokens = tokenizar(linha, ',');

            if (tokens.size() >= 6 && tokens.back() == "TREINADOR")
            {
                std::string nomePessoa = tokens[0];
                Treinador *tre = dynamic_cast<Treinador *>(pessoas.count(nomePessoa) ? pessoas[nomePessoa] : nullptr);

                if (tre)
                {
                    std::string atletasString = tokens[5];
                    std::vector<std::string> atletasNomes = tokenizar(atletasString, ';');

                    for (const std::string &nomeAtleta : atletasNomes)
                    {
                        if (nomeAtleta.empty())
                            continue;

                        Atleta *atl = buscarAtleta(nomeAtleta);
                        if (atl)
                        {
                            tre->setAtleta(atl);
                        }
                    }
                }
            }
        }
        arqPessFase2.close();
        std::cout << "  - Vínculos Treinador -> Atleta reconstruídos." << std::endl;
    }

    std::cout << "✅ Carregamento de dados concluído." << std::endl;
}
//-------------------------------------------------------------------------------------------------------------------------

//-------------------------------------EXTRA-----------------------------------------------------------------//
// IMPLEMENTAÇÃO: Gerar relatórios estatísticos (Opção 8)
// chama o metodo gerarRelatoriosEstatisticas()

//struct importante para opção 2 do submenu
struct RankPais
{
    std::string nome; //nome do pais
    int ouro = 0;  //contador de medalha ouro
    int prata = 0; //contador de medalha prata
    int bronze = 0; //contador de medalha bronze
    int total = 0; // Contagem simples

    // Critério de classificação: Ouro > Prata > Bronze > Total
    bool operator>(const RankPais &other) const //sobrecarga do operador > para desempate.
    {
        if (ouro != other.ouro) // se o contador de ouro for diferente que o do outro pais retorna se é maior ou não
            return ouro > other.ouro;
        if (prata != other.prata) // se o contador de prata for diferente que o do outro pais retorna se é maior ou não
            return prata > other.prata;
        if (bronze != other.bronze) //se o contador de bronze for diferente que o do outro pais retorna se é maior ou não
            return bronze > other.bronze;
        return total > other.total; //se todos for igual retorna qual tem mais medalhas no total
    }
};

//metodo central chamado pela opção 9 do menu principal
void GestaoOlimpica::gerarRelatoriosEstatisticas()
{
    int opcao;

    do
    {
        std::cout << "\n========== SUBMENU DE RELATÓRIOS E ESTATÍSTICAS ==========" << std::endl;
        std::cout << "1. Número total de medalhas por país (todos os anos/eventos)" << std::endl;
        std::cout << "2. Classificação dos países com mais medalhas" << std::endl;
        std::cout << "3. Atletas que ganharam mais medalhas" << std::endl;
        std::cout << "4. Atletas que mais participaram das competições" << std::endl;
        std::cout << "5. Modalidades com a maior quantidade de atletas associados" << std::endl;
        std::cout << "6. Anos em que determinados países mais ganharam medalhas" << std::endl;
        std::cout << "7. Exibir relatório geral de Pessoas " << std::endl;
        std::cout << "8. Voltar ao Menu Principal" << std::endl;
        std::cout << "==========================================================" << std::endl;
        std::cout << "Escolha uma opção: ";

        if (!(std::cin >> opcao))
        {
            std::cout << "Entrada inválida. Por favor, digite um número." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (opcao)
        {
        case 1:
            estatisticaMedalhasPorPais();
            break;
        case 2:
            estatisticaClassificacaoPaises();
            break;
        case 3:
            estatisticaAtletasMaisMedalhas();
            break;
        case 4:
            estatisticaAtletasMaisParticipacoes();
            break;
        case 5:
            estatisticaModalidadesMaisAtletas();
            break;
        case 6:
            estatisticaAnosMaisMedalhasPais();
            break;
        case 7:
            relatorioGeralPessoas();
            break;
        case 8:
            std::cout << "Voltando..." << std::endl;
            break;
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    } while (opcao != 8); //vai repetir até a opção ser diferente de 8
}

// Opção 1
void GestaoOlimpica::estatisticaMedalhasPorPais()
{
    std::cout << "\n--- ESTATÍSTICA: TOTAL DE MEDALHAS POR PAÍS ---" << std::endl;

    // Estrutura para armazenar e facilitar a ordenação (País -> Contagem)
    std::vector<std::pair<std::string, int>> resultado;

    // 1. Coleta de Dados
    for (const auto &par : paises)
    {
        Pais *p = par.second;
        // O país deve ter um método para retornar a contagem total de medalhas.
        int totalMedalhas = p->getMedalhas().size(); //retorna tamanho do vetor de medalhas
 
        if (totalMedalhas > 0)
        {
            resultado.push_back({p->nome, totalMedalhas}); //adiciona elemento ao vetor de pares
        }
    }

    // 2. Ordenação
    std::sort(resultado.begin(), resultado.end(), [](const auto &a, const auto &b)
              {
        // Ordena do maior número de medalhas para o menor
        return a.second > b.second; }); //função lambda para ordenação

    // 3. Exibição
    std::cout << std::setw(30) << std::left << "País"
              << std::setw(10) << std::right << "Total" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    for (const auto &item : resultado)
    {
        std::cout << std::setw(30) << std::left << item.first
                  << std::setw(10) << std::right << item.second << std::endl;
    }
    std::cout << "\n";
}

//Opção 2
void GestaoOlimpica::estatisticaClassificacaoPaises()
{
    std::cout << "\n--- ESTATÍSTICA: CLASSIFICAÇÃO GERAL DOS PAÍSES ---" << std::endl;

    std::vector<RankPais> ranking;

    // 1. Coleta de Dados
    for (const auto &par : paises)
    {
        Pais *p = par.second; //objeto p é atribuido ao segundo elemento do map
        RankPais rp; //variavel da struct
        rp.nome = p->nome; //atribui ao nome do pais 

        // faz a contagem de medalhas por tipo
        for (Medalha *m : p->getMedalhas())
        {
            if (m->tipo == "Ouro")
                rp.ouro++;
            else if (m->tipo == "Prata")
                rp.prata++;
            else if (m->tipo == "Bronze")
                rp.bronze++;
            rp.total++;
        }

        if (rp.total > 0)
        {
            ranking.push_back(rp);
        }
    }

    // 2. Ordenação (usando o operador > da struct RankPais)
    std::sort(ranking.begin(), ranking.end(), [](const RankPais &a, const RankPais &b)
              { return a > b; }); //função lambda para ordenar com a sobrecarga do operador >

    // 3. Exibição
    std::cout << std::setw(5) << std::left << "Pos."
              << std::setw(30) << "País"
              << std::setw(10) << std::right << "Ouro"
              << std::setw(10) << "Prata"
              << std::setw(10) << "Bronze"
              << std::setw(10) << "Total" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    int pos = 1;
    for (const auto &item : ranking)
    {
        std::cout << std::setw(5) << std::left << pos++
                  << std::setw(30) << item.nome
                  << std::setw(10) << std::right << item.ouro
                  << std::setw(10) << item.prata
                  << std::setw(10) << item.bronze
                  << std::setw(10) << item.total << std::endl;
    }
    std::cout << "\n";
}

//Opção 3
void GestaoOlimpica::estatisticaAtletasMaisMedalhas()
{
    std::cout << "\n--- ESTATÍSTICA: ATLETAS COM MAIS MEDALHAS ---" << std::endl;

    std::vector<std::pair<std::string, int>> resultado; //criar um vetores de pares

    // 1. Coleta de Dados
    for (const auto &par : pessoas)
    {
        Atleta *atleta = dynamic_cast<Atleta *>(par.second); //faz o downcast

        // Verifica se é realmente um Atleta e se tem medalhas
        if (atleta && !atleta->getMedalhas().empty()){ //se mnão for atleta é um nulo
            int totalMedalhas = atleta->getMedalhas().size(); //quantidade de medalhas
            resultado.push_back({atleta->nome, totalMedalhas}); //adiciona no vetor de pares, que contem o nome do atleta e o total de medalhas
        }
    }

    // 2. Ordenação
    std::sort(resultado.begin(), resultado.end(), [](const auto &a, const auto &b){ //função lambda para ordenar pela quantidade de medalhas
                  return a.second > b.second; // Maior número de medalhas primeiro
              });

    // 3. Exibição
    std::cout << std::setw(30) << std::left << "Atleta"
              << std::setw(10) << std::right << "Medalhas" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    for (const auto &item : resultado)
    {
        std::cout << std::setw(30) << std::left << item.first
                  << std::setw(10) << std::right << item.second << std::endl;
    }
    std::cout << "\n";
}

//Opção 4
void GestaoOlimpica::estatisticaAtletasMaisParticipacoes()
{
    std::cout << "\n--- ESTATÍSTICA: ATLETAS COM MAIS PARTICIPAÇÕES ---" << std::endl;

    std::vector<std::pair<std::string, int>> resultado; //vetor de pares

    // 1. Coleta de Dados
    for (const auto &par : pessoas)
    {
        Atleta *atleta = dynamic_cast<Atleta *>(par.second); //faz um downcast

        if (atleta){ //se for atleta vai entrar
            int participacoes = atleta->getParticipacoes(); //pega o numero de participações de cada atleta
            resultado.push_back({atleta->nome, participacoes}); //adiciona o elemento com o nome do atleta e o numero de participações no vetor resultado
        }
    }

    // 2. Ordenação
    std::sort(resultado.begin(), resultado.end(), [](const auto &a, const auto &b){ //função lambda para ordenar pela quantidade de participações nas olimpiadas
                  return a.second > b.second; // Maior número de participações primeiro
              });

    // 3. Exibição
    std::cout << std::setw(30) << std::left << "Atleta"
              << std::setw(15) << std::right << "Participações" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    for (const auto &item : resultado)
    {
        std::cout << std::setw(30) << std::left << item.first
                  << std::setw(15) << std::right << item.second << std::endl;
    }
    std::cout << "\n";
}

//Opção 5
void GestaoOlimpica::estatisticaModalidadesMaisAtletas()
{
    std::cout << "\n--- ESTATÍSTICA: MODALIDADES COM MAIS ATLETAS ---" << std::endl;

    std::vector<std::pair<std::string, int>> resultado; //vetor de pares com o nome da modalidade e a quantidade de atletas associado a essa modalidade

    // 1. Coleta de Dados
    for (const auto &par : modalidades){ //vai pegar todas as modalidades cadastradas que estão no map central
        Modalidade *m = par.second;
        // Assume que Modalidade::getAtletas() retorna o vetor de Atleta*
        int totalAtletas = m->getAtletasAssociados().size(); //pega o total de atletas dessa modalidade

        if (totalAtletas > 0)
        {
            resultado.push_back({m->nome, totalAtletas}); //adiciona elemento ao vetor. Com o nome da modalidade e o total de atletas
        }
    }

    // 2. Ordenação
    std::sort(resultado.begin(), resultado.end(), [](const auto &a, const auto &b){ //ordenação com a função lambda baseada na quantidade de atletas
                  return a.second > b.second; // Maior número de atletas primeiro
              });

    // 3. Exibição
    std::cout << std::setw(30) << std::left << "Modalidade"
              << std::setw(15) << std::right << "Total Atletas" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    for (const auto &item : resultado)
    {
        std::cout << std::setw(30) << std::left << item.first
                  << std::setw(15) << std::right << item.second << std::endl;
    }
    std::cout << "\n";
}

//opção 6
void GestaoOlimpica::estatisticaAnosMaisMedalhasPais()
{
    std::string codPais;
    std::cout << "\n--- ESTATÍSTICA: ANOS DE MAIOR SUCESSO DE UM PAÍS ---" << std::endl;
    std::cout << "Digite o código do País: ";
    std::cin >> codPais;

    // colocar tudo para maiusculo
    std::transform(codPais.begin(), codPais.end(), codPais.begin(), ::toupper);

    Pais *pais = buscarPais(codPais);
    if (!pais)
    {
        std::cout << "ERRO: País com o código '" << codPais << "' não encontrado." << std::endl;
        return;
    }

    // Map: Ano -> Contagem de Medalhas
    std::map<int, int> contagemPorAno; //cria um map com o primeiro elemento representando o ano e o segundo o total de medalhas
    int maxMedalhas = 0; //contador de medalhas

    // 1. Coleta e Contagem
    for (Medalha *m : pais->getMedalhas()){ //percorre por todas as medalhas
        contagemPorAno[m->anoObtencao]++; //incrementa a quantidade de medalhas
        if (contagemPorAno[m->anoObtencao] > maxMedalhas){ //se a quantidade de medalhas do ano for maior q o maximo de medalhas, vai atualizar o maximo de medalhas
            maxMedalhas = contagemPorAno[m->anoObtencao]; //atualiza o maximo de medalhas
        }
    }

    if (contagemPorAno.empty()) //se não tiver medalhas
    {
        std::cout << "O País '" << pais->nome << "' não obteve medalhas registradas." << std::endl;
        return;
    }

    // 2. Exibição dos Anos de Maior Sucesso
    std::cout << "\nAnos em que o País '" << pais->nome << "' mais obteve medalhas (" << maxMedalhas << " medalhas):" << std::endl;

    std::cout << std::setw(10) << std::left << "Ano"
              << std::setw(10) << std::right << "Medalhas" << std::endl;
    std::cout << std::string(20, '-') << std::endl;

    for (const auto &par : contagemPorAno){ // filtra o ano recorde, já q pode ter mais de um ano com recorde de medalhas
        if (par.second == maxMedalhas)
        {
            std::cout << std::setw(10) << std::left << par.first //o ano que obteve recorde
                      << std::setw(10) << std::right << par.second << " <--" << std::endl; //a quantidade de medalhas
        }
        else
        {
            std::cout << std::setw(10) << std::left << par.first  // o ano 
                      << std::setw(10) << std::right << par.second << std::endl; //quantidade de medalha
        }
    }
    std::cout << "\n";
}

//Opção 7
void GestaoOlimpica::relatorioGeralPessoas(){
    //imprimir o relatorio geral de cada pessoa
    std::cout << "\n================ RELATÓRIO GERAL DE PESSOAS ================" << std::endl;
    std::cout << "Total de Pessoas Cadastradas: " << pessoas.size() << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    int numAtletas = 0;
    int numTreinadores = 0;

    // Itera sobre a coleção central de pessoas (STL Map)
    for (const auto &par : pessoas)
    {
        Pessoa *p = par.second;

        // Chamada Polimórfica:
        // O C++ determina qual versão de exibirDados() chamar em tempo de execução
        p->exibirDados(); // exibe o resultado baseado em qual pessoa é

        // Contagem: Usa dynamic_cast para identificar o tipo real do objeto - faz o downcasrt
        if (dynamic_cast<Atleta *>(p))
        {
            numAtletas++; //incrementa a qtd de atletas
        }
        else if (dynamic_cast<Treinador *>(p))
        {
            numTreinadores++; //incrementa a qtd de treinador
        }

        std::cout << "\n------------------------------------------------------------" << std::endl;
    }

    //imprime o resumo, que é o total de atleta e treinadores
    std::cout << "\n--- RESUMO ---" << std::endl;
    std::cout << "Total de Atletas: " << numAtletas << std::endl;
    std::cout << "Total de Treinadores: " << numTreinadores << std::endl;
    std::cout << "============================================================" << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
