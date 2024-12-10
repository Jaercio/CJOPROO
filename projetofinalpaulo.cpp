#include <iostream>
#include <vector>
#include <string>
#include <locale>

using namespace std;

// Classe que representa uma conta banc�ria
class Conta {
private:
    int numeroConta;
    int senha;
    string nomeUsuario;
    double saldoDisponivel;
    double saldoTotal;

public:
    Conta(int numero, int senhaConta, const string& nome, double saldoDisp, double saldoTot)
        : numeroConta(numero), senha(senhaConta), nomeUsuario(nome), saldoDisponivel(saldoDisp), saldoTotal(saldoTot) {}

    int obterNumeroConta() const {
        return numeroConta;
    }

    bool validarSenha(int senhaDigitada) const {
        return senha == senhaDigitada;
    }

    string obterNomeUsuario() const {
        return nomeUsuario;
    }

    double obterSaldoDisponivel() const {
        return saldoDisponivel;
    }

    double obterSaldoTotal() const {
        return saldoTotal;
    }

    void depositar(double valor) {
        saldoTotal += valor;
    }

    void sacar(double valor) {
        if (valor <= saldoDisponivel) {
            saldoDisponivel -= valor;
            saldoTotal -= valor;
        }
    }
};

// Classe que simula um banco de dados de contas
class Banco {
private:
    vector<Conta> contas;

public:
    Banco() {
        // Inicializando com algumas contas de exemplo
        contas.push_back(Conta(12345, 1234, "Jaercio Junior", 1000.0, 1200.0));
        contas.push_back(Conta(67890, 5678, "Usuario de teste", 2000.0, 2500.0));
    }

    Conta* autenticarUsuario(int numeroConta, int senha) {
        for (auto& conta : contas) {
            if (conta.obterNumeroConta() == numeroConta && conta.validarSenha(senha)) {
                return &conta;
            }
        }
        return nullptr;
    }
};

// Classe que representa o caixa eletr�nico
class CaixaEletronico {
private:
    Banco banco;
    Conta* contaAtual;

    void mostrarMenu() {
        cout << "\nMenu Principal:\n";
        cout << "1 - Ver Saldo\n";
        cout << "2 - Sacar Dinheiro\n";
        cout << "3 - Depositar Dinheiro\n";
        cout << "4 - Sair\n";
        cout << "Escolha uma op��o: ";
    }

    void verSaldo() {
        cout << "\nSaldo dispon�vel: R$" << contaAtual->obterSaldoDisponivel() << endl;
        cout << "Saldo total: R$" << contaAtual->obterSaldoTotal() << endl;
    }

    void sacarDinheiro() {
        double valor;
        cout << "Digite o valor para sacar: ";
        cin >> valor;

        if (valor > contaAtual->obterSaldoDisponivel()) {
            cout << "Saldo insuficiente.\n";
        } else {
            contaAtual->sacar(valor);
            cout << "Saque realizado com sucesso. Pegue o dinheiro.\n";
        }
    }

    void depositarDinheiro() {
        double valor;
        cout << "Digite o valor para depositar: ";
        cin >> valor;

        if (valor <= 0) {
            cout << "Valor inv�lido.\n";
        } else {
            contaAtual->depositar(valor);
            cout << "Dep�sito realizado com sucesso.\n";
        }
    }

public:
    CaixaEletronico() : contaAtual(nullptr) {}

    void iniciar() {
        cout << "Bem-vindo ao Caixa Eletr�nico!\n";

        while (true) {
            int numeroConta, senha;
            cout << "Digite o n�mero da conta: ";
            cin >> numeroConta;
            cout << "Digite a senha: ";
            cin >> senha;

            contaAtual = banco.autenticarUsuario(numeroConta, senha);

            if (contaAtual) {
                cout << "Ol�, " << contaAtual->obterNomeUsuario() << "! Login bem-sucedido!\n";
                break;
            } else {
                cout << "N�mero da conta ou senha inv�lidos. Tente novamente.\n";
            }
        }

        while (true) {
            mostrarMenu();

            int opcao;
            cin >> opcao;

            switch (opcao) {
                case 1:
                    verSaldo();
                    break;
                case 2:
                    sacarDinheiro();
                    break;
                case 3:
                    depositarDinheiro();
                    break;
                case 4:
                    cout << "Obrigado por usar o caixa eletr�nico. At� mais!\n";
                    return;
                default:
                    cout << "Op��o inv�lida. Tente novamente.\n";
            }
        }
    }
};

// Fun��o principal
int main() {
    setlocale(LC_ALL, "");
    CaixaEletronico caixa;
    caixa.iniciar();
    return 0;
}
