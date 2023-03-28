#ifndef REQUESTCONFIG_HPP
#define REQUESTCONFIG_HPP

#include "headers.hpp"



typedef  std::vector<bool> MethAllow;

struct ReqLoc
{
    bool                        _autoindex;
    _string		                __path;
    _string                     __file;
    _string                     __root;
    MethAllow                   _AllowMeth;
    std::pair<bool, std::string> __redirect;    
};




struct DataConf
{
    _string             __body_size;
    _string             __host;
    _string             __name;
    std::vector<ReqLoc> __locations;
};


#endif