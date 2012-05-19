#ifndef	LIB_MATH_HPP
#define	LIB_MATH_HPP

#include <windows.h>

namespace Lib{
namespace Math{
	
	/**
	 *	run_count回の試行を100回行い、その平均実行時間を求める.
	 *
	 *	@param	(*func)()	計測対象の関数ポインタ
	 *	@param	run_count	試行回数。10万回がデフォルト。
	 *	@return	平均実行時間
	 */
	double MeasureRunTime(void (*func)(), int run_count= 100000){
		DWORD start, stop;
		double ret;
		
		ret= 0.0;
		for(int n= 0; n < 100; ++n){
			start= GetTickCount();
			for(int i= 0; i < run_count; ++i)
				(*func)();
			stop= GetTickCount();
			
			ret+= static_cast<double>(stop - start) / static_cast<double>(run_count);
		}
		
		return ret / 100.0;
	}

}
}

#endif	//	LIB_MATH_HPP
