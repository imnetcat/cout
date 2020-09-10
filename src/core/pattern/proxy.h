#pragma once
namespace Cout
{
	namespace Core
	{
		namespace Pattern
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
}