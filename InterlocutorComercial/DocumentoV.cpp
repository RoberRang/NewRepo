#include "DocumentoV.h"
#include "Fecha.h"
#include "Validaciones.h"
#include "MedidorV.h"


DocumentoV::DocumentoV(string nombreArchivo)
{
	this->documento = Documento();
	this->nombreArchivo = nombreArchivo;
	this->documentoRN = DocumentoRN(nombreArchivo);
}
DocumentoV::~DocumentoV()
{
}
///
void DocumentoV::RegistrarPago()
{
	this->documento = Documento();
	int numero;
	char dato;

	do {
		system("cls||clear");
		cout << "-------------------------------------------------" << endl;
		cout << "Nuevo Registro de pago de Documento " << endl;
		cout << "--------------------------------------------------" << endl;
		numero = Validaciones::DatoObligarorioNum("Numero del Documento");
		//VALIDAR QUE EL NUMERO DE FACTURA EXISTA 

		if (!this->documentoRN.ValidarDocumentoNumero(numero)) {
			cout << "El numero ingresado no es valido " << endl;

		}
		//seteo que se pago la factura y guardo en archivo
		else
		{
			this->documento = this->documentoRN.getDocumento();
			if (this->documento.getPago() == true)
			{
				cout << "EL DOCUMENTO YA ESTA PAGO" << endl << endl;
			}
			else {
				this->documento.setPago(true);
				if (this->documentoRN.ControlModificaciones(documento))
					cout << "EL PAGO FUE REGISTRADO EXITOSAMENTE" << endl;
			}
		}
		cout << "Desea cargar otro numero de documento?" << endl;
		dato = Validaciones::DatoObligarorioChar("'S' o 'N'");
		if (toupper(dato) != 'S') {
			return;
		}
	} while (true);

}

/// 
/// 
/// <summary>
/// M�todo que permite dar de alta un Documento y lo graba en el archivo que contiene los documentos.
/// </summary>
void DocumentoV::NuevoDocumento()
{
	/// <summary>
	/// DEBE INGRESAR UN NUMERO DE ID DE MEDIDOR, CON ESE ID ME TRAE EL ID DEL INTERLOCUTOR PARA LLENAR EL DOCUMENTO PARA ESE INTER
	/// VALIDAR SI EL ID ES EL MISMO QUE ME TRAE OK, SINO NO EXISTE EL MEDIDOR
	/// </summary>
	this->documento = Documento();
	Fecha fecha;
	int id;
	bool volver = false;
	float lecturaActual;
	char dato;

	do {
		cout << "-------------------------------------------------" << endl;
		cout << "Nuevo ingreso de datos del Documento " << endl;
		cout << "--------------------------------------------------" << endl;
		id = Validaciones::DatoObligarorioNum("Id del Medidor");

		if (!this->documentoRN.validarIdMedidor(id) || this->documentoRN.validarFechaDocumento(id)) {
			cout << "El ID ingresado no es valido o documento ya generado" << endl;
			cout << "Desea ingresar otro ID?" << endl;
			dato = Validaciones::DatoObligarorioChar("'S' o 'N'");
			if (toupper(dato) == 'S') {
				system("cls||clear");
				continue;
			}
			else {
				return;
			}
		}
		else {
			lecturaActual = Validaciones::DatoObligarorioDecimal("la lectura actual");
			///SE CALCULA EL CONSUMO PARA ESTE DOCUMENTO
			float consumo = this->documentoRN.CalcularConsumo(lecturaActual);
			if (consumo >= 0)
			{
				cout << this->separador << endl;
				cout << "\t\t\t\t\tATENCION! " << endl;
				cout << this->separador << endl;
				cout << "ESTA CREANDO UN NUEVO DOCUMENTO CON EL NUMERO " << documentoRN.IdDocumento(documento) << endl;
				cout << "PARA EL CLIENTE | NOMBRE: " << this->documentoRN.getInterlocutorComercial().getNombre();
				cout << "\tAPELLIDO: " << this->documentoRN.getInterlocutorComercial().getApellido() << endl;
				cout << this->separador << endl;
				cout << "\t\t\t\t\t\t\t\t\t\tLectura anterior: " << documentoRN.getMedidor().getLectura() << endl;
				cout << "\t\t\t\t\t\t\t\t\t\tLectura actual: " << lecturaActual << endl;
				cout << "\t\t\t\t\t\t\t\t\t\tPor un consumo de: " << consumo << " KWH" << endl;
				cout << this->separador << endl;
				cout << "Desea continuar?" << endl;


				dato = Validaciones::DatoObligarorioChar("'S' o 'N'");
				if (toupper(dato) == 'S')
				{

					fecha.cargarFechaActual();
					this->documento.setFecha(fecha);
					this->documento.setIdinter(this->documentoRN.getInterlocutorComercial().getId_ic());
					this->documento.setIdcc(this->documentoRN.getCuentaContrato().getId_cc());
					this->documento.setIdtar(this->documentoRN.getTarifa().getIdTarifa());
					this->documento.setConsumo(consumo);
					this->documento.setImporte(this->documentoRN.CalcularImporte(consumo));
					this->documentoRN.GuardarLectura(id, lecturaActual);

					//cout << " el importe total es: $ " << documento.getImporte() << endl;
					//SE GUARDA LA FACTURA EN DISCO
					if (this->documentoRN.AltaDocumento(this->documento)) {
						cout << this->separador << endl;
						cout << "\t\t\t\tSE CREO EL SIGUIENTE DOCUMENTO EXITOSAMENTE" << endl;
						cout << this->separador << endl;
						cout << "NUMERO DE DOCUMENTO: " << documento.getNumero() << "\t\tNUMERO DE CLIENTE: " << documento.getIdinter() << "\t\t\tFecha de creacion:" << documento.getFecha().toStringFecha() << endl;
						cout << this->separador << endl;
						cout << "\t\t\t\t\t\t\t\t\t\tCargo Fijo:\t $ " << this->documentoRN.getTarifa().getCargoFijo() << endl;
						cout << "\t\t\t\t\t\t\t\t\t\tCargo Variable:\t $ " << this->documentoRN.getTarifa().getCargoVariable() << endl;
						cout << "\t\t\t\t\t\t\t\t\t\tImpuestos:\t $ " << this->documentoRN.getTarifa().getImpuestos() << endl;
						cout << "\t\t\t\t\t\t\t\t\t\tTotal consumo:\t " << this->documento.getConsumo() << " KWH" << endl;
						cout << this->separador << endl;
						cout << "\t\t\t\t\t\t\t\t\t\tTotal a Pagar:\t $" << documento.getImporte() << endl;
						cout << this->separador << endl;

						cout << this->separador << endl;
						Validaciones::SystemPause();
						cout << this->separador << endl;
						cout << "Desea cargar otro documento con un nuevo Id de medidor?" << endl;
						dato = Validaciones::DatoObligarorioChar("'S' o 'N'");
						if (toupper(dato) == 'S')
						{
							system("cls||clear");
							volver = true;

						}
						else {
							return;
						}
					}
					else {
						cout << this->separador << endl;
						cout << "ATENCION NO SE CREO EL DOCUMENTO" << endl;
						cout << this->separador << endl;
						Validaciones::SystemPause();
						break;
					}

				}
				else {
					return;
				}
			}
			//SI EL CONSUMO DA NEGATIVO. INGRESO UNA LECTURA ACTUAL MENOR A LA ANTERIOR O UNA LECTURA NEGATIVA
			else {
				cout << this->separador << endl;
				cout << "******************ATENCION EL CONSUMO CALCULADO ES NEGATIVO***************" << endl;
				cout << "-----------POSIBLE CONEXION CLANDESTINA O DEFECTO EN LECTURA DEL INSPECTOR----------------" << endl;
				cout << "-----------------------REPORTAR A SUPERVISOR-------------------" << endl;
				cout << this->separador << endl;
				Validaciones::SystemPause();
				system("cls||clear");
				break;
			}
		}


	} while (true || volver != true);


}


