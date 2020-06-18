#pragma once
#ifndef _FACADE_H_
#define _FACADE_H_
namespace CORE
{
	namespace PATTERN
	{
		/*
			Facade class provides a simple interface for complex logic of one or
			several subsystems.Facade delegates customer requests to relevant
			objects within the subsystem.The facade is also responsible for managing their life
			cycle.All this protects the client from the unwanted complexity of the subsystem.
		*/
		template<class Component>
		class Facade
		{
		protected:
			Component *_component;

		public:
			Facade() : _component(new Component) { }
			Facade(Component *real_subject) : _component(real_subject) { }

			~Facade()
			{
				if(_component)
					delete _component;
			}
		};
	}
}
#endif