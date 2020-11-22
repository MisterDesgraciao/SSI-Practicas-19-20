/*
Seguridad en Sistemas Informáticos. 3er curso. Universidad de La Laguna.
Práctica 2. Cifrado de Vigenere.

Implementa el cifrado y descifrado de Vigenere según la descripción que se incluye a continuación:
Se usará el alfabeto sin Ñ, con W y sin espacios, luego el módulo para las operaciones será m=26.
El cifrado opera sobre bloques de letras, y la clave es una palabra o frase que se repite cuantas veces sea necesario.

Hecho por Óscar Ignacio Pozo Fernández.
correo: alu0101036526@ull.edu.es
Fecha: 18/02/2020
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//transforma el mensaje a Mayúsculas
string mayusculas(string key) {
	string ajustar = "";
	for (int i=0; i<key.size(); i++) {
		//ASCII Alphabet Characters van del 65 hasta el 122 (A-z)
		if (static_cast<unsigned char>(key[i]) > 64 &&  static_cast<unsigned char>(key[i]) < 123) {
			ajustar = ajustar + key[i];
		}
	}
	//tras eliminar los espacios y las letras no ASCII, transforma el resto a mayúsculas.
	transform(ajustar.begin(), ajustar.end(), ajustar.begin(), ::toupper);
	cout << ajustar << endl;
	return ajustar;
}

string cifrado(string mensaje, string clave, bool Signo) {
	string aux, msg, key;
	msg = mayusculas(mensaje);
	key = mayusculas(clave);	
	int val, j = 0;
	char Letra;	

	for (int i=0; i<msg.size(); i++) {
		if (j >= key.size())
			j = 0;

		if (Signo == true) {
			int C1 = static_cast<unsigned char>(msg[i]);
			int C2 = static_cast<unsigned char>(key[j])-65;
			//cout << C1 << " + " << C2 << endl;
			val = C1 + C2;
			if (val > 90)
				val = val - 26;
		}else if(Signo == false){
			int C1 = static_cast<unsigned char>(msg[i]);
			int C2 = static_cast<unsigned char>(key[j])-65;
			//cout << C1 << " - " << C2 << endl;
			val = C1 - C2;
			if (val < 65)
				val = val + 26;
		}
		//cout << val << endl;
		Letra = static_cast<char>(val);
		aux.push_back(Letra);
		j++;
	}
	return aux;
}


int main() {
	string mensaje = "";
	string clave = "";
	string coded = "";
	string decoded = "";

	cout << "Introduzca el mensaje a cifrar: " << endl;
	getline(cin, mensaje, '\n');
	
	cout << "--------------------" << endl;
		
	cout << "Introduzca la palabra clave: " << endl;
	getline(cin, clave, '\n');
	
	coded = cifrado(mensaje, clave, true);
	cout << '\n' << coded << endl;
	cout << "---------------" << endl;
	decoded = cifrado(coded, clave, false);
	cout << '\n' << decoded << endl;
}
