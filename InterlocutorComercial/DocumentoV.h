#pragma once
#include "DocumentoRN.h"


class DocumentoV
{
private:
	Documento documento;
	string nombreArchivo;
	DocumentoRN documentoRN;
	string separador = "-------------------------------------------------------------------------------------------------------------";
public:
	DocumentoV(string nombreArchivo);
	~DocumentoV();
	void NuevoDocumento();
	void ListarDocumentos();
	void RegistrarPago();
	void ListarDocumentosImpagos();
	void ListarDocumentosPagos();
	//void ModificarDocumento();
	//void MenuModificarDocumento();
	void MenuDocumento();
	void setNombreArchivo(string nombreArchivo);
	string getNombreArchivo();
	Documento getDocumento();
	void setDocumento(Documento& documento);
	DocumentoRN getDocumentoRN();
	

};