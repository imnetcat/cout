#pragma once
#include "../../src/core/config.h"
#ifdef INDEBUG
#include "../../src/core/testing/module_test.h"
#include "../../src/core/testing/assert.h"
using namespace Core::Testing;

#include "../../src/core/logging/log_line.h"
#include "../../src/core/logging/log.h"
#include "../../src/core/logging/error.h"
#include "../../src/core/logging/info.h"
#include "../../src/core/logging/warn.h"
#include "../../src/core/logging/logger.h"
ModuleTest LoggingUnitTests = {
	{
		new UnitTest([]() {
			Core::Logging::log_line line("<LABLE>");
			const auto labl = line.lable;
			const auto log = "simple log";
			
			std::stringstream ss;
			ss << labl << " " << log;
			ASSERT_EQUAL(line.Formating(log), ss.str());
		}),
		new UnitTest([]() {
			Core::Logging::log_line line("<[LABLE]>");
			const auto labl = line.lable;
			const auto log = "advanced log text\n 09731124\n sample log line";

			std::stringstream ss;
			ss << labl << " " << log;
			ASSERT_EQUAL(line.Formating(log), ss.str());
		}),
		new UnitTest([]() {
			Core::Logging::log_line line("LАвLЁ");
			const auto labl = line.lable;
			const auto text = "extended~advanced log text\n ёёё%^&@#%---09-731124\n\t\t sample log line";

			std::stringstream ss;
			ss << labl << " " << text;
			ASSERT_EQUAL(line.Formating(text), ss.str());
		}),
		new UnitTest([]() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto log = "Simple log";
			logger.Info(log);

			Core::Logging::Info i;
			ASSERT_EQUAL(out.str(), i.log(log));
		}),
		new UnitTest([]() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto log = "Non-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap";
			logger.Info(log);

			Core::Logging::Info i;
			ASSERT_EQUAL(out.str(), i.log(log));
		}),
		new UnitTest([]() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto log = "ЁЁёёёЁЁ простой лог:)()0))";
			logger.Info(log);

			Core::Logging::Info i;
			ASSERT_EQUAL(out.str(), i.log(log));
		}),
		new UnitTest([]() {
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

			ASSERT_EQUAL(out.str(), expected.str());
		}),
		new UnitTest([]() {
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

			ASSERT_EQUAL(out.str(), expected.str());
		}),
		new UnitTest([]() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except = Exceptions::Core::access_denied(WHERE, "Simple log");
			logger.Warning(except);

			Core::Logging::Warn i;
			ASSERT_EQUAL(out.str(), i.log(except.log()));
		}),
		new UnitTest([]() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except = Exceptions::Core::invalid_argument(WHERE, "ЁЁёёёЁЁ простой лог:)()0))");
			logger.Warning(except);

			Core::Logging::Warn i;
			ASSERT_EQUAL(out.str(), i.log(except.log()));
		}),
		new UnitTest([]() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument(WHERE, "ЁЁёёёЁЁ простой лог:)()0))");
			logger.Warning(except1);
			Core::Logging::Warn i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument(WHERE, "on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Warning(except2);
			expected << i.log(except2.log());

			ASSERT_EQUAL(out.str(), expected.str());
		}),
		new UnitTest([]() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument(WHERE, "ЁЁёёёЁЁ простой лог:)()0))");
			logger.Warning(except1);
			Core::Logging::Warn i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument(WHERE, "on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Warning(except2);
			expected << i.log(except2.log());
			const auto except3 = Exceptions::Core::invalid_argument(WHERE, "Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends");
			logger.Warning(except3);
			expected << i.log(except3.log());
			const auto except4 = Exceptions::Core::invalid_argument(WHERE, "После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду");
			logger.Warning(except4);
			expected << i.log(except4.log());

			ASSERT_EQUAL(out.str(), expected.str());
		}),
		new UnitTest([]() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument(WHERE, "ЁЁёёёЁЁ простой лог:)()0))");
			logger.Warning(except1);
			Core::Logging::Warn i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument(WHERE, "on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Warning(except2);
			expected << i.log(except2.log());
			const auto except3 = Exceptions::Core::invalid_argument(WHERE, "Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends");
			logger.Warning(except3);
			expected << i.log(except3.log());
			const auto except4 = Exceptions::Core::invalid_argument(WHERE, "После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду");
			logger.Warning(except4);
			expected << i.log(except4.log());

			ASSERT_EQUAL(out.str(), expected.str());
		}),
		new UnitTest([]() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except = Exceptions::Core::access_denied(WHERE, "Simple log");
			logger.Error(except);

			Core::Logging::Error i;
			ASSERT_EQUAL(out.str(), i.log(except.log()));
		}),
		new UnitTest([]() {
			std::stringstream out;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except = Exceptions::Core::invalid_argument(WHERE, "ЁЁёёёЁЁ простой лог:)()0))");
			logger.Error(except);

			Core::Logging::Error i;
			ASSERT_EQUAL(out.str(), i.log(except.log()));
		}),
		new UnitTest([]() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument(WHERE, "ЁЁёёёЁЁ простой лог:)()0))");
			logger.Error(except1);
			Core::Logging::Error i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument(WHERE, "on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Error(except2);
			expected << i.log(except2.log());

			ASSERT_EQUAL(out.str(), expected.str());
		}),
		new UnitTest([]() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument(WHERE, "ЁЁёёёЁЁ простой лог:)()0))");
			logger.Error(except1);
			Core::Logging::Error i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument(WHERE, "on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Error(except2);
			expected << i.log(except2.log());
			const auto except3 = Exceptions::Core::invalid_argument(WHERE, "Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends");
			logger.Error(except3);
			expected << i.log(except3.log());
			const auto except4 = Exceptions::Core::invalid_argument(WHERE, "После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду");
			logger.Error(except4);
			expected << i.log(except4.log());

			ASSERT_EQUAL(out.str(), expected.str());
		}),
		new UnitTest([]() {
			std::stringstream out;
			std::stringstream expected;
			Core::Logging::Logger logger([&out](const std::string& log) {
				out << log;
			});
			const auto except1 = Exceptions::Core::invalid_argument(WHERE, "ЁЁёёёЁЁ простой лог:)()0))");
			logger.Error(except1);
			Core::Logging::Error i;
			expected << i.log(except1.log());
			const auto except2 = Exceptions::Core::invalid_argument(WHERE, "on-Simple logggg4679 -sfad 375=6 sdf$^2 25&&&&90!!)_(@_%(+ yeap");
			logger.Error(except2);
			expected << i.log(except2.log());
			const auto except3 = Exceptions::Core::invalid_argument(WHERE, "Once the server has sent the greeting (welcoming) message and the \n \
					client has received it, the client normally sends");
			logger.Error(except3);
			expected << i.log(except3.log());
			const auto except4 = Exceptions::Core::invalid_argument(WHERE, "После того, как сервер отправил приветственное(приветственное) сообщение и \n \
				клиент получил его, клиент обычно отправляет команду");
			logger.Error(except4);
			expected << i.log(except4.log());

			ASSERT_EQUAL(out.str(), expected.str());
		})
	}
};
#endif