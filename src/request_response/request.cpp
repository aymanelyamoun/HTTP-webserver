#include "../../inc/req_res.hpp"
// #include "../../inc/utils.hpp"

request::request()
{
    // start_line.resize(3, string(""));
    start_line.reserve(3);
    body = "";
}
request::request(string req)
{
    start_line.reserve(3);
    body = "";
    parse(req);
}

void request::request_checkpoint()
{
    validate_start_line();
    fill_req();
}

void request::parse(string req)
{
    std::stringstream s_request(req);
    string tmp_str;
    string line;

    std::getline(s_request, line, '\r');
    std::stringstream start_l_s(line);
    std::getline(s_request, line, '\n');

    short i = 0;
    for (; i < 3 and std::getline(start_l_s, tmp_str, ' '); i++)
        start_line.push_back(tmp_str);

    if (i != 3)
        std::cout << "err msg\n";

    while (std::getline(s_request, tmp_str, '\n') and tmp_str != string("\r"))
    {
        size_t pos = tmp_str.find(":");
        headers.push_back(std::make_pair(string(tmp_str.substr(0, pos)), string(tmp_str.substr(pos + 1))));
        // std::cout << headers.back()->fist;
    }

    if (tmp_str != "\r")
        std::cout << "err msg\n";
    while (std::getline(s_request, tmp_str))
        body.append(tmp_str);


    
    request_checkpoint();
}

short request::method_num()
{
    if (start_line[METHOD] == "GET")
        return (GET);
    if (start_line[METHOD] == "POST")
        return (POST);
    if (start_line[METHOD] == "DELETE")
        return (DELETE);
    return -1;
}

int request::fill_req()
{
    request_info.method = method_num();
    request_info.requested_file = start_line[SOURCE];

    for(vec_strp_it it = headers.begin(); it != headers.end(); it++)
    {
        // std::cout << "=" << it->first << std::endl;
        if (_to_lower(it->first) == "host")
        {
            if (request_info.host != "")
            {
                response.set_status(400, "bad request3");
                return 1;
            }
            request_info.host = it->second;
        }
        if (_to_lower(it->first) == "content-type")
        {
            if (request_info.content_type.first != "")
            {
                response.set_status(400, "bad request4");
                return 1;
            }
            fill_content_type(request_info , it->second);
            // request_info.content_type = it->second;
        }
        if (_to_lower(it->first) == "content-length")
        {
            if (request_info.content_length != -1)
            {
                response.set_status(400, "bad request5");
                return 1;
            }
            // std::cout << it->second <<;
            // print(it->second);
            request_info.content_length = std::stoi(it->second);
            if (request_info.content_length < 0)
            {
                response.set_status(400, "bad request");
                return 1;
            }
        }

        if (_to_lower(it->first) == "connection")
        {
            if (request_info.connection != "")
            {
                response.set_status(400, "bad request6");
                return 1;
            }
            request_info.connection = it->second;
        }
        // if (_to_lower(it->first) == "accept")
        // {
        //     fill_accept(*it);
        // }
    }
    request_info.body.swap(body);
    return 0;
}

void request::validate_start_line()
{
    if (start_line.size() != 3){/*bad request*/}
    if (start_line[METHOD] == "GET" || start_line[METHOD] == "POST" || start_line[METHOD] == "DELETE")
    {
        /*
            // add a function to check is the method allowed for the requested source ;
            if ( methods.is_allowed(start_line[METHOD], req) == NOT_ALLOWED)
            {
                set_status(405, "Method Not Allowed");
                return ;
            }
            check for the source existence and accessibility ;
            methods.check_content_type(req, &reference) ;
        */
        if (valid_http(start_line[PROTOCOL]) == false)
        {
            response.set_status(505, "HTTP Version Not Supported");
            return ;
        }

        // checking for source existence
        // methods.handler(start_line[METHOD], req);

        // check for source accessibility using sngat's config file for allowed paths and method (using the method class)
        // * to be done 
    }
    else
    {
        response.set_status(501, "Not Implemented");
    }
}

void request::print_req()
{
    for (vec_str_it it = start_line.begin();it != start_line.end(); it++)
    {
        if (it + 1 == start_line.end())
            std::cout << *it << std::endl;
        else
            std::cout << *it << " ";
    }
    // std::cout << std::endl;

    // for (vec_strp_it it = headers.begin(); it != headers.end(); it++)
    // 	std::cout << it->first << ":" << it->second << std::endl;
    std::cout << "host: " << request_info.host << std::endl;
    std::cout << "content_length: " << request_info.content_length << std::endl;
    std::cout << "connection: " << request_info.connection << std::endl;
    // std::cout << 
    std::cout << std::endl;
    std::cout << std::endl << body;
}

// void request::print_req(std::string req)
// {
//     this->parse(req);
//     this->print_req();
// }

void request::print(string s)
{
    size_t i = 0;
    while (i < s.size())
    {
        if (s[i] == '\n')
            std::cout << "\\n";
        else if (s[i] == '\r')
            std::cout << "\\r";
        else
            std::cout << s[i];
        // cout << s[i];
        i++;
    }
    std::cout << std::endl;
}
