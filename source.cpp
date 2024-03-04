#include "proyect.cpp"  // Change this line to 'source.cpp' to compile in VS Code, if its on your computer then leave it as 'proyect.cpp'

int main() {
  int n=0, opc, quantum;
  float *llegada = new float [n];
  float *rafagaCPU = new float [n];
  
  //vector<Proceso> procesoSJF(0);
  float llegadaSJF;
  float rafagaSJF;

  cout << "\nIngrese el numero de procesos (entre 1 y 5): ";
  cin >> n;

  if (n < 1 || n > 5) {
    cout << "Numero de procesos invalido. Debe ser entre 1 y 5.\n";
    return 0;
  }

  for (int i = 0; i < n; i++) {
    cout << "\nIngrese el tiempo del llegada del proceso " << i + 1 << ": ";
    cin >> llegada[i];
    cout << "Ingrese la ráfaga del proceso " << i + 1 << ": ";
    cin >> rafagaCPU[i];
  }

  do {
    cout << "\n\n================== MENU PRINCIPAL ======================" << endl;
    cout << "1) FCFS" << endl;
    cout << "2) SJF" << endl;
    cout << "3) RR" << endl;
    cout << "Ingrese un algoritmo: ";
    cin >> opc;

    switch (opc) {
      case 0:
        break;
      case 1:
        // FCFS
        fcfs(n, llegada, rafagaCPU);
        break;
      case 2:
        // SJF
        sjf(n, llegada, rafagaCPU);
        break;
      case 3:
        cout << "Ingrese el quantum: ";
        cin >> quantum;
        rr(n, llegada, rafagaCPU, quantum);
        break;
      default:
        break;
    }
  } while (opc != 0);

  return 0;
}
