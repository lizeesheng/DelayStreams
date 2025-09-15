#include "DelayOutStream.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <conio.h>
#include <windows.h>

void defaultStopperOfDout(int& a,std::string& s)
{
	a=1;
	s.clear();
}
void clrscr()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
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
void DelayOutStream::setColor(unsigned short color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
void DelayOutStream::outBuffer()
{
	if(isColorChange)
	{
		setColor(tmpMANI.value);
	}
	for(auto& i : streambuffer){
		std::cout << i;
		usleep(delayTime * 1000);
		if(enableStopping){
			if(kbhit()){
				if(getch()==stopKey){
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
	if(isColorChange){
		setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		isColorChange = false;
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
	return {streambuffer,tmpOSS,delayTime,precision,enableStopping,stopFunc,isColorChange};
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
void DelayOutStream::clearStatus()
{
	isColorChange = false;
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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
DelayOutStream& DelayOutStream::operator<<(const MANIPULATION mani)
{
	switch(mani.type)
	{
	case 0:
		streambuffer = '\n';
		outBuffer();
		break;
	case 1:
		streambuffer = '\r';
		outBuffer();
		break;
	case 2:
		isColorChange = true;
		tmpMANI.type = mani.type;
		tmpMANI.value = mani.value;
		break;
	case 3:
		clrscr();
		break;
	}
	clearBuffer();
	return *this;
}
DelayOutStream::MANIPULATION setcolor(unsigned short color)
{
	return {2,color};
}
DelayOutStream::MANIPULATION linef = {0,-1};
DelayOutStream::MANIPULATION carre = {1,-1};
DelayOutStream::MANIPULATION cls = {3,-1};
DelayOutStream dout(10,true,defaultStopperOfDout);
