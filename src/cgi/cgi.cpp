#include "../inc/req_res.hpp"



int cgi(_cgi_info cgi_info , HTTP_request &request_info, HTTP_response &response)
{
	(void) request_info;
	const char* lang_path = cgi_info.lang_path.c_str();
	const char* cgi_name = cgi_info.cgi_name.c_str();
	std::string subtracted_body = request_info.body;
	subtracted_body.erase(0, 5);
	const char* body = subtracted_body.c_str();
	
	char *av[] = {(char *) lang_path, (char *) cgi_name, (char *) body, nullptr};
	FILE *fp = tmpfile();
	int fd = fileno(fp);
	pid_t pid = fork();
	if (pid == -1)
	{
		std::cerr << "cgi error\n";
		exit(500);
	}
	if (pid == 0)
	{
		if (fd == -1)
		{
			perror("open");
			std::cerr << "error\n";
			exit(500);
		}
		if (dup2(fd, 1) == -1)
		{
			std::cerr << "dup error\n";
			exit(500);
		}
		execve(lang_path, av, NULL);
		perror("execve"); // Print error message
		close(fd);
		exit(500);
	}
	wait(NULL);
	long fileSize = ftell(fp);
	response.content_length = fileSize;
	response.set_status(200, "OK");
	response.content_type = "text/html";
	rewind(fp);
	char readFromFile[fileSize + 1];
	fread(readFromFile, 1, fileSize, fp);
	response.body = readFromFile;
	return 1;
}