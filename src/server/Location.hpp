#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "everything.hpp"
class Location
{
	private:
		bool                          __autoindex;
		_string                       __place;
		_string                       __root;
		_methods                      __methods;
		std::pair<bool, std::string>  __redirect;
	public:
		Location(bool autoindex, _string place_index, _string root, _methods const &meth, std::pair<bool, std::string> redre): __methods(meth)
		{
			this->__autoindex = autoindex;
			this->__place = place_index;
			this->__root = root;
			this->__redirect = redre;
		}
};



#endif