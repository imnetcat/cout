#pragma once
#include "../../src/core/config.h"
#ifdef INDEBUG
#include "../../src/core/testing/module_test.h"
#include "../../src/core/testing/assert.h"
using namespace Cout::Core::Testing;
#include <utility>
#include "../../src/core/exception.h"

ModuleTest ExceptionssUnitTests = {
	{
		new UnitTest([]() {
			const auto except = Cout::Exceptions::Core::invalid_argument(WHERE, "example exception");
			const Cout::Exceptions::base& except_interface = except;
			ASSERT_EQUAL(except_interface.what(), except.what());
		}),
		new UnitTest([]() {
			const auto except = Cout::Exceptions::Core::invalid_argument(WHERE, "example exception");
			const Cout::Exceptions::base& except_interface = except;
			ASSERT_EQUAL(except_interface.what(), except.what());
		}),
		new UnitTest([]() {
			const auto except = Cout::Exceptions::Core::invalid_argument(WHERE, "Обычное исключение написанное кирилицей ~~~ lable");
			const Cout::Exceptions::base& except_interface = except;
			ASSERT_EQUAL(except_interface.what(), except.what());
		}),
		new UnitTest([]() {
			const auto except = Cout::Exceptions::Core::invalid_argument(WHERE, "Обычное исключение написанное кирилицей ~~~ lable");
			const Cout::Exceptions::base& except_interface = except;
			ASSERT_EQUAL(except_interface.what(), except.what());
		})
	}
};
#endif
