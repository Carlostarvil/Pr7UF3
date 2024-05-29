#pragma once

#include <iostream>
#include <string>
#include <cstdlib> // Para la generación de números aleatorios
#include <ctime>   // Para inicializar la semilla de generación aleatoria

using namespace std;

const int FILAS = 10;
const int COLUMNAS = 6;

class Casilla {
public:
    virtual ~Casilla() = default;
    virtual char mostrar() const = 0;
};

class Vacio : public Casilla {
public:
    char mostrar() const override;
};

class Personaje : public Casilla {
protected:
    int vida;
    int ataque;
    string nombre;
    int posicionX;
    int posicionY;

public:
    Personaje(int vida, int ataque, const string& nombre, int posicionX, int posicionY);

    int getVida() const;
    int getAtaque() const;
    string getNombre() const;
    int getPosicionX() const;
    int getPosicionY() const;

    void recibirDanio(int danio);
    void mover(int nuevaX, int nuevaY);
    virtual char mostrar() const override = 0;
};

class Jugador : public Personaje {
public:
    Jugador(int vida, int ataque, const string& nombre, int posicionX, int posicionY);

    char mostrar() const override;
};

class Enemigo : public Personaje {
public:
    Enemigo(int vida, int ataque, const string& nombre, int posicionX, int posicionY);

    char mostrar() const override;
    virtual int atacar() const;
};

class EnemigoFinal : public Enemigo {
public:
    EnemigoFinal(int vida, int ataque, const string& nombre, int posicionX, int posicionY);

    char mostrar() const override;
    int atacar() const override;
};

class Salida : public Casilla {
public:
    char mostrar() const override;
};

void imprimirNivel(Casilla* crearNivel[FILAS][COLUMNAS]);

bool batalla(Personaje& jugador, Personaje& enemigo);
