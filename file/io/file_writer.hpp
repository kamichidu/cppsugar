#ifndef	LIB_FILE_IO_CFILEWRITER_HPP
#define	LIB_FILE_IO_CFILEWRITER_HPP

#include <string>
#include <wchar.h>

namespace lib{
namespace file{
namespace io{

/**
 *	ファイル書き込み用クラス.
 *
 *	@author  kamichidu
 *	@version 2012-05-20 (日)
 */
template<class DestCharT= wchar_t>
class file_writer{
	public:
		file_writer(std::string const& file_name, int mode);
		explicit file_writer(file_writer const& obj);
		~file_writer();
	public:
		void write(std::wstring const& format, ...);
		void write_line(std::wstring const& format, ...);
		void write_line();
		void close();
	private:
};

/**
 *	コンストラクタ.
 *
 *	@since	0.01
 *	@param	file_name	ファイル名
 *	@param	over_write	trueなら上書きモード
 */
template<class DestCharT>
inline
file_writer<DestCharT>::file_writer(std::string const& file_name, int mode){
}

/**
 *	コピーコンストラクタ.
 *
 *	@since	0.01
 *	@param	obj	被コピークラス
 */
template<class DestCharT>
inline
file_writer<DestCharT>::file_writer(file_writer const& obj){
}

/**
 *	デストラクタ.
 *
 *	@since	0.01
 */
template<class DestCharT>
inline
file_writer<DestCharT>::~file_writer(){
}

/**
 *	ファイルに文字列を書き込む.
 *
 *	@since	0.01
 *	@param	format	書き込む文字列
 */
template<class DestCharT>
inline
void file_writer<DestCharT>::write(std::wstring const& format, ...){
}

/**
 *	ファイルに文字列(末尾に\nを追加)を書き込む.
 *
 *	@since	0.01
 *	@param	format	書き込む文字列
 */
template<class DestCharT>
inline
void file_writer<DestCharT>::write_line(std::wstring const& format, ...){
}

/**
 *	ファイルに改行を書き込む.
 *
 *	@since	0.02
 */
template<class DestCharT>
inline
void file_writer<DestCharT>::write_line(){
}

/**
 *	ファイルを閉じる.
 *
 *	@since	0.01
 */
template<class DestCharT>
inline
void file_writer<DestCharT>::close(){
}

}
}
}

#endif	//	#ifndef	LIB_FILE_IO_FILEWRITER_HPP
