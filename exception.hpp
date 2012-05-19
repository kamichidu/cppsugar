#ifndef	LIB_CEXCEPTION_HPP_
#define	LIB_CEXCEPTION_HPP_

#include <string>
#include <wchar.h>

namespace lib{
	/**
	 *	_TCHARで文字列を扱う基底例外クラス。.
	 *
	 *	課題
	 *	_tcsdup()がNULLを返したときの処理をどうするか。
	 * 
	 *	@author	 kamichidu
	 *	@version 2012-05-20 (日)
	 */
	class exception{
		public:
			exception();
			explicit exception(std::wstring const& what);
			explicit exception(exception const& obj);
			~exception();
		public:
			const wchar_t* what() const;
		public:
			exception& operator = (exception const& obj);
		private:
			std::wstring _what;
	};
	
	/**
	 *	デフォルトコンストラクタ。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 */
	inline
	exception::exception(){
		_what= L"unknonw exception.";
	}
	
	/**
	 *	引数つきコンストラクタ。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@param	exception	被コピー例外クラス
	 */
	inline
	exception::exception(exception const& obj){
		_what= obj._what;
	}
	
	/**
	 *	引数つきコンストラクタ.
	 *
	 *	@since	0.02
	 *	@version	0.01
	 *	@param	s	例外メッセージ
	 */
	inline
	exception::exception(std::wstring const& what){
		_what= what;
	}
	
	/**
	 *	デストラクタ。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 */
	inline
	exception::~exception(){
		_what= L"";
	}
	
	/**
	 *	例外メッセージを返す。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@return	例外を表す文字列
	 */
	inline
	wchar_t const* exception::what() const{
		return _what.c_str();
	}
	
	/**
	 *	=演算子オーバーロード。.
	 *
	 *	@since  2012-05-20 (日)
	 *	@param  e コピーする例外クラス
	 *	@return *this
	 */
	inline
	exception& exception::operator = (exception const& obj){
		if(this != &obj)
			_what= obj._what;
		return *this;
	}
}

#endif	//	LIB_CEXCEPTION_HPP_

