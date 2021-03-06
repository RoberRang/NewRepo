#include "InterfaceSalida.h"
#include "CuentaContratoV.h"
#include "MedidorV.h"
#include "InterlocutorComercialV.h"
#include "MedidorV.h"
#include "DocumentoV.h"
#include "TarifaV.h"
#include "CuentaContratoV.h"



InterfaceSalida::InterfaceSalida()
{}

InterfaceSalida::~InterfaceSalida()
{}

void InterfaceSalida::setTextoSalida(string texto)
{
	this->textoSalida = texto;
}

string InterfaceSalida::getTextoSalida()
{
	return this->textoSalida;
}

void InterfaceSalida::setTextosSalida(vector<string> textos)
{
	this->textosSalida = textos;
}

vector<string> InterfaceSalida::getTestosSalida()
{
	return this->textosSalida;
}

//Funcion de promedio
float CalRecaudacion(int dni, int opcion, int anioConsulta, bool pago);
float CalcularPromedioPorTarifa(int tar, int anio);

/// <summary>
/// M�todo que graba el texto que estan en el vecotr dentro de archivo indicado en el parametro nombreArchivo.
/// </summary>
/// <returns>Booleano</returns>
bool InterfaceSalida::GrabarTextosSalida(vector<string> textos, string nombreArchivo)
{
	ofstream archivo;
	archivo.open(nombreArchivo, ios::app | ios::out);

	if (archivo.fail())
		return false;

	for (auto& texto : textos)
		archivo << texto + "\n";

	archivo.close();
	return true;
}

// Lee el archivo masivo CSV para generar un .DAT de Interlocutores.
bool InterfaceSalida::LeeTextosEntradaInterlocutor(string nombreArchivo)
{
	ifstream archivo;
	archivo.open(nombreArchivo, ios::in);

	if (archivo.fail())
		return false;
	string str = "";
	char pattern = ';';
	int posInit = 0;
	vector<string> results;
	while (getline(archivo, str))
	{
		InterlocutorComercial interlocutorArch;
		string splitted;
		Direccion direccion;
		Fecha fecha;
		int indice = 0;
		int posFound = 0;

		while (posFound >= 0)
		{

			int dia, mes, anio;
			posFound = str.find(pattern, posInit);
			splitted = str.substr(posInit, posFound - posInit);
			switch (indice)
			{
			case 0:
				interlocutorArch.setId_ic(stoi(splitted));
				break;
			case 1:
				interlocutorArch.setNombre(splitted);
				break;
			case 2:
				interlocutorArch.setApellido(splitted);
				// medArch.setEstado(splitted == "true" ? true : false);
				break;
			case 3:
				interlocutorArch.setDni(stoi(splitted));
				break;
			case 4:
				interlocutorArch.setEmail(splitted);
				break;
			case 5:
			{
				anio = stoi(splitted);
				fecha.setAnio(anio);
				break;
			}
			case 6:
			{
				mes = stoi(splitted);
				fecha.setMes(stoi(splitted));
				break;
			}
			case 7:
			{
				dia = stoi(splitted);
				fecha.setDia(dia);
				interlocutorArch.setFechaIngresoId(fecha);
				break;
			}
			case 8:
				direccion.setCalle(splitted);
				break;
			case 9:
				direccion.setNumero(stoi(splitted));
				break;
			case 10:
				direccion.setCodPostal(splitted);
				break;
			case 11:
				direccion.setLocalidad(splitted);
				break;
			case 12:
			{
				direccion.setProvincia(splitted);
				interlocutorArch.setDireccionId(direccion);
				break;
			}
			case 13:
				interlocutorArch.setNumPosicionArchivo(stoi(splitted));
				break;
			case 14:
				interlocutorArch.setActivo(splitted == "true" ? true : false);
				break;
			default:
				break;
			}
			indice++;
			posInit = posFound + 1;
		}
		InterlocutorComercialAD interlocutorAD(NOMBRE_ARCH_IC);
		interlocutorAD.GuardarEnArchivoInterlocutor(interlocutorArch);
	}
	archivo.close();
	return true;
}

