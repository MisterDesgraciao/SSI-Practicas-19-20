/*
Seguridad en Sistemas Informáticos. 3er curso. Universidad de La Laguna.
Práctica 3. Cifrado RC4.

Implementar el cifrado RC4. Debe ser válido para cualquier longitud de clave y texto original.

Hecho por: Óscar Ignacio Pozo Fernández
alu0101036526@ull.edu.es
*/

#include <iostream>

using namespace std;


int main() {

	for (int i=0; i<256; i++) {
		S[i] = i;
		K[i] = 
	}

	int j=0;
	for (int x=0; x<256; x++) {
		int aux = 0;
		j = (j + S[i] + K[i]) %255 /*mod 256*/;

		//intercambia S[i] y S[j]
		aux = S[i];
		S[i] = S[j];
		S[j] = aux;
	}
}

