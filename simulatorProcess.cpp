/* Nombres: 

	 Manuel Otiz - 2341245
	 Maycol Taquez - 2375000
	 Allan Paredes - 2340004
	    
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Def de los registros y la memoria
int ACC = 0; // Acumulador
int ICR = 0; // Instruction COunter Register
int MAR = 0; // Memory Address Register
int MDR = 0; // Memory Data REgister
string UC = "IDLE"; // Control Unit State
		    //
map<string, int> memory; // Memoria principal 
			 //
// Def de las funciones para las instrucciones SET, ADD,...
void SET(string addr, int value) {
	memory[addr] = value;
}

void LDR(string addr) {
	ACC = memory[addr];
}

void ADD(string addr1, string addr2 = "", string addr3 = "") {
	if (addr2.empty()) {
		ACC += memory[addr1];
	} else if (addr3.empty()) {
		ACC = memory[addr1] + memory[addr2];
	} else {
		memory[addr3] = memory[addr1] + memory[addr2];
	}
}

void INC(string addr) {
	memory[addr]++;
}

void DEC(string addr) {
	memory[addr]--;
}

void STR(string addr) {
	memory[addr] = ACC;
}

void SHW(string addr) {
	if (addr == "ACC") {
		cout << "Valor en ACC: " <<  ACC << endl;
	} else if (addr == "ICR") {
		cout << "Valor en ICR: " <<  ICR << endl;
	} else if (addr == "MAR") {
		cout << "Valor en MAR: " <<  MAR << endl;
	} else if (addr == "MDR") {
		cout << "Valor en MDR: " <<  MDR << endl;
	} else if (addr == "UC") {
		cout << "Estado de UC: " <<  UC << endl;
	} else {
		cout << "Valor en memoria " << addr << ": " <<  memory[addr] << endl;
	}
}

void PAUSE(){
}

void END() {
	// se finaliza la ejecucion
	return;
}

// cargar y ejecutar los programas
void executeProgram(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Error: No se pudo abrir el archivo " << filename << endl;
		return;
	}
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string instruction, addr1, addr2, addr3;
		int value;

		ss >> instruction >> addr1;

		cout << "Ejecutando: " <<instruction << " " << addr1 << " " << addr2 << " " << addr3 << " " << endl;

		if (instruction == "SET") {
			ss >> value;
			SET(addr1, value);
			cout << "SET " << addr1 << " = " << value << endl;
		} else if (instruction == "LDR") {
			LDR(addr1);
			cout << "LDR " << addr1 << " -> ACC = " << ACC << endl;
		} else if (instruction == "ADD") {
			ADD(addr1, addr2, addr3);
			cout << "ADD " << addr1 << " + " << addr2 << " -> " << addr3 << " = " << memory[addr3] << endl;
		} else if (instruction == "INC") {
			INC(addr1);
			cout << "INC " << addr1 << " = " << memory[addr1] << endl;
		} else if (instruction == "DEC") {
			DEC(addr1);
			cout << "DEC " << addr1 << " = " << memory[addr1] << endl; 
		} else if (instruction == "STR") {
			STR(addr1);
			cout << "STR ACC -> " << addr1 << " = " << memory[addr1] << endl;
		} else if (instruction == "SHW") {
			SHW(addr1);
		} else if (instruction == "PAUSE") {
			PAUSE();
		} else if (instruction == "END") {
			END();
		}

		ICR++;
	}
}

int main() {
	// Ejecucion de los programas
	cout << "------- Primer Programa ---------" << endl;
	executeProgram("programa1.txt");
	cout << "------- Segundo Programa ---------" << endl; 
	executeProgram("programa2.txt");
	cout << "------- Tercer Programa ---------" << endl;
	executeProgram("programa3.txt");

	return 0;
}
