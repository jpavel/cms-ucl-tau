// Dear emacs, this is -*- c++ -*-
// $Id$
#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

// Add the declarations of your cycles, and any other classes for which you
// want to generate a dictionary, here. The usual format is:
//
// #pragma link C++ class MySuperClass+;

#pragma link C++ class Analysis+;
#pragma link C++ class myevent+;
#pragma link C++ class myobject+;
#pragma link C++ class TLorentzVector+;
#pragma link C++ class TProfile+;
#pragma link C++ class std::vector<std::vector<int> >+;
#pragma link C++ class std::vector<std::vector<double> >+;
//#pragma link C++ class TLorentzVector+;




#pragma link C++ class vector<myobject>;
#pragma link C++ class vector<myobject>::iterator;
#pragma link C++ function operator==(const vector<myobject>::iterator&,const vector<myobject>::iterator&); 
#pragma link C++ function operator!=(const vector<myobject>::iterator&,const vector<myobject>::iterator&); 
#pragma link C++ function operator<=(const vector<myobject>::iterator&,const vector<myobject>::iterator&); 
#pragma link C++ function operator>=(const vector<myobject>::iterator&,const vector<myobject>::iterator&); 
#pragma link C++ function operator<(const vector<myobject>::iterator&,const vector<myobject>::iterator&); 
#pragma link C++ function operator>(const vector<myobject>::iterator&,const vector<myobject>::iterator&); 
#pragma link C++ function operator-(const vector<myobject>::iterator&,const vector<myobject>::iterator&); 
#pragma link C++ function operator+(const vector<myobject>::iterator::difference_type,const vector<myobject>::iterator&); 
#pragma link C++ class myGenobject+;
#pragma link C++ class vector<myGenobject>;
#pragma link C++ class vector<myGenobject>::iterator;
#pragma link C++ function operator==(const vector<myGenobject>::iterator&,const vector<myGenobject>::iterator&); 
#pragma link C++ function operator!=(const vector<myGenobject>::iterator&,const vector<myGenobject>::iterator&); 
#pragma link C++ function operator<=(const vector<myGenobject>::iterator&,const vector<myGenobject>::iterator&); 
#pragma link C++ function operator>=(const vector<myGenobject>::iterator&,const vector<myGenobject>::iterator&); 
#pragma link C++ function operator<(const vector<myGenobject>::iterator&,const vector<myGenobject>::iterator&); 
#pragma link C++ function operator>(const vector<myGenobject>::iterator&,const vector<myGenobject>::iterator&); 
#pragma link C++ function operator-(const vector<myGenobject>::iterator&,const vector<myGenobject>::iterator&); 
#pragma link C++ function operator+(const vector<myGenobject>::iterator::difference_type,const vector<myGenobject>::iterator&);

#pragma link C++ class PostAnalysis+;
#pragma link C++ class std::vector<bool>+;

#endif // __CINT__
