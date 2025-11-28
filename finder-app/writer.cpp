#include<fcntl.h> //open flags
#include<unistd.h> // write, close
#include<sys/stat.h> //mode constants
#include<cstring> //strerror
#include<cerrno> //errno
#include<string>
#include<syslog.h>


int main(int argc, char* argv[]) {
	//open syslog connection
	openlog("writer_log", LOG_PID, LOG_USER);

	if(argc != 3) {
		syslog(LOG_ERR," pass filepath and string to be written ");
		closelog();
		return 1;
	}

	std::string writepath = argv[1];
	std::string writestring = argv[2];

	//open file, create if not present
	int fd = open(writepath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd < 0) {
		syslog(LOG_ERR, "Error, unable to open/create file %s : %s", writepath.c_str(), strerror(errno));
		closelog();
		return 1;
	}
	// write to file
	size_t bytesWritten = write(fd, writestring.c_str(), writestring.size());
	if (bytesWritten < 0 || static_cast<size_t>(bytesWritten) != writestring.size()) {
		syslog(LOG_ERR, "Error : Failed to write %s to file %s : %s",writestring.c_str(), writepath.c_str(), strerror(errno));
		close(fd);
		closelog();
		return 1;
	}
	// close the file
	if(close(fd) < 0) {
		syslog(LOG_ERR, "Error : Failed to close file %s : %s",writepath.c_str(), strerror(errno));
		closelog();
		return 1;

	}
	// log success
	syslog(LOG_DEBUG, "Writing %s to file  %s", writestring.c_str(),writepath.c_str());

	//close syslog
	closelog();
	return 0;

}
