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

bool verificaPorta(string ponCpe) {
  for (auto& i : ponCpe) {
    if (!isalnum(i)) {
      cerr << BOLD_TEXT RED_TEXT "O valor da pon deve ser entre um numero inteiro de 1-8!" RESET_TEXT << endl;
      return false;
    }
  }
  try {
    int y = stoi(ponCpe);
    if (y <= 8 && y > 0 && ponCpe.size() == 1) {
      return true;
    } else {
      cerr << BOLD_TEXT RED_TEXT "O valor da pon deve ser entre 1-8!" RESET_TEXT << endl;
    }
  }
  catch (const std::exception& e) {
    cerr << BOLD_TEXT RED_TEXT "O valor da pon deve ser entre um numero inteiro de 1-8!" RESET_TEXT << endl;
  }
  return false;
}

bool verificaOnu(string slotCpe) {
  for (auto& i : slotCpe) {
    if (!isalnum(i)) {
      cerr << BOLD_TEXT RED_TEXT "O valor da onu deve ser entre um numero inteiro de 1-64!" RESET_TEXT << endl;
      return false;
    }
  }
  try {
    int y = stoi(slotCpe);

    if (y < 65 && y > 0) {
      return true;
    } else {
      cerr << BOLD_TEXT RED_TEXT "O valor da pon deve ser entre 1-64!" RESET_TEXT << endl;
    }
  }
  catch (const std::exception& e) {
    cerr << BOLD_TEXT RED_TEXT "O valor da pon deve ser entre um numero inteiro de 1-64!" RESET_TEXT << endl;
  }
  return false;
}

bool verificaVlan(string vlanSalva) {
  for (auto& i : vlanSalva) {
    if (!isalnum(i)) {
      cerr << RED_TEXT "O valor da vlan deve ser entre um numero inteiro de 1-4094!" RESET_TEXT << endl;
      return false;
    }
  }
  try {
    int w = stoi(vlanSalva);

    if (w <= 4094 && w >= 1) {
      return true;
    } else {
      cerr << RED_TEXT "O valor da pon deve ser entre 1-4094!" RESET_TEXT << endl;
    }
  }
  catch (const std::exception& e) {
    cerr << RED_TEXT "O valor da vlan deve ser entre um numero inteiro de 1-4094!" RESET_TEXT << endl;
  }
  return false;
}

bool verificaMac(string mac) {
  for (auto& i : mac) {
    if (!isxdigit(i)) {
      cerr << BOLD_TEXT RED_TEXT "O valor do mac deve conter apenas caracteres hexadecimais!" RESET_TEXT << endl;
      return false;
    }
  }
  try {
    if (mac.size() == 8) {
      return true;
    }
  }
  catch (const std::exception& e) {
    cerr << BOLD_TEXT RED_TEXT "O valor do mac deve conter 8 caracteres hexadecimais!" RESET_TEXT << endl;
  }
  return false;
}

bool verificaEscolha(string escolha) {
  for (auto& i : escolha) {
    if (!isalnum(i)) {
      cerr << BOLD_TEXT RED_TEXT "O valor deve ser entre um numero inteiro de 1-2!" RESET_TEXT << endl;
      return false;
    }
  }
  try {
    int y = stoi(escolha);
    if (y <= 2 && y >= 1 && escolha.size() == 1) {
      return true;
    } else {
      cerr << BOLD_TEXT RED_TEXT "O valor deve ser entre um numero inteiro de 1-2!" RESET_TEXT << endl;
    }
  }
  catch (const std::exception& e) {
    cerr << BOLD_TEXT RED_TEXT "O valor deve ser entre um numero inteiro de 1-2!" RESET_TEXT << endl;
  }
  return false;
}

bool verificaMacVendor(string macVendor) {
  for (auto& i : macVendor) {
    if (!isalpha(i)) {
      cerr << BOLD_TEXT RED_TEXT "O valor do vendor deve conter apenas caracteres alfabeticos!" RESET_TEXT << endl;
      return false;
    }
  }
  try {
    if (macVendor.size() == 4) {
      return true;
    } else {
      cerr << BOLD_TEXT RED_TEXT "O valor do vendor deve ser conter 4 caracteres" RESET_TEXT << endl;
    }
  }
  catch (const std::exception& e) {
    cerr << BOLD_TEXT RED_TEXT "O valor do vendor deve ser conter 4 caracteres" RESET_TEXT << endl;
  }
  return false;
}

