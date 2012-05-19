#ifndef	LIB_XORSHIFT_HPP
#define	LIB_XORSHIFT_HPP

#include	<tchar.h>
#include	<time.h>
#include	<crtdbg.h>
#include	"CException.hpp"

namespace lib{
	/**
	 *	XorShiftによる乱数生成ジェネレータ.
	 *
	 *	TODO ほぼフルスクラッチ
	 *
	 *	@author	Chiduru
	 *	@version	0.02
	 */
	class xorshift{
		public:
			explicit xorshift(unsigned __int32 seed);
			unsigned __int32 Generate();
			unsigned __int32 Generate(unsigned __int32 min, unsigned __int32 max);
			unsigned __int32 Generate(unsigned __int32 max);
			unsigned __int32 GenerateBit();
			_TCHAR GenerateAlphabet();
			
			bool testxorshift();
		
		private:
			unsigned __int32 _x;
			unsigned __int32 _y;
			unsigned __int32 _z;
			unsigned __int32 _w;
	};
	
	/**
	 *	コンストラクタ.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@param	seed	乱数の種
	 */
	xorshift::xorshift(unsigned __int32 seed= static_cast<unsigned __int32>(time(NULL))){
		_x= seed;
		_y= 1234 * _x + 56789;
		_z= 1234 * _y + 56789;
		_w= 1234 * _z + 56789;
	}
	
	/**
	 *	乱数生成.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@return	生成された乱数
	 */
	unsigned __int32 xorshift::Generate(){
		unsigned __int32 t;
		
		t= _x ^ (_x << 15);
		_x= _y;
		_y= _z;
		_z= _w;
		_w= (_w ^ (_w >> 21)) ^ (t ^ (t >> 4));
		
		return _w;
	}
	
	/**
	 *	範囲指定つき乱数生成.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@param	min	生成される乱数の最小値
	 *	@param	max	生成される乱数の最大値
	 *	@return	min以上max以下の、生成された乱数
	 */
	unsigned __int32 xorshift::Generate(unsigned __int32 min, unsigned __int32 max){
		if(min < 0 || max < 0)
			throw CException(_T("最小値または最大値に負数が指定されました。"));
		else if(min > max)
			throw CException(_T("最小値よりも小さい最大値が指定されました。"));
		
		unsigned __int32 tmp= Generate();
		
		tmp%= (max - min) + 1;
		tmp+= min;
		
		_ASSERT(tmp >= min && tmp <= max);
		
		return tmp;
	}
	
	/**
	 *	最大値指定つき乱数生成.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@param	max	生成される乱数の最大値
	 *	@return	max以下の生成された乱数
	 */
	unsigned __int32 xorshift::Generate(unsigned __int32 max){
		if(max < 0)
			throw CException(_T("最大値に負数が指定されました。"));
		
		unsigned __int32 tmp= Generate();
		
		tmp%= max + 1;
		
		_ASSERT(tmp <= max);
		
		return tmp;
	}
	
	/**
	 *	ビット生成.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@return	生成されたビット
	 */
	unsigned __int32 xorshift::GenerateBit(){
		return Generate(1);
	}
	
	/**
	 *	アルファベット生成.
	 *
	 *	@since	0.02
	 *	@return	_TCHAR型のa-zA-z
	 */
	_TCHAR xorshift::GenerateAlphabet(){
		_TCHAR c;
		__int32 offset;
		
		offset= Generate(0, 51);
		
		if(offset < 26)
			c= _T('a') + offset;
		else
			c= _T('A') + offset - 26;
		
		_ASSERT((c >= _T('a') && c <= _T('z')) || (c >= _T('A') && c <= _T('Z')));
		
		return c;
	}
	
	/**
	 *	xorshiftクラスのテストコード.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@return	テストをパスすればtrue、しなければfalse
	 */
	bool xorshift::testxorshift(){
		//	Generate(min, max)が正しく範囲内の数値を返すか
		for(unsigned __int32 min= 0, max= 10000; min != max; ++min, --max){
			for(__int32 count= 0; count < 1000; ++count){
				unsigned __int32 val= Generate(min, max);
				
				if(val < min || val > max){
					return false;
				}
			}
		}
		
		return true;
	}
}

#endif	//	LIB_XORSHIFT_HPP
