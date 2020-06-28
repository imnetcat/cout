#pragma once
#include "../../core/testing/module_test.h"
#include "../../core/testing/assert.h"
using namespace Core::Testing;
#include <utility>
#include "../../core/exception.h"

ModuleTest ExceptionssUnitTests = {
	"Exceptionss",
	{
		new unit_equal("exceptions interface", []() {
			const auto except = Exceptions::Core::invalid_argument("example exception");
			const Exceptions::base& except_interface = except;
			return AssertEqual(except_interface.what(), except.what());
		}),
		new unit_equal("exceptions interface log formating", []() {
			const auto except = Exceptions::Core::invalid_argument("example exception");
			const Exceptions::base& except_interface = except;
			return AssertEqual(except_interface.what(), except.what());
		}),
		new unit_equal("exceptions interface log formating with cyrillic/latin symbols", []() {
			const auto except = Exceptions::Core::invalid_argument("Обычное исключение написанное кирилицей ~~~ lable");
			const Exceptions::base& except_interface = except;
			return AssertEqual(except_interface.what(), except.what());
		}),
		new unit_equal("exceptions interface log formating with cyrillic/latin symbols and custom stacktrace", []() {
			const auto except = Exceptions::Core::invalid_argument("Обычное исключение написанное кирилицей ~~~ lable",
				"my custom stacktrace: exception there ok so");
			const Exceptions::base& except_interface = except;
			return AssertEqual(except_interface.what(), except.what());
		})
	}
};