void helloMessage() {
  char pattern[100][100] = { BOLD_TEXT GREEN_TEXT
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

void printResultado(string mac, string cpe, string macVendor, int slot, int pon, int vlan) {
  printf("\x1b[2J");
  printf("\x1b[H");
  cout << BOLD_TEXT PURPLE_TEXT "Copiar e colar os comandos abaixo (linha por linha) no terminal "
    "da OLT" RESET_TEXT << endl << endl;

  cout << "onu set " << BOLD_TEXT CYAN_TEXT"1/" << pon << "/" << slot << RESET_TEXT " meprof intelbras-"
    BOLD_TEXT PINK_TEXT << cpe << RESET_TEXT" vendorid ZNTS serno fsan " BOLD_TEXT CYAN_TEXT << mac << RESET_TEXT << endl;
  cout << "create gpon-olt-onu-config " << BOLD_TEXT CYAN_TEXT "1-1-" << pon << "-" << slot
    << RESET_TEXT "/gpononu" << endl;
  cout << "set serial-no-vendor-id = " BOLD_TEXT CYAN_TEXT << macVendor << RESET_TEXT << endl;
  cout << "commit gpon-olt-onu-config " << BOLD_TEXT CYAN_TEXT "1-1-" << pon << "-" << slot
    << RESET_TEXT "/gpononu" << endl;
  cout << endl;

  int slotcpemgr = 500 + slot;

  if (cpe == "110g") {
    cout << BOLD_TEXT PURPLE_TEXT "Copiar os valores de bridge downlink - Modo Bridge" RESET_TEXT << endl;
    cout << endl;
    cout << "bridge add" << BOLD_TEXT CYAN_TEXT" 1-1-" << pon << "-" << slot
      << RESET_TEXT "/gpononu downlink vlan " BOLD_TEXT CYAN_TEXT << vlan << RESET_TEXT" tagged eth 1" << endl;
    cout << endl;
  } else {
    cout << BOLD_TEXT PURPLE_TEXT "Copiar os valores de bridge downlink - Modo Router" RESET_TEXT << endl;
    cout << endl;
    cout << "bridge add " << BOLD_TEXT CYAN_TEXT "1-1-" << pon << "-" << slot
      << RESET_TEXT "/gpononu downlink vlan " BOLD_TEXT CYAN_TEXT << vlan << RESET_TEXT" tagged rg" << endl;
    cout << endl;
    cout << BOLD_TEXT PURPLE_TEXT "Para habilitar CPE-MGR, copiar os valores abaixo" RESET_TEXT << endl;
    cout << endl;
    cout << "cpe-mgr add local " << BOLD_TEXT CYAN_TEXT "1-1-" << pon << "-" << slotcpemgr
      << RESET_TEXT "/gponport gtp 1100000000" << endl;
    cout << "bridge add " << BOLD_TEXT CYAN_TEXT"1-1-" << pon << "-" << slot
      << RESET_TEXT "/gpononu gem 514 gtp 1100000000 downlink vlan " BOLD_TEXT CYAN_TEXT << vlan
      << RESET_TEXT" tagged rg" << endl
      << endl;
  }
}

int main() {
  try {
    printf("\x1b[2J");
    helloMessage();
    char saida;

    do {
      string ponCpe, slotCpe, vlanCpe, mac, cpe;
      string vendor, macVendor, cpeVerifica, cpeWifi;
      int slot, pon, vlan;

      do {
        cout << YELLOW_TEXT "Qual a PON que a CPE se encontra ?" RESET_TEXT << endl;
        cin >> ponCpe;
      } while (!verificaPorta(ponCpe));

      pon = stoi(ponCpe);

      do {
        cout << YELLOW_TEXT "Qual o slot na PON que voce deseja provisionar a CPE ?" RESET_TEXT << endl;
        cin >> slotCpe;
      } while (!verificaOnu(slotCpe));

      slot = stoi(slotCpe);

      do {
        cout << GREEN_TEXT " ===================================================== " RESET_TEXT << endl;
        cout << GREEN_TEXT " # A ONT/ONU é Intelbras ou de Terceiros?            # " RESET_TEXT << endl;
        cout << GREEN_TEXT " # Digite o numero que corresponde a sua CPE!        # " RESET_TEXT << endl;
        cout << GREEN_TEXT " # 1---Intelbras                                     # " RESET_TEXT << endl;
        cout << GREEN_TEXT " # 2---Terceiros                                     # " RESET_TEXT << endl;
        cout << GREEN_TEXT " ===================================================== " RESET_TEXT << endl;
        cin >> vendor;
      } while (!verificaEscolha(vendor));

      switch (stoi(vendor)) {
        case 1:
          macVendor = "ITBS";
          break;
        case 2:
          do {
            cout << GREEN_TEXT " ===================================================== " RESET_TEXT << endl;
            cout << GREEN_TEXT " # Qual o vendor/sn/modelo dessa ONT/ONU?            # " RESET_TEXT << endl;
            cout << GREEN_TEXT " # Exemplo: ZNTS/HWTC/FHTT...etc!                    # " RESET_TEXT << endl;
            cout << GREEN_TEXT " ===================================================== " RESET_TEXT << endl;
            cin >> macVendor;
          } while (!verificaMacVendor(macVendor));
          for (char& c : macVendor) {
            c = std::toupper(c);
          }
          break;

        default:
          cout << BOLD_TEXT RED_TEXT "Parametro de Vendor invalido, encerrando programa..." RESET_TEXT << endl;
          return 0;
          break;
      }

      do {
        cout << GREEN_TEXT " ===================================================== " RESET_TEXT << endl;
        cout << GREEN_TEXT " # Ela ira operar em modo router ou bridge?          # " RESET_TEXT << endl;
        cout << GREEN_TEXT " # Digite o numero que corresponde a sua CPE!        # " RESET_TEXT << endl;
        cout << GREEN_TEXT " # 1---Router                                        # " RESET_TEXT << endl;
        cout << GREEN_TEXT " # 2---Bridge                                        # " RESET_TEXT << endl;
        cout << GREEN_TEXT " ===================================================== " RESET_TEXT << endl;
        cin >> cpeVerifica;
      } while (!verificaEscolha(cpeVerifica));

      switch (stoi(cpeVerifica)) {
        case 1:
          do {
            cout << GREEN_TEXT " ===================================================== " RESET_TEXT << endl;
            cout << GREEN_TEXT " # A CPE tem rede wifi?                              # " RESET_TEXT << endl;
            cout << GREEN_TEXT " # Digite o numero que corresponde a sua CPE         # " RESET_TEXT << endl;
            cout << GREEN_TEXT " # 1---Sim                                           # " RESET_TEXT << endl;
            cout << GREEN_TEXT " # 2---Nao                                           # " RESET_TEXT << endl;
            cout << GREEN_TEXT " ===================================================== " RESET_TEXT << endl;
            cin >> cpeWifi;
          } while (!verificaEscolha(cpeWifi));

          switch (stoi(cpeWifi)) {
            case 1:
              cpe = "142ng";
              break;
            case 2:
              cpe = "1420g";
              break;
            default:
              cout << BOLD_TEXT RED_TEXT "Parametro de Wifi invalido, encerrando programa..." RESET_TEXT << endl;
              return 0;
              break;
          }
          break;
        case 2:
          cpe = "110g";
          break;
        default:
          cout << BOLD_TEXT RED_TEXT "Parametro do modo de operacao invalido, encerrando programa..." RESET_TEXT << endl;
          return 0;
          break;
      }

      do {
        cout << YELLOW_TEXT "Digite os ultimos 8 digitos do MAC da CPE: " RESET_TEXT << endl;
        cin >> mac;
      } while (!verificaMac(mac));

      do {
        cout << YELLOW_TEXT "Qual a vlan sera utilizada ?" RESET_TEXT << endl;
        cin >> vlanCpe;
      } while (!verificaVlan(vlanCpe));

      vlan = stoi(vlanCpe);

      printResultado(mac, cpe, macVendor, slot, pon, vlan);

      cout << YELLOW_TEXT "Deseja provisionar novamente? S/N" RESET_TEXT << endl;
      cin >> saida;
      saida = toupper(saida);
      ponCpe.clear();
      slotCpe.clear();
      cpe.clear();
      mac.clear();
    } while (saida != 'N');
  }
  catch (...) {
    cout << BOLD_TEXT RED_TEXT "algum parametro nao foi reconhecido, encerrando programa..." RESET_TEXT
      << endl;
  }
}
