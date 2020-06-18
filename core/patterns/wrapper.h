#pragma once
#ifndef _WRAPPER_H_
#define _WRAPPER_H_
namespace CORE
{
	namespace PATTERN
	{
		/*
			The Decorator (Wrapper) base class follows the same interface as the other components.
			The main purpose of this class is to define a wrapper interface for all specific
			decorators.The default wrapper code implementation may include a field
			for storing the wrapped component and its initialization.
		*/
		template<class Component>
		class Wrapper : public Component
		{
		protected:
			Component *_component;

		public:
			Wrapper(Component *real_subject) : _component(real_subject) { }

			~Wrapper()
			{
				delete _component;
			}
		};
	}
}
#endif