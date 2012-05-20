#ifndef	LIB_CSTATISTIC_HPP_
#define	LIB_CSTATISTIC_HPP_

#include <cmath>

namespace lib{
	/**
	 *	統計処理クラス.
	 *
	 *	@version 2012-05-20 (日)
	 *	@author  kamichidu
	 */
	template<class Ttype>
	class statistic{
		public:
			statistic(Ttype const* data, int n);
			explicit statistic(statistic const& obj);
			~statistic();
		public:
			int size() const;
			Ttype const& max() const;
			Ttype const& min() const;
			double sum() const;
			double mean() const;
			Ttype const& mode() const;
			double median() const;
			double variance() const;
			double standard_deviation() const;
		private:
			// TODO: データの持ち方をc++ライクに変更
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
	statistic<Ttype>::statistic(Ttype const* data, int n) : _size(n){
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
	statistic<Ttype>::statistic(statistic const& obj) : _size(obj._size){
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
	statistic<Ttype>::~statistic(){
		delete [] _data;
		_data= nullptr;
	}
	
	/**
	 *	登録されたデータの個数.
	 *
	 *	@since	0.02
	 *	@return	統計データの個数
	 */
	template<class Ttype>
	int statistic<Ttype>::size() const{
		return _size;
	}
	
	/**
	 *	統計データ中の最大値.
	 *
	 *	@since	0.01
	 *	@return	最大値
	 */
	template<class Ttype>
	Ttype const& statistic<Ttype>::max() const{
		return _data[_size - 1];
	}
	
	/**
	 *	統計データ中の最小値.
	 *
	 *	@since	0.01
	 *	@return	最小値
	 */
	template<class Ttype>
	Ttype const& statistic<Ttype>::min() const{
		return _data[0];
	}
	
	/**
	 *	合計を求める.
	 *
	 *	@since	0.01
	 *	@return	合計
	 */
	template<class Ttype>
	double statistic<Ttype>::sum() const{
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
	double statistic<Ttype>::mean() const{
		return sum() / _size;
	}
	
	/**
	 *	最頻値を求める.
	 *
	 *	@since	0.02
	 *	@return	最頻値
	 */
	template<class Ttype>
	Ttype const& statistic<Ttype>::mode() const{
		
		return 0;
	}
	
	/**
	 *	中央値を求める.
	 *
	 *	@since	0.01
	 *	@return	中央値
	 */
	template<class Ttype>
	double statistic<Ttype>::median() const{
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
	double statistic<Ttype>::variance() const{
		double average, variance;
		
		average= mean();
		
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
	double statistic<Ttype>::standard_deviation() const{
		return sqrt(variance());
	}
}

#endif	//	LIB_CSTATISTIC_HPP_

