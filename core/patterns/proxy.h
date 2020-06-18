#pragma once
#ifndef _PROXY_H_
#define _PROXY_H_
namespace CORE
{
	namespace PATTERN
	{
		/*
			A proxy allows you to intercept
			calls to a wrapped object.
		*/
		template<class Component>
		class Proxy : public Component 
		{
		private:
			Component *_component;

		public:
			Proxy() : _component(new Component) { }
			Proxy(Component *real_subject) : _component(real_subject) { }

			~Proxy() 
			{
				delete _component;
			}
		};
	}
}
#endif