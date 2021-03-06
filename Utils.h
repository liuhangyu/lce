#ifndef __NCE_UTILS_H
#define __NCE_UTILS_H

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>


//64bit switch

#if __BYTE_ORDER == __BIG_ENDIAN
	#define ntohll(x)       (x)
	#define htonll(x)       (x)
#else
	#if __BYTE_ORDER == __LITTLE_ENDIAN
		#define ntohll(x)     __bswap_64 (x)
		#define htonll(x)     __bswap_64 (x)
	#endif
#endif


namespace lce
{

    int bind(int iFd,const std::string &sHost,uint16_t wPort);

    int listen(int iFd);

	int setNBlock(int iFd);
	
	int setNODelay(int iFd);

	int close(const int iFd);


	int setNCloseWait(const int iFd);

	int send(int iFd, const char *buf, int count);

	int sendto(int iFd,const char *buf,int count,const std::string &sIp,uint16_t wPort);

    int createUdpSock();
    int createTcpSock();

    int connect(int iFd,const std::string &sHost,uint16_t wPort);

	inline time_t getTickCount()
    {
        timeval tv;
        gettimeofday(&tv, 0);
        return tv.tv_sec * 1000 + tv.tv_usec/1000;
    }

    std::string& trimString(std::string& sSource);


    inline std::string inetNtoA(const uint32_t dwIp)
    {
        struct in_addr in;
        in.s_addr = htonl(dwIp);
        return std::string(inet_ntoa(in));
    }

	template <class T>
    std::string toStr(const T &t)
	{
		std::stringstream stream;
		stream.precision(20);
		stream<<t;
		return stream.str();
	}

	void initDaemon();

    bool setFileLimit(const uint32_t dwLimit);
	bool setCoreLimit(const uint32_t dwLimit);

	std::string getGMTDate(const time_t& cur);

	time_t gmt2Time(const char *str);


	std::string formUrlEncode(const std::string& sSrc);
	std::string formUrlDecode(const std::string& sSrc);
	std::string charToHex(char c);
	inline char hexToChar(char first, char second)
	{
		int digit;
		digit = (first >= 'A' ? ((first & 0xDF) - 'A') + 10 : (first - '0'));
		digit *= 16;
		digit += (second >= 'A' ? ((second & 0xDF) - 'A') + 10 : (second - '0'));
		return static_cast<char>(digit);
	}

	inline size_t hashString(const char* __s)
	{
		unsigned long __h = 0; 
		for ( ; *__s; ++__s)
			__h = 5*__h + *__s;

		return size_t(__h);
	}

	inline size_t hashString(const std::string& __s)
	{
		unsigned long __h = 0; 
		for ( size_t i=0; i<__s.size(); ++i )
			__h = 5*__h + __s[i];

		return size_t(__h);
	}

};
#endif
