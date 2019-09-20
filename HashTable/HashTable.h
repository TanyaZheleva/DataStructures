#pragma once
#include <iostream>

template<class datatype, class keytype>
class Element
{
public:
	Element() = delete;
	Element(datatype) = delete;
	Element(datatype _data, keytype _key) :data(_data), key(_key) {};

	keytype getKey()const
	{
		return this->key;
	};
	datatype getData()const
	{
		return this->data;
	}
private:
	datatype data;
	keytype key;
};

template<class datatype, class keytype>
class HashMap
{
public:
	HashMap(unsigned _size);
	HashMap(const HashMap&) = delete;
	HashMap& operator=(const HashMap&) = delete;
	~HashMap();

	//hashing functions
	unsigned division(keytype _key);
	unsigned knutMultiplicative(keytype _key);
	unsigned aditiveHashing(keytype _key);
	unsigned doubleHashing(keytype _key);

	//basic operations with a hash map
	void put(Element<datatype, keytype>& _add);
	datatype get(keytype _findKey) const;
	void remove(keytype _key);

private:
	Element<datatype, keytype>** slots;
	unsigned size;
};

template<class datatype, class keytype>
inline HashMap<datatype, keytype>::HashMap(unsigned _size) :size(_size)
{
	slots = new Element<datatype, keytype>* [size];
	for (size_t i = 0; i < size; i++)
	{
		slots[i] = nullptr;
	}
}

template<class datatype, class keytype>
inline HashMap<datatype, keytype>::~HashMap()
{
	for (size_t i = 0; i < size; i++)
	{
		delete slots[i];
	}
	delete slots;
}

template<class datatype, class keytype>
inline unsigned HashMap<datatype, keytype>::division(keytype _key)
{
	return _key % size;
}

template<class datatype, class keytype>
inline unsigned HashMap<datatype, keytype>::knutMultiplicative(keytype _key)
{
	const double knut = 0.618033;
	double  newKey = double(_key * knut) - (int)(_key * knut);
	return (unsigned ) (size * newKey);

}

template<class datatype, class keytype>
inline unsigned HashMap<datatype, keytype>::aditiveHashing(keytype _key)
{
	if (std::is_same_v<keytype, char*>)
	{
		unsigned result = 0;
		int i = 0;
		while (_key[i] != '\0')
		{
			result += _key[i];
			i++;
		}
		return result % size;
	}
	else
	{
		std::cout << "Not possible to use this function on this keytype\n";
	}
}

template<class datatype, class keytype>
inline unsigned HashMap<datatype, keytype>::doubleHashing(keytype _key)
{
	unsigned newKey = division(_key);
	if (slots[newKey] != nullptr)
	{
	newKey = knutMultiplicative(newKey);
	}
	return newKey;
}

template<class datatype, class keytype>
inline void HashMap<datatype, keytype>::put(Element<datatype, keytype>& _add)
{
	keytype _index = _add.getKey();
	//add hashing function
	if (_index >= 0 && _index < size)
	{
		if (slots[_index] == nullptr)
			slots[_index] = new Element<datatype, keytype>(_add);
		else
			std::cout << "Collision\n";
	}
	else
	{
		std::cout << "Wrong key\n";
	}
}

template<class datatype, class keytype>
inline datatype HashMap<datatype, keytype>::get(keytype _findKey) const
{
	if (_findKey >=0 && _findKey < size)
	{
		return slots[_findKey]->getData();
	}
	else
	{
		std::cout << "No such key exist\n";
	}
}

template<class datatype, class keytype>
inline void HashMap<datatype, keytype>::remove(keytype _key)
{
	if (slots[_key] != nullptr)
	{
		slots[_key] = nullptr;
	}
}
