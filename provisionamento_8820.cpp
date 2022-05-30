#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int main() {
  try {
    cout << "Provisionar ONT ITBS OLT 8820G" << endl;
    cout << endl;
    char saida;

    do {
      string ponCpe, slot, vlan, mac, cpe;
      int slotCpe, pon, w, x = 0, y = 0, z;

      // variavel booleana usada para loop de modo de operacao
      bool cpeVerifica = false;

      // loop usado para garantir selecao de pon correta
      while (y > 8 || y <= 0) {
        cout << "Qual a PON que a CPE se encontra ?" << endl;
        cin >> ponCpe;
        pon = stoi(ponCpe);  // stoi converte o valor de ponCpe para inteiro
        y = pon;
      }

      // loop usado para garantir a selecao de slot correto
      while (z > 64 || z <= 0) {
        cout << "Qual o slot na PON que voce deseja provisionar a CPE ?"
             << endl;
        cin >> slot;
        slotCpe = stoi(slot);  // stoi converte o valor de slot para inteiro
        z = slotCpe;
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
          cpeVerifica = true;
          cpe = "142ng";
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
        cout << "Qual a vlan sera utilizada ?" << endl;
        cin >> vlan;
        w = stoi(vlan);  // stoi converte o valor de vlan para inteiro
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

      int slotcpemgr = 500 + slotCpe;

      if (cpe == "142ng") {
        cout << "Bridge downlink - Modo Router" << endl;
        cout << endl;
        cout << "bridge add 1-1-" << pon << "-" << slot
             << "/gpononu downlink vlan " << vlan << " tagged rg" << endl;
        cout << endl;
        cout << "Habilitar CPE-MGR" << endl;
        cout << endl;
        cout << "cpe-mgr add local 1-1-" << pon << "-" << slotcpemgr
             << "/gponport gtp 1100000000" << endl;
        cout << "bridge add 1-1-" << pon << "-" << slot
             << "/gpononu gem 514 gtp 1100000000 downlink vlan " << vlan
             << " tagged rg" << endl
             << endl;
      }

      else if (cpe == "110g") {
        cout << "Bridge downlink - Modo Bridge" << endl;
        cout << endl;
        cout << "bridge add 1-1-" << pon << "-" << slot
             << "/gpononu downlink vlan " << vlan << " tagged eth 1" << endl;
        cout << endl;
      }

      cout << "Deseja provisionar novamente ? S/N" << endl;
      cin >> saida;
      saida = toupper(saida);  // converte a string saida em maiusculo
      ponCpe.clear();          // limpa os valores de ponCpe
      slot.clear();            // limpa os valores de slot
      cpe.clear();             // limpa os valores de cpe
    } while (saida != 'N');
  } catch (...) {
    cout << "algum parametro nao foi reconhecido, encerrando programa..."
         << endl;
  }
}
