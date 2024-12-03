//PROYECTO FINAL UNIDAD 3
//GENERADOR DE CONTRASEÑAS SEGURAS
//INTEGRANTES:ALDAIR COYOLT OLIVEROS
//SUAREZ PUEYRREDON EVELYN SCARLETT, TUZ OVILLA BRYAN JOSUE
#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime> 
#include <regex>
using namespace std;


//declarando funciones principales
void gencontra();
void comprodefzdeco();
void genfracla();
void entropia();
string generarcontrasena(int longitud);
int evaluarfuerza(const string& password);
string calificarfuerza(int puntuacion);
void regreso();



int main() {
	int opcion;
	do{
		cout << "======================================" << endl;
		cout << "        Bienvenido al               " << endl;
		cout << "        generador de contrasenas  " << endl;
		cout << "======================================" << endl;
		cout << "Seleccione una opcion:" << endl;
		cout << "1. generador de contrasenas seguras" << endl;
		cout << "2. comprobador de fuerza de contrasena" << endl;
		cout << "3. Generador de frases clave" << endl;
		cout << "4.Medidor de entropia de contrasena " << endl;
		cout << "5.Salir" << endl; 
		cout << "======================================" << endl;
		cout << "Ingrese su opcion: ";
		cin >> opcion;

		if (cin.fail()) {
			cout << "\nError: Entrada no valida. Por favor, ingrese un nmero entero.\n" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue; 
		}
		
		switch(opcion) {
		case 1:
			gencontra();
			break;
		case 2:
			comprodefzdeco();
			break;
		case 3:
			genfracla();
			break;
		case 4:
			entropia();
			break;
		case 5:
			cout << "Gracias por usar nuestro servivio,Hasta luego\n"<< endl;
			break;
		default:
			cout << "\nOpcion no valida, Por favor intente de nuevo.\n" << endl;
		}

	} while (opcion != 5);
	return 0;
}

void gencontra() {
	cout << "\n======================================" << endl;
	cout << "      GENERADOR DE CONTRASENAS        " << endl;
	cout << "======================================\n" << endl;

	int longitud;
	cout << "Ingrese el tamano de la contrasena (entre 8 y 16): ";
	cin >> longitud;

	if (longitud < 8 || longitud > 16) {
		cout << "Error: La longitud debe estar entre 8 y 16 caracteres " << endl;
		return;
	}

	string contrasena = generarcontrasena(longitud);
	cout << "La contrasena generada es: " << contrasena << endl;
	regreso();
}


string generarcontrasena(int longitud) {
	const string minusculas = "abcdefghijklmnopqrstuvwxyz";
	const string mayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const string numeros = "0123456789";
	const string simbolos = "!@#$%^&*()-_=+[]{}|;:,.<>?/";
	string conjuntoCaracteres = minusculas + mayusculas + numeros + simbolos;
	string contrasena;

	
	srand(static_cast<unsigned int>(time(0)));


	for (int i = 0; i < longitud; i++) {
		int indiceAleatorio = rand() % conjuntoCaracteres.length();
		contrasena += conjuntoCaracteres[indiceAleatorio];
	}
	return contrasena;

}

void comprodefzdeco() {
	cout << "\n\n=================================================" << endl;
	cout << "BIENVINIDO AL COMPROBADOR DE FUERZA DE CONTRASENA" << endl;
	cout << "=================================================\n" << endl;

	string password;
	cout << "Introducir contrasena:";
	cin >> password;

	int fuerza = evaluarfuerza(password);
	string clasificacion = calificarfuerza(fuerza);

	cout << "\nfuerza de la contrasena: " << clasificacion << endl;
	regreso();
}
	
int evaluarfuerza(const string& password) {
	int puntuacion = 0;

	if (password.length() >= 8) puntuacion++;

	if (regex_search(password, regex("[a-z]"))) puntuacion++;

	if (regex_search(password, regex("[A-Z]"))) puntuacion++;

	if (regex_search(password, regex("[0-9]"))) puntuacion++;

	if (regex_search(password, regex("[^a-zA-Z0-9]"))) puntuacion++;

	if (regex_search(password, regex("[!@#$%^&*()_+{}|:?><?]"))) puntuacion++;
	return puntuacion;

}
	string calificarfuerza(int puntuacion) {
		if (puntuacion <= 2) return "debil";
		if (puntuacion == 3)return "moderado";
		return "Fuerte";
	}




void genfracla() {
	cout << "\n======================================" << endl;
	cout << "GENERADOR DE FRASES CLAVE" << endl;
	cout << "======================================" << endl;
	
	int opcion;
	cout << "Seleccione una opcion:" << endl;
	cout << "1. Generar frase clave desde palabras dadas" << endl;
	cout << "2. Generar frase clave aleatoria" << endl;
	cout << "Ingrese su opcion: ";
	cin >> opcion;

	if (opcion == 1) {
		cin.ignore(); // Limpiar el buffer de entrada
		string palabras;
		cout << "Ingrese varias palabras separadas por espacios: ";
		getline(cin, palabras);

		
		string fraseClave = palabras;
		regex e("a|e|i|o|u");
		fraseClave = regex_replace(fraseClave, e, "*"); 
		cout << "Frase clave generada: " << fraseClave << endl;
	}
	else if (opcion == 2) {
		const string palabrasAleatorias[] = {
			"sol", "luna", "estrella", "nube", "rio", "mar",
			"montana", "bosque", "fuego", "viento", "trueno"
		};
		srand(static_cast<unsigned int>(time(0)));
		string fraseClave;

		
		for (int i = 0; i < 4; ++i) {
			if (i > 0) fraseClave += "-"; 
			fraseClave += palabrasAleatorias[rand() % 11];
		}

		cout << "Frase clave generada aleatoriamente: " << fraseClave << endl;
	}
	else {
		cout << "Opcion invalida. Por favor intente de nuevo." << endl;
	}

	regreso();
}
	



void entropia() {
	cout << "\n======================================" << endl;
	cout << "      MEDIDOR DE ENTROPIA             " << endl;
	cout << "======================================\n" << endl;

	string password;
	cout << "Introduce la contrasena para medir su entropia: ";
	cin >> password;

	int n = 0;
	if (regex_search(password, regex("[a-z]"))) n += 26;  // Minúsculas
	if (regex_search(password, regex("[A-Z]"))) n += 26;  // Mayúsculas
	if (regex_search(password, regex("[0-9]"))) n += 10;  // Dígitos
	if (regex_search(password, regex("[^a-zA-Z0-9]"))) n += 32;  // Símbolos

	double entropia = password.length() * log2(n);

	cout << "La entropia de la contrasena es: " << entropia << " bits" << endl;
	regreso();
}


void regreso() {
	cout << "\nPresiona Enter para continuar...";
	cin.ignore();
	cin.get();
	system("cls");
}


