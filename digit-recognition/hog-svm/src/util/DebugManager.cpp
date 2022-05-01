#include "DebugManager.h"

bool DebugManager::isPathDefined = false;
std::ofstream* DebugManager::currStream = NULL;
char DebugManager::directoryPath[1024];
char DebugManager::debugPath[1024];
// The stream that debug output is sent to. By default
// this points to std::cerr.
std::ostream* debugStream(&std::cout);
// Null stream. This file stream will never be opened and acts
// as a null stream for DebugStream().
std::ofstream nullStream;

// Throughout the library's codebase this function is called
// to get the stream that debug output should be sent to.
std::ostream& DebugManager::GetCoutStream(std::string className)
{
	//http://w3facility.org/question/redirect-debug-output-to-null-stream-instead-of-stdcerr/
	//http://stackoverflow.com/questions/19200207/redirect-debug-output-to-null-stream-instead-of-stdcerr
	if (noDebug(className))
		return nullStream;
	return *debugStream;
}
void DebugManager::CloseDebugFileOStream(){
	if (DebugManager::currStream != NULL){
		DebugManager::currStream->flush();
		DebugManager::currStream->close();
	}
	DebugManager::currStream = NULL;
}
void DebugManager::FlushDebugFileOStream(){
	if (DebugManager::currStream != NULL)
		DebugManager::currStream->flush();
}
std::ofstream& DebugManager::GetDebugFileOStream(std::string className)
{
	//http://w3facility.org/question/redirect-debug-output-to-null-stream-instead-of-stdcerr/
	//http://stackoverflow.com/questions/19200207/redirect-debug-output-to-null-stream-instead-of-stdcerr
	if (noDebug(className))
		return nullStream;
	if (DebugManager::currStream == NULL){
		DebugManager::currStream = new std::ofstream();
		DebugManager::currStream->open(getLogFileName(), std::ofstream::out | std::ofstream::app);
	}
	if (DebugManager::currStream != NULL ? DebugManager::currStream->is_open() : false)
		return *DebugManager::currStream;
	return nullStream;
}


/*std::ostream& DebugManager::GetDebugStream(std::string className)
{
	//http://w3facility.org/question/redirect-debug-output-to-null-stream-instead-of-stdcerr/
	//http://stackoverflow.com/questions/19200207/redirect-debug-output-to-null-stream-instead-of-stdcerr
	if (noDebug(className))
		return nullStream;
	return *debugStream;
}*/

void DebugManager::setDebugPath(char* inputDebugPath){
	isPathDefined = true;
	sprintf(directoryPath, "%s", inputDebugPath);
	#ifdef textMode
		sprintf(debugPath, "%s/log_data.txt", inputDebugPath);
	#else
		sprintf(debugPath, "%s/log_data.html", inputDebugPath);
	#endif
}

const char* DebugManager::getDebugDirectoryPath(){
  if (isPathDefined)
    {
      return directoryPath;
    }
  else{
	 return "/tmp/";
  }
  return getLogFileName();
};

const char* DebugManager::getLogFileName(){
	if (isPathDefined)
	{
		return DebugManager::debugPath;
	}
	#ifdef windows
		#ifdef textMode
			return "c:\\log_data.txt";
		#endif
		return "c:\\log_data.html";
	#endif
	#ifdef textMode
		return "/tmp/log_data.txt";
	#endif
		return "/tmp/log_data.html";
};

/*
	Return a true in case the debug image needs to be displayed, false otherwise.
*/
bool DebugManager::allowImageDisplay(std::string className){
  if (className.find("hw02") != std::string::npos)
    return true;
  
  return false;
}

bool DebugManager::createDebugImage(std::string className){
  if (className.find("hw02") != std::string::npos)
    return true;
  
  return false;
}

bool DebugManager::noDebug(std::string className){
	if (className.find("hw02") != std::string::npos)
		return false;
  
	return true;
}


char *make_message(const char* fmt, ...) {
	/* Guess we need no more than 100 bytes. */
	int n, size = 100;
	char *p;
	va_list ap;
	if ((p = (char *)malloc (size * sizeof(char))) == NULL)
		return NULL;
	while (1) {
		// Try to print in the allocated space. 
		va_start(ap, fmt);
		n = vsnprintf (p, size, fmt, ap);
		va_end(ap);
		// If that worked, return the string.
		if (n > -1 && n < size)
		   return p;
		// Else try again with more space. 
		if (n > -1)    // glibc 2.1 
		   size = n+1; // precisely what is needed
		else           // glibc 2.0
		   size *= 2;  // twice the old size
		if ((p = (char *)realloc (p, size * sizeof(char))) == NULL)
		   return NULL;
	}
}
