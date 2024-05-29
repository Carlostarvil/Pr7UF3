#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int FILAS = 10;
const int COLUMNAS = 6;

class Personaje {
public:
    int vida;
    int ataque;
    string nombre;
    int posicionX;
    int posicionY;

    // Constructor de la clase Personaje
    Personaje(int vida, int ataque, string nombre, int posX, int posY)
        : vida(vida), ataque(ataque), nombre(nombre), posicionX(posX), posicionY(posY) {}
};

class EnemigoFinal : public Personaje {
public:
    int superAtaque1;
    int superAtaque2;

    // Constructor de la clase EnemigoFinal
    EnemigoFinal(int vida, int ataque, string nombre, int posX, int posY, int superAtaque1, int superAtaque2)
        : Personaje(vida, ataque, nombre, posX, posY), superAtaque1(superAtaque1), superAtaque2(superAtaque2) {}
};

// Función para imprimir el nivel
void imprimirNivel(char crearNivel[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            cout << crearNivel[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para librar una batalla por turnos
bool batalla(Personaje& jugador, Personaje& enemigo) {
    while (jugador.vida > 0 && enemigo.vida > 0) {
        // Turno del enemigo
        int ataqueEnemigo = rand() % 3 + 1; 
        jugador.vida -= ataqueEnemigo;
        cout << "El enemigo te ataca infligiendo " << ataqueEnemigo << " de daño. Tu vida: " << jugador.vida << endl;

        if (jugador.vida <= 0) {
            cout << "¡Oh no! ¡El enemigo te ha derrotado! Game Over." << endl;
            return false;
        }

        // Turno del jugador
        enemigo.vida -= jugador.ataque;
        cout << "Atacas al enemigo infligiendo " << jugador.ataque << " de daño. Vida del enemigo: " << enemigo.vida << endl;

        if (enemigo.vida <= 0) {
            cout << "Has derrotado al enemigo!" << endl;
            return true;
        }
    }
    return false;
}

int main() {
    // Inicializar la semilla para la generación aleatoria
    srand(static_cast<unsigned int>(time(0)));

    // Bucle principal del juego
    while (true) {
        // Crear el nivel y colocar el jugador en la posición inicial
        char crearNivel[FILAS][COLUMNAS] = {};

        // Inicializar todas las casillas a Vacio
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                crearNivel[i][j] = '.';
            }
        }

        // Colocar la salida en una posición aleatoria de la última fila
        int columnaSalida = rand() % COLUMNAS;
        int filaSalida = FILAS - 1;
        crearNivel[filaSalida][columnaSalida] = 'S';

        // Colocar al jugador en la posición inicial
        Personaje jugador(20, 4, "Jugador", 0, 0);
        crearNivel[jugador.posicionX][jugador.posicionY] = 'X';

        // Colocar al enemigo final en la salida
        EnemigoFinal enemigoFinal(15, 7, "EnemigoFinal", filaSalida, columnaSalida, 10, 12);
        crearNivel[enemigoFinal.posicionX][enemigoFinal.posicionY] = 'F';

        // Colocar a los enemigos en posiciones aleatorias
        for (int k = 0; k < 2; ++k) {
            int filaEnemigo;
            int columnaEnemigo;
            do {
                filaEnemigo = rand() % FILAS;
                columnaEnemigo = rand() % COLUMNAS;
            } while (crearNivel[filaEnemigo][columnaEnemigo] != '.');

            crearNivel[filaEnemigo][columnaEnemigo] = 'E';
        }

        // Imprimir el nivel inicial
        imprimirNivel(crearNivel);
        cout << "¡Comienza el juego!" << endl;

        // Bucle para el movimiento del jugador
        while (true) {
            cout << "¿Hacia dónde quieres mover al jugador? (arriba/abajo/izquierda/derecha): ";
            string direccion;
            cin >> direccion;

            int nuevaPosX = jugador.posicionX;
            int nuevaPosY = jugador.posicionY;

            // Actualizar la posición del jugador según la dirección elegida, verificando los límites
            if (direccion == "arriba" && nuevaPosX > 0) {
                nuevaPosX--;
            }
            else if (direccion == "abajo" && nuevaPosX < FILAS - 1) {
                nuevaPosX++;
            }
            else if (direccion == "izquierda" && nuevaPosY > 0) {
                nuevaPosY--;
            }
            else if (direccion == "derecha" && nuevaPosY < COLUMNAS - 1) {
                nuevaPosY++;
            }
            else {
                cout << "Movimiento inválido. Inténtalo de nuevo." << endl;
                continue;
            }

            // Verificar si el jugador alcanzó la salida
            if (nuevaPosX == filaSalida && nuevaPosY == columnaSalida) {
                cout << "¡Has encontrado la salida! Ahora debes enfrentarte al enemigo final." << endl;
                if (batalla(jugador, enemigoFinal)) {
                    cout << "¡Felicidades! ¡Has derrotado al enemigo final y ganado el juego!" << endl;
                }
                else {
                    cout << "¡Oh no! ¡El enemigo final te ha derrotado! Game Over." << endl;
                }
                break; 
            }

            // Verificar si el jugador ha llegado a una casilla con enemigo
            if (crearNivel[nuevaPosX][nuevaPosY] == 'E' || crearNivel[nuevaPosX][nuevaPosY] == 'F') {
                cout << "¡Te has encontrado con un enemigo!" << endl;

                // Obtener la vida y el ataque del enemigo
                Personaje enemigo(5, 3, "Enemigo", nuevaPosX, nuevaPosY); 
                if (crearNivel[nuevaPosX][nuevaPosY] == 'F') {
                    enemigo.vida = enemigoFinal.vida;
                    enemigo.ataque = enemigoFinal.ataque;
                }

                // Iniciar la batalla con el enemigo encontrado
                if (!batalla(jugador, enemigo)) {
                    cout << "Game Over." << endl;
                    break;
                }

                // Si el jugador ganó la batalla, eliminar al enemigo del tablero
                if (crearNivel[nuevaPosX][nuevaPosY] == 'E') {
                    crearNivel[nuevaPosX][nuevaPosY] = '.';
                }
                else if (crearNivel[nuevaPosX][nuevaPosY] == 'F') {
                    crearNivel[nuevaPosX][nuevaPosY] = 'S'; // Cambia el enemigo final por la salida
                }
            }

            // Mover al jugador a la nueva posición
            crearNivel[jugador.posicionX][jugador.posicionY] = '.';
            jugador.posicionX = nuevaPosX;
            jugador.posicionY = nuevaPosY;
            crearNivel[jugador.posicionX][jugador.posicionY] = 'X';

           
            imprimirNivel(crearNivel);
        }

       
        cout << "¿Quieres jugar nuevamente? (s/n): ";
        char jugarNuevamente;
        cin >> jugarNuevamente;
        if (jugarNuevamente != 's' && jugarNuevamente != 'S') {
            break; 
        }
    }

    // Esperar a que el usuario presione Enter antes de salir
    cout << "Presiona Enter para salir...";
    cin.ignore(); 
    cin.get(); 

    return 0;
}