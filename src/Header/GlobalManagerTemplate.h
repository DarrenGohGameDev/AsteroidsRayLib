#pragma once
#include <stdexcept>
#include <string>
#include <typeinfo>

template<typename T>

class GlobalManagerTemplate
{
	public:
		static T* instance;

		GlobalManagerTemplate()
		{
			if (instance)
			{
				throw std::runtime_error(
					std::string("Duplicate manager created : ") + typeid(T).name()
				);
			}
			instance = static_cast<T*>(this);
		}

		virtual ~GlobalManagerTemplate()
		{
			instance = nullptr;
		}

		static T& Get()
		{
			static T instance;
			return instance;
		}
};

template<typename T>
T* GlobalManagerTemplate<T>::instance = nullptr;

