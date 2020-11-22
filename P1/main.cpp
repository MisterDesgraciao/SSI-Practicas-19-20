/*
Seguridad en Sistemas Informáticos. 3er curso. Universidad de La Laguna.
Práctica 1. Cifrado de Vernam.

Crear un programa que cifre un mensaje original usando la clave que se le de.
También incluir el proceso contrario: descifrar el mensaje usando la clave que se le otorgue.

Hecho por Óscar Ignacio Pozo Fernández.
correo: alu0101036526@ull.edu.es
Fecha: 10/02/2020
*/

#include <iostream>
#include <string>	//uso de strings
#include <bits/stdc++.h>	
#include <math.h>	//uso de pow
#include <stdlib.h>	//uso de rand

using namespace std;

//comprobamos cada letra del mensaje si es un 1 o 0.
bool isBinary(string msg) {
	int ln = msg.length();
	for (int i=0; i<ln; i++) {  //recorremos todo el mensaje
		if ( msg[i] != '1' && msg[i] != '0' ) {
			cout << "El mensaje no está en Binario!" << endl;
			return false;
		}
	}
	cout << "El mensaje está en Binario" << endl;
	return true;  //solo devuelve true si todo el mensaje está en binario
}

//convierte el numero entero a binario
string division(int num) {
		string aux = "";
		while (num > 0) {  //mientras el valor sea mayor que 0
			if (num % 2 == 0) {  //metemos el resto de dividir entre 2
				aux.push_back('0');
			}else{
				aux.push_back('1');
			}
			num /= 2;
		}

		while (aux.length() < 8) { //si la longitud no es 8 bits, añadimos 0 hasta que lo sea
			aux.push_back('0');
		}

		reverse(aux.begin(), aux.end() );  //le damos la vuelta al binario
		cout << aux << endl;
		return aux;
}

//convertir el string a binario
string toBinary(string mensaje) {
	
	int ln = mensaje.length();
	string binary = "";

	for (int i=0; i<ln; i++) {  //por cada letra del mensaje
		int num = int(mensaje[i]);
		string aux = "";
	
		aux = division(num);  //aux almacena el binario de cada letra 

		binary = binary + aux;  //y lo añadimos a la cadena final
	}
	return binary;
}

//convertir el binario en un string ASCII
string fromBinary(string msg) {
	//si no son 8*n bits no se puede convertir a ASCII
	if (msg.length() % 8 != 0) {
		cout << "No se puede convertir a ASCII un binario que no tenga un múltiplo 8 de en bits"  << endl;
		return msg;
	}else{
		cout << "Convertimos a ASCII: " << msg << endl;
		string mensaje = "";
		int num = 0;
		int loops = msg.length() / 8;
		cout << "Nº de bytes a convertir: " << loops << endl;

		for (int i=0; i<loops; i++) {  //por cada letra/byte
			int num = 0;
			for (int j=0+8*i; j<8*(i+1) ; j++) {  //comprobamos el bit de 8 en 8
				//cout << "Vuelta: " << j << endl;
				//cout << "Bit: " << msg[j] << endl;
				if (msg[j] == '1') {  
					int x = pow(2, j-8*i);
					num += 128 / x;  //si es 1, se suma el 2^n correspondiente
					//cout << num << endl;
				}
			}
			//cout << num << endl;
			char Letra = static_cast<char>(num);  //convertimos el nº a ASCII
			//cout << Letra << endl;
			mensaje.push_back(Letra);  //lo metemos en mensaje
		}
		return mensaje;
	}
}

//puertaXOR para cifrar/descifrar el mensaje
string puertaXOR(string msg, string key) {
	string mensaje = msg;
	string llave = key;
	string cifrado = "";
	int x = mensaje.length();

	for (int i=0; i<x; i++) {
		if (mensaje[i] == llave[i]) {  //si son iguales (0 y 0 ó 1 y 1)
			cifrado.push_back('0');
		}else{							//si son diferentes (0 y 1)
			cifrado.push_back('1');
		}
	}
	return cifrado;
}

//esta función cifra y descifra, pues ambas son la misma operación
string cifrar(string msg) {
	string codificado = "";
	int v1=0, aux=0, opt=0;
	string key = "";

	string binario = toBinary(msg);
	cout << binario << endl;

	cout << "\nElija como quiere generar la clave:\n1.Generar clave aleatoria\n2.Introducir una clave por teclado." << endl;
	cin >> opt;
	switch (opt) {
		case 1: 
			v1 = pow(2, binario.length() );
			cout << "Clave generada aleatoriamente: " << v1 << endl;
			aux = rand() % v1; 
			key = division(aux);
			cout << "Clave generada en binario: " << key << endl;
			break;
		case 2: 
			cout << "Introduzca la clave (aleatoria) de " << binario.length() << " caracteres binarios: " << endl;
			cin >> key;
			break;
	}

	if (key.length() != binario.length() ) {
		cout << "La clave no tiene la misma longitud que el mensaje a codificar." << endl;
		cout << "La clave debe ser de " << binario.length() << " caracteres binarios" << endl;	
	}else{
		if ( isBinary(binario) && isBinary(key) ) {
			codificado = puertaXOR(binario, key);	
		}else{
			cout << "Uno de los dos argumentos no es binario" << endl;
		}
	}
	return codificado;
}


int main() {
	string msg = "";
	string msg2 = "";
	string key = "";

	cout << "Introduzca el mensaje a codificar: " << endl;
	cin >> msg;
	
	//key = "001111000001100001110011";  //clave de la dispositiva

	string codedBi = cifrar(msg);
	cout << "El mensaje cifrado es: " << codedBi << endl;
	string coded = fromBinary(codedBi);
	cout << coded << endl;
	
	cout << "\nIntroduzca el mensaje a decodificar: " << endl;
	cin >> msg2;
	//key = "0000111100100001";	//clave de la diapositiva
	string decoded = cifrar(msg2);
	cout << "El mensaje descifrado es: " << decoded << endl;
	cout << fromBinary(decoded) << endl;
}
