#include "../../inc/req_res.hpp"

void set_cookies(HTTP_request &request_info, HTTP_response &response)
{
	(void)response;
	(void)request_info;
    std::time_t now = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", std::localtime(&now));
	std::cout << "buffer : " << buffer << std::endl;
    // if (request_info.cookies.empty())
    

    // return std::string(buffer);

}
