#pragma once

#include "CuentaContrato.h"
#include "CuentaContratoAD.h"

#include "Validaciones.h"

class CuentaContratoRN
{
private:
	CuentaContratoAD cuentaContratoAD;
	string nombreArchivo;

public:
	CuentaContratoRN(string nombreArchivo);
	CuentaContratoRN();
	~CuentaContratoRN();
	
	CuentaContrato BuscarCuentaContrato(int id_cc);
	bool ModificarTarifaCuentaContrato(CuentaContrato& CuentaContrato);
	bool ModificarMedidorCuentaContrato(CuentaContrato& CuentaContrato);
	bool ModificarCuentaContrato(CuentaContrato& CuentaContrato);
	bool AltaCuentaContrato(CuentaContrato& CuentaContrato);
	int CantidadCuentaContrato();
	string getNombreArchivo();
	vector<CuentaContrato> getCuentaContrato();
	void setNombreArchivo(string nombre);
};