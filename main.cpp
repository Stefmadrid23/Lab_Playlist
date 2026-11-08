
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
    ss << minutos << ":" << setw(2) << setfill('0') << seg;

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
    string formato() const {
        return titulo + " - " + artista + " (" + formatoTiempo(duracion) + ")";
    }
};
    struct Accion {
    string tipo;      // Texto: "agregar" o "eliminar"
    Cancion cancion;  // Cancion completa
    int posicion;     // Entero: índice de la canción en la playlist, desde 0
 
    Accion() : tipo(""), cancion(), posicion(0) {}
    Accion(string t, Cancion c, int p) : tipo(t), cancion(c), posicion(p) {}
};
     
// 1.4 Tipo agregado Album
struct Album {
    string titulo;        // Texto: título del álbum
    int ano;              // Entero: año del álbum
    Cancion canciones[4]; // Arreglo nativo de 4 canciones
 
    // Suma de las duraciones, en segundos
    int duracionTotal() const {
        int total = 0;
        for (int i = 0; i < 4; i++) total += canciones[i].duracion;
        return total;
    }
};


    
// 2.1 Pila de capacidad fija con arreglo nativo y contador tope
template <typename T>
class PilaEstatica {
public:
    static const int CAPACIDAD = 3;  // Constante: tamaño máximo de la pila
    T elementos[CAPACIDAD];          // Arreglo nativo de elementos
    int tope;                        // Cantidad de elementos guardados
 
    PilaEstatica() : tope(0) {}
 
    // Agrega el elemento al tope; error si está llena
    void push(const T& elemento) {
        if (estaLlena()) throw runtime_error("Pila llena: no cabe otro elemento");
        elementos[tope] = elemento;
        tope++;
    }

// Quita y devuelve el elemento del tope; error si está vacía
    T pop() {
        if (estaVacia()) throw runtime_error("Pila vacía: no hay nada que sacar");
        tope--;
        return elementos[tope];
    }
 
    // Devuelve el elemento del tope sin quitarlo; error si está vacía
    T peek() const {
        if (estaVacia()) throw runtime_error("Pila vacía: no hay tope que ver");
        return elementos[tope - 1];
    }
 
    // true si no hay elementos
    bool estaVacia() const { return tope == 0; }
 
    // true si se llegó a la capacidad
    bool estaLlena() const { return tope == CAPACIDAD; }
 
    // Cuántos elementos hay
    int tamano() const { return tope; }
 
    // El tamaño máximo
    int capacidad() const { return CAPACIDAD; }
};
 
