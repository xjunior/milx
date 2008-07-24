
// by Rafal Maj (C) 2008 ; LGPL license

// debug.

#include <sstream>
#include <stdexcept>

template<typename T> T* UsePtr_(T *ptr, const char* file, int line, const char *expr) { 
	if (!ptr) {
		std::ostringstream oss;
		oss << "Trying to use NULL pointer";
		oss << ", in " << file << ':' << line;
		oss << ", expression ' " << expr << " ' ";
		oss << "!";
		throw std::runtime_error(oss.str());
	}
	return ptr;
}

#define UsePtr(X) UsePtr_(X,__FILE__,__LINE__,#X)


