#pragma once
#include <vector>
#include "RenderUtils.hpp"
using namespace std;
template <typename T>

class TemplatePool
{
private:
	const unsigned int DEFAULT_NUMB = 300;
protected:
	vector<T*> v;
public:
	TemplatePool() { for (int i = 0; i < DEFAULT_NUMB; i++) { T* aux = new T(new RenderItem()); v.push_back(aux); aux->setActive(false); } }; //crea un numero inicial por defecto
	TemplatePool(const unsigned int numInicial) { for (int i = 0; i < numInicial; i++) { T* aux = new T(new RenderItem()); v.push_back(aux); aux->setActive(false); } }; //crea un numero proporcionado 

	virtual ~TemplatePool() { for (T* it : v) { delete it; it = nullptr; } }; //destruye todos los elementos del vector

	const int size() { return v.size(); }; //size del vector
	
	T* getObject() { //devuelve un objeto inactivo de la pool o crea uno nuevo
		vector<T*>::iterator it = v.begin();

		bool found = false;
		T* aux = nullptr;

		while (it != v.end() && !found) { 
			if (!(*it)->isActive()) { //si encuentra uno inactivo, para el buvle y activa el objeto (flaga  true y lo registra como renderItem)
				aux = (*it);
				found = true;
				(*it)->setActive();
			}
			
			it++;
		}	

		if (!found) { //si no ha encontrado ninguno, crea uno nuevo y lo activa
			aux = new T(new RenderItem());
			v.push_back(aux);
			aux->setActive();
		}

		return aux;
	};

	T* generateObject(Vector3 pos, Vector3 vel, Vector3 ac, Vector3 color) {

		T* p = getObject();

		p->setPosition(pos);
		p->setColor(color);

		p->v = vel; //sets de velocidad y aceleracion
		p->a = ac;

		return p;
	};
};

