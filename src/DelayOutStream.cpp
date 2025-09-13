#include "DelayOutStream.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <conio.h>
void defaultStopperOfDout(int& a,std::string& s)
{
	a=1;
	s.clear();
}
DelayOutStream::DelayOutStream()
{
	clearBuffer();
}
DelayOutStream::DelayOutStream(bool status)
{
	clearBuffer();
	setStatusOfStopping(status,defaultStopperOfDout);
}
DelayOutStream::DelayOutStream(bool status,void (*stopFuncArg)(int&,std::string&))
{
	clearBuffer();
	setStatusOfStopping(status,stopFuncArg);
}
DelayOutStream::DelayOutStream(unsigned int time)
{
	clearBuffer();
	delayTime = time;
}
DelayOutStream::DelayOutStream(unsigned int time,bool status)
{
	clearBuffer();
	delayTime = time;
	setStatusOfStopping(status,defaultStopperOfDout);
}
DelayOutStream::DelayOutStream(unsigned int time,bool status,void (*stopFuncArg)(int&,std::string&))
{
	clearBuffer();
	delayTime = time;
	setStatusOfStopping(status,stopFuncArg);
}
DelayOutStream::~DelayOutStream()
{
	clearBuffer();
}
void DelayOutStream::outBuffer()
{
	for(auto& i : streambuffer){
		std::cout << i;
		usleep(delayTime * 1000);
		if(enableStopping){
			if(_kbhit()){
				if(_getch()==27){
					int status = 0;
					std::string stopMsg;
					stopMsg.clear();
					(*stopFunc)(status,stopMsg);
					if(status == 1){
						return;
					} else if(status == 0){
						exit(0);
					}
					if(!stopMsg.empty()){
						dout << stopMsg;
					}
				}
			}
		}
	}
}
void DelayOutStream::clearBuffer()
{
	tmpOSS.clear();
	tmpOSS.str("");
	streambuffer.clear();
}
void DelayOutStream::setDelayTime(unsigned int time)
{
	delayTime = time;
}
DelayOutStream::DelayOutStreamVarsType DelayOutStream::getVars()
{
	return {streambuffer,tmpOSS,delayTime,precision,enableStopping,stopFunc};
}
std::string DelayOutStream::greatestIntegerOutput(__int128 num){
	std::string rt = "";
    if (num < 0) {
        rt += '-';
        num = -num;
    }
    if (num > 9) {
        rt += greatestIntegerOutput(num / 10);
    }
    rt += char(num % 10 + '0');
    return rt;
}
void DelayOutStream::setStatusOfStopping(bool status)
{
	enableStopping = status;
}
void DelayOutStream::setStatusOfStopping(bool status,void (*stopFuncArg)(int&,std::string&))
{
	enableStopping = status;
	stopFunc = stopFuncArg;
}
void DelayOutStream::setPrecision(int a)
{
	precision = a;
}
DelayOutStream& DelayOutStream::operator<<(const bool outContent)
{
	streambuffer = (outContent?"1":"0");
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const char outContent)
{
	streambuffer.resize(1);
	streambuffer[0] = outContent;
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const unsigned char outContent)
{
	streambuffer.resize(1);
	streambuffer[0] = outContent;
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const short outContent)
{
	streambuffer = std::to_string(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const unsigned short outContent)
{
	streambuffer = std::to_string(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const int outContent)
{
	streambuffer = std::to_string(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const unsigned int outContent)
{
	streambuffer = std::to_string(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const long outContent)
{
	streambuffer = std::to_string(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const unsigned long outContent)
{
	streambuffer = std::to_string(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const long long outContent)
{
	streambuffer = std::to_string(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const unsigned long long outContent)
{
	streambuffer = std::to_string(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const double outContent)
{
	tmpOSS << std::fixed << std::setprecision(precision) << outContent;
	streambuffer = tmpOSS.str();
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const long double outContent)
{
	tmpOSS << std::fixed << std::setprecision(precision) << outContent;
	streambuffer = tmpOSS.str();
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const float outContent)
{
	tmpOSS << std::fixed << std::setprecision(precision) << outContent;
	streambuffer = tmpOSS.str();
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const __int128 outContent)
{
	streambuffer = greatestIntegerOutput(outContent);
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(char* outContent)
{
	streambuffer = outContent;
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const char* outContent)
{
	streambuffer = outContent;
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream& DelayOutStream::operator<<(const std::string outContent)
{
	streambuffer = outContent;
	outBuffer();
	clearBuffer();
	return *this;
}
DelayOutStream dout(50,true,defaultStopperOfDout);
