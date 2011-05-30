#ifndef	LIB_FILE_IO_CFILEWRITER_HPP
#define	LIB_FILE_IO_CFILEWRITER_HPP

#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>
#include "CException.hpp"

namespace Lib{
namespace File{
namespace IO{

	/**
	 *	ファイル書き込み用クラス.
	 *
	 *	@author	Chiduru
	 *	@version	0.02
	 */
	class CFileWriter{
		public:
			explicit CFileWriter(_TCHAR const* file_name, bool over_write);
			explicit CFileWriter(CFileWriter const& obj);
			~CFileWriter();
		public:
			void Write(_TCHAR const* format, ...);
			void WriteLine(_TCHAR const* format, ...);
			void WriteLine();
			void Close();
		private:
			FILE* _out;
	};
	
	/**
	 *	コンストラクタ.
	 *
	 *	@since	0.01
	 *	@param	file_name	ファイル名
	 *	@param	over_write	trueなら上書きモード
	 */
	inline
	CFileWriter::CFileWriter(_TCHAR const* file_name, bool over_write= true) : _out(NULL){
		try{
			_TCHAR mode[2];
			
			//	over_writeがtrueならmodeはw、falseならmodeはa
			_tcscpy_s(mode, 2, over_write ? _T("w") : _T("a"));
			
			if(_tfopen_s(&_out, file_name, mode) != 0)
				throw _T("ファイルを開けませんでした。");
		}
		catch(_TCHAR const* msg){
			throw CException(msg);
		}
	}
	
	/**
	 *	コピーコンストラクタ.
	 *
	 *	@since	0.01
	 *	@param	obj	被コピークラス
	 */
	inline
	CFileWriter::CFileWriter(CFileWriter const& obj) : _out(NULL){
	}
	
	/**
	 *	デストラクタ.
	 *
	 *	@since	0.01
	 */
	inline
	CFileWriter::~CFileWriter(){
		if(_out)
			fclose(_out);
		_out= NULL;
	}
	
	/**
	 *	ファイルに文字列を書き込む.
	 *
	 *	@since	0.01
	 *	@param	format	書き込む文字列
	 */
	inline
	void CFileWriter::Write(_TCHAR const* format, ...){
		try{
			va_list arg;
			
			va_start(arg, format);
			
			if(format == NULL)
				throw _T("文字列にNULLが指定されました。");
			
			if(_out){
				if(_vftprintf(_out, format, arg) < 0)
					throw _T("書き込みに失敗しました。");
			}
			else
				throw _T("ファイルが開かれていません。");
			
			va_end(arg);
		}
		catch(_TCHAR const* msg){
			throw CException(msg);
		}
	}
	
	/**
	 *	ファイルに文字列(末尾に\nを追加)を書き込む.
	 *
	 *	@since	0.01
	 *	@param	format	書き込む文字列
	 */
	inline
	void CFileWriter::WriteLine(_TCHAR const* format, ...){
		try{
			va_list arg;
			
			va_start(arg, format);
			
			if(format == NULL)
				throw _T("文字列にNULLが指定されました。");
			
			if(_out){
				_TCHAR* reformat;
				reformat= new _TCHAR[_tcslen(format) + 2];
				_stprintf(reformat, _T("%s%s"), format, "\n");
				if(_vftprintf(_out, reformat, arg) < 0){
					delete [] reformat;
					throw _T("書き込みに失敗しました。");
				}
				delete [] reformat;
			}
			else
				throw _T("ファイルが開かれていません。");
			
			va_end(arg);
		}
		catch(_TCHAR const* msg){
			throw CException(msg);
		}
	}
	
	/**
	 *	ファイルに改行を書き込む.
	 *
	 *	@since	0.02
	 */
	inline
	void CFileWriter::WriteLine(){
		try{
			Write(_T("\n"));
		}
		catch(CException const& e){
			throw e;
		}
	}
	
	/**
	 *	ファイルを閉じる.
	 *
	 *	@since	0.01
	 */
	inline
	void CFileWriter::Close(){
		try{
			if(fclose(_out) == EOF)
				throw _T("ファイルが閉じられませんでした。");
			_out= NULL;
		}
		catch(_TCHAR const* msg){
			throw CException(msg);
		}
	}

}
}
}

#endif	//	#ifndef	LIB_FILE_IO_FILEWRITER_HPP
