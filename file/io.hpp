#ifndef	LIB_FILE_IO_HPP
#define	LIB_FILE_IO_HPP

#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include "CException.hpp"

namespace Lib{
namespace File{
namespace IO{

	/**
	 *	file_pathで指定されたファイルの中身を全て読み込み、領域を確保して返す.
	 *
	 *	返されたポインタはdelete[]で解放しなければならない。
	 *
	 *	@param	file_path	読み込むファイルパス
	 *	@return	読み込んだ文字列へのポインタ(領域確保済)
	 */
	_TCHAR* Slerp(_TCHAR const* file_path){
		_TCHAR* str;
		
		try{
			unsigned __int32 length;
			_TCHAR buf[256];
			FILE* in;
			
			_tfopen_s(&in, file_path, _T("r"));
			if(in == NULL)
				throw _T("ファイルを開けませんでした。");
			
			//	ファイル中の文字数を数える
			length= 0;
			while(_fgettc(in) != _TEOF)
				++length;
			
			//	先頭位置に戻す
			if(fseek(in, 0, SEEK_SET))
				throw _T("ファイル操作に失敗しました。");
			
			//	領域の確保
			str= new _TCHAR[length + 1];
			
			//	実際にファイルから文字列を読み込み、終端文字列をセット
			*str= _T('\0');
			while(_fgetts(buf, 256, in))
				_tcsncat_s(str, length + 1, buf, 256);
			
			if(fclose(in) == EOF){
				delete str;
				str= NULL;
				
				throw _T("ファイルを閉じられませんでした。");
			}
		}
		catch(_TCHAR const* mes){
			throw Lib::CException(mes);
		}
		catch(std::bad_alloc&){
			throw Lib::CException(_T("領域が確保できませんでした。"));
		}
		catch(...){
			throw Lib::CException(_T("不明なエラーが発生しました。"));
		}
		
		return str;
	}

}
}
}

#endif	//	#ifndef	LIB_FILE_IO_HPP
