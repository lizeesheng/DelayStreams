#ifndef _DELAYOUTSTREAM_H_
#define _DELAYOUTSTREAM_H_
#include <string>
#include <sstream>

void defaultStopperOfDout(int& a,std::string& str);
class DelayOutStream
{
	private:
		std::string streambuffer;
		unsigned int delayTime = 20;   //Unit:ms;
		unsigned short precision = 6;
		bool enableStopping = false;
		void (*stopFunc)(int&,std::string&);
		std::ostringstream tmpOSS;
	public:
		struct DelayOutStreamVarsType
		{
			std::string buf;
			std::ostringstream& tO;
			unsigned int dT = 20;
			unsigned short p = 6;
			bool eS = false;
			void (*sF)(int&,std::string&);
		};
		DelayOutStream();
		DelayOutStream(bool status);
		DelayOutStream(bool status,void (*stopFuncArg)(int&,std::string&));
		DelayOutStream(unsigned int time);
		DelayOutStream(unsigned int time,bool status);
		DelayOutStream(unsigned int time,bool status,void (*stopFuncArg)(int&,std::string&));
		virtual ~DelayOutStream();
		void outBuffer();
		void clearBuffer();
		void setDelayTime(unsigned int time);
		void setStatusOfStopping(bool status);
		void setStatusOfStopping(bool status,void (*stopFuncArg)(int&,std::string&));
		void setPrecision(int a);
		DelayOutStreamVarsType getVars();
		std::string greatestIntegerOutput(__int128 integer);
		DelayOutStream& operator<<(const bool outContent);
		DelayOutStream& operator<<(const char outContent);
		DelayOutStream& operator<<(const unsigned char outContent);
		DelayOutStream& operator<<(const short outContent);
		DelayOutStream& operator<<(const unsigned short outContent);
		DelayOutStream& operator<<(const int outContent);
		DelayOutStream& operator<<(const unsigned int outContent);
		DelayOutStream& operator<<(const long outContent);
		DelayOutStream& operator<<(const unsigned long outContent);
		DelayOutStream& operator<<(const long long outContent);
		DelayOutStream& operator<<(const unsigned long long outContent);
		DelayOutStream& operator<<(const double outContent);
		DelayOutStream& operator<<(const long double outContent);
		DelayOutStream& operator<<(const float outContent);
		DelayOutStream& operator<<(const __int128 outContent);
		DelayOutStream& operator<<(char* outContent);
		DelayOutStream& operator<<(const char* outContent);
		DelayOutStream& operator<<(const std::string outContent);
		DelayOutStream& operator<<(DelayOutStream& (*)(DelayOutStream&));
};

extern DelayOutStream dout;
#endif