/// <summary>
/// Funci�n global para listar todos los documentos del archivo.
/// </summary>


void DocumentoV::ListarDocumentos()
{
	vector<Documento> documentos = this->documentoRN.getDocumentos();

	for (int i = 0; i < documentos.size(); i++)
	{
		cout << documentos[i].toStringDocumento() << endl;
	}

}
//LISTAR DOCUMENTOS IMPAGOS

void DocumentoV::ListarDocumentosImpagos()
{
	vector<Documento> documentos = this->documentoRN.getDocumentos();

	for (int i = 0; i < documentos.size(); i++)
	{
		if(documentos[i].getPago()==false)
		cout << documentos[i].toStringDocumento() << endl;
	}
}
//listar DOCUMENTOS PAGOS

void DocumentoV::ListarDocumentosPagos()
{
	vector<Documento> documentos = this->documentoRN.getDocumentos();

	for (int i = 0; i < documentos.size(); i++)
	{
		if (documentos[i].getPago() == true)
			cout << documentos[i].toStringDocumento() << endl;
	}
}
/// <summary>
/// Metodo que muestra un menu de opciones para las altas bajas y modificaciones de documentos.
/// </summary>
void DocumentoV::MenuDocumento()
{
	bool salir = false;
	do
	{
		cout << "-------------------------------------------------" << endl;
		cout << "Menu Documento" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "1. Nuevo Documento" << endl;
		cout << "2. Registrar el Pago de Documento" << endl;
		cout << "3. Listar Documentos" << endl;
		cout << "4. Listar Documentos Pagos" << endl;
		cout << "5. Listar Documentos Impagos" << endl;
		cout << "6. Listar Medidores disponibles" << endl;
		cout << "0. Salir" << endl;
		cout << "-------------------------------------------------" << endl;
		int opcion;
		cout << "Ingrese una opcion: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1:
			this->NuevoDocumento();
			break;
		case 2:
			this->RegistrarPago();
			break;

		case 3:
			this->ListarDocumentos();
			
			break;
		
		case 4:
			this->ListarDocumentosPagos();
			break;

		case 5:
			this->ListarDocumentosImpagos();
			break;
		
		case 6:
			{
			MedidorV medidorV("medidores.dat");
			//Le pasas false para traer los medidores desinstalados=Disponibles
			medidorV.ListarMedidor(true);
			break;
			}
		case 0:
			salir = true;
			system("cls||clear");
			break;
		default:
			cout << "Opcion no valida" << endl;
			break;
		}
	} while (salir == false);
}


void DocumentoV::setNombreArchivo(string nombreArchivo)
{
	this->nombreArchivo = nombreArchivo;
}
string DocumentoV::getNombreArchivo()
{
	return this->nombreArchivo;
}

void DocumentoV::setDocumento(Documento& documento)
{
	this->documento = documento;
}

Documento DocumentoV::getDocumento()
{
	return this->documento;
}
DocumentoRN DocumentoV::getDocumentoRN()
{
	return this->documentoRN;
}

