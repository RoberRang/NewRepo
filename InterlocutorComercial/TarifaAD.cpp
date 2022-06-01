#include <fstream>
#include "TarifaAD.h"

TarifaAD::TarifaAD(string nombreArchivo)
{
	this->nombreArchivo = nombreArchivo;
}
TarifaAD::~TarifaAD()
{
}
void TarifaAD::setNombreArchivo(string nombreArchivo)
{
	this->nombreArchivo = nombreArchivo;
}
string TarifaAD::getNombreArchivo()
{
	return this->nombreArchivo;
}
/// <summary>
/// M�todo que devuelve la cantidad de Tarifas que hay en el archivo de datos.
/// </summary>
/// <returns>entero</returns>
int TarifaAD::TotalTarifaEnArchivo()
{
	ifstream archivo;
	archivo.open(this->getNombreArchivo(), ios::in);
	if (archivo.fail())
		return -1;
	int cantidad = 0;
	archivo.seekg(0, ios::end);
	int pos = archivo.tellg();
	cantidad = pos / sizeof(Tarifa);
	return cantidad;

}
/// <summary>
/// M�todo que guarda la Tarifa en el archivo de datos y devuelve verdadero cuando resulta correta la grabaci�n.
/// </summary>
/// <returns>Booleano</returns>
bool TarifaAD::GuardarEnArchivoTarifa(Tarifa& tarifa)
{
	Tarifa tarifaAD = tarifa;
	ofstream archivo;
	archivo.open(this->getNombreArchivo(), ios::binary | ios::app | ios::out);
	if (archivo.fail())
		return false;

	int posArchivo = TotalTarifaEnArchivo();
	tarifaAD.setNumPosicionArchivo(posArchivo);
	archivo.write((char*)&tarifaAD, sizeof(Tarifa));
	archivo.close();
	return true;
}
/// <summary>
/// Este m�todo permite modificar en el archivo la Tarifa enviada por parametro
/// </summary>
/// <param name="Tarifa"></param>
/// <returns></returns>
bool TarifaAD::ActualizarEnArchivoTarifa(Tarifa& tarifa)
{
	fstream archivo;
	archivo.open(this->getNombreArchivo(), ios::binary | ios::in | ios::out);
	archivo.seekg(0); //se ubica en el inicio del archivo
	if (archivo.fail())
		return false;

	archivo.seekp(tarifa.getNumPosicionArhivo() * sizeof(Tarifa), ios::cur);

	//cout << "Posicion: " << to_string(archivo.tellp()) << endl;
	archivo.write((char*)&tarifa, sizeof(Tarifa));
	archivo.close();
	return true;
}
/// <summary>
/// M�todo que devuleve un objeto tipo Tarifa  que este dentro del archivo de datos
/// </summary>
/// <param name="posicion"></param>
/// <returns>Tarifa</returns>
Tarifa TarifaAD::getTarifaArchivo(int id_tarifa)
{
	Tarifa tarifa;
	ifstream archivo;
	archivo.open(this->getNombreArchivo(), ios::in);
	if (archivo.fail())
		return tarifa;

	while (archivo.read((char*)&tarifa, sizeof(Tarifa)))
	{
		if (!archivo.eof())
			if (tarifa.getIdTarifa() == id_tarifa)
			{
				archivo.close();
				return tarifa;
			}
	}
	archivo.close();
	tarifa = Tarifa();
	return tarifa;
}

/// <summary>
/// Funci�n que devuleve todas las Tarifa  del archivo en un vector
/// </summary>
vector<Tarifa> TarifaAD::getTarifaArchivo()
{
	Tarifa tarifa;
	vector<Tarifa> tarifas;
	ifstream archivo;
	archivo.open(this->getNombreArchivo(), ios::in);
	if (archivo.fail())
		return tarifas;
	while (archivo.read((char*)&tarifa, sizeof(Tarifa)))
	{
		if (!archivo.eof())
		{
			tarifas.push_back(tarifa);
		}
	}
	return tarifas;
}