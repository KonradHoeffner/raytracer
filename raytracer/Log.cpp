export module Log;

import <fstream>;
import <string>;

using std::ofstream;
using std::string;
using std::endl;

string fileNameLogfile("logfile.txt"); 

ofstream logfile(fileNameLogfile.c_str());

ofstream& getLogfile()
{
	return logfile;
}

// Schreibt Inhalt einer Variablen ins Logfile
export void logVar(string message, double d)
{
	logfile << message << ": " << d << endl;
}

// Schreibt Inhalt einer Variablen ins Logfile
export void logVar(string message, int i)
{
	logfile << message << ": " << i << endl;
}

export void logVar(string message, bool b)
{
	logfile << message << ": ";
	logfile << (b?"wahr":"falsch"); 
	logfile << endl;
}

