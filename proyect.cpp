#include "proyecto.h"

// Ordenar procesos por tiempo de llegada (para el sort)
bool compararLlegadaFCFS(const Proceso&a, const Proceso&b) {
  return a.tiempoLlegada < b.tiempoLlegada;
}

// Comparar tiempo de llegada para SJF
bool compararLlegadaSJF(Proceso a, Proceso b) {
    return a.tiempoLlegada < b.tiempoLlegada;
}

//  Comparar ráfaga de CPU para SJF
bool comparaRafaga(Proceso a, Proceso b) {
    return a.rafaga < b.rafaga;
}

// Promedio de tiempo de finalización
float tiempoPromedioFinalizacion(int n, Proceso p[]) {
    float sumaTiempos = 0;
    for (int i = 0; i < n; i++) {
        sumaTiempos += p[i].tiempoFinalizacion;
    }
    return sumaTiempos / n;
}

// Promedio de tiempo de espera
float tiempoPromedioEspera(int n, Proceso p[]) {
  float sumaTiempos = 0;
  for (int i = 0; i < n; i++) {
    sumaTiempos += p[i].tiempoEspera;
  }
  return sumaTiempos/n;
}


// ----------------- ROUND ROBIN -----------------
// Encontrar el tiempo de espera de cada proceso
void RRfindWaitingTime(const Proceso a[], int n, float burstTime[], int waitingTime[], int quantum) {
  int* rem_bt = new int[n];

  // Copiar ráfagas de CPU
  for (int i = 0; i < n; i++) {
    rem_bt[i] = burstTime[i];
  }

  // Tiempo actual
  int t = 0;

  // Mientras haya procesos
  while (1) {
    bool done = true;
    for (int i = 0; i < n; i++) {

      // Si el proceso no ha terminado
      if (rem_bt[i] > 0) {
        done = false;

        // Si la ráfaga es mayor al quantum
        if (rem_bt[i] > quantum) {
          t += quantum; // Aumentar el tiempo actual al quantum
          rem_bt[i] -= quantum;
        } else { // Si la ráfaga es menor o igual al quantum
          t = t + rem_bt[i]; // Aumentar el tiempo actual al tiempo de ráfaga
          waitingTime[i] = t - burstTime[i];  // Calcular el tiempo de espera
          rem_bt[i] = 0; // La ráfaga es 0
        }
      }
    }
    if (done == true) {
      break;
    }
  }
}

// Encontrar el tiempo de retorno de cada proceso
void RRfindTurnAroundTime(const Proceso a[], int n, float burstTime[], int waitingTime[], int turnAroundTime[]) {
  for (int i = 0; i < n; i++) {
    turnAroundTime[i] = burstTime[i] + waitingTime[i];
  }
}



// ---------------------- ALGORITMOS -----------------------------


// FCFS
void fcfs(int n, float llegada[], float rafagaCPU[]) {
  Proceso *p = new Proceso[n];
  for (int i = 0; i < n; i++) {
    p[i].pID = i + 1;
    p[i].tiempoLlegada = llegada[i];
    p[i].rafaga = rafagaCPU[i];
    p[i].inicioEjecucion = -1;
    p[i].tiempoFinalizacion = -1;
  }
  //ordenar los procesos por tiempo de llegada
  sort(p, p + n, compararLlegadaFCFS);
  
  // ------------EJECUCIÓN DE LOS PROCESOS-------------
  for (int i = 0; i < n; i++) {
    if(i == 0){
      p[i].inicioEjecucion = p[i].tiempoLlegada;
      p[i].tiempoEspera = p[i].inicioEjecucion - p[i].tiempoLlegada;
      p[i].tiempoFinalizacion = p[i].inicioEjecucion + p[i].rafaga;
    } else {    
      p[i].inicioEjecucion = p[i - 1].tiempoFinalizacion;
      p[i].tiempoEspera = p[i].inicioEjecucion - p[i].tiempoLlegada;
      p[i].tiempoFinalizacion = p[i].inicioEjecucion + p[i].rafaga;
    }
  }
  float promedioE = tiempoPromedioEspera(n, p);
  float promedioF = tiempoPromedioFinalizacion(n, p);
  
  // Mostrar resultados
  cout << "\n~~~~~~~~~~~~~ FCFS ~~~~~~~~~~~~~~" << endl;
  cout << "Proceso\tRafaga\tInicio\tTiempo Espera\tFinal" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].pID << "\t" 
        << p[i].rafaga << "\t"
        << p[i].inicioEjecucion << "\t" 
        << p[i].tiempoEspera << "\t" 
        << p[i].tiempoFinalizacion << endl;
    }

  cout << "Tiempo promedio de espera: " << promedioE << endl;
  cout << "Tiempo promedio de finalizacion: " << promedioF << endl;
  delete []p;
}


