#ifndef	LIB_XORSHIFT_HPP
#define	LIB_XORSHIFT_HPP

#include	<tchar.h>
#include	<time.h>
#include	<crtdbg.h>
#include	"CException.hpp"

namespace Lib{
	/**
	 *	XorShiftによる乱数生成ジェネレータ.
	 *
	 *	@author	Chiduru
	 *	@version	0.01
	 */
	class CXorShift{
		public:
			explicit CXorShift(unsigned int seed);
			unsigned int Generate();
			unsigned int Generate(unsigned int min, unsigned int max);
			unsigned int Generate(unsigned int max);
			unsigned int GenerateBit();
			
			bool TestCXorShift();
		
		private:
			unsigned int _x, _y, _z, _w;
			
	};
	
	/**
	 *	コンストラクタ.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@param	seed	乱数の種
	 */
	CXorShift::CXorShift(unsigned int seed= static_cast<unsigned int>(time(NULL))){
		_x=	seed;
		_y=	1234 * _x + 56789;
		_z=	1234 * _y + 56789;
		_w=	1234 * _z + 56789;
	}
	
	/**
	 *	乱数生成.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@return	生成された乱数
	 */
	unsigned int CXorShift::Generate(){
		unsigned int	t;
		
		t=	_x ^ (_x << 11);
		_x=	_y;
		_y=	_z;
		_z=	_w;
		_w=	(_w ^ (_w >> 19)) ^ (t ^ (t >> 8));
		
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
	unsigned int CXorShift::Generate(unsigned int min, unsigned int max){
		if(min < 0 || max < 0)
			throw CException(_T("最小値または最大値に負数が指定されました。"));
		else if(min > max)
			throw CException(_T("最小値よりも小さい最大値が指定されました。"));
		
		unsigned int tmp=	Generate();
		
		tmp%=	(max - min) + 1;
		tmp+=	min;
		
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
	unsigned int CXorShift::Generate(unsigned int max){
		if(max < 0)
			throw CException(_T("最大値に負数が指定されました。"));
		
		unsigned int tmp=	Generate();
		
		tmp%=	max + 1;
		
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
	unsigned int CXorShift::GenerateBit(){
		return Generate(1);
	}
	
	/**
	 *	CXorShiftクラスのテストコード.
	 *
	 *	@since	0.01
	 *	@version	0.01
	 *	@return	テストをパスすればtrue、しなければfalse
	 */
	bool CXorShift::TestCXorShift(){
		//	Generate(min, max)が正しく範囲内の数値を返すか
		for(unsigned int min= 0, max= 10000; min != max; ++min, --max){
			for(int count= 0; count < 1000; ++count){
				unsigned int val=	Generate(min, max);
				
				if(val < min || val > max){
					return false;
				}
			}
		}
		
		return true;
	}
}

#endif	//	LIB_XORSHIFT_HPP