// Lee el archivo masivo CSV para generar un .DAT de Medidores
bool InterfaceSalida::LeeTextosEntrada(string nombreArchivo)
{
	ifstream archivo;
	archivo.open(nombreArchivo, ios::in);

	if (archivo.fail())
		return false;
	string str = "";
	char pattern = ';';
	int posInit = 0;
	vector<string> results;
	while (getline(archivo, str))
	{
		Medidor medArch;
		string splitted;
		int indice = 0;
		int posFound = 0;
		while (posFound >= 0)
		{
			posFound = str.find(pattern, posInit);
			splitted = str.substr(posInit, posFound - posInit);
			switch (indice)
			{
			case 0:
				medArch.setId(stoi(splitted));
				break;
			case 1:
				medArch.setIdCuentaContrato(stoi(splitted));
				break;
			case 2:
				medArch.setEstado(splitted == "true" ? true : false);
				break;
			case 3:
				medArch.setLectura(stof(splitted));
				break;
			case 4:
				medArch.setNumPosicionArchivo(stoi(splitted));
				break;
			default:
				break;
			}
			indice++;
			posInit = posFound + 1;
		}
		MedidorAD medAD("medidores.dat");
		medAD.GuardarEnArchivoMedidor(medArch);
	}

	archivo.close();
	return true;
}

void InterfaceSalida::MostrarTextosSalida(vector<string> textos, string tituloTexo)
{
	cout << this->separador << endl;
	cout << tituloTexo << endl;
	cout << this->separador << endl;
	for (auto& texto : textos)
		cout << texto << endl;
	cout << this->separador << endl;
}

void InterfaceSalida::MenuPrincipal()
{
	int opcion = 0;
	do
	{
		cout << this->separador << endl;
		cout << "\t\tCONSULTAS DE GESTION ENERGETICA" << endl;
		cout << this->separador << endl;
		cout << "|\t1. Para menu Interlocutor Comercial" << endl;
		cout << "|\t2. Para menu Cuenta Contrato" << endl;
		cout << "|\t3. Para menu Medidor" << endl;
		cout << "|\t4. Para menu Tarifa" << endl;
		cout << "|\t5. Para menu Facturacion" << endl;
		cout << "|\t6. Para menu Consultas" << endl;
		cout << "|\t7. Para menu Exportacion CVS" << endl;
		cout << "|\t0. Para Salir" << endl;
		cout << this->separador << endl;
		opcion = Validaciones::DatoObligarorioNum("Opcion");

		if (opcion == 0)
		{
			char salir;
			cout << "Desea salir completamente del sistema " << endl;
			salir = Validaciones::DatoObligarorioChar(" S para salir");
			if (toupper(salir) == 'S')
			{
				system("cls||clear");
				cout << "GRACIAS POR USAR EL SISTEMA DE GESTION ENERGETICA!!!" << endl;
				Validaciones::SystemPause();
				exit(1);
			}
		}

		system("cls||clear");
		switch (opcion)
		{
		case 1:
		{
			system("cls||clear");
			InterlocutorComercialV interVista(NOMBRE_ARCH_IC);
			interVista.MenuInterlocutorComecial();
			break;
		}
		case 2:
		{
			system("cls||clear");
			CuentaContratoV cuentaContratoV(NOMBRE_ARCH_CC);
			cuentaContratoV.MenuCuentaContrato();
			break;
		}
		case 3:
		{
			system("cls||clear");
			MedidorV medidor(NOMBRE_ARCH_MED);
			medidor.MenuMedidor();
			break;
		}
		case 4:
		{
			system("cls||clear");
			TarifaV tarifa(NOMBRE_ARCH_TAR);
			tarifa.MenuTarifa();
			break;
		}
		case 5:
		{
			system("cls||clear");
			DocumentoV documento(NOMBRE_ARCH_DOC);
			documento.MenuDocumento();
			break;
		}
		case 6:
		{
			system("cls||clear");
			this->MenuConsultas();
			break;
		}
		case 7:
		{
			system("cls||clear");
			this->MenuExportacion();
			break;
		}
		default:
			system("cls||clear");
			break;
		}
		system("cls||clear");
	} while (true);
}

