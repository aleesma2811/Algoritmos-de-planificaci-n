#include "proyecto.h"

// Ordenar procesos por tiempo de llegada (para el sort)
bool compararLlegadaFCFS(const Proceso&a, const Proceso&b) {
  return a.tiempoLlegada < b.tiempoLlegada;
}


bool compararLlegadaSJF(Proceso a, Proceso b) {
    return a.tiempoLlegada < b.tiempoLlegada;
}

bool ordenarRafaga(const Proceso &a, const Proceso &b) {
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
    return sumaTiempos / n;
}

// ---------------------- ALGORITMOS -----------------------------

// FCFS
void fcfs(int n, float llegada[], float rafagaCPU[]) {
  Proceso p[n];
  for (int i = 0; i < n; i++) {
    p[i].pID = i + 1;
    p[i].tiempoLlegada = llegada[i];
    p[i].rafaga = rafagaCPU[i];
    p[i].inicioEjecucion = -1;
    p[i].tiempoFinalizacion = -1;
  }
  //ordenar los procesos por tiempo de llegada
  sort(p, p + n, compararLlegadaFCFS);

  // ------------PROMEDIO TIEMPO ESPERA-------------
  
  float tiempoActual = 0;

  for (int i = 0; i < n; i++) {
    // Actualizar tiempo de llegada (el tiempo actual se actualiza al tiempo de llegada del siguiente proceso)
    if (tiempoActual < p[i].tiempoLlegada) {
      tiempoActual = p[i].tiempoLlegada;
    }

    // Establecer tiempo de finalización de cada proceso
    p[i].inicioEjecucion = tiempoActual;
    // Se suma el tiempo actual (tiempo que lleva esperando el proceso) mas la rafaga
    p[i].tiempoFinalizacion = tiempoActual + p[i].rafaga;
    // Actualizar tiempo actual
    tiempoActual = p[i].tiempoFinalizacion;
  }

  float promedioE = tiempoPromedioEspera(n, p);
  float promedioF = tiempoPromedioFinalizacion(n, p);

  // Mostrar resultados
  cout << "\n~~~~~~~~~~~~~ FCFS ~~~~~~~~~~~~~~" << endl;
  cout << "Proceso\tRafaga\tInicio\tFinal" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].pID << "\t" 
        << p[i].rafaga << "\t"
        << p[i].inicioEjecucion << "\t" 
        << p[i].tiempoFinalizacion << endl;
    }

  cout << "Tiempo promedio de espera: " << promedioE << endl;
  cout << "Tiempo promedio de finalizacion: " << promedioF << endl;
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
    tiempoActual += primerProceso.rafaga;
    primerProceso.tiempoFinalizacion = tiempoActual;
    primerProceso.tiempoEspera = tiempoActual - primerProceso.tiempoLlegada - primerProceso.rafaga;

  tiempoEsperaTotal += primerProceso.tiempoEspera;
  tiempoFinalizadoTotal += primerProceso.tiempoFinalizacion;

  // Eliminar primer proceso
  sjf.erase(sjf.begin());

  // Mostrar resultados
  cout << "\n~~~~~~~~~~~~~ SJF ~~~~~~~~~~~~~~" << endl;
  cout << "Proceso\tRafaga\tTiempo de espera\tTiempo de finalizacion" << endl;
  cout << primerProceso.pID << "\t" << primerProceso.rafaga << "\t" << primerProceso.tiempoEspera << "\t\t\t" << primerProceso.tiempoFinalizacion << endl;
  
  while (!sjf.empty()) {
     // ordenar procesos restantes por ráfaga
    sort(sjf.begin(), sjf.end(), ordenarRafaga);
    Proceso ProcesoActual = sjf[0];

    tiempoActual += ProcesoActual.rafaga;
    ProcesoActual.tiempoFinalizacion = tiempoActual;
    ProcesoActual.tiempoEspera = tiempoActual - ProcesoActual.tiempoLlegada - ProcesoActual.rafaga;

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