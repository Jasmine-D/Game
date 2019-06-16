#include"MyUtility.h"
string MyTool::getCurrentTime()
{
	time_t t;
	time(&t);
	char tmp[64] = { 0 };
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %X", localtime((&t)));
	string timeStr = tmp;
	return timeStr;
}

/// 在win32平台下，将 GBK 编码 转为 UTF-8
string MyTool::gbk_2_utf8(const string text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//采用 Lambda表达式，将 string 转换成 wstring . Lambda表达式，通俗的解释就是，一个匿名函数.
	wstring tes = [=]()
	{
		setlocale(LC_ALL, "chs");
		const char* _Source = text.c_str();
		size_t _Dsize = text.size() + 1;
		wchar_t* _Dest = new wchar_t[_Dsize];
		wmemset(_Dest, 0, _Dsize);
		mbstowcs(_Dest, _Source, _Dsize);
		std::wstring result = _Dest;
		delete[] _Dest;
		setlocale(LC_ALL, "C");
		return result;
	}();

	int asciSize = WideCharToMultiByte(CP_UTF8, 0, tes.c_str(), tes.size(), NULL, 0, NULL, NULL);
	if (asciSize == ERROR_NO_UNICODE_TRANSLATION || asciSize == 0)
	{
		return string();
	}

	char* resultString = new char[asciSize];
	int conveResult = WideCharToMultiByte(CP_UTF8, 0, tes.c_str(), tes.size(), resultString, asciSize, NULL, NULL);
	if (conveResult != asciSize)
	{
		return string();
	}
	string buff = "";
	buff.append(resultString, asciSize);

	delete[] resultString;
	return buff;

#else
	return text;
#endif

}