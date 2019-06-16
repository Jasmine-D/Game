#ifndef _MY_UTILITY_H_
#define _MY_UTILITY_H_
#include "cocos2d.h"

using namespace std;
class MyTool {
public:
	static string getCurrentTime();
	static string gbk_2_utf8(const string text);
};
#endif   
