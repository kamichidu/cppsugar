#ifndef	LIB_CSTATISTIC_HPP
#define	LIB_CSTATISTIC_HPP

#include <stdio.h>
#include <math.h>

namespace Lib{
	/**
	 *	統計処理クラス.
	 *
	 *	@version	0.01
	 *	@author	Chiduru
	 */
	template<class Ttype>
	class CStatistic{
		public:
			explicit CStatistic(Ttype const* data, int n);
			CStatistic(CStatistic const& obj);
			~CStatistic();
			
			Ttype const& GetMax() const;
			Ttype const& GetMin() const;
			double GetSum() const;
			double GetAverage() const;
			Ttype const& GetMode() const;
			double GetMedian() const;
			double GetVariance() const;
			double GetStandardDeviation() const;
		
		protected:
			Ttype* _data;
			int _size;
	};
	
	/**
	 *	コンストラクタ.
	 *
	 *	後のことを考えて、昇順にソートしておく。
	 *
	 *	@since	0.01
	 *	@param	data	統計データが保存された配列の先頭ポインタ
	 *	@param	n		統計データの個数
	 */
	template<class Ttype>
	CStatistic<Ttype>::CStatistic(Ttype const* data, int n) : _size(n){
		_data= new Ttype[_size];
		
		for(int i= 0; i < _size; ++i)
			_data[i]= data[i];
		
		//	ソート
		for(int i= 0; i < _size - 1; ++i){
			for(int j= _size - 1; j > i; --j){
				if(_data[j - 1] > _data[j]){
					Ttype temp;
					temp= _data[j];
					_data[j]= _data[j - 1];
					_data[j - 1]= temp;
				}
			}
		}
	}
	
	/**
	 *	コピーコンストラクタ.
	 *
	 *	@since	0.01
	 *	@param	obj	被コピー対象のオブジェクト
	 */
	template<class Ttype>
	CStatistic<Ttype>::CStatistic(CStatistic const& obj) : _size(obj._size){
		_data= new Ttype[_size];
		
		for(int i= 0; i < _size; ++i)
			_data[i]= obj._data[i];
		
		//	ソート
		for(int i= 0; i < _size - 1; ++i){
			for(int j= _size - 1; j > i; --j){
				if(_data[j - 1] > _data[j]){
					Ttype temp;
					temp= _data[j];
					_data[j]= _data[j - 1];
					_data[j - 1]= temp;
				}
			}
		}
	}
	
	/**
	 *	デストラクタ.
	 *
	 *	@since	0.01
	 */
	template<class Ttype>
	CStatistic<Ttype>::~CStatistic(){
		delete [] _data;
		_data= NULL;
	}
	
	/**
	 *	統計データ中の最大値.
	 *
	 *	@since	0.01
	 *	@return	最大値
	 */
	template<class Ttype>
	Ttype const& CStatistic<Ttype>::GetMax() const{
		return _data[_size - 1];
	}
	
	/**
	 *	統計データ中の最小値.
	 *
	 *	@since	0.01
	 *	@return	最小値
	 */
	template<class Ttype>
	Ttype const& CStatistic<Ttype>::GetMin() const{
		return _data[0];
	}
	
	/**
	 *	合計を求める.
	 *
	 *	@since	0.01
	 *	@return	合計
	 */
	template<class Ttype>
	double CStatistic<Ttype>::GetSum() const{
		double sum;
		
		sum= 0.0;
		
		for(int i= 0; i < _size; ++i)
			sum+= _data[i];
		
		return sum;
	}
	
	/**
	 *	平均を求める.
	 *
	 *	@since	0.01
	 *	@return	平均
	 */
	template<class Ttype>
	double CStatistic<Ttype>::GetAverage() const{
		return GetSum() / _size;
	}
	
	/**
	 *	最頻値を求める.
	 *
	 *	@return	最頻値
	 */
	template<class Ttype>
	Ttype const& CStatistic<Ttype>::GetMode() const{
		return 0;
	}
	
	/**
	 *	中央値を求める.
	 *
	 *	@return	中央値
	 */
	template<class Ttype>
	double CStatistic<Ttype>::GetMedian() const{
		//	奇数の場合
		if(_size % 2){
			return _data[_size / 2];
		}
		//	偶数の場合
		else{
			double val;
			val= _data[_size / 2 - 1];
			val+= _data[_size / 2];
			return val / 2.0;
		}
	}
	
	/**
	 *	分散を求める.
	 *
	 *	@since	0.01
	 *	@return	分散
	 */
	template<class Ttype>
	double CStatistic<Ttype>::GetVariance() const{
		double average, variance;
		
		average= GetAverage();
		
		variance= 0.0;
		for(int i= 0; i < _size; ++i){
			variance+= (_data[i] - average) * (_data[i] - average);
		}
		variance/= _size;
		
		return variance;
	}
	
	/**
	 *	標準偏差を求める.
	 *
	 *	@since	0.01
	 *	@return	標準偏差
	 */
	template<class Ttype>
	double CStatistic<Ttype>::GetStandardDeviation() const{
		return sqrt(GetVariance());
	}
}

#endif	//	LIB_CSTATISTIC_HPP