void InterfaceSalida::MenuExportacion()
{
	int opcion = 0;
	int retorno = 0;
	int anioConsulta = 0;
	int dni = 0;
	const int VAL1 = 1;
	
	do
	{
		system("cls||clear");
		cout << this->separador << endl;
		cout << "\t*** EXPORTACION DE DATOS FORMATO CSV ***" << endl;
		cout << this->separador << endl;
		cout << "|1. Exportacion de Interlocutores Comerciales" << endl;
		cout << "|2. Exportacion de Detalle de Facturas + Promedio Anual/Clientes (PAGOS)" << endl;
		cout << "|3. Exportacion de Detalle de Facturas + Promedio Anual/Clientes (IMPAGOS)" << endl;
		cout << "|0. Para volver" << endl;
		cout << this->separador << endl;
		opcion = Validaciones::DatoObligarorioNum("Opcion");
		switch (opcion)
		{
		case 1:
		{
		
			int ok = this->ExportarIC();
			if (this->ExportarIC() == 0)
				cout << endl;
				cout << "\tExportacion correcta" << endl;
				cout << endl;
			Validaciones::SystemPause();
			break;
		}
		case 2:
		{	
			
			cout << this->separador << endl;
			anioConsulta = Validaciones::DatoObligarorioNum("Ingrese año de consulta o (0) para volver al menu anterior");
			if (anioConsulta <=0) {

				break;
			}

			retorno = CalRecaudacion(dni, VAL1, anioConsulta,true);

			if (retorno < 0) {

				retorno = 0;
			}

			if (this->ExportarPromedioRecaudacion(anioConsulta, retorno,true)) {
				cout << endl;
				cout << "\tExportacion correcta" << endl;
				cout << endl;
				Validaciones::SystemPause();
				break;
			}
				
			cout << "\tExportación fallida" << endl;
		}
		case 3:
		{

			cout << this->separador << endl;
			anioConsulta = Validaciones::DatoObligarorioNum("Ingrese año de consulta o (0) para volver al menu anterior");
			if (anioConsulta <= 0) {

				break;
			}

			retorno = CalRecaudacion(dni, VAL1, anioConsulta,false);

			if (retorno < 0) {

				retorno = 0;
			}

			if (this->ExportarPromedioRecaudacion(anioConsulta, retorno,false)) {
				cout << endl;
				cout << "\tExportacion correcta" << endl;
				cout << endl;
				Validaciones::SystemPause();
				break;
			}

			cout << "\tExportación fallida" << endl;
		}
		case 0:
		{
			return;
		}
		default:
			break;
		}
	} while (true);
}

void InterfaceSalida::MenuConsultas()
{
	int opcion = 0;
	do
	{
		system("cls||clear");
		cout << this->separador << endl;
		cout << "\t***CONSULTAS DE GESTION ENERGETICA***" << endl;
		cout << "\t**********REPORTES**********" << endl;
		cout << this->separador << endl;
		cout << "|\t1. Consulta energia trimestral anual" << endl;
		cout << "|\t2. Promedio de recaudacion" << endl;
		cout << "|\t3. Consulta cliente datos comerciales" << endl;
		cout << "|\t4. Reporte Anual de Documentos Pagos e Impagos" << endl;
		cout << "|\t0. Para volver" << endl;
		cout << this->separador << endl;
		opcion = Validaciones::DatoObligarorioNum("Opcion");

		system("cls||clear");
		switch (opcion)
		{
		case 1:
		{
			system("cls||clear");
			int anio;
			anio = Validaciones::DatoObligarorioNum("Anio a consultar ");
			ConsumoTrimestralPorAnio(anio);
			break;
		}
		case 2:
		{
			PromedioRecaudacion();
			break;
		}
		case 3:
		{
			system("cls||clear");
			int dni;
			dni = Validaciones::DatoObligarorioNum("DNI a consultar o (0) para volver al menu");
			if (dni == 0) {
				break;
			}

			this->ClienteDatosComerciales(dni);
			break;
		}
		case 4:
		{	system("cls||clear");
		int anio;
		int pago;
		float porcentaje;
		cout << this->separador << endl << endl;
		anio = Validaciones::DatoObligarorioNum("anio a consultar");
		cout << this->separador << endl << endl;
		pago = Validaciones::DatoObligarorioNum("Pagas (1) o Impagas (0)");

		if (pago == 1 || pago == 0)
		{
			porcentaje = FacturasPorcentaje(anio, pago);
			string pagos = pago ? "pagos" : "impagos";
			if (porcentaje > -1)
			{	
				cout << this->separador << endl << endl;
				cout << "|\tEl porcentaje del anio |"<<anio<<"| de los documentos "<<"|" << pagos <<"|" << " es |" << porcentaje << "%|" << endl << endl;
				cout << this->separador << endl;
			}
			Validaciones::SystemPause();
			break;
		}
		else {
			break;
		}
		}
		case 0:
		{
			return;
		}
		default:
			break;
		}
	} while (true);
}

