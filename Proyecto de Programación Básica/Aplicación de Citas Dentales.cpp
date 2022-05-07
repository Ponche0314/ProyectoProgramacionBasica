#include <iostream>
#include <string>
#include <locale.h>
#include <iomanip>
#include <fstream>

using namespace std;

int opción = 0, prcUnit = 0, opciónTrat = 0, numCitaActual = 1, mod = 0, elim = 0;
bool opciónválida = true, inputIncorrecto = false;
char respuesta;

string nombrePacienteTemp, fechaCitaTemp, horaCitaTemp;
int tratElegidoTemp, cantTratTemp;

struct Cita {

	int cantTrat = 0, tratElegido = 0, numCita = 0;
	string nomCliente, fechaCita, horaCita;
	bool citaVigente = false;

	Cita* anterior = nullptr;
	Cita* siguiente = nullptr;

};

Cita* primerCita = nullptr;
Cita* últimaCita = nullptr;
Cita* citaAux = nullptr;

void registrarCita(string nomCliente, string fechaCita, string horaCita, int tratElegido, int cantTrat) {

	Cita* nuevaCita = new Cita;

	nuevaCita->numCita = numCitaActual;
	nuevaCita->nomCliente = nomCliente;
	nuevaCita->fechaCita = fechaCita;
	nuevaCita->horaCita = horaCita;
	nuevaCita->tratElegido = tratElegido;
	nuevaCita->cantTrat = cantTrat;
	nuevaCita->citaVigente = true;

	if (numCitaActual == 1) {
		primerCita = nuevaCita;
		últimaCita = nuevaCita;
	}
	else {
		nuevaCita->anterior = últimaCita;
		últimaCita->siguiente = nuevaCita;
		últimaCita = nuevaCita;
	}
	numCitaActual++;

}

void imprimirCitas() {

	citaAux = primerCita;

	if (!citaAux) {
		cout << "No hay citas registradas.\n";
	}
	else {

		while (citaAux) {
			cout << "Número de cita: " << setw(3) << setfill('0') << citaAux->numCita;
			cout << "\nNombre del paciente: " << citaAux->nomCliente;
			cout << "\nFecha de la cita: " << citaAux->fechaCita;
			cout << "\nHora de la cita: " << citaAux->horaCita;
			cout << "\nTratamiento elegido: ";

			switch (citaAux->tratElegido) {
			case 1: {
				prcUnit = 150;
				cout << "Diagnóstico dental.\n";
				cout << "Descripción del tratamiento: En odontología prevenir es curar. Un diagnóstico a tiempo te ayudará a evitar patologías dentales graves en el futuro.";
				break;
			}
			case 2: {
				prcUnit = 1500;
				cout << "Blanqueamiento dental.\n";
				cout << "Descripción del tratamiento: El blanqueamiento dental es uno de los tratamientos estéticos más seguros y eficaces, utilizado para aclarar los dientes de manera uniforme haciendo que tu dentadura se vea lo más blanca posible.";
				break;
			}
			case 3: {
				prcUnit = 800;
				cout << "Aplicación de coronas o carillas.\n";
				cout << "Descripción del tratamiento: Di adiós a los dientes dañados, opta por nuestras coronas de zirconia y carillas dentales.";
				break;
			}
			case 4: {
				prcUnit = 1800;
				cout << "Endodoncia.\n";
				cout << "Descripción del tratamiento: Una endodoncia consiste en la extracción de la pulpa, un pequeño tejido situado en el centro del diente, cuando este es removido, el espacio restante se limpia, remoldea y rellena.";
				break;
			}
			case 5: {
				prcUnit = 2000;
				cout << "Implantes dentales.\n";
				cout << "Descripción del tratamiento: Rediseñamos tu imagen y salud bucal con implantes dentales siendo la forma más natural de reponer un diente.";
				break;
			}
			case 6: {
				prcUnit = 1500;
				cout << "Ortodoncia.\n";
				cout << "Descripción del tratamiento: La ortodoncia se encarga de corregir la posición de los dientes tomando en cuenta la estructura facial, estética dental y la salud articular.";
				break;
			}
			case 7: {
				prcUnit = 150;
				cout << "Ajuste de brackets.\n";
				cout << "Descripción del tratamiento: Las sesiones de ajustes son necesarios para cambiar bandas elásticas desgastadas, comprobar cómo evoluciona la dentadura y efectuar correcciones en los alambres.";
				break;
			}
			}

			cout << "\nPrecio unitario del tratamiento: " << prcUnit << " pesos.";
			cout << "\nCantidad del tratamiento elegido: " << citaAux->cantTrat << ".";

			cout << "\nTotal: " << prcUnit * citaAux->cantTrat << " pesos.\n\n";

			citaAux = citaAux->siguiente;
		}
	}

}

