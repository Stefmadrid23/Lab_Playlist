
// --- Paso 1: Tipos compuestos y agregados ---


function formatoTiempo(segundos) {
    const minutos = Math.floor(segundos / 60);
    const segRestantes = segundos % 60;
    const segTexto = segRestantes < 10 ? `0${segRestantes}` : `${segRestantes}`;
    return `${minutos}:${segTexto}`;
}


class Cancion {
    constructor(titulo, artista, duracion) {
        this.titulo = titulo;
        this.artista = artista;
        this.duracion = duracion; 
    }

    formato() {
        return `${this.titulo} - ${this.artista} (${formatoTiempo(this.duracion)})`;
    }
}

// 1.3 Clase Accion
class Accion {
    constructor(tipo, cancion, posicion) {
        this.tipo = tipo;       // agregar o eliminar
        this.cancion = cancion; // Objeto Cancion
        this.posicion = posicion; // Índice desde cero
    }
}

// 1.4 Clase Album
class Album {
    constructor(titulo, anio, canciones) {
        this.titulo = titulo;
        this.anio = anio;
        this.canciones = canciones; 
    }

    cantidad() {
        return this.canciones.length;
    }

    duracionTotal() {
        let total = 0;
        for (let i = 0; i < this.canciones.length; i++) {
            total += this.canciones[i].duracion;
        }
        return total;
    }
}

// --- Paso 2: Pila estática (PilaEstatica) ---

class PilaEstatica {
    #arreglo;
    #capacidad;
    #tope;

    constructor(capacidad) {
        this.#capacidad = capacidad;
        this.#arreglo = new Array(capacidad);
        this.#tope = 0;
    }

    push(elemento) {
        if (this.estaLlena()) {
            console.log("Error Pila llena: no cabe otro elemento");
            return;
        }
        this.#arreglo[this.#tope] = elemento;
        this.#tope++;
    }

    pop() {
        if (this.estaVacia()) {
            console.log("Error Pila vacía: no hay nada que sacar");
            return undefined;
        }
        this.#tope--;
        const elemento = this.#arreglo[this.#tope];
        this.#arreglo[this.#tope] = undefined;
        return elemento;
    }

    peek() {
        if (this.estaVacia()) {
            return undefined;
        }
        return this.#arreglo[this.#tope - 1];
    }

    estaVacia() {
        return this.#tope === 0;
    }

    estaLlena() {
        return this.#tope === this.#capacidad;
    }

    tamano() {
        return this.#tope;
    }

    capacidad() {
        return this.#capacidad;
    }
}

// --- Paso 3: Pila dinámica (PilaDinamica) ---

class PilaDinamica {
    #arreglo;

    constructor() {
        this.#arreglo= [];
    }

    push(elemento) {
        this.#arreglo.push(elemento);
    }

    pop() {
        if (this.estaVacia()) {
            console.log("Error Pila vacía: no hay nada que sacar");
            return undefined;
        }
        return this.#arreglo.pop();
    }

    peek() {
        if (this.estaVacia()) {
            return undefined;
        }
        return this.#arreglo[this.#arreglo.length - 1];
    }

    estaVacia() {
        return this.#arreglo.length === 0;
    }

    tamano() {
        return this.#arreglo.length;
    }
}

// --- Paso 4: Editor de Playlist ---

class EditorPlaylist {
    #playlist;
    #deshacer;
    #rehacer;

    constructor() {
        this.#playlist = [];
        this.#deshacer = new PilaEstatica(3);
        this.#rehacer = new PilaDinamica();
    }

    agregar(cancion) {
        if (this.#deshacer.estaLlena()) {
            console.log("Historial lleno: guarda la playlist para seguir editando");
            return;
        }
        this.#playlist.push(cancion);
        const accion = new Accion("agregar", cancion, this.#playlist.length - 1);
        this.#deshacer.push(accion);
        while (!this.#rehacer.estaVacia()) {
            this.#rehacer.pop();
        }
    }

    eliminar(posicion) {
        if (this.#deshacer.estaLlena()) {
            console.log("Historial lleno: guarda la playlist para seguir editando");
            return;
        }
        const idx = posicion - 1;
        if (idx < 0 || idx >= this.#playlist.length) {
            console.log("Posición inválida.");
            return;
        }
        const cancionEliminada = this.#playlist.splice(idx, 1)[0];
        const accion = new Accion("eliminar", cancionEliminada, idx);
        this.#deshacer.push(accion);
        while (!this.#rehacer.estaVacia()) {
            this.#rehacer.pop();
        }
    }

    deshacer() {
        if (this.#deshacer.estaVacia()) {
            console.log("Nada que deshacer");
            return;
        }
        const accion = this.#deshacer.pop();
        if (accion.tipo === "agregar") {
            this.#playlist.splice(accion.posicion, 1);
        } else if (accion.tipo === "eliminar") {
            this.#playlist.splice(accion.posicion, 0, accion.cancion);
        }
        this.#rehacer.push(accion);
    }

    rehacer() {
        if (this.#rehacer.estaVacia()) {
            console.log("Nada que rehacer");
            return;
        }
        const accion = this.#rehacer.pop();
        if (accion.tipo === "agregar") {
            this.#playlist.splice(accion.posicion, 0, accion.cancion);
        } else if (accion.tipo === "eliminar") {
            this.#playlist.splice(accion.posicion, 1);
        }
        this.#deshacer.push(accion);
    }

    guardar() {
        while (!this.#deshacer.estaVacia()) {
            this.#deshacer.pop();
        }
        while (!this.#rehacer.estaVacia()) {
            this.#rehacer.pop();
        }
        console.log("Playlist guardada.");
    }

    estado() {
        const titulos = this.#playlist.map(c => c.titulo).join(", ");
        return `[ ${titulos} ] . Deshacer ${this.#deshacer.tamano()}/3 . Rehacer ${this.#rehacer.tamano()}`;
    }

    mostrar() {
        let duracionTotalSec = 0;
        this.#playlist.forEach((cancion, index) => {
            console.log(`${index + 1}. ${cancion.formato()}`);
            duracionTotalSec += cancion.duracion;
        });
        console.log(`Duración total: ${formatoTiempo(duracionTotalSec)}`);
    }
}

