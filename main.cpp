#include <iostream>

using namespace std;

enum Direccion {Norte, Sur, Este, Oeste};

class LugarDelMapa

{

    public:

        virtual void Entrar()=0;

};

class Habitacion : public LugarDelMapa

{

    private:

        LugarDelMapa*    _lados[4];

        int                _numeroHabitacion;

    public:

        Habitacion(int numHabitacion){}

        LugarDelMapa* ObtenerLado(Direccion) const{}

        void EstablecerLado(Direccion, LugarDelMapa*){}

        virtual void Entrar(){}

};

class Pared : public LugarDelMapa

{

    public:

        Pared(){}

        virtual void Entrar(){}

};

class Puerta : public LugarDelMapa

{

    private:

        Habitacion* _habitacion1;

        Habitacion* _habitacion2;

        bool        _estaAbierta;

    public:

        Puerta(Habitacion* =0, Habitacion* =0){}

        virtual void Entrar(){}

        Habitacion* OtroLadoDe(Habitacion*){}

};

class Laberinto

{

    private:

        //...

    public:

        Laberinto(){}

        void AnadirHabitacion(Habitacion*){}

        Habitacion* NumeroDeHabitacion(int) const{}

        void operacion(){cout<<"Una operacion del laberinto\n";}

};

class Hechizo{};

class HabitacionEncantada : public Habitacion

{

    public:

        HabitacionEncantada(int numHabitacion,Hechizo*):Habitacion(numHabitacion){}

};

class PuertaQueNecesitaHechizo : public Puerta

{

    public:

        PuertaQueNecesitaHechizo(Habitacion* h1, Habitacion* h2):Puerta(h1,h2){}

};

class JuegoDelLaberinto

{

    public:

        Laberinto* CrearLaberinto();

        virtual Laberinto* FabricarLaberinto() const {return new Laberinto;}

        virtual Habitacion* FabricarHabitacion(int n) const {return new Habitacion(n);}

        virtual Pared* FabricarPared() const {return new Pared;}

        virtual Puerta* FabricarPuerta(Habitacion* h1, Habitacion* h2) const {return new Puerta(h1,h2);}

};

Laberinto* JuegoDelLaberinto::CrearLaberinto()

{

    Laberinto* unLaberinto    = FabricarLaberinto();

    Habitacion* h1            = FabricarHabitacion(1);

    Habitacion* h2            = FabricarHabitacion(2);

    Puerta* unaPuerta        = FabricarPuerta(h1, h2);

    unLaberinto->AnadirHabitacion(h1);

    unLaberinto->AnadirHabitacion(h2);

    h1->EstablecerLado(Norte, FabricarPared());

    h1->EstablecerLado(Este, unaPuerta);

    h1->EstablecerLado(Sur, FabricarPared());

    h1->EstablecerLado(Oeste, FabricarPared());

    h1->EstablecerLado(Norte, FabricarPared());

    h1->EstablecerLado(Este, FabricarPared());

    h1->EstablecerLado(Sur, FabricarPared());

    h1->EstablecerLado(Oeste, unaPuerta);

    return unLaberinto;

}

/*

Juegos diferentes pueden heredar de JuegoDelLaberinto para especializar partes del laberinto. Las sublcases de JuegoDelLaberinto

pueden redefinir algunos de los métodos de fabricación o todos para especificar variantes de los productos. Por ejemplo:

JuegoDelLaberintoEncantado puede redefinir los porductos Habitacion y Puerta para devolver sus variantes Encantadas.

*/

class JuegoDelLaberintoEncantado : public JuegoDelLaberinto

{

    protected:

        Hechizo* Hechizar() const{return new Hechizo;}

    public:

        JuegoDelLaberintoEncantado(){}

        virtual Habitacion* FabricarHabitacion(int n) const {return new HabitacionEncantada(n, Hechizar());}

        virtual Puerta* FabricarPuerta(Habitacion* h1, Habitacion* h2) const {return new PuertaQueNecesitaHechizo(h1,h2);}

};

void main()

{

    JuegoDelLaberinto* juego;

    juego = new JuegoDelLaberintoEncantado();

    Laberinto* unLaberinto = juego->CrearLaberinto();

    unLaberinto->operacion();

    cin.get();

}
