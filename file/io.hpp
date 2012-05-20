#ifndef	LIB_FILE_IO_HPP_
#define	LIB_FILE_IO_HPP_

#include <fstream>
#include <iterator>
#include <string>

namespace lib{
namespace file{
namespace io{

/**
 * perlのslurp関数と同様の機能を提供する関数。<br>
 * 
 * @param  file_path データを読み込むファイルパス
 * @param  <CharT>   文字型
 * @return ファイルの内容がすべて読み込まれたstd::basic_string<CharT>
 */
template<class CharT= wchar_t>
std::basic_string<CharT> slurp(std::string const& file_path){
	std::basic_fstream<CharT> ifs(file_path, std::ios::in | std::ios::binary);
	std::istreambuf_iterator<CharT> begin(ifs);
	std::istreambuf_iterator<CharT> end;
	
	std::basic_string<CharT> buf(begin, end);
	
	return buf;
}

}
}
}

#endif	//	#ifndef	LIB_FILE_IO_HPP_