void leerCitas() {
	ifstream leerCitas;
	leerCitas.open("Datos.txt");

	if (leerCitas.is_open()) {

		int conteo = 1;
		string linea;

		while (getline(leerCitas, linea)) {
			if (conteo == 1) {
				nombrePacienteTemp = linea;
				conteo++;
			}
			else if (conteo == 2) {
				fechaCitaTemp = linea;
				conteo++;
			}
			else if (conteo == 3) {
				horaCitaTemp = linea;
				conteo++;
			}
			else if (conteo == 4) {
				tratElegidoTemp = stoi(linea);
				conteo++;
			}
			else if (conteo == 5) {
				cantTratTemp = stoi(linea);
				registrarCita(nombrePacienteTemp, fechaCitaTemp, horaCitaTemp, tratElegidoTemp, cantTratTemp);
				conteo = 1;
			}
		}

		leerCitas.close();
	}
	else {
		cout << "Error al crear el archivo de guardado.\n\n";
	}


}

void guardarDatos() {

	ofstream guardarCitasTemp;
	guardarCitasTemp.open("Datos.txt");

	citaAux = primerCita;

	if (guardarCitasTemp.is_open()) {

		if (!citaAux) {
			guardarCitasTemp << "No hay citas registradas.\n";
		}
		else {
			while (citaAux) {
				guardarCitasTemp << citaAux->nomCliente << endl;
				guardarCitasTemp << citaAux->fechaCita << endl;
				guardarCitasTemp << citaAux->horaCita << endl;
				guardarCitasTemp << citaAux->tratElegido << endl;
				guardarCitasTemp << citaAux->cantTrat << endl;
				citaAux = citaAux->siguiente;
			}
		}

		guardarCitasTemp.close();
	}
	else {
		cout << "\nError al crear el archivo de guardado.\n";
	}

}

void guardarCitas() {

	ofstream guardarCitas;

	guardarCitas.open("Lista de Citas.txt");

	citaAux = primerCita;

	if (guardarCitas.is_open()) {

		if (!citaAux) {
			guardarCitas << "No hay citas registradas.\n";
		}
		else {
			while (citaAux) {
				guardarCitas << "Número de cita: " << setw(3) << setfill('0') << citaAux->numCita;
				guardarCitas << "\nNombre del paciente: " << citaAux->nomCliente;
				guardarCitas << "\nFecha de la cita: " << citaAux->fechaCita;
				guardarCitas << "\nHora de la cita: " << citaAux->horaCita;
				guardarCitas << "\nTratamiento elegido: ";

				switch (citaAux->tratElegido) {
				case 1: {
					prcUnit = 150;
					guardarCitas << "Diagnóstico dental.\n";
					guardarCitas << "Descripción del tratamiento: En odontología prevenir es curar. Un diagnóstico a tiempo te ayudará a evitar patologías dentales graves en el futuro.";
					break;
				}
				case 2: {
					prcUnit = 1500;
					guardarCitas << "Blanqueamiento dental.\n";
					guardarCitas << "Descripción del tratamiento: El blanqueamiento dental es uno de los tratamientos estéticos más seguros y eficaces, utilizado para aclarar los dientes de manera uniforme haciendo que tu dentadura se vea lo más blanca posible.";
					break;
				}
				case 3: {
					prcUnit = 800;
					guardarCitas << "Aplicación de coronas o carillas.\n";
					guardarCitas << "Descripción del tratamiento: Di adiós a los dientes dañados, opta por nuestras coronas de zirconia y carillas dentales.";
					break;
				}
				case 4: {
					prcUnit = 1800;
					guardarCitas << "Endodoncia.\n";
					guardarCitas << "Descripción del tratamiento: Una endodoncia consiste en la extracción de la pulpa, un pequeño tejido situado en el centro del diente, cuando este es removido, el espacio restante se limpia, remoldea y rellena.";
					break;
				}
				case 5: {
					prcUnit = 2000;
					guardarCitas << "Implantes dentales.\n";
					guardarCitas << "Descripción del tratamiento: Rediseñamos tu imagen y salud bucal con implantes dentales siendo la forma más natural de reponer un diente.";
					break;
				}
				case 6: {
					prcUnit = 1500;
					guardarCitas << "Ortodoncia.\n";
					guardarCitas << "Descripción del tratamiento: La ortodoncia se encarga de corregir la posición de los dientes tomando en cuenta la estructura facial, estética dental y la salud articular.";
					break;
				}
				case 7: {
					prcUnit = 150;
					guardarCitas << "Ajuste de brackets.\n";
					guardarCitas << "Descripción del tratamiento: Las sesiones de ajustes son necesarios para cambiar bandas elásticas desgastadas, comprobar cómo evoluciona la dentadura y efectuar correcciones en los alambres.";
					break;
				}
				}

				guardarCitas << "\nPrecio unitario del tratamiento: " << prcUnit << " pesos.";
				guardarCitas << "\nCantidad del tratamiento elegido: " << citaAux->cantTrat << ".";

				guardarCitas << "\nTotal: " << prcUnit * citaAux->cantTrat << " pesos.\n\n";

				citaAux = citaAux->siguiente;
			}
		}

		guardarCitas.close();

	}
	else {
		cout << "\nError al crear el archivo de guardado.\n";
	}

}


