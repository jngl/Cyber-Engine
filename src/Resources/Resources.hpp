#pragma once

#include <string>

namespace Resources
{
	void createResources();
    void destroyResources();
	
	template<class T>
	class Resource
	{
	public:
		T& operator*();
		T* operator->();
	};
	
	template<class ResourceTypeDef>
	class ResourceManager
	{
	public:
		typedef typename ResourceTypeDef::ResourceType ResourceType;
		
		static Resource<ResourceType> get(std::string name);
	}
};
