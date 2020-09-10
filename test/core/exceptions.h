#pragma once
#include "../../core/config.h"
#ifdef INDEBUG
#include "../../core/testing/module_test.h"
#include "../../core/testing/assert.h"
using namespace Core::Testing;
#include <utility>
#include "../../core/exception.h"

ModuleTest ExceptionssUnitTests = {
	{
		new UnitTest([]() {
			const auto except = Exceptions::Core::invalid_argument(WHERE, "example exception");
			const Exceptions::base& except_interface = except;
			ASSERT_EQUAL(except_interface.what(), except.what());
		}),
		new UnitTest([]() {
			const auto except = Exceptions::Core::invalid_argument(WHERE, "example exception");
			const Exceptions::base& except_interface = except;
			ASSERT_EQUAL(except_interface.what(), except.what());
		}),
		new UnitTest([]() {
			const auto except = Exceptions::Core::invalid_argument(WHERE, "Обычное исключение написанное кирилицей ~~~ lable");
			const Exceptions::base& except_interface = except;
			ASSERT_EQUAL(except_interface.what(), except.what());
		}),
		new UnitTest([]() {
			const auto except = Exceptions::Core::invalid_argument(WHERE, "Обычное исключение написанное кирилицей ~~~ lable");
			const Exceptions::base& except_interface = except;
			ASSERT_EQUAL(except_interface.what(), except.what());
		})
	}
};
#endif