int main() {

	setlocale(LC_CTYPE, "Spanish");
	leerCitas();

	while (opción != 5) {
		cout << "Seleccione una de las siguientes opciones:\n\n";
		cout << "1. Agendar cita.\n";
		cout << "2. Modificar cita.\n";
		cout << "3. Eliminar cita.\n";
		cout << "4. Lista de citas vigentes.\n";
		cout << "5. Salir.\n\n";
		cout << "Digite una opción: ";
		cin >> opción;

		switch (opción) {
		case 1: {

			system("cls");

			cout << "Número de cita: " << setw(3) << setfill('0') << numCitaActual;
			cout << "\n\nIntroduzca el nombre del paciente: ";
			cin.ignore();
			getline(cin, nombrePacienteTemp);
			system("cls");


			cout << "//SELECCIÓN DE TRATAMIENTO//\n\n";
			cout << "1. Diagnóstico dental.\n";
			cout << "Descripción del tratamiento: En odontología prevenir es curar. Un diagnóstico a tiempo te ayudará a evitar patologías dentales graves en el futuro.\n";
			cout << "Precio unitario del tratamiento: 150 pesos.\n\n";

			cout << "2. Blanqueamiento dental.\n";
			cout << "Descripción del tratamiento: El blanqueamiento dental es uno de los tratamientos estéticos más seguros y eficaces, utilizado para aclarar los dientes de manera uniforme haciendo que tu dentadura se vea lo más blanca posible.\n";
			cout << "Precio unitario del tratamiento: 1500 pesos.\n\n";

			cout << "3. Aplicación de coronas o carillas.\n";
			cout << "Descripción del tratamiento: Di adiós a los dientes dañados, opta por nuestras coronas de zirconia y carillas dentales.\n";
			cout << "Precio unitario del tratamiento: 800 pesos.\n\n";

			cout << "4. Endodoncia.\n";
			cout << "Descripción del tratamiento: Una endodoncia consiste en la extracción de la pulpa, un pequeño tejido situado en el centro del diente, cuando este es removido, el espacio restante se limpia, remoldea y rellena.\n";
			cout << "Precio unitario del tratamiento: 1800 pesos.\n\n";

			cout << "5. Implantes dentales.\n";
			cout << "Descripción del tratamiento: Rediseñamos tu imagen y salud bucal con implantes dentales siendo la forma más natural de reponer un diente.\n";
			cout << "Precio unitario del tratamiento: 1800 pesos.\n\n";

			cout << "6. Ortodoncia.\n";
			cout << "Descripción del tratamiento: La ortodoncia se encarga de corregir la posición de los dientes tomando en cuenta la estructura facial, estética dental y la salud articular.\n";
			cout << "Precio unitario del tratamiento: 1500 pesos.\n\n";

			cout << "7. Ajuste de brackets.\n";
			cout << "Descripción del tratamiento: Las sesiones de ajustes son necesarios para cambiar bandas elásticas desgastadas, comprobar cómo evoluciona la dentadura y efectuar correcciones en los alambres.\n";
			cout << "Precio unitario del tratamiento: 150 pesos.\n\n";

			do {
				cout << "Elija un tratamiento: ";
				cin >> opciónTrat;

				switch (opciónTrat) {
				case 1: {
					prcUnit = 150;
					opciónválida = false;
					tratElegidoTemp = 1;
					break;
				}

				case 2: {
					prcUnit = 1500;
					opciónválida = false;
					tratElegidoTemp = 2;
					break;
				}

				case 3: {
					prcUnit = 800;
					opciónválida = false;
					tratElegidoTemp = 3;
					break;
				}

				case 4: {
					prcUnit = 1800;
					opciónválida = false;
					tratElegidoTemp = 4;
					break;
				}

				case 5: {
					prcUnit = 1800;
					opciónválida = false;
					tratElegidoTemp = 5;
					break;
				}

				case 6: {
					prcUnit = 1500;
					opciónválida = false;
					tratElegidoTemp = 6;
					break;
				}

				case 7: {
					prcUnit = 150;
					opciónválida = false;
					tratElegidoTemp = 7;
					break;
				}

				default: cout << "\nDigite una opción válida.";

				}
			} while (opciónválida);

			cout << "\nIngrese cantidad del tratamiento: ";
			cin >> cantTratTemp;

			cout << "\nTotal: " << prcUnit * cantTratTemp << " pesos.\n";

			system("pause");
			system("cls");

			cout << "Ingrese la fecha de la cita en formato dd/mm/aaaa (ej. 10/12/2022): ";
			cin >> fechaCitaTemp;

			cout << "\nIngrese la hora de la cita en formato 24 horas (ej. 14:30): ";
			cin >> horaCitaTemp;

			registrarCita(nombrePacienteTemp, fechaCitaTemp, horaCitaTemp, tratElegidoTemp, cantTratTemp);

			system("cls");

			cout << "Cita generada correctamente.\n";

			system("pause");
			system("cls");

			break;
		}

		case 2: {
			system("cls");

			Cita* citaAModificar = nullptr;

			citaAux = primerCita;

			if (!citaAux) {
				cout << "No hay citas registradas.\n";
				system("pause");
				cout << "\n";
			}
			else {

				cout << "La lista de citas vigentes son:\n";
				while (citaAux) {
					cout << setw(3) << setfill('0') << citaAux->numCita << "\n";
					citaAux = citaAux->siguiente;
				}

				cout << "\nIngrese el número de cita que desee modificar: ";
				cin >> mod;

				citaAux = primerCita;

				while (citaAux) {

					if (citaAux->numCita == mod) {
						citaAModificar = citaAux;
					}

					citaAux = citaAux->siguiente;
				}

				if (!citaAModificar) {
					inputIncorrecto = true;
				}

				if (inputIncorrecto) {
					cout << "\nIntroduza un número de cita de la lista proporcionada.\n";
					system("pause");
					cout << "\n";
				}
				else {
					cout << "\nElija qué dato de esa cita quiere modificar:\n\n";
					cout << "1. Nombre del paciente.\n";
					cout << "2. Fecha de la cita.\n";
					cout << "3. Hora de la cita.\n";
					cout << "4. Tratamiento elegido.\n";
					cout << "5. Cantidad del tratamiento elegido.\n\n";

					cout << "Digite una opción: ";
					cin >> opción;

					switch (opción) {

					case 1: {
						system("cls");

						cout << "Introduzca el nombre del paciente: ";
						cin.ignore();
						getline(cin, citaAModificar->nomCliente);
						break;
					}

					case 2: {
						system("cls");
						cout << "Ingrese la fecha de la cita en formato dd/mm/aaaa (ej. 10/12/2022): ";
						cin >> citaAModificar->fechaCita;
						break;
					}

					case 3: {
						system("cls");
						cout << "Ingrese la hora de la cita en formato 24 horas (ej. 14:30): ";
						cin >> citaAModificar->horaCita;
						break;
					}

					case 4: {
						system("cls");

						cout << "1. Diagnóstico dental.\n";
						cout << "Descripción del tratamiento: En odontología prevenir es curar. Un diagnóstico a tiempo te ayudará a evitar patologías dentales graves en el futuro.\n";
						cout << "Precio unitario del tratamiento: 150 pesos.\n\n";

						cout << "2. Blanqueamiento dental.\n";
						cout << "Descripción del tratamiento: El blanqueamiento dental es uno de los tratamientos estéticos más seguros y eficaces, utilizado para aclarar los dientes de manera uniforme haciendo que tu dentadura se vea lo más blanca posible.\n";
						cout << "Precio unitario del tratamiento: 1500 pesos.\n\n";

						cout << "3. Aplicación de coronas o carillas.\n";
						cout << "Descripción del tratamiento: Di adiós a los dientes dañados, opta por nuestras coronas de zirconia y carillas dentales.\n";
						cout << "Precio unitario del tratamiento: 800 pesos.\n\n";

						cout << "4. Endodoncia.\n";
						cout << "Descripción del tratamiento: Una endodoncia consiste en la extracción de la pulpa, un pequeño tejido situado en el centro del diente, cuando este es removido, el espacio restante se limpia, remoldea y rellena.\n";
						cout << "Precio unitario del tratamiento: 1800 pesos.\n\n";

						cout << "5. Implantes dentales.\n";
						cout << "Descripción del tratamiento: Rediseñamos tu imagen y salud bucal con implantes dentales siendo la forma más natural de reponer un diente.\n";
						cout << "Precio unitario del tratamiento: 1800 pesos.\n\n";

						cout << "6. Ortodoncia.\n";
						cout << "Descripción del tratamiento: La ortodoncia se encarga de corregir la posición de los dientes tomando en cuenta la estructura facial, estética dental y la salud articular.\n";
						cout << "Precio unitario del tratamiento: 1500 pesos.\n\n";

						cout << "7. Ajuste de brackets.\n";
						cout << "Descripción del tratamiento: Las sesiones de ajustes son necesarios para cambiar bandas elásticas desgastadas, comprobar cómo evoluciona la dentadura y efectuar correcciones en los alambres.\n";
						cout << "Precio unitario del tratamiento: 150 pesos.\n\n";

						do {
							cout << "Elija un tratamiento: ";
							cin >> opciónTrat;

							switch (opciónTrat) {
							case 1: {
								opciónválida = false;
								citaAModificar->tratElegido = 1;
								break;
							}

							case 2: {
								opciónválida = false;
								citaAModificar->tratElegido = 2;
								break;
							}

							case 3: {
								opciónválida = false;
								citaAModificar->tratElegido = 3;
								break;
							}

							case 4: {
								opciónválida = false;
								citaAModificar->tratElegido = 4;
								break;
							}

							case 5: {
								opciónválida = false;
								citaAModificar->tratElegido = 5;
								break;
							}

							case 6: {
								opciónválida = false;
								citaAModificar->tratElegido = 6;
								break;
							}

							case 7: {
								opciónválida = false;
								citaAModificar->tratElegido = 7;
								break;
							}

							default: cout << "\nDigite una opción válida.";

							}
						} while (opciónválida);

						break;
					}

					case 5: {
						system("cls");
						cout << "Ingrese cantidad del tratamiento: ";
						cin >> citaAModificar->cantTrat;
						break;
					}

					default:
						cout << "\nIngrese un dígito válido.";
						system("pause");
					}
				}
			}

			inputIncorrecto = false;
			system("cls");

			break;
		}

		case 3: {
			system("cls");

			Cita* citaAEliminar = nullptr;

			citaAux = primerCita;

			if (!citaAux) {
				cout << "No hay citas registradas.\n";
				system("pause");
				cout << "\n";
			}
			else {

				cout << "La lista de citas vigentes son:\n";
				while (citaAux) {
					cout << setw(3) << setfill('0') << citaAux->numCita << "\n";
					citaAux = citaAux->siguiente;
				}

				cout << "\nIngrese el número de cita que desea eliminar: ";
				cin >> elim;

				citaAux = primerCita;

				while (citaAux) {

					if (citaAux->numCita == elim) {
						citaAEliminar = citaAux;
					}

					citaAux = citaAux->siguiente;
				}

				if (!citaAEliminar) {
					inputIncorrecto = true;
				}

				if (inputIncorrecto) {
					cout << "\nIntroduza un número de cita de la lista proporcionada.\n";
					system("pause");
					cout << "\n";
				}
				else {

					if (citaAEliminar == primerCita) {

						if (citaAEliminar->siguiente) {
							primerCita = citaAEliminar->siguiente;
						}

					}
					else if (citaAEliminar == últimaCita) {

						if (citaAEliminar->anterior) {
							últimaCita = citaAEliminar->anterior;
							citaAEliminar->anterior->siguiente = NULL;
						}

					}
					else {

						citaAEliminar->anterior->siguiente = citaAEliminar->siguiente;
						citaAEliminar->siguiente->anterior = citaAEliminar->anterior;

					}

					if (citaAEliminar == primerCita && citaAEliminar == últimaCita) {

						citaAux = primerCita;

						while (citaAux) {

							if (citaAEliminar->numCita == citaAux->numCita) {
								citaAux = nullptr;
								primerCita = nullptr;
							}

							while (citaAux) {
								citaAux = citaAux->siguiente;
							}
						}

					}

					inputIncorrecto = false;
					delete citaAEliminar;

					system("cls");

					cout << "Cita eliminada correctamente.\n";

					system("pause");

					system("cls");
				}
			}

			break;
		}

		case 4: {
			system("cls");

			imprimirCitas();

			system("pause");
			system("cls");

			break;

		}

		default: cout << "\nDigite una opción válida.\n\n";
		}
	}

	system("cls");

	cout << "¡Gracias por utilizar el programa!\n";

	guardarDatos();
	guardarCitas();

	return 0;
}

