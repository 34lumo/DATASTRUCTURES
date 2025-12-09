#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <unordered_map>
#include <set>

using namespace std;

struct AlumnoInfo {
	int nivel;
	//igual hay que añadir algo mas
};

class Academia {
	public:
		void nuevo_estudiante(string DNI, int nivel) {
			if (alumnos.count(DNI) > 0)
				throw std::domain_error("ALUMNO YA MATRICULADO");
			/* 
			if (alumnos.find(DNI) != alumnos.end())
				throw std::domain_error("ALUMNO YA MATRICULADO");
			*/
			if (nivel < 0 || nivel > 6) {
				throw std::domain_error("NIVEL ERRONEO");
			}
			//AÑADIR
			alumnos.insert({ DNI, {nivel } });
			//alumnos[DNI] = {nivel};
			cursos[nivel].push_front(DNI); //O(1)
		}

		void promocionar(string DNI) { //O(log(a))
			if (alumnos.find(DNI) != alumnos.end()) //O(1)
				throw std::domain_error("ALUMNO NO ENCONTRADO");
			if (alumnos[DNI].nivel > 6) {//O(1) tablas hash tienen coste constante
				throw std::domain_error("ALUMNO YA GRADUADO");
			}
			/*
			if (graduados.contains(DNI)) {//log(a) siendo a el nº de alumnos
				throw std::domain_error("ALUMNO YA GRADUADO");
			}
			*/
			if (alumnos[DNI].nivel == 6) {
				graduados.insert(DNI); //O(log(a))
			}
			//AÑADIR
			alumnos[DNI].nivel++; //O(1)
			cursos[alumnos[DNI].nivel].remove(DNI);
			alumnos[DNI].nivel++; //O(1)
			if (alumnos[DNI].nivel <= 6) 
				cursos[alumnos[DNI].nivel].push_front(DNI);
			//O(1) LO AÑADO AL NUEVO GRUPO
		}

		list<string> lista_graduados() {//O(n) respecto al numero de alumnos
			list<string> resultado; //doblemente enlazada
			for (string dni : graduados) {
				resultado.push_back(dni);
			}
			return resultado;
		}

		int grupo_alumno(string DNI) {
			if (alumnos.find(DNI) != alumnos.end()) //O(1)
				throw std::domain_error("ALUMNO NO ENCONTRADO");
			if (alumnos[DNI].nivel > 6) {//O(1) tablas hash tienen coste constante
				throw std::domain_error("ALUMNO YA GRADUADO");
			}

			return alumnos[DNI].nivel;
		}

		string novato(int curso) {
			if (curso < 0 || curso > 6) throw std::domain_error("GRUPO INCORRECTO");
			if (cursos[curso].empty()) throw std::domain_error("GRUPO VACIO");
			return cursos[curso].front();
		}

	private:
		//map<string, AlumnoInfo> alumnos;
		unordered_map<string, AlumnoInfo> alumnos;
		//siempre que no importe el orden uso unordered_map ya que los costes de sus funciones son menor

		set<string> graduados;

		unordered_map<int, list<string>> cursos;


	
};