void InterfaceSalida::ConsumoTrimestralPorAnio(int anio)
{
	DocumentoAD documentoAD(NOMBRE_ARCH_DOC);
	vector<Documento> documentos;
	documentos = documentoAD.getDocumentosArchivo();
	int totalConsumoVerano = 0, totalConsumoOtonio = 0, totalConsumoInvierno = 0, totalConsumoPrimavera = 0;
	int cantidadDocVerano = 0, cantidadDocOtonio = 0, cantidadDocInvierno = 0, cantidadDocPrimavera = 0;
	for (auto& doc : documentos)
	{
		if (doc.getFecha().getAnio() == anio)
		{
			// Priemr Trimestre
			if (doc.getFecha().getMes() >= 1 && doc.getFecha().getMes() <= 3)
			{
				totalConsumoVerano += doc.getConsumo();
				cantidadDocVerano++;
			}
			// Segundo Trimestre
			if (doc.getFecha().getMes() >= 4 && doc.getFecha().getMes() <= 6)
			{
				totalConsumoOtonio += doc.getConsumo();
				cantidadDocOtonio++;
			}
			// Tercero
			if (doc.getFecha().getMes() >= 7 && doc.getFecha().getMes() <= 9)
			{
				totalConsumoInvierno += doc.getConsumo();
				cantidadDocInvierno++;
			}
			// Cuarto
			if (doc.getFecha().getMes() >= 10 && doc.getFecha().getMes() <= 12)
			{
				totalConsumoPrimavera += doc.getConsumo();
				cantidadDocPrimavera++;
			}
		}
	}
	system("cls||clear");
	string cadena, promedio;
	vector<string> datosAExportar;
	
	cout << separador << endl;
	cadena = "|CONSUMOS Y PROMEDIOS DEL ANIO: ";
	cout << "|" << cadena << anio << endl;
	datosAExportar.push_back(cadena);
	cout << separador << endl;
	if (cantidadDocVerano > 0)
	{		
		stringstream stream;
		stream << fixed << setprecision(2) <<(float) totalConsumoVerano / cantidadDocVerano;
		promedio = stream.str();

		cadena = "1er Trimestre (Enero Febrero Marzo)\t\t Total consumo: " + to_string(totalConsumoVerano) + " KWH\t Promedio: " + promedio;
		cout << "|" << cadena << endl;
		cadena = "1er Trimestre," + to_string(totalConsumoVerano) + "," + promedio;
		datosAExportar.push_back(cadena);
	}
	else
	{
		cadena = "1er Trimestre - No hay consumos registrados ";
		cout << "|" << cadena << endl;
		datosAExportar.push_back(cadena);
	}
	if (cantidadDocOtonio > 0)
	{
		stringstream stream;
		stream << fixed << setprecision(2) << (float)totalConsumoOtonio / cantidadDocOtonio;
		promedio = stream.str();

		cadena = "2do Trimestre (Abril Mayo Junio)\t\t Total consumo: " + to_string(totalConsumoOtonio) + " KWH\t Promedio: " + promedio;
		cout << "|" << cadena << endl;
		cadena = "2do Trimestre," + to_string(totalConsumoOtonio) + "," + promedio;
		datosAExportar.push_back(cadena);
	}
	else
	{
		cadena = "2do Trimestre - No hay consumos registrados ";
		cout << "|" << cadena << endl;
		datosAExportar.push_back(cadena);
	}
	if (cantidadDocInvierno > 0)
	{
		stringstream stream;
		stream << fixed << setprecision(2) << (float)totalConsumoInvierno / cantidadDocInvierno;
		promedio = stream.str();

		cadena = "3ro Trimestre (Julio Agosto Septiembre)\t Total consumo: " + to_string(totalConsumoInvierno) + " KWH\t Promedio: " + promedio;
		cout << "|" << cadena << endl;
		cadena = "3ro Trimestre," + to_string(totalConsumoInvierno) + "," + promedio;
		datosAExportar.push_back(cadena);
	}
	else
	{
		cadena = "3ro Trimestre - No hay consumos registrados ";
		cout << "|" << cadena << endl;
		datosAExportar.push_back(cadena);
	}
	if (cantidadDocPrimavera > 0)
	{
		stringstream stream;
		stream << fixed << setprecision(2) << (float)totalConsumoPrimavera / cantidadDocPrimavera;
		promedio = stream.str();

		cadena = "4to Trimestre (Octubre Noviembre Diciembre)\t Total consumo: " + to_string(totalConsumoPrimavera) + " KWH\t Promedio: " + promedio;
		cout << "|" << cadena << endl;
		cadena = "4to Trimestre," + to_string(totalConsumoPrimavera) + "," + promedio;
		datosAExportar.push_back(cadena);
	}
	else
	{
		cadena = "4to Trimestre - No hay consumos registrados ";
		cout << "|" << cadena << endl;
		datosAExportar.push_back(cadena);
	}
	cout << separador << endl;
	Validaciones::SystemPause();
	cout << "Desea exportar los datos a un archivo formato 'csv' ?" << endl;
	char dato = Validaciones::DatoObligarorioChar(" 'S' o cualquier otra letra para salir");
	if (dato == 'S')
	{
		this->GrabarTextosSalida(datosAExportar, "ConsumosPromedios" + to_string(anio) + ".csv");
		cout << "Datos exportados" << endl;
	}
}

