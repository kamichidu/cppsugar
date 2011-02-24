#ifndef	LIB_CEXCEPTION_HPP
#define	LIB_CEXCEPTION_HPP

#include	<tchar.h>
#include	<crtdbg.h>

namespace Lib{
	/**
	 *	_TCHARで文字列を扱う基底例外クラス。.
	 *
	 *	@author	Chiduru
	 *	@version	0.01
	 */
	class CException{
		private:
			typedef	_TCHAR*			LPTSTR;
			typedef	const _TCHAR*	LPCTSTR;
			
		public:
			explicit CException();
			explicit CException(LPCTSTR message);
			explicit CException(const CException& e);
			~CException();
			LPCTSTR What() const;
			CException& operator=(const CException& e);
			
		private:
			LPTSTR	m_what;
	};
	
	/**
	 *	デフォルトコンストラクタ。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 */
	inline CException::CException(){
		m_what=	_tcsdup(_T("Unknown exception"));
	}
	
	/**
	 *	引数つきコンストラクタ。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@param	message	例外メッセージ
	 */
	inline CException::CException(LPCTSTR message){
		_ASSERT(message);
		m_what=	_tcsdup(message);
	}
	
	/**
	 *	デストラクタ。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 */
	inline CException::~CException(){
		free(m_what);
		m_what=	_T('\0');
	}
	
	/**
	 *	例外メッセージを返す。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@return	例外を表す文字列
	 */
	inline LPCTSTR CException::What() const{
		return m_what;
	}
	
	/**
	 *	=演算子オーバーロード。.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@param	e	コピーする例外クラス
	 *	@return	自分自身
	 */
	inline CException& CException::operator=(const CException& e){
		free(m_what);
		m_what=	_tcsdup(e.What());
		return *this;
	}
}

#endif	//	LIB_CEXCEPTION_HPP
