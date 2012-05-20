#ifndef LIB_EXCEPTION_INVALID_ARGUMENT_HPP_
#define LIB_EXCEPTION_INVALID_ARGUMENT_HPP_

#include <string>
#include <wchar.h>
#include "exception.hpp"

namespace lib{
namespace exception{

/**
 * 不正な引数に対してスローされる例外クラス<br>
 *
 * @author  kamichidu
 * @version 2012-05-20 (日)
 * @param <CharT> 使用する文字型
 */
template<class CharT= wchar_t>
class invalid_argument : public exception<CharT>{
	public:
		invalid_argument(std::basic_string<CharT> const& what);
		virtual ~invalid_argument();
};

/**
 * 文字列を受け取り初期化<br>
 *
 * @since 2012-05-20 (日)
 * @param what 例外メッセージ
 */
template<class CharT>
inline
invalid_argument<CharT>::invalid_argument(std::basic_string<CharT> const& what) : exception<CharT>(what){
}

/**
 * 
 * @since 2012-05-20 (日)
 */
template<class CharT>
inline
invalid_argument<CharT>::~invalid_argument(){
}

}
}

#endif // #ifndef LIB_EXCEPTION_INVALID_ARGUMENT_HPP_

