#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <class T> 
class Singleton 
{ 
public: 
  static T& instance() 
  { 
	static T instance; 
	return instance; 
  } 
protected: 
	Singleton(); 
	~Singleton(); 
	Singleton(const Singleton &); 
	Singleton& operator=(const Singleton &); 
};

#endif 