// --- Pruebas principales 

function ejecutarPruebas() {
    // Creacion de las 4 canciones
    const c1 = new Cancion("Dynamite", "BTS", 199);
    const c2 = new Cancion("Hooligan", "BTS", 244);
    const c3 = new Cancion("They don´t know about us", "BTS", 165);
    const c4 = new Cancion("Butter", "BTS", 183);

    // Creacion del álbum con las 4 canciones
    const miAlbum = new Album("Hit", 2026, [c1, c2, c3, c4]);

    console.log("--- PASO 1.5: MOSTRAR ÁLBUM ---");
    // 1. Título del álbum, año y cantidad de canciones
    console.log(`${miAlbum.titulo} (${miAlbum.anio}) - ${miAlbum.cantidad()} canciones`);

    // 2. Numeracion de las canciones
    miAlbum.canciones.forEach((cancion, index) => {
        console.log(`${index + 1}. ${cancion.formato()}`);
    });

    // 3. Duración total del álbum 
    console.log(`Duración del álbum: ${formatoTiempo(miAlbum.duracionTotal())}\n`);

    console.log("--- PASO 2.4 & 3.3: PRUEBA DE PILAS ---");
    const pilaEstaticaTest = new PilaEstatica(3);
    pilaEstaticaTest.push(c1);
    pilaEstaticaTest.push(c2);
    pilaEstaticaTest.push(c3);
    console.log(`Tamaño estática: ${pilaEstaticaTest.tamano()}, Tope: ${pilaEstaticaTest.peek().titulo}`);
    pilaEstaticaTest.push(c4); // Error: Pila llena

    while (!pilaEstaticaTest.estaVacia()) {
        console.log(`Sacando de estática: ${pilaEstaticaTest.pop().titulo}`);
    }
    pilaEstaticaTest.pop(); // Error: Pila vacía

    const pilaDinamicaTest = new PilaDinamica();
    pilaDinamicaTest.push(c1);
    pilaDinamicaTest.push(c2);
    pilaDinamicaTest.push(c3);
    pilaDinamicaTest.push(c4);
    console.log(`Tamaño dinámica tras 4 elementos: ${pilaDinamicaTest.tamano()}\n`);

    console.log("--- PASO 4.4: SECUENCIA DE 13 PASOS CON TU ÁLBUM ---");
    const editor = new EditorPlaylist();
    const canc = miAlbum.canciones;

    const pasos = [
        () => editor.agregar(canc[0]),
        () => editor.agregar(canc[1]),
        () => editor.agregar(canc[2]),
        () => editor.agregar(canc[3]),
        () => editor.deshacer(),
        () => editor.deshacer(),
        () => editor.rehacer(),
        () => editor.eliminar(1),
        () => editor.rehacer(),
        () => editor.deshacer(),
        () => editor.guardar(),
        () => editor.deshacer(),
        () => editor.agregar(canc[3])
    ];

    const nombresOperaciones = [
        "agregar canción 1 del álbum",
        "agregar canción 2",
        "agregar canción 3",
        "agregar canción 4",
        "deshacer",
        "deshacer",
        "rehacer",
        "eliminar(1)",
        "rehacer",
        "deshacer",
        "guardar",
        "deshacer",
        "agregar canción 4"
    ];

    pasos.forEach((op, index) => {
        op();
        console.log(`Paso ${index + 1} · ${nombresOperaciones[index]} -> ${editor.estado()}`);
    });

    console.log("\n--- RESULTADO FINAL DE LA PLAYLIST ---");
    editor.mostrar();
}

ejecutarPruebas();