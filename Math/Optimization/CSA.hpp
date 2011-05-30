#ifndef LIB_MATH_OPTIMIZATION_CSA_HPP
#define	LIB_MATH_OPTIMIZATION_CSA_HPP

#include <limits.h>
#include <math.h>
#include <vector>
#include "CXorShift.hpp"
#include "CException.hpp"

//	optimization	最適化
//	optimize		最適化する
//	objective function	目的関数
//	limiting conditions; constraint	制約条件
//	optimal solution	最適解
//	candidate			候補
//	candidate solution	候補解
//	adaptation	適応

namespace Lib{
namespace Math{
namespace Optimization{

	/**
	 *	SA法用基底抽象クラス.@n
	 *	@n
	 *	【使い方】@n
	 *	1, このクラスを継承したクラスを作成します。@n
	 *	2, ObjectiveFunction、UpdateTemperature、GenerateNeighbor、CheckConstraintの4関数をオーバーライドします。@n
	 *	3, Optimizeを実行します。@n
	 *	@n
	 *	3の結果、求めた最適解が返値として返されます。あとは焼くなり似るなりお好きに。@n
	 *	@n
	 *	【注意点】@n
	 *	　使い方の2で示した4関数は、この基底クラスでは例外を投げるのみの実装しかありません。@n
	 *	そのため、派生クラスで新しい実装を与えない限り、まともに動作しません。@n
	 *	　またTtypeにはC++の基本型以外のクラスも指定できますが、指定するクラスが'>'、'-'、'='演算子オーバーロードを実装している必要があります。@n
	 *	コピーコンストラクタも実装されていれば言うことはありません。コピーコンストラクタについては、std::vectorの実装に依存します。@n
	 *
	 *	@version	0.01
	 *	@date	created at 2011-05-31 ... updated at 2011-05-31
	 *	@author	Chiduru
	 */
	template<class Ttype>
	class CSA{
		public:
			explicit CSA(std::vector<Ttype> const& initial_solution, double initial_temperature, double freeze_temperature);
			std::vector<Ttype> const& Optimize();
		protected:
			virtual Ttype const ObjectiveFunction(std::vector<Ttype> const& vars) const;
			virtual double UpdateTemperature(double t) const;
			virtual std::vector<Ttype> const GenerateNeighbor(std::vector<Ttype> const& basis) const;
			virtual bool CheckConstraint(std::vector<Ttype> const& neighbor) const;
		private:
			std::vector<Ttype> _initial_solution;
			std::vector<Ttype> _optimal_solution;
			double _initial_temperature;
			double _freeze_temperature;
			Lib::CXorShift _random;
	};
	
	/**
	 *	制約条件のチェック.
	 *
	 *	@since	0.01
	 *	@param	neighbor	近傍解
	 *	@return	真偽値
	 */
	template<class Ttype>
	inline
	bool CSA<Ttype>::CheckConstraint(std::vector<Ttype> const& neighbor) const{
		throw Lib::CException(_T("再定義されていません。"));
	}
	
	/**
	 *	近傍解の生成.
	 *
	 *	@since	0.01
	 *	@param	basis	近傍解の基準値
	 *	@return	近傍解
	 */
	template<class Ttype>
	inline
	std::vector<Ttype> const CSA<Ttype>::GenerateNeighbor(std::vector<Ttype> const& basis) const{
		throw Lib::CException(_T("再定義されていません。"));
	}
	
	/**
	 *	温度更新関数.
	 *
	 *	@since	0.01
	 *	@param	now_temperature	現在温度
	 *	@return	更新された温度
	 */
	template<class Ttype>
	inline
	double CSA<Ttype>::UpdateTemperature(double now_temperature) const{
		throw Lib::CException(_T("再定義されていません。"));
	}
	
	/**
	 *	目的関数.
	 *
	 *	@since	0.01
	 *	@param	vars	設計変数
	 *	@return	適応度
	 */
	template<class Ttype>
	inline
	Ttype const CSA<Ttype>::ObjectiveFunction(std::vector<Ttype> const& vars) const{
		throw Lib::CException(_T("再定義されていません。"));
	}
	
	/**
	 *	コンストラクタ.
	 *
	 *	@since	0.01
	 *	@param	initial_solution	初期解
	 *	@param	initial_temperature	初期温度
	 *	@param	freeze_temperature	凍結温度
	 */
	template<class Ttype>
	inline
	CSA<Ttype>::CSA(std::vector<Ttype> const& initial_solution, double initial_temperature, double freeze_temperature) 
		: _initial_solution(initial_solution), _initial_temperature(initial_temperature), _freeze_temperature(freeze_temperature){
	}
	
	/**
	 *	SA法を実行.
	 *
	 *	@since	0.01
	 *	@return	求めた最適解
	 */
	template<class Ttype>
	std::vector<Ttype> const& CSA<Ttype>::Optimize(){
		double temperature;
		std::vector<Ttype> solution;
		
		temperature= _initial_temperature;
		solution= _initial_solution;
		
		//	凍結温度までSA法を実行
		while(temperature >= _freeze_temperature){
			std::vector<Ttype> neighbor;
			Ttype adaptation_level_1, adaptation_level_2;
			
			//	近傍解の生成
			neighbor= GenerateNeighbor(solution);
			
			//	適応度の計算
			adaptation_level_1= ObjectiveFunction(solution);
			adaptation_level_2= ObjectiveFunction(neighbor);
			
			//	最適解の更新
			if(adaptation_level_2 > adaptation_level_1){
				solution= neighbor;
			}
			//	改悪受理のチェック
			else{
				double probability, accept_probability;
				
				probability= static_cast<double>(_random.Generate()) / static_cast<double>(UINT_MAX);
				accept_probability= exp(-abs(adaptation_level_2 - adaptation_level_1) / temperature);
				
				//	確率的に改悪受理
				if(probability < accept_probability)
					solution= neighbor;
			}
			
			//	温度の更新
			temperature= UpdateTemperature(temperature);
		}
		
		//	最適解の保存
		_optimal_solution= solution;
		
		return _optimal_solution;
	}

}
}
}

#endif	//	#ifndef LIB_MATH_OPTIMIZATION_CSA_HPP
