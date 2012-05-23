#ifndef	LIB_EXCEPTION_EXCEPTION_HPP_
#define	LIB_EXCEPTION_EXCEPTION_HPP_

#include <string>
#include <wchar.h>

namespace lib{
namespace exception{

/**
 * 汎用例外クラス<br>
 *
 * @author  kamichidu
 * @version 2012-05-20 (日)
 * @param <CharT> 使用する文字型
 */
template<class CharT= wchar_t>
class exception{
	public:
		exception();
		explicit exception(std::basic_string<CharT> const& what);
		explicit exception(exception<CharT> const& obj);
		virtual ~exception();
	public:
		virtual std::basic_string<CharT> const& what() const;
	public:
		exception& operator = (exception<CharT> const& obj);
	private:
		std::basic_string<CharT> _what;
};

/**
 *
 * @since 2012-05-20 (日)
 */
template<class CharT>
inline
exception<CharT>::exception(){
}

/**
 *
 * @since 2012-05-20 (日)
 * @param obj コピーする例外オブジェクト
 */
template<class CharT>
inline
exception<CharT>::exception(exception<CharT> const& obj){
	_what= obj._what;
}

/**
 *
 * @since 2012-05-20 (日)
 * @param what 例外メッセージ
 */
template<class CharT>
inline
exception<CharT>::exception(std::basic_string<CharT> const& what){
	_what= what;
}

/**
 *
 * @since 2012-05-20 (日)
 */
template<class CharT>
inline
exception<CharT>::~exception(){
}

/**
 *
 * @since 2012-05-20 (日)
 * @return
 *     例外メッセージ
 */
template<class CharT>
inline
std::basic_string<CharT> const& exception<CharT>::what() const{
	return _what;
}

/**
 * 代入を行う。<br>
 *
 * @since 2012-05-20 (日)
 * @param obj 代入するオブジェクト
 * @return 
 *     被代入オブジェクト
 */
template<class CharT>
inline
exception<CharT>& exception<CharT>::operator = (exception<CharT> const& obj){
	if(this != &obj)
		_what= obj._what;
	return *this;
}

}
}

#endif	//	LIB_EXCEPTION_EXCEPTION_HPP_

