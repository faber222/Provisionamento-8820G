#include <cctype>
#include <iostream>
#include <string>

#define RESET_COLOR     "\033[0m"
#define BLACK_TEXT      "\033[30m"
#define RED_TEXT        "\033[31m"
#define GREEN_TEXT      "\033[32m"
#define YELLOW_TEXT     "\033[33m"
#define BLUE_TEXT       "\033[34m"
#define MAGENTA_TEXT    "\033[35m"
#define CYAN_TEXT       "\033[36m"
#define WHITE_TEXT      "\033[37m"
#define BOLD_TEXT       "\033[1m"
#define PINK_TEXT       "\033[38;5;206m" 
#define PURPLE_TEXT     "\033[38;5;141m" 
#define UNDERLINE_TEXT  "\033[4m"
#define RESET_TEXT "\033[0m"

// #   ___    ___   ___    ___    _____  #
// #  / _ \  / _ \ |__ \  / _ \  / ____| #
// # | (_) || (_) |   ) || | | || |  __  #
// #  > _ <  > _ <   / / | | | || | |_ | #
// # | (_) || (_) | / /_ | |_| || |__| | #
// #  \___/  \___/ |____| \___/  \_____| #

using namespace std;

void helloMessage() {
  char pattern[100][100] = { GREEN_TEXT
          " ===================================================== ",
          " #                                                   # ",
          " #           Copyright Intelbras 2023.               # ",
          " #           Todos os direitos reservados            # ",
          " #          ___    ___   ___    ___    _____         # ",
          " #         / _ \\  / _ \\ |__ \\  / _ \\  / ____|        # ",
          " #        | (_) || (_) |   ) || | | || |  __         # ",
          " #         > _ <  > _ <   / / | | | || | |_ |        # ",
          " #        | (_) || (_) | / /_ | |_| || |__| |        # ",
          " #         \\___/  \\___/ |____| \\___/  \\_____|        # ",
          " #                                                   # ",
          " #         Provisionar ONT/ONU na OLT 8820G          # ",
          " ===================================================== "
      RESET_TEXT };

  for (int i = 0; i < 15; i++) {
    printf("%s\n", pattern[i]);
  }
}

void printResultado(string mac, string cpe, int slot, int pon, int vlan) {
  printf("\x1b[2J");
  printf("\x1b[H");
  cout << "Copiar e colar os comandos abaixo (linha por linha) no terminal "
    "da OLT"
    << endl
    << endl;

  cout << "onu set " << CYAN_TEXT"1/" << pon << "/" << slot << RESET_TEXT " meprof intelbras-"
    PINK_TEXT << cpe << RESET_TEXT" vendorid ZNTS serno fsan " YELLOW_TEXT << mac << RESET_TEXT << endl;
  cout << "create gpon-olt-onu-config " << CYAN_TEXT "1-1-" << pon << "-" << slot
    << RESET_TEXT "/gpononu" << endl;
  cout << "set serial-no-vendor-id = ITBS" << endl;
  cout << "commit gpon-olt-onu-config " << CYAN_TEXT "1-1-" << pon << "-" << slot
    << RESET_TEXT "/gpononu" << endl;
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
}

int main() {
  try {
    printf("\x1b[2J"); 
    helloMessage();
    char saida;

    do {
      string ponCpe, slotCpe, vlanCpe, mac, cpe;
      int slot, pon, vlan, w = 0, x = 0, y = 0, z = 0;
      bool cpeVerifica = false;

      while (y > 8 || y <= 0) {
        while (ponCpe.size() != 1 || ponCpe == "0") {
          cout << "Qual a PON que a CPE se encontra ?" << endl;
          cin >> ponCpe;
        }
        pon = stoi(ponCpe);
        y = pon;
      }

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
        z = slot = stoi(slotSalvo);

        slotSalvo.clear();
      }

      while (!cpeVerifica) {
        string x;
        cout << "Ela ira operar em modo router ou bridge ?" << endl;
        cin >> x;

        for (auto& i : x) {
          cpe += tolower(i);
        }

        if (cpe == "router") {
          string cpeCaptura;
          int cpeCapturaConvert;
          cout << "===================================================== " << endl;
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
          cpe.clear();
        }
      }

      while (x != 8) {
        cout << "Digite os ultimos 8 digitos do MAC da CPE: " << endl;
        cin >> mac;
        x = mac.size();
      }

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

        w = vlan = stoi(vlanSalva);
        vlanCpe.clear();
      }
      printResultado(mac, cpe, slot, pon, vlan);

      cout << "Deseja provisionar novamente? S/N" << endl;
      cin >> saida;
      saida = toupper(saida);
      ponCpe.clear();
      slotCpe.clear();
      cpe.clear();
      mac.clear();
    } while (saida != 'N');
  }
  catch (...) {
    cout << RED_TEXT "algum parametro nao foi reconhecido, encerrando programa..." RESET_TEXT
      << endl;
  }
}
