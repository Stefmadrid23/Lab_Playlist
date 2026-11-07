// Creacion de las 4 canciones
const c1 = new Cancion("Dynamite", "Pop","BTS", 199);
const c2 = new Cancion("Hooligan", "Pop","BTS",244 );
const c3 = new Cancion("They don´t know about us", "BTS",165 );
const c4 = new Cancion("Butter", "BTS",183 );

// Creacion del álbum con las 4 canciones
const miAlbum = new Album("Hit", 2026, [c1, c2, c3, c4]);


// 1. Título del álbum, año y cantidad de canciones
console.log(`${miAlbum.titulo} (${miAlbum.anio}) - ${miAlbum.cantidad()} canciones`);

// 2.  Numeracion de las canciones
miAlbum.canciones.forEach((cancion, index) => {
    console.log(`${index + 1}. (${cancion.formato()})`);
});

// 3. Duración total del álbum 
console.log(`Duración del álbum: ${formatoTiempo(miAlbum.duracionTotal()} segundos)`);