void InterfaceSalida::PromedioRecaudacion()
{
	
	//Promedio de recaudacion anual ->  para todos los clientes con documentos pagos
	//Promedio de recaudacion por cada cliente -> solo documentos pagos
	//Promedio de recaudacion por tarifa 

	int opcion;

	system("cls||clear");
	do {
		int dni = -1;
		float retorno = 0;
		int anioConsulta;
		cout << this->separador << endl;
		cout << "\t***CONSULTAS DE GESTION ENERGETICA***" << endl;
		cout << "\t**********REPORTES**********" << endl;
		cout << this->separador << endl;
		cout << "|\t1. Promedio de recaudacion Anual (Para todos los clientes)" << endl;
		cout << "|\t2. Promedio de recaudacion Anual (Por cliente)" << endl;
		cout << "|\t3. Promedio de recaudacion Anual (Por tarifa)" << endl;
		cout << "|\t0. Para volver" << endl;
		cout << this->separador << endl;
		opcion = Validaciones::DatoObligarorioNum("opcion");

		switch (opcion) {
		case 1: {
			cout << endl;
			cout << this->separador << endl;
			anioConsulta = Validaciones::DatoObligarorioNum("Ingrese año de consulta o (0) para volver al menu anterior");

			if (anioConsulta <= 0) {
				break;
			}

			retorno = CalRecaudacion(dni, opcion, anioConsulta,true);

			if (retorno == -1) {
				retorno = 0;
			}

			//Transforma a 2 decimales cualquier float.
			stringstream stream;
			stream << fixed << setprecision(2) << retorno;
			string DecimalRetorno = stream.str();

			cout << "El promedio total todos los cliente es : $" << DecimalRetorno << endl;
			cout << this->separador << endl;

			Validaciones::SystemPause();
			cout << separador << endl;

			cout << "Desea exportar el detalle en formato 'csv' ?" << endl;
			char dato = Validaciones::DatoObligarorioChar(" 'S' o cualquier otra letra para salir");
			if (dato == 'S')
			{
				InterfaceSalida::ExportarPromedioRecaudacion(anioConsulta,retorno,true);
				cout << "Datos exportados" << endl;
				Validaciones::SystemPause();
			}

			break;
		}
		case 2: {

			anioConsulta = Validaciones::DatoObligarorioNum("Ingrese año de consulta ");
			cout << this->separador << endl;

			if (anioConsulta <= 0) {
				break;
			}

			dni = Validaciones::DatoObligarorioNum("ID Interlocutor Comercial o (0) para volver al menu anterior");
			cout << endl;
			if (dni <= 0) {
				break;
			}
			
			retorno = CalRecaudacion(dni, opcion,anioConsulta,true);

			if (retorno == -1) {
				cout << "El cliente no existe" << endl;
				Validaciones::SystemPause();
				break;
			}
			else {
				if (retorno == -2) {
					retorno = 0;
				}
			}

			//Transforma a 2 decimales cualquier float.
			stringstream stream;
			stream << fixed << setprecision(2) << retorno;
			string DecimalRetorno = stream.str();

			cout << "El promedio total para el cliente #" << dni << " es : $" << DecimalRetorno << endl;
			cout << this->separador << endl;
			Validaciones::SystemPause();
			break;
		}
		case 3: {

			TarifaAD tarifaAD(NOMBRE_ARCH_TAR);
			Tarifa tarifa;
			int tar;
			
			do{	
				
				tar= Validaciones::DatoObligarorioNum("el ID de la tarifa");
				// validar que el numero ingresado corresponda con un id de tarifa
				tarifa = tarifaAD.getTarifaArchivo(tar);

			} while ( tarifa.getIdTarifa()==0);

			cout << endl;
			int anio= Validaciones::DatoObligarorioNum("el anio");
			cout << endl;
			cout << endl;
			cout << this->separador << endl;
			float retorno = CalcularPromedioPorTarifa(tar, anio);
			
			if (retorno == -1) {
				retorno = 0;
			}

			stringstream stream;
			stream << fixed << setprecision(2) << retorno;
			string s = stream.str();
			
			cout << "El promedio total por la tarifa es : $" << s << endl;
			cout << this->separador << endl;
			Validaciones::SystemPause();
			break;
		}
		case 0:
		{
			system("cls||clear");
			return;
		}
		default: {
			break;
		}

		}
		system("cls||clear");

	} while (true);

}

