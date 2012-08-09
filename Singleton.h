#ifndef SINGLETON_H
#define SINGLETON_H

/**
 * An implementation of the Singleton design pattern. This allows us to use global instances of certain classes.
 * 
 * \tparam T the class to encapsulate.
 */
template <class T>
class Singleton
{
public:
	/**
	 * Create a new instance of a class.
	 * 
	 * \note this only works for classes that have constructors without any parameters.
	 */
	
	/**
	 * Destroy the encapsulated instance of the class.
	 */
	static void DestroyInstance()
	{
		delete instance;
	}
	
	/**
	 * Get the encapsulated instance of the class.
	 * 
	 * \return the encapsulated instance of the class.
	 */
	static T& GetInstance()
	{
		return *instance;
	}
	
	/**
	 * Set the instance of the class. This is useful when classes must be constructed manually.
	 * 
	 * \param newInstance the user-created instance of the class to be used.
	 */
	static void SetInstance(T* newInstance)
	{
		if( instance )
			DestroyInstance();
		
		instance = newInstance;
	}
	
private:
	Singleton() { }
	~Singleton() { }
	
	static T* instance;
};

template <class T>
T* Singleton<T>::instance = 0;

#endif // SINGLETON_H
