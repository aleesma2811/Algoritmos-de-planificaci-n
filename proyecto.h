#pragma once
#include <iostream>
#include <algorithm> // Para sort()
#include <vector>
using namespace std;

struct Proceso {
  // FCFS
  int pID; // ID del proceso
  float tiempoLlegada; 
  float rafaga; 
  float inicioEjecucion; // Tiempo de inicio del proceso
  float tiempoFinalizacion; // Tiempo de finalización del proceso
  float quantum;

  // SJF
  float tiempoEspera;
};

bool compararLlegadaFCFS(const Proceso&a, const Proceso&b);
bool compararLlegadaSJF(Proceso a, Proceso b);
float tiempoPromedioFinalizacion(int n, Proceso p[]);

// ---------------- Algoritmos ----------------
void fcfs(int n, float llegada[], float rafagaCPU[]);
void sjf(int n, float llegada[], float rafagaCPU[]);
void rr(int n, float llegada[], float rafagaCPU[], int quantum);
