#pragma once

#include "Medidor.h"
#include "MedidorAD.h"


class MedidorRN
{
public:
	MedidorRN(string nombreArchivo);
	MedidorRN();
	~MedidorRN();

	Medidor BuscarCMedidor(int idMedidor);
	bool ModificaMedidor(Medidor& medidor);
	bool AltaMedidor(Medidor& medidor);
	int IdMedidor(Medidor& medidor);
	int CantidadMedidores();
	string getNombreArchivo();
	vector<Medidor> getMedidores();
	void setNombreArchivo(string nombre);
	

private:
	MedidorAD medidorAD;
	string nombreArchivo;
};