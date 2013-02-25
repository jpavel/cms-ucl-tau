#include <iostream>
void run_filter_eventNumber()
{
	long n_evt=-1;
	std::string input="filelist.txt";
	std::string events="eventlist.txt";
	
	cout << "events: " << n_evt << endl;
	cout << "input files: " << input << endl;
	cout << "events: " << events << endl;
	
	
	gROOT->ProcessLine(" .L filter_eventNumber.C++ ");
	filter_eventNumber(input, events, n_evt);
	return;
}
