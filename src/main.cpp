#include "functions.hpp"

int main() {
    int option = 0;
    int n = 0;
    std::vector<Times> tempos;

    std::cout << "1 - Criar os arquivos\n"
                << "2 - Criar as estruturas\n"
                << "3 - Sair\n"
                << "Opcao: ";
    std::cin >> option;

    switch (option) {
        case 1:
            createFiles();
            break;
        case 2:
            std::cout << "\nQuantas vezes que o programa deve rodar: ";
            std::cin >> n;
            for(int i=0; i<n; i++) {
                readFiles(&tempos);
            }
            createTimeFile(tempos, n);
            break;
        case 3:
            break;
        default:
            std::cout << "Opcao invalida!" << std::endl;
            break;
    }

    return 0;
}