#include <cctype>
#include <iostream>
#include <string>

#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"

using namespace std;

int main() {
  try {
    string mensagem = RED_TEXT "Provisionar ONT ITBS OLT 8820G" RESET_TEXT;
    char saida;
    char pattern[100][100] = {
        " ===================================================== ",
        " ===     ======     =======   ======      ====      == ",
        " ==  ===  ====  ===  ====   =   ===   ==   ==   ==   = ",
        " =  =====  ==  =====  ==   ===   ==  ====  ==  ====  = ",
        " ==  ===  ====  ===  ========   ===  ====  ==  ======= ",
        " ===     ======     ========   ====  ====  ==  ======= ",
        " ==  ===  ====  ===  ======   =====  ====  ==  ===   = ",
        " =  =====  ==  =====  ====   ======  ====  ==  ====  = ",
        " ==  ===  ====  ===  ====   =======   ==   ==   ==   = ",
        " ===     ======     ====        ====      ====      == ",
        " ===================================================== "
    };

    int i;
    for (i = 0; i < 11; i++) {
        printf("%s\n", pattern[i]);
    }
    cout << mensagem << endl;
    cout << endl;


// #   ___    ___   ___    ___    _____  #
// #  / _ \  / _ \ |__ \  / _ \  / ____| #
// # | (_) || (_) |   ) || | | || |  __  #
// #  > _ <  > _ <   / / | | | || | |_ | #
// # | (_) || (_) | / /_ | |_| || |__| | #
// #  \___/  \___/ |____| \___/  \_____| #

// # ===================================================== #
// # ===     ======     =======   ======      ====      == #
// # ==  ===  ====  ===  ====   =   ===   ==   ==   ==   = #
// # =  =====  ==  =====  ==   ===   ==  ====  ==  ====  = #
// # ==  ===  ====  ===  ========   ===  ====  ==  ======= #
// # ===     ======     ========   ====  ====  ==  ======= #
// # ==  ===  ====  ===  ======   =====  ====  ==  ===   = #
// # =  =====  ==  =====  ====   ======  ====  ==  ====  = #
// # ==  ===  ====  ===  ====   =======   ==   ==   ==   = #
// # ===     ======     ====        ====      ====      == #
// # ===================================================== #

    do {
      string ponCpe, slotCpe, vlanCpe, mac, cpe;
      int slot, pon, vlan, w = 0, x = 0, y = 0, z = 0;

      // variavel booleana usada para loop de modo de operacao
      bool cpeVerifica = false;

      // loop usado para garantir selecao de pon correta
      while (y > 8 || y <= 0) {
        while (ponCpe.size() != 1 || ponCpe == "0") {
          cout << "Qual a PON que a CPE se encontra ?" << endl;
          cin >> ponCpe;
        }
        pon = stoi(ponCpe);  // stoi converte o valor de ponCpe para inteiro
        y = pon;
      }

      // loop usado para garantir a selecao de slot correto
      while (z > 64 || z <= 0) {
        string slotSalvo;
        cout << "Qual o slot na PON que voce deseja provisionar a CPE ?"
             << endl;
        cin >> slotCpe;

        for (auto& i : slotCpe) {
          if (!isalnum(i)) {
            break;
          }
          slotSalvo += i;
        }
        slot = stoi(slotSalvo);

        // stoi converte o valor de slot para inteiro
        z = slot;
        slotSalvo.clear();
      }

      // loop booleano para cpeVerifica
      while (!cpeVerifica) {
        string x;
        cout << "Ela ira operar em modo router ou bridge ?" << endl;
        cin >> x;

        // loop usando auto&, varre cada valor de x, que foi declarado no cin
        // anterior e armazena dentro da variavel local i
        for (auto& i : x) {
          // tolower converte cada valor de i para minusculo e armazena dentro
          // de cpe
          cpe += tolower(i);
        }

        if (cpe == "router") {
          string cpeCaptura;
          int cpeCapturaConvert;
          cout << "Qual modelo de CPE voce esta utilizando?" << endl;
          cout << "Digite o numero que corresponde a sua CPE" << endl;
          cout << "1---142NG/142NW/121W/WiFiber 121AC" << endl;
          cout << "2---1420g/R1" << endl;
          cin >> cpeCaptura;
          cpeCapturaConvert = stoi(cpeCaptura);
          switch (cpeCapturaConvert) {
            case 1:
              cpeVerifica = true;
              cpe = "142ng";
              break;
            case 2:
              cpeVerifica = true;
              cpe = "1420g";
              break;
            default:
              cout << "Opcao invalida" << endl;
              cpe.clear();
              cpeCaptura.clear();
              break;
          }

        } else if (cpe == "bridge") {
          cpeVerifica = true;
          cpe = "110g";
        } else {
          cout << "modo invalido" << endl;
          cpe.clear();  // limpa os dados armazenados de cpe para o proximo loop
        }
      }

      // loop usado para garantir a selecao de mac correto
      while (x != 8) {
        cout << "Digite os ultimos 8 digitos do MAC da CPE: " << endl;
        cin >> mac;
        x = mac.size();  // mac.size() retorna a quantidade de caracteres
                         // presentes dentro de mac e armazena em x
      }

      // loop usado para garantir a selecao de vlan correta
      while (w >= 4094 || w <= 0) {
        string vlanSalva;
        cout << "Qual a vlan sera utilizada ?" << endl;
        cin >> vlanCpe;
        cout << endl;
        for (auto& i : vlanCpe) {
          if (!isalnum(i)) {
            break;
          }
          vlanSalva += i;
        }

        w = vlan =
            stoi(vlanSalva);  // stoi converte o valor de vlan para inteiro
        vlanCpe.clear();
      }

      cout << "Copiar e colar os comandos abaixo (linha por linha) no terminal "
              "da OLT"
           << endl
           << endl;

      cout << "onu set 1/" << pon << "/" << slot << " meprof intelbras-" << cpe
           << " vendorid ZNTS serno fsan " << mac << endl;
      cout << "create gpon-olt-onu-config 1-1-" << pon << "-" << slot
           << "/gpononu" << endl;
      cout << "set serial-no-vendor-id = ITBS" << endl;
      cout << "commit gpon-olt-onu-config 1-1-" << pon << "-" << slot
           << "/gpononu" << endl;
      cout << endl;

      int slotcpemgr = 500 + slot;

      if (cpe == "142ng" || cpe == "1420g") {
        cout << "Copiar os valores de bridge downlink - Modo Router" << endl;
        cout << endl;
        cout << "bridge add 1-1-" << pon << "-" << slot
             << "/gpononu downlink vlan " << vlan << " tagged rg" << endl;
        cout << endl;
        cout << "Para habilitar CPE-MGR, copiar os valores abaixo" << endl;
        cout << endl;
        cout << "cpe-mgr add local 1-1-" << pon << "-" << slotcpemgr
             << "/gponport gtp 1100000000" << endl;
        cout << "bridge add 1-1-" << pon << "-" << slot
             << "/gpononu gem 514 gtp 1100000000 downlink vlan " << vlan
             << " tagged rg" << endl
             << endl;
      }

      else if (cpe == "110g") {
        cout << "Copiar os valores de bridge downlink - Modo Bridge" << endl;
        cout << endl;
        cout << "bridge add 1-1-" << pon << "-" << slot
             << "/gpononu downlink vlan " << vlan << " tagged eth 1" << endl;
        cout << endl;
      }

      cout << "Deseja provisionar novamente? S/N" << endl;
      cin >> saida;
      saida = toupper(saida);  // converte a string saida em maiusculo
      ponCpe.clear();          // limpa os valores de ponCpe
      slotCpe.clear();         // limpa os valores de slot
      cpe.clear();             // limpa os valores de cpe
      // vlan.clear();            // limpa os valores de vlan
      mac.clear();  // limpa os valores de mac
    } while (saida != 'N');
  } catch (...) {
    cout << "algum parametro nao foi reconhecido, encerrando programa..."
         << endl;
  }
}
