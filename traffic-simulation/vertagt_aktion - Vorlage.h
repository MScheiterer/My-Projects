#pragma once

#include <list>

namespace vertagt
{
	// Oberklasse VAktion
	template <class T>
	class VAktion
	{
	protected:
		std::list<T>& p_pListe;  // Zeiger auf Liste der Objekte

	public:
	    //%%%%%%%%%% Standard Konstruktor gelöscht %%%%%%%%%%
		VAktion(std::list<T>& ptListe) : p_pListe(ptListe){}
		virtual ~VAktion() = default;
		virtual void vAusfuehren() = 0;
	};

	// PushBack
	template <class T>
	class VPushBack : public VAktion<T>
	{
	private:
		T p_objekt;

	public:
	    //%%%%%%%%%% Standard Konstruktor gelöscht %%%%%%%%%%
		VPushBack(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj))	{}
		virtual ~VPushBack() = default;
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.push_back(std::move(p_objekt));
		}
	};


	// PushFront
	//%%%%%%%%%% Mein Code %%%%%%%%%%
	template <class T>
	class VPushFront : public VAktion<T>
	{
	private:
		T p_objekt;

	public:
		VPushFront(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj)) {}
		virtual ~VPushFront() = default;

		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.push_front(std::move(p_objekt));
		}
	};
	//%%%%%%%%%% Ende mein Code %%%%%%%%%%

	// Erase
	template <class T>
	class VErase : public VAktion<T>
	{
	public:
		using iterator = typename std::list<T>::iterator;

	private:
		iterator p_it;  // bei erase Iterator speichern

	public:
		//%%%%%%%%%% Standard Konstruktor gelöscht %%%%%%%%%%
		VErase(std::list<T>& liste, iterator it) : VAktion<T>(liste), p_it(it) {} //%%%%%%%%%% Mein Code %%%%%%%%%%
		virtual ~VErase() = default;
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.erase(p_it); //%%%%%%%%%% Mein Code %%%%%%%%%%
		}
	};
}  // namespace vertagt
