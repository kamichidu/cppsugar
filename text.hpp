#ifndef LIB_TEXT_HPP_
#define	LIB_TEXT_HPP_

#include <cstdlib>
#include <string>
#include <memory>

namespace lib{
namespace text{

/**
 * std::stringの文字列をstd::wstringに変換する。.<br>
 * 
 * @param text 変換の対象となる文字列
 * @return
 *     textから変換されたstd::wstring
 */
inline
std::wstring string2wstring(std::string const& text){
	size_t const buf_size= text.length() + 1;
	std::unique_ptr<wchar_t> buf(new wchar_t[buf_size]);
	
	mbstowcs(buf.get(), text.c_str(), buf_size);
	
	return buf.get();
}

/**
 * std::wstringの文字列をstd::stringに変換する。.<br>
 * 
 * @param text 変換の対象となる文字列
 * @return
 *     textから変換されたstd::string
 */
inline
std::string wstring2string(std::wstring const& text){
	size_t const buf_size= text.length() * 2 + 1;
	std::unique_ptr<char> buf(new char[buf_size]);
	
	wcstombs(buf.get(), text.c_str(), buf_size);
	
	return buf.get();
}

}
}

#endif // #ifndef LIB_TEXT_HPP_

