#include "InterlocutorComercialRN.h"

class InterlocutorComercialV
{   
    private:
    InterlocutorComercial interlocutorComercial;
    string nombreArchivo;
    InterlocutorComercialRN interlocutorComercialRN;
    public:
    InterlocutorComercialV(string nombreArchivo);
    ~InterlocutorComercialV();
    void NuevoInterlocutor();
    void ListarInterlocutores();
    void ModificarInterlocutor();
    void MenuModificarInterlocutor();
    void MenuInterlocutorComecial();
    void setNombreArchivo(string nombreArchivo);
    string getNombreArchivo();
    void setInterlocutorComercial(InterlocutorComercial& interlocutorComercial);
};