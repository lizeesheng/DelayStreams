#ifndef _DELAYOUTSTREAM_H_
#define _DELAYOUTSTREAM_H_
#include <string>
#include <sstream>

#define FOREGROUND_BLUE 0x1
#define FOREGROUND_GREEN 0x2
#define FOREGROUND_RED 0x4
#define FOREGROUND_INTENSITY 0x8
#define BACKGROUND_BLUE 0x10
#define BACKGROUND_GREEN 0x20
#define BACKGROUND_RED 0x40
#define BACKGROUND_INTENSITY 0x80

void defaultStopperOfDout(int& a,std::string& str);
void clrscr();
class DelayOutStream
{
	private:
		std::string streambuffer;
		unsigned int delayTime = 20;   //Unit:ms;
		unsigned short precision = 6;
		bool enableStopping = false;
		bool isColorChange = false;
		void (*stopFunc)(int&,std::string&);
		std::ostringstream tmpOSS;
	public:
		enum KEY_CODE {
			ESCAPE = 27,
			DOT    = 110,
			MINUS  = 109,
			PLUS   = 107,
			TIMES  = 106
		};

乘号	106	42
加号	107	43
Enter	13	13
减号	109	45
小数点	110	46
除号
		struct MANIPULATION
		{
			int type;
			int value;
		};
		MANIPULATION tmpMANI = {-1,-1};
		char stopKey = 27;
		struct DelayOutStreamVarsType
		{
			std::string buf;
			std::ostringstream& tO;
			unsigned int dT = 20;
			unsigned short p = 6;
			bool eS = false;
			void (*sF)(int&,std::string&);
			bool iCC = false;
		};
		DelayOutStream();
		DelayOutStream(bool status);
		DelayOutStream(bool status,void (*stopFuncArg)(int&,std::string&));
		DelayOutStream(unsigned int time);
		DelayOutStream(unsigned int time,bool status);
		DelayOutStream(unsigned int time,bool status,void (*stopFuncArg)(int&,std::string&));
		virtual ~DelayOutStream();
		void setColor(unsigned short color);
		void outBuffer();
		void clearBuffer();
		void setStopKey(char key);
		void setDelayTime(unsigned int time);
		void setStatusOfStopping(bool status);
		void setStatusOfStopping(bool status,void (*stopFuncArg)(int&,std::string&));
		void setPrecision(int a);
		void clearStatus();
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
		DelayOutStream& operator<<(const char* outContent);
		DelayOutStream& operator<<(const std::string outContent);
		DelayOutStream& operator<<(DelayOutStream& (*)(DelayOutStream&));
		DelayOutStream& operator<<(const MANIPULATION mani);
};
DelayOutStream::MANIPULATION setcolor(unsigned short color);
extern DelayOutStream::MANIPULATION linef;
extern DelayOutStream::MANIPULATION carre;
extern DelayOutStream::MANIPULATION cls;
extern DelayOutStream dout;
#endif
