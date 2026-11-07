
function formatoTiempo(segundos) {
    const minutos = Math.floor(segundos / 60);
    const segsRestantes = segundos % 60;
    
    const minFormateado = String(minutos).padStart(2, '0');
    const segFormateado = String(segsRestantes).padStart(2, '0');
    
    return `${minFormateado}:${segFormateado}`;
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

class Accion {
    constructor(tipo, cancion, posicion) {
        this.tipo = tipo;       
        this.cancion = cancion;   
        this.posicion = posicion; 
    }
}

class Album {
    constructor(titulo, anio, canciones = []) {
        this.titulo = titulo;        
        this.anio = anio;            
        this.canciones = canciones;   
    }

    cantidad() {
        return this.canciones.length;
    }

    duracionTotal() {
        return this.canciones.reduce((acumulador, cancion) => acumulador + cancion.duracion, 0);
    }
}


class PilaEstatica {
    #capacidad;
    #arreglo;
    #tope;

    constructor(capacidad) {
        this.#capacidad = capacidad;
        this.#arreglo = new Array(capacidad);
        this.#tope = -1;
    }

  
    push(elemento) {
        if (this.estaLlena()) {
            throw new Error("error pila llena: no cabe otro elemento");
        }
        this.#tope++;
        this.#arreglo[this.#tope] = elemento;
    }

    pop() {
        if (this.estaVacia()) {
            throw new Error("error pila vacia: no hay nada que sacar");
        }
        const elemento = this.#arreglo[this.#tope];
        this.#arreglo[this.#tope] = undefined;
        this.#tope--;
        return elemento;
    }

    peek() {
        if (this.estaVacia()) {
            return undefined;
        }
        return this.#arreglo[this.#tope];
    }

      estaVacia() {
        return this.#tope === -1;
    }

    estaLlena() {
        return this.#tope === this.#capacidad - 1;
    }


    tamano() {
        return this.#tope + 1;
    }

    capacidad() {
        return this.#capacidad;
    }
}


