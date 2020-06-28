#pragma once
#include "../../core/testing/module_test.h"
#include "../../core/testing/assert.h"
using namespace Core::Testing;

#include "../../core/logging/log_line.h"
#include "../../core/logging/log.h"
#include "../../core/logging/error.h"
#include "../../core/logging/info.h"
#include "../../core/logging/warn.h"
#include "../../core/logging/logger.h"
ModuleTest LoggingUnitTests = {
	"Logging",
	{
		new unit_equal("formating with qwerty symbols", []() {
			Core::Logging::log_line line("LABLE");
			const auto labl = line.lable;
			const auto left_sep = line.separator_left;
			const auto right_sep = line.separator_right;
			const auto log = "simple log";
			
			std::stringstream ss;
			ss << left_sep << labl << right_sep << log;
			return AssertEqual(line.Formating(log), ss.str());
		}),
		new unit_equal("formating with qwerty symbols and nums", []() {
			Core::Logging::log_line line("LABLE");
			const auto labl = line.lable;
			const auto left_sep = line.separator_left;
			const auto right_sep = line.separator_right;
			const auto log = "advanced log text\n 09731124\n sample log line";

			std::stringstream ss;
			ss << left_sep << labl << right_sep << log;
			return AssertEqual(line.Formating(log), ss.str());
		}),
		new unit_equal("formating with cyrillic symbols, qwerty symbols and nums", []() {
			Core::Logging::log_line line("LАвLЁ");
			const auto labl = line.lable;
			const auto left_sep = line.separator_left;
			const auto right_sep = line.separator_right;
			const auto text = "extended~advanced log text\n ёёё%^&@#%---09-731124\n\t\t sample log line";

			std::stringstream ss;
			ss << left_sep << labl << right_sep << text;
			return AssertEqual(line.Formating(text), ss.str());
		}),
		new unit_equal("logging the info line with only latin text", []() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto log = "Simple log";
			logger.Info(log);

			Core::Logging::Info i;
			return AssertEqual(out.str(), i.log(log));
		}),
		new unit_equal("logging the info line with ascii symbols", []() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto log = "Non-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap";
			logger.Info(log);

			Core::Logging::Info i;
			return AssertEqual(out.str(), i.log(log));
		}),
		new unit_equal("logging the info line with cyrillic symbols", []() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto log = "ЁЁёёёЁЁ простой лог:)()0))";
			logger.Info(log);

			Core::Logging::Info i;
			return AssertEqual(out.str(), i.log(log));
		}),
		new unit_equal("logging the two info line with cyrillic/latin symbols", []() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			auto log = "ЁЁёёёЁЁ простой лог:)()0))";
			logger.Info(log);
			Core::Logging::Info i;
			expected << i.log(log);
			log = "Non-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap";
			logger.Info(log);
			expected << i.log(log);

			return AssertEqual(out.str(), expected.str());
		}),
		new unit_equal("logging the several info lines with cyrillic/latin symbols", []() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			auto log = "ЁЁёёёЁЁ простой лог:)()0))";
			logger.Info(log);
			Core::Logging::Info i;
			expected << i.log(log);
			log = "Non-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap";
			logger.Info(log);
			expected << i.log(log);
			log = "Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends";
			logger.Info(log);
			expected << i.log(log);
			log = "После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду";
			logger.Info(log);
			expected << i.log(log);

			return AssertEqual(out.str(), expected.str());
		}),
		new unit_equal("logging the warning line with only latin text", []() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except = Exceptions::Core::access_denied("Simple log");
			logger.Warning(except);

			Core::Logging::Warn i;
			return AssertEqual(out.str(), i.log(except.log()));
		}),
		new unit_equal("logging the info warning with cyrillic symbols", []() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except = Exceptions::Core::invalid_argument("ЁЁёёёЁЁ простой лог:)()0))");
			logger.Warning(except);

			Core::Logging::Warn i;
			return AssertEqual(out.str(), i.log(except.log()));
		}),
		new unit_equal("logging the two warning line with cyrillic/latin symbols", []() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument("ЁЁёёёЁЁ простой лог:)()0))");
			logger.Warning(except1);
			Core::Logging::Warn i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument("on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Warning(except2);
			expected << i.log(except2.log());

			return AssertEqual(out.str(), expected.str());
		}),
		new unit_equal("logging the several warning lines with cyrillic/latin symbols", []() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument("ЁЁёёёЁЁ простой лог:)()0))");
			logger.Warning(except1);
			Core::Logging::Warn i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument("on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Warning(except2);
			expected << i.log(except2.log());
			const auto except3 = Exceptions::Core::invalid_argument("Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends");
			logger.Warning(except3);
			expected << i.log(except3.log());
			const auto except4 = Exceptions::Core::invalid_argument("После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду");
			logger.Warning(except4);
			expected << i.log(except4.log());

			return AssertEqual(out.str(), expected.str());
		}),
		new unit_equal("logging the several warning lines with cyrillic/latin symbols and custom stacktrace",  []() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument("ЁЁёёёЁЁ простой лог:)()0))", "Application :: Some custom stacktrace");
			logger.Warning(except1);
			Core::Logging::Warn i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument("on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Warning(except2);
			expected << i.log(except2.log());
			const auto except3 = Exceptions::Core::invalid_argument("Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends", "Application :: Custom stacktrace");
			logger.Warning(except3);
			expected << i.log(except3.log());
			const auto except4 = Exceptions::Core::invalid_argument("После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду");
			logger.Warning(except4);
			expected << i.log(except4.log());

			return AssertEqual(out.str(), expected.str());
		}),
		new unit_equal("logging the error line with only latin text", []() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except = Exceptions::Core::access_denied("Simple log");
			logger.Error(except);

			Core::Logging::Error i;
			return AssertEqual(out.str(), i.log(except.log()));
		}),
		new unit_equal("logging the info error with cyrillic symbols", []() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except = Exceptions::Core::invalid_argument("ЁЁёёёЁЁ простой лог:)()0))");
			logger.Error(except);

			Core::Logging::Error i;
			return AssertEqual(out.str(), i.log(except.log()));
		}),
		new unit_equal("logging the two error line with cyrillic/latin symbols", []() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument("ЁЁёёёЁЁ простой лог:)()0))");
			logger.Error(except1);
			Core::Logging::Error i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument("on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Error(except2);
			expected << i.log(except2.log());

			return AssertEqual(out.str(), expected.str());
		}),
		new unit_equal("logging the several error lines with cyrillic/latin symbols", []() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument("ЁЁёёёЁЁ простой лог:)()0))");
			logger.Error(except1);
			Core::Logging::Error i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument("on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Error(except2);
			expected << i.log(except2.log());
			const auto except3 = Exceptions::Core::invalid_argument("Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends");
			logger.Error(except3);
			expected << i.log(except3.log());
			const auto except4 = Exceptions::Core::invalid_argument("После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду");
			logger.Error(except4);
			expected << i.log(except4.log());

			return AssertEqual(out.str(), expected.str());
		}),
		new unit_equal("logging the several error lines with cyrillic/latin symbols and custom stacktrace", []() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument("ЁЁёёёЁЁ простой лог:)()0))", "Application :: Some custom stacktrace");
			logger.Error(except1);
			Core::Logging::Error i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument("on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Error(except2);
			expected << i.log(except2.log());
			const auto except3 = Exceptions::Core::invalid_argument("Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends", "Application :: Custom stacktrace");
			logger.Error(except3);
			expected << i.log(except3.log());
			const auto except4 = Exceptions::Core::invalid_argument("После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду");
			logger.Error(except4);
			expected << i.log(except4.log());

			return AssertEqual(out.str(), expected.str());
		})
	}
};
