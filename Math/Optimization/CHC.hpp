#ifndef LIB_MATH_OPTIMIZATION_CHC_HPP
#define	LIB_MATH_OPTIMIZATION_CHC_HPP

#include <vector>
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
	 *	HC法用基底抽象クラス.@n
	 *	@n
	 *	【使い方】@n
	 *	1, このクラスを継承したクラスを作成します。@n
	 *	2, ObjectiveFunction、GenerateNeighbor、CheckConstraintの3関数をオーバーライドします。@n
	 *	3, Optimizeを実行します。@n
	 *	@n
	 *	3の結果、求めた最適解が返値として返されます。あとは焼くなり似るなりお好きに。@n
	 *	@n
	 *	【注意点】@n
	 *	　使い方の2で示した3関数は、この基底クラスでは例外を投げるのみの実装しかありません。@n
	 *	そのため、派生クラスで新しい実装を与えない限り、まともに動作しません。@n
	 *	　またTtypeにはC++の基本型以外のクラスも指定できますが、指定するクラスが'>'、'-'、'='演算子オーバーロードを実装している必要があります。@n
	 *	コピーコンストラクタも実装されていれば言うことはありません。コピーコンストラクタについては、std::vectorの実装に依存します。@n
	 *
	 *	@version	0.02
	 *	@date	created at 2011-06-01 ... updated at 2011-06-02
	 *	@author	Chiduru
	 */
	template<class Ttype>
	class CHC{
		public:
			explicit CHC(std::vector<Ttype> const& initial_solution, unsigned long long steps);
			std::vector<Ttype> const Optimize();
		protected:
			virtual Ttype const ObjectiveFunction(std::vector<Ttype> const& vars) const;
			virtual std::vector<Ttype> const GenerateNeighbor(std::vector<Ttype> const& basis) const;
			virtual bool CheckConstraint(std::vector<Ttype> const& neighbor) const;
		private:
			std::vector<Ttype> _initial_solution;
			unsigned long long _steps;
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
	bool CHC<Ttype>::CheckConstraint(std::vector<Ttype> const& neighbor) const{
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
	std::vector<Ttype> const CHC<Ttype>::GenerateNeighbor(std::vector<Ttype> const& basis) const{
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
	Ttype const CHC<Ttype>::ObjectiveFunction(std::vector<Ttype> const& vars) const{
		throw Lib::CException(_T("再定義されていません。"));
	}
	
	/**
	 *	コンストラクタ.
	 *
	 *	@since	0.01
	 *	@param	initial_solution	初期解
	 *	@param	steps	実行ステップ数
	 */
	template<class Ttype>
	inline
	CHC<Ttype>::CHC(std::vector<Ttype> const& initial_solution, unsigned long long steps) 
		: _initial_solution(initial_solution), _steps(steps){
	}
	
	/**
	 *	HC法を実行.
	 *
	 *	@since	0.01
	 *	@return	求めた最適解
	 */
	template<class Ttype>
	std::vector<Ttype> const CHC<Ttype>::Optimize(){
		std::vector<Ttype> solution;
		
		solution= _initial_solution;
		
		//	steps回数だけ解の更新
		for(unsigned long long step= 0; step < _steps; ++step){
			std::vector<Ttype> neighbor;
			Ttype adaptation_level_1, adaptation_level_2;
			
			//	近傍解の生成
			do{
				neighbor= GenerateNeighbor(solution);
			}while(!CheckConstraint(neighbor));
			
			//	適応度の計算
			adaptation_level_1= ObjectiveFunction(solution);
			adaptation_level_2= ObjectiveFunction(neighbor);
			
			//	最適解の更新
			if(adaptation_level_2 > adaptation_level_1){
				solution= neighbor;
			}
		}
		
		return solution;
	}

}
}
}

#endif	//	#ifndef LIB_MATH_OPTIMIZATION_CHC_HPP
