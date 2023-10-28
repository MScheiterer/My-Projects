#pragma once

#include "vertagt_aktion - Vorlage.h"
#include <list>
#include <memory>

namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktor
		VListe() = default; //%%%%%%%%%% Mein Code %%%%%%%%%%

		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear() //%%%%%%%%%% Mein Code %%%%%%%%%%
		{
			vAktualisieren();
			p_objekte.clear();
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end(); //%%%%%%%%%% Mein Code %%%%%%%%%%
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			return p_objekte.end(); //%%%%%%%%%% Mein Code %%%%%%%%%%
		}
		bool empty() const
		{
			return p_objekte.empty(); //%%%%%%%%%% Mein Code %%%%%%%%%%
		}

		// Schreibfunktionen
		void push_back(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			unique_ptr<VPushBack<T>> temp = make_unique<VPushBack<T>>(p_objekte, move(obj)); //moving obj necessary if T is type unique_ptr
			p_aktionen.push_back(move(temp)); //%%%%%%%%%% Mein Code %%%%%%%%%%
		}

		void push_front(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			unique_ptr<VPushFront<T>> temp = make_unique<VPushFront<T>>(p_objekte, move(obj)); //moving obj necessary if T is type unique_ptr
			p_aktionen.push_back(move(temp)); //%%%%%%%%%% Mein Code %%%%%%%%%%
		}

		void erase(iterator it)
		{
			// Aktionselement für PushBack auf Liste erzeugen (hier Iterator statt Objekt !)
			unique_ptr<VErase<T>> temp = make_unique<VErase<T>>(p_objekte, it);
			p_aktionen.push_back(move(temp)); //%%%%%%%%%% Mein Code %%%%%%%%%%
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			// Änderungen auf Objektliste übertragen
			for (auto& pAktion : p_aktionen)
			{
				// Aktion ausführen
				pAktion->vAusfuehren(); //%%%%%%%%%% Mein Code %%%%%%%%%%
			}
			// Aktionsliste löschen
			p_aktionen.clear(); //%%%%%%%%%% Mein Code %%%%%%%%%%%

		}

		int size()
		{
			return p_objekte.size();
		}
	};
} // namespace vertagt
