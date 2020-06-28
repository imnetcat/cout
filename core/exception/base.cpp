#include "base.h"
using namespace std;

Core::Exception::base::base(const std::exception& ex) : _when(ex.what()) {}
Core::Exception::base::base(const string w) : _when(w) { };
Core::Exception::base::base(const string en, const string ere)
	: _when(en), _where(ere) { };


const string Core::Exception::base::log() const noexcept
{
	string log;
	log += "\twhat  : " + string(what()) + "\n";
	log += "\twhen  : " + _when + "\n";
	log += "\twhere : " + _where + "\n";
	return log;
}

const string Core::Exception::base::log(const std::string& when_preppend, const std::string& where_preppend) const noexcept
{
	string log;
	log += "\twhat  : " + string(what()) + "\n";
	log += "\twhen  : " + when_preppend + "\n\t\t" + _when + "\n";
	log += "\twhere : " + where_preppend + "\n\t\t" + _where + "\n";
	return log;
}