float CalRecaudacion(int dni, int opcion,int anioConsulta,bool pago) {

	DocumentoAD documentoAD(NOMBRE_ARCH_DOC);
	vector<Documento> documentos;
	documentos = documentoAD.getDocumentosArchivo();

	// Si el pago es false (esta pendiente) y no se cuenta
	const int VAR = 1;
	bool salida = true;
	float promedioCliente = 0, promedioAnual = 0;
	int contadorCliente = 0, contadorAnual = 0;

	if (dni != -1) {

		for (int i = 0; i < documentos.size(); i++) {
			if (documentos[i].getIdinter() == dni) {
				salida = false;
			}
		}

		if (salida == true && opcion != VAR)
			return -1;
	}

	for (int i = 0; i < documentos.size(); i++) {

		if (documentos[i].getPago() == pago && opcion == VAR && documentos[i].getFecha().getAnio() == anioConsulta) {
			promedioAnual += documentos[i].getImporte();
			contadorAnual++;
		}
		else {
			if (documentos[i].getPago() == pago && documentos[i].getIdinter() == dni && documentos[i].getFecha().getAnio()==anioConsulta) {
				promedioCliente += documentos[i].getImporte();
				contadorCliente++;
			}
		}

	}


	if (opcion == VAR) {

		if (promedioAnual != 0 && contadorAnual != 0) {
			return float(promedioAnual / contadorAnual);
		}
		return -1;

	}
	else {

		if (promedioCliente != 0 && contadorCliente != 0) {
			return float(promedioCliente / contadorCliente);
		}
		return -2;

	}
}

