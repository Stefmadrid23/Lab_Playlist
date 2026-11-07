
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

int main()
{
// Función para convertir segundos a formato m:ss
string FormatoTiempo(int segundos) {
    int minutos = segundos / 60;
    int seg = segundos % 60;

    stringstream formato;
    formato << minutos << ":" << setw(2) << setfill('0') << seg;

    return formato.str();
}

// Estructura Cancion
struct Cancion {
    string titulo;
    string artista;
    int duracion; // Duración en segundos

    // Método que devuelve Titulo - Artista (m:ss)
    string formato() {
        return titulo + " - " + artista + " (" + FormatoTiempo(duracion) + ")";
    }
    void display(){
        cout<<"Cancion incompleta";
    }
};

int main() {
    Cancion cancion;

    cancion.titulo = "Mi Cancion";
    cancion.artista = "Mi Artista";
    cancion.duracion = 245;

    cout << cancion.formato() << endl;

    return 0;
    
    // Tipo Album
struct Album {
    string titulo "Careless Whisper", "Wind of Change", "Imagine", " Hello"; 
    int ano "1984", "1990", "1971", "2015";
    Cancion canciones[4]; // Arreglo nativo de 4 canciones 
    
};

// Tipo para las operaciones de la playlist
struct Operacion {
    string tipo;       // "agregar" o "eliminar"
    Cancion cancion;   // Una cancion incompleta
    int posicion;      // Indice de la cancion, desde 0
}
//En el programa principal crea un album con tus cuatro canciones y muestra: Una linea con el formato titulo del album (ano). Las cuatro canciones numeradas del 1 al 4, usando formato (). 
//una linea con el formato Duracion del album: m : ss. 


// la clase es una plantilla (template <typename T>, para que la pila guarde canciones o acciones. La capacidad es una constante CAPACIDAD  = 3 y los elementos van en un arreglo nativo T elementos [CAPACIDAD]
};

// Programa la clase PilaDinamica en los dos lenguajes. No tiene limite de capacidad 


