#include "base.h"
using namespace std;
using namespace Cout;

Exceptions::base::base(const std::exception& ex) : _when(ex.what()) {}
Exceptions::base::base(const string en, const string ere)
	: _when(en), _where(ere) { };


const string Cout::Exceptions::base::log() const noexcept
{
	string log;
//#ifdef INDEBUG
	log += "\twhat  : " + what() + "\n";
	log += "\twhen  : " + _when + "\n";
	log += "\twhere : " + _where + "\n";
//#else
	//log = id();
	//log += _where;
//#endif
	return log;
}

const string Cout::Exceptions::base::log(const std::string& when_preppend, const std::string& where_preppend) const noexcept
{
	string log;
//#ifdef INDEBUG
	log += "\twhat  : " + what() + "\n";
	log += "\twhen  : " + when_preppend + "\n\t\t" + _when + "\n";
	log += "\twhere : " + where_preppend + "\n\t\t" + _where + "\n";
//#else
	//log = id();
	//log += _where;
//#endif
	return log;
}