float CalcularPromedioPorTarifa(int tar, int anio){
	
	DocumentoAD documentoAD(NOMBRE_ARCH_DOC);
	Documento documento;
	vector<Documento> documentos;
	documentos = documentoAD.getDocumentosArchivo();

	float cantidadDeFacturas=0;
	float montoAcumulado=0;

	for(int i =0; i < documentos.size(); i++){

		if(documentos[i].getFecha().getAnio()==anio && documentos[i].getIdtar()==tar && documentos[i].getPago()){
			montoAcumulado+=documentos[i].getConsumo();
			cantidadDeFacturas++;
		}

	}
	if (montoAcumulado == 0){
		return 0;
	} else {
		return montoAcumulado/cantidadDeFacturas;
	}
	
}

int InterfaceSalida::ExportarIC()
{
	InterlocutorComercialAD interComAD(NOMBRE_ARCH_IC);
	vector<InterlocutorComercial> interlocutores = interComAD.getInterlocutoresArchivo();
	vector<string> salidaInterlocutor;
	for (auto& interlocutor : interlocutores)
		salidaInterlocutor.push_back(interlocutor.toStringInterlocutor(true, true));
	try
	{
		this->GrabarTextosSalida(salidaInterlocutor, "ExpoInterlocutoresComerciales.csv");
	}
	catch (const std::exception&)
	{
		return -1;
	}
	return 0;
}

int InterfaceSalida::ExportarPromedioRecaudacion(int anio,float promedio,bool pago)
{
	DocumentoAD documentoAD(NOMBRE_ARCH_DOC);
	vector<Documento> DocumentosPagos = documentoAD.getDocumentosArchivo();
	vector<string> salidaClientesPagos; 

	Fecha fechaActual;
	fechaActual.cargarFechaActual();
	salidaClientesPagos.push_back(this->separador);
	salidaClientesPagos.push_back("#Detalle de las facturas paga para todos los clientes#");
	salidaClientesPagos.push_back(this->separador);
	salidaClientesPagos.push_back("Fecha de consulta: " + fechaActual.toStringFecha());

	for (auto& documento : DocumentosPagos) {
		if (documento.getPago() == pago && documento.getFecha().getAnio() == anio) {
			salidaClientesPagos.push_back(documento.toStringDocumento());
		}
	}
	if (pago) {
		salidaClientesPagos.push_back("#Promedio de Recaudacion# $" + to_string(promedio));
	}
	else {
		salidaClientesPagos.push_back("#Promedio a Recaudar# $" + to_string(promedio));
	}
	
	salidaClientesPagos.push_back("#Anio consultado: " + to_string(anio));

	salidaClientesPagos.push_back(this->separador);

	try
	{
		this->GrabarTextosSalida(salidaClientesPagos, "DetalleDeRecaudacionClientes.csv");
	}
	catch (const std::exception&)
	{
		return -1;
	}
	return 1;

	
}