//SJF
void sjf(int n, float llegada[], float rafagaCPU[]) {
  // Insertar datos al vector SJF
  vector<Proceso> sjf(n);

  for (int i = 0; i < n; i++) {
    sjf[i].pID = i + 1;
    sjf[i].tiempoLlegada = llegada[i];
    sjf[i].rafaga = rafagaCPU[i];
  }
  // Ordenar por tiempo de llegada
  sort(sjf.begin(), sjf.end(), compararLlegadaSJF);

  int tiempoEsperaTotal = 0;
  int tiempoFinalizadoTotal = 0;
  int tiempoActual = 0;

  // Ejecutar el primer proceso que llega
  Proceso primerProceso = sjf[0];
  //tiempoActual = primerProceso.rafaga;
  tiempoActual = primerProceso.tiempoLlegada + primerProceso.rafaga;
  primerProceso.tiempoFinalizacion = tiempoActual;
  //primerProceso.tiempoEspera = tiempoActual - primerProceso.tiempoLlegada - primerProceso.rafaga;
  primerProceso.tiempoEspera = primerProceso.tiempoLlegada;

  tiempoEsperaTotal += primerProceso.tiempoEspera;
  tiempoFinalizadoTotal += primerProceso.tiempoFinalizacion;

  // Mostrar resultados
  cout << "\n~~~~~~~~~~~~~ SJF ~~~~~~~~~~~~~~" << endl;
  cout << "Proceso\tRafaga\tTiempo de espera\tTiempo de finalizacion" << endl;
  cout << primerProceso.pID << "\t" << primerProceso.rafaga << "\t" << primerProceso.tiempoEspera << "\t\t\t" << primerProceso.tiempoFinalizacion << endl;
  // Eliminar primer proceso
  sjf.erase(sjf.begin());

   // ordenar procesos restantes por ráfaga
  sort(sjf.begin(), sjf.end(), comparaRafaga);
  
  while (!sjf.empty()) {
    Proceso ProcesoActual = sjf[0];

    tiempoActual += ProcesoActual.rafaga;
    ProcesoActual.tiempoFinalizacion = tiempoActual;
    //ProcesoActual.tiempoEspera = tiempoActual - ProcesoActual.tiempoLlegada - ProcesoActual.rafaga;
    ProcesoActual.tiempoEspera = tiempoActual - ProcesoActual.tiempoLlegada;

    tiempoEsperaTotal += ProcesoActual.tiempoEspera;
    tiempoFinalizadoTotal += ProcesoActual.tiempoFinalizacion;

    cout << ProcesoActual.pID << "\t" << ProcesoActual.rafaga << "\t" << ProcesoActual.tiempoEspera << "\t\t\t" << ProcesoActual.tiempoFinalizacion << "\n";
    sjf.erase(sjf.begin());
  }
  // Calcular promedios
  double promedioTiempoEspera = (double)tiempoEsperaTotal / n;
  double promedioTiempoFinalizado = (double)tiempoFinalizadoTotal / n;

  // Mostrar promedios
  cout << "Tiempo de espera promedio: " << promedioTiempoEspera << "\n";
  cout << "Tiempo de finalizacion promedio: " << promedioTiempoFinalizado << "\n";
}

// Round Robin (RR)
void rr(int n, float llegada[], float rafagaCPU[], int quantum) {
  vector<Proceso> rr(n);
  
  for (int i = 0; i < n; i++) {
    rr[i].pID = i + 1;
    rr[i].tiempoLlegada = llegada[i];
    rr[i].rafaga = rafagaCPU[i];
  }

  int* waitingTime = new int[n];
  int* turnAroundTime = new int[n];
  int total_wt = 0, total_tat = 0;

  // Encontrar el tiempo de espera y el tiempo de retorno
  RRfindWaitingTime(rr.data(), n, rafagaCPU, waitingTime, quantum);
  RRfindTurnAroundTime(rr.data(), n, rafagaCPU, waitingTime, turnAroundTime);

  // Mostrar resultados
  cout << "\nProceso\tRafaga\tTiempo de espera\tTiempo de retorno" << endl;
  for (int i = 0; i < n; i++) {
    total_wt = total_wt + waitingTime[i];
    total_tat = total_tat + turnAroundTime[i];
    cout << i + 1 << "\t" << rafagaCPU[i] << "\t" << waitingTime[i] << "\t\t\t" << turnAroundTime[i] << endl;
  }
  cout << "Tiempo promedio de espera: " << (float)total_wt / (float)n << endl;

  // Liberar memoria
  delete[] waitingTime;
  delete[] turnAroundTime;
  cout << "Tiempo promedio de retorno: " << (float)total_tat / (float)n << endl;
}