#include "Stdafx/stdafx.h"

#include "CommonMacroFunction.h"

#include <string>
#include <locale>

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

MonoBehaviour* IsDerivedFromMonoBehaviour(Component* _c)
{
	return dynamic_cast<MonoBehaviour*>(_c);
}

// unicode to ansi.
string WcsToMbsKorean(wstring const& _wstr)
{
	typedef codecvt<wchar_t, char, mbstate_t> codecvt_t;

	//locale loc("kor");
	locale loc("Korean");
	codecvt<wchar_t, char, mbstate_t> const& codecvt = use_facet<codecvt_t>(loc);

	mbstate_t state = mbstate_t();

	vector<char> buff((_wstr.size() + 1) * codecvt.max_length());

	wchar_t const* in_next = _wstr.c_str();

	char* out_next = &buff[0];

	codecvt_t::result r = codecvt.out(state,
		_wstr.c_str(), _wstr.c_str() + _wstr.size(),
		in_next, &buff[0], &buff[0] + buff.size(), out_next);

	return string(&buff[0]);
}

// unicode to utf8.
string WcsToMbsUtf8(wstring const& _wstr)
{
	int utf8Size = 0;
	string utf8;

	utf8Size = WideCharToMultiByte(CP_UTF8,
		WC_ERR_INVALID_CHARS, _wstr.c_str(),
		static_cast<int>(_wstr.size()),
		NULL, 0, NULL, NULL);

	utf8.resize(utf8Size);

	WideCharToMultiByte(CP_UTF8,
		WC_ERR_INVALID_CHARS, _wstr.c_str(),
		static_cast<int>(utf8Size), const_cast<char*>(utf8.c_str()),
		static_cast<int>(utf8.size()), NULL, NULL);

	return utf8;
}

// utf8 to unicode.
wstring MbsUtf8ToWcs(string const& _str)
{
	int unicodeSize = 0;
	int strSize = (int)(_str.size());
	wstring unicode;

	unicodeSize = MultiByteToWideChar(CP_UTF8,
		MB_ERR_INVALID_CHARS, _str.c_str(),
		strSize, NULL, 0);

	unicode.resize(unicodeSize);

	MultiByteToWideChar(CP_UTF8,
		MB_ERR_INVALID_CHARS, _str.c_str(),
		strSize, const_cast<wchar_t*>(unicode.c_str()),
		static_cast<int>(unicode.size()));

	return unicode;
}