void InterfaceSalida::ClienteDatosComerciales(int dni)
{
	system("cls||clear");
	string cadena;
	vector<string> datosAExportar;
	cout << separador << endl;
	cadena = "|\t\tCONSULTA DE CLIENTE DATOS COMERCIALES DOCUMENTO NRO: " + to_string(dni);
	cout << cadena << endl;
	cadena = "CONSULTA DE CLIENTE DATOS COMERCIALES DOCUMENTO NRO: " + to_string(dni);
	datosAExportar.push_back(cadena);

	InterlocutorComercial intLoc = InterlocutorComercialAD(NOMBRE_ARCH_IC).getInterlocutorArchivo(dni);
	if (intLoc.getDni() != dni)
	{
		cout << "Documento no encontrado, por favor corrobore el dato ingresado!!!" << endl;
		Validaciones::SystemPause();
		return;
	}
	CuentaContrato ctaContrato = CuentaContratoAD(NOMBRE_ARCH_CC).getCuentaContratoArchivo(intLoc.getId_ic());
	if (intLoc.getId_ic() != ctaContrato.getId_cc())
	{
		cout << "Cliente sin cuenta, para vesializar datos comerciales se debe crear una cuenta para el cliente con DNI: " << dni << endl;
		Validaciones::SystemPause();
		return;
	}
	Medidor medidor = MedidorAD(NOMBRE_ARCH_MED).getMedidorArchivo(ctaContrato.getId_Medidor());
	Tarifa tarifa = TarifaAD(NOMBRE_ARCH_TAR).getTarifaArchivo(ctaContrato.getId_Tarifa());
	cout << separador << endl;
	string activo = intLoc.getActivo() ? "Activo" : "Inactivo";
	cadena = "|Cliente Nro: " + to_string(intLoc.getId_ic()) + "\tEstado: " + activo +
		"\t\tNombre y Apellido: " + intLoc.getNombre() + ", " + intLoc.getApellido();
	cout << cadena << endl;
	cadena = "Cliente," + to_string(intLoc.getId_ic()) + "," + to_string(intLoc.getDni()) + "," + activo + "," + intLoc.getNombre() + "," + intLoc.getApellido();
	datosAExportar.push_back(cadena);
	cadena = "\tTarifa: " + to_string(tarifa.getIdTarifa()) + "\tCargo Fijo: " + to_string(tarifa.getCargoFijo()) +
		"\tCargo Variable: " + to_string(tarifa.getCargoVariable()) + "\tImpuesto: " + to_string(tarifa.getImpuestos());
	cout << cadena << endl;
	cadena = "Tarifa," + to_string(tarifa.getIdTarifa()) + "," + to_string(tarifa.getCargoFijo()) + "," + to_string(tarifa.getCargoVariable()) + "," + to_string(tarifa.getImpuestos());
	datosAExportar.push_back(cadena);
	cadena = "\tMedidor Nro: " + to_string(medidor.getId()) + " Ultima lectura: " + to_string(medidor.getLectura());
	cout << cadena << endl;
	cout << separador << endl;
	cadena = "Medidor," + to_string(medidor.getId()) + "," + to_string(medidor.getLectura());
	datosAExportar.push_back(cadena);
	Validaciones::SystemPause();
	cout << "Desea exportar los datos a un archivo formato 'csv' ?" << endl;
	char dato = Validaciones::DatoObligarorioChar(" 'S' o cualquier otra letra para salir");
	if (dato == 'S')
	{
		this->GrabarTextosSalida(datosAExportar, "DatosComerciales" + to_string(dni) + ".csv");
		cout << "Datos exportados" << endl;
	}
}

///REPORTE DE PORCENTAJE DE FACTURAS PAGAS O IMPAGAS POR ANIO
float  InterfaceSalida::FacturasPorcentaje(int anio, bool pago) {

	DocumentoAD documentoAD(NOMBRE_ARCH_DOC);
	vector<Documento> documentos;
	documentos = documentoAD.getDocumentosArchivo();

	// Si el pago es false (esta pendiente) y no se cuenta
	int contadorNopago = 0, contadorPago = 0, contadorDocumentos = 0;
	float porcenPago = 0, porcenNoPago = 0;

	for (int i = 0; i < documentos.size(); i++) {
		if (documentos[i].getFecha().getAnio() == anio)
		{
			if (documentos[i].getPago() == true)
			{
				contadorPago++;
			}
			else

			{
				contadorNopago++;

			}
		}
		
	}
	if (contadorPago==0 && contadorNopago==0) {
			cout << this->separador << endl;
			cout<<"\t\t\t\t\t|| ATENCION ||" << endl;
			cout << this->separador << endl;
			cout << "\t\t|| No hay registro de documentos facturados en el anio ingresado ||"<<endl;
			cout << this->separador << endl << endl;
			return -1;
		}
	contadorDocumentos = contadorPago + contadorNopago;
	porcenPago = float(contadorPago * 100) / contadorDocumentos;
	porcenNoPago = float(contadorNopago * 100) / contadorDocumentos;
	if (porcenPago < 0 || porcenNoPago < 0)
	{
		porcenPago = 0;
		porcenNoPago = 0;
		return -1;
	}

	if (pago == true)
	{

		return porcenPago;
	}
	else
	{

		return porcenNoPago;
	}

}