// 2.4 Prueba de la pila estática con canciones
void probarPilas(const Album& album) {
    cout << "=== probarPilas (PilaEstatica de Cancion, capacidad 3) ===" << endl;
    PilaEstatica<Cancion> pila;
 
    // 1. Meter las tres primeras canciones
    for (int i = 0; i < 3; i++) {
        pila.push(album.canciones[i]);
        cout << "push '" << album.canciones[i].titulo << "' -> tamano: "
             << pila.tamano() << "/" << pila.capacidad() << endl;
    }
 
    // 2. Intentar meter la cuarta
    try {
        pila.push(album.canciones[3]);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "tamano: " << pila.tamano() << " | peek: " << pila.peek().titulo << endl;
 
    // 3. Sacar todas con while
    while (!pila.estaVacia()) {
        cout << "tamano: " << pila.tamano() << " | peek: " << pila.peek().titulo << endl;
        pila.pop();
    }
 
    // 4. Intentar sacar una más
    try {
        pila.pop();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
}
 
// ============================================================
// PASO 3. Pila dinámica (std::vector)
// ============================================================
 
// 3.2 Sin límite de capacidad; usa std::vector<T>
template <typename T>
class PilaDinamica {
public:
    vector<T> elementos;  // Vector que guarda los elementos
 
    // Agrega al final (push_back)
    void push(const T& elemento) { elementos.push_back(elemento); }
 
    // Quita y devuelve el último; error si está vacía
    T pop() {
        if (estaVacia()) throw runtime_error("Pila vacía: no hay nada que sacar");
        T x = elementos.back();
        elementos.pop_back();
        return x;
    }
 
    // Devuelve el último sin quitarlo; error si está vacía
    T peek() const {
        if (estaVacia()) throw runtime_error("Pila vacía: no hay tope que ver");
        return elementos.back();
    }
 
    // true si no hay elementos (empty)
    bool estaVacia() const { return elementos.empty(); }
 
    // Cantidad de elementos (size)
    int tamano() const { return (int)elementos.size(); }
};
 
// 3.3 Prueba de la pila dinámica (la cuarta canción sí entra)
void probarPilaDinamica(const Album& album) {
    cout << "=== probarPilaDinamica (sin limite) ===" << endl;
    PilaDinamica<Cancion> pila;
 
    for (int i = 0; i < 4; i++) {
        pila.push(album.canciones[i]);
        cout << "push '" << album.canciones[i].titulo << "' -> tamano: " << pila.tamano() << endl;
    }
 
    while (!pila.estaVacia()) {
        cout << "tamano: " << pila.tamano() << " | peek: " << pila.peek().titulo << endl;
        pila.pop();
    }
 
    try {
        pila.pop();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    try {
        pila.peek();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
}
 
// ============================================================
// PASO 5. Editor de playlist
// ============================================================
 
class EditorPlaylist {
public:
    vector<Cancion> playlist;          // La playlist del editor
    PilaEstatica<Accion> pilaDeshacer; // Historial de deshacer (máx. 3) - "deshacer"
    PilaDinamica<Accion> pilaRehacer;  // Historial de rehacer - "rehacer"
 
    // Agrega una canción al final de la playlist
    void agregar(const Cancion& cancion) {
        if (pilaDeshacer.estaLlena()) {
            cout << "Historial lleno: guarda la playlist para seguir editando" << endl;
            return;
        }
        playlist.push_back(cancion);
        pilaDeshacer.push(Accion("agregar", cancion, (int)playlist.size() - 1));
        pilaRehacer = PilaDinamica<Accion>();  // vacía rehacer
    }
 
    // Elimina la canción en la posición (empieza en 1)
    void eliminar(int posicion) {
        if (pilaDeshacer.estaLlena()) {
            cout << "Historial lleno: guarda la playlist para seguir editando" << endl;
            return;
        }
        if (posicion < 1 || posicion > (int)playlist.size()) {
            cout << "Posición inválida" << endl;
            return;
        }
        int indice = posicion - 1;
        Cancion quitada = playlist[indice];
        playlist.erase(playlist.begin() + indice);
        pilaDeshacer.push(Accion("eliminar", quitada, indice));
        pilaRehacer = PilaDinamica<Accion>();  // vacía rehacer
    }
 
    // Deshace la última acción
    void deshacer() {
        if (pilaDeshacer.estaVacia()) {
            cout << "Nada que deshacer" << endl;
            return;
        }
        Accion a = pilaDeshacer.pop();
        if (a.tipo == "agregar")
            playlist.erase(playlist.begin() + a.posicion);           // quita la canción
        else
            playlist.insert(playlist.begin() + a.posicion, a.cancion); // la vuelve a poner
        pilaRehacer.push(a);
    }
 
    // Rehace la última acción deshecha
    void rehacer() {
        if (pilaRehacer.estaVacia()) {
            cout << "Nada que rehacer" << endl;
            return;
        }
        Accion a = pilaRehacer.pop();
        if (a.tipo == "agregar")
            playlist.insert(playlist.begin() + a.posicion, a.cancion); // la vuelve a poner
        else
            playlist.erase(playlist.begin() + a.posicion);             // la vuelve a quitar
        pilaDeshacer.push(a);
    }
 
    // Vacía las dos pilas y confirma
    void guardar() {
        pilaDeshacer = PilaEstatica<Accion>();
        pilaRehacer = PilaDinamica<Accion>();
        cout << "Playlist guardada" << endl;
    }
 
    // Texto: [ Titulo1, Titulo2 ] · Deshacer n/3 · Rehacer m
    string estado() const {
        stringstream ss;
        ss << "[ ";
        for (size_t i = 0; i < playlist.size(); i++) {
            if (i > 0) ss << ", ";
            ss << playlist[i].titulo;
        }
        ss << " ] · Deshacer " << pilaDeshacer.tamano() << "/" << pilaDeshacer.capacidad()
           << " · Rehacer " << pilaRehacer.tamano();
        return ss.str();
    }
 
    // Muestra la playlist numerada y la duración total
    void mostrar() const {
        int total = 0;
        for (size_t i = 0; i < playlist.size(); i++) {
            cout << (i + 1) << ". " << playlist[i].formato() << endl;
            total += playlist[i].duracion;
        }
        cout << "Duración total: " << formatoTiempo(total) << endl;
    }
};
 
// 5.2 Secuencia del Paso 4.4
void ejecutarSecuencia(const Album& album) {
    cout << "=== EditorPlaylist ===" << endl;
    EditorPlaylist editor;
    int paso = 0;
 
    auto reporte = [&](const string& operacion) {
        cout << "Paso " << paso << " · " << operacion << " → " << editor.estado() << endl;
    };
 
    paso = 1;  editor.agregar(album.canciones[0]); reporte("agregar canción 1");
    paso = 2;  editor.agregar(album.canciones[1]); reporte("agregar canción 2");
    paso = 3;  editor.agregar(album.canciones[2]); reporte("agregar canción 3");
    paso = 4;  editor.agregar(album.canciones[3]); reporte("agregar canción 4");
    paso = 5;  editor.deshacer();                  reporte("deshacer");
    paso = 6;  editor.deshacer();                  reporte("deshacer");
    paso = 7;  editor.rehacer();                   reporte("rehacer");
    paso = 8;  editor.eliminar(1);                 reporte("eliminar(1)");
    paso = 9;  editor.rehacer();                   reporte("rehacer");
    paso = 10; editor.deshacer();                  reporte("deshacer");
    paso = 11; editor.guardar();                   reporte("guardar");
    paso = 12; editor.deshacer();                  reporte("deshacer");
    paso = 13; editor.agregar(album.canciones[3]); reporte("agregar canción 4");
 
    cout << endl;
    editor.mostrar();
}
 
// ============================================================
// Programa principal
// ============================================================
int main() {
    // 1.5 Álbum con cuatro canciones reales
    Album album;
    album.titulo = "Mis Favoritas";
    album.ano = 2026;
    album.canciones[0] = Cancion("Careless Whisper", "George Michael", 300);
    album.canciones[1] = Cancion("Wind of Change", "Scorpions", 312);
    album.canciones[2] = Cancion("Imagine", "John Lennon", 187);
    album.canciones[3] = Cancion("Hello", "Adele", 295);
 
    cout << album.titulo << " (" << album.ano << ")" << endl;
    for (int i = 0; i < 4; i++)
        cout << (i + 1) << ". " << album.canciones[i].formato() << endl;
    cout << "Duración del álbum: " << formatoTiempo(album.duracionTotal()) << endl << endl;
 
    probarPilas(album);          // Paso 2.4
    probarPilaDinamica(album);   // Paso 3.3
    ejecutarSecuencia(album);    // Paso 5.2
 
    return 0;
}
 


