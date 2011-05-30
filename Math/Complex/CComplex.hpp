#ifndef	LIB_MATH_COMPLEX_CCOMPLEX_HPP
#define	LIB_MATH_COMPLEX_CCOMPLEX_HPP

#define	_USE_MATH_DEFINES

#include <iostream>
#include <cmath>

namespace Lib{
namespace Math{
namespace Complex{
	enum Identifier{
		Re, 
		Im, 
	};
	
	enum Unit{
		Rad, 
		Deg, 
	};

	/**
	 *	複素数クラス.
	 *
	 *	@author	Chiduru
	 *	@version	0.01
	 */
	class CComplex{
		public:
			//	コンストラクタ
			explicit CComplex(double re, double im);
			
			//	メソッド
			double Arg(Unit unit) const;
			double Abs() const;
			
			//	演算子
			double& operator [] (Identifier id);
			CComplex const& operator () (double re, double im);
			double const& operator [] (Identifier id) const;
			CComplex const operator + (CComplex const& r) const;
			CComplex const operator - (CComplex const& r) const;
			CComplex const operator * (CComplex const& r) const;
			CComplex const operator / (CComplex const& r) const;
			CComplex const& operator += (CComplex const& r);
			CComplex const& operator -= (CComplex const& r);
			CComplex const& operator *= (CComplex const& r);
			CComplex const& operator /= (CComplex const& r);
			bool operator == (CComplex const& r) const;
			bool operator != (CComplex const& r) const;
			friend CComplex const operator * (double l, CComplex const& r);
			friend CComplex const operator * (CComplex const& l, double r);
			friend CComplex const operator / (double l, CComplex const& r);
			friend CComplex const operator / (CComplex const& l, double r);
			
			//	差し込み演算子
			friend std::ostream& operator << (std::ostream& stream, CComplex const& obj);
			friend std::wostream& operator << (std::wostream& stream, CComplex const& obj);
		
		private:
			double _re;
			double _im;
	};
	
	/**
	 *	コンストラクタ.
	 *
	 *	@since	0.01
	 *	@param	re	実部
	 *	@param	im	虚部
	 */
	inline
	CComplex::CComplex(double re= 0.0, double im= 0.0) : _re(re), _im(im){
	}
	
	/**
	 *	アクセサ.
	 *	少々疑問だが、セッターとゲッターを両立させる。
	 *
	 *	@since	0.01
	 *	@param	id	ReかImを指定
	 *	@return	実部か虚部の参照
	 */
	inline
	double& CComplex::operator [] (Identifier id){
		return (id == Re) ? _re : _im;
	}
	inline
	double const& CComplex::operator [] (Identifier id) const{
		return (id == Re) ? _re : _im;
	}
	
	/**
	 *	セッター.
	 *	実部と虚部を同時に設定.
	 *
	 *	@since	0.01
	 *	@param	re	実部
	 *	@param	im	虚部
	 *	@return	*this
	 */
	inline
	CComplex const& CComplex::operator () (double re, double im){
		CComplex temp(re, im);
		*this= temp;
		return *this;
	}
	
	/**
	 *	+演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	*thisとrの加算結果
	 */
	inline
	CComplex const CComplex::operator + (CComplex const& r) const{
		CComplex temp(_re + r._re, _im + r._im);
		return temp;
	}
	
	/**
	 *	-演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	*thisとrの減算結果
	 */
	inline
	CComplex const CComplex::operator - (CComplex const& r) const{
		CComplex temp(_re - r._re, _im - r._im);
		return temp;
	}
	
	/**
	 *	*演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	*thisとrの乗算結果
	 */
	inline
	CComplex const CComplex::operator * (CComplex const& r) const{
		CComplex temp(
			_re * r._re - _im * r._im, 
			_re * r._im + _im * r._re);
		return temp;
	}
	
	/**
	 *	/演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	*thisとrの除算結果
	 */
	inline
	CComplex const CComplex::operator / (CComplex const& r) const{
		CComplex temp(
			(_re * r._re + _im * r._im) / (r._re * r._re + r._im * r._im), 
			(_im * r._re - _re * r._im) / (r._re * r._re + r._im * r._im));
		return temp;
	}
	
	/**
	 *	+=演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	*thisとrの加算結果
	 */
	inline
	CComplex const& CComplex::operator += (CComplex const& r){
		*this= *this + r;
		return *this;
	}
	
	/**
	 *	-=演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	*thisとrの減算結果
	 */
	inline
	CComplex const& CComplex::operator -= (CComplex const& r){
		*this= *this - r;
		return *this;
	}
	
	/**
	 *	*=演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	*thisとrの乗算結果
	 */
	inline
	CComplex const& CComplex::operator *= (CComplex const& r){
		*this= *this * r;
		return *this;
	}
	
	/**
	 *	/=演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	*thisとrの除算結果
	 */
	inline
	CComplex const& CComplex::operator /= (CComplex const& r){
		*this= *this / r;
		return *this;
	}
	
	/**
	 *	==演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	真理値
	 */
	inline
	bool CComplex::operator == (CComplex const& r) const{
		return (_re == r[Re] && _im == r[Im]);
	}
	
	/**
	 *	!=演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	r	右辺
	 *	@return	真理値
	 */
	inline
	bool CComplex::operator != (CComplex const& r) const{
		return (_re != r[Re] || _im != r[Im]);
	}
	
	/**
	 *	*演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	l	
	 *	@param	r
	 *	@return	
	 */
	inline
	CComplex const operator * (double l, CComplex const& r){
		CComplex temp(
			l * r[Re], 
			l * r[Im]);
		return temp;
	}
	
	/**
	 *	*演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	l	
	 *	@param	r
	 *	@return	
	 */
	inline
	CComplex const operator * (CComplex const& l, double r){
		CComplex temp(
			l[Re] * r, 
			l[Im] * r);
		return temp;
	}
	
	/**
	 *	/演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	l	
	 *	@param	r
	 *	@return	
	 */
	inline
	CComplex const operator / (double l, CComplex const& r){
		CComplex temp(l, 0.0);
		temp/= r;
		return temp;
	}
	
	/**
	 *	/演算子オーバーロード.
	 *
	 *	@since	0.01
	 *	@param	l	
	 *	@param	r
	 *	@return	
	 */
	inline
	CComplex const operator / (CComplex const& l, double r){
		CComplex temp(
			l[Re] / r, 
			l[Im] / r);
		return temp;
	}
	
	/**
	 *	偏角を求める.
	 *
	 *	@since	0.01
	 *	@param	unit	単位の指定(ラジアンか度)
	 *	@return	偏角
	 */
	inline
	double CComplex::Arg(Unit unit= Rad) const{
		double rad;
		
		//	[-pi, pi]
		rad= atan2(_im, _re);
		
		if(unit == Deg)
			return (rad * 180.0 * M_1_PI);
		else
			return rad;
	}
	
	/**
	 *	絶対値を求める.
	 *
	 *	@since	0.01
	 *	@return	絶対値
	 */
	inline
	double CComplex::Abs() const{
		return sqrt(_re * _re + _im * _im);
	}
	
	/**
	 *	ostreamに複素数を書き込む.
	 *
	 *	@since	0.01
	 *	@param	stream	書き込み先ストリーム
	 *	@param	obj		複素数
	 *	@return	書き込んだストリーム
	 */
	inline
	std::ostream& operator << (std::ostream& stream, CComplex const& obj){
		stream << "(" << obj[Re] << ") + j(" << obj[Im] << ")";
		return stream;
	}
	
	/**
	 *	wostreamに複素数を書き込む.
	 *
	 *	@since	0.01
	 *	@param	stream	書き込み先ストリーム
	 *	@param	obj		複素数
	 *	@return	書き込んだストリーム
	 */
	inline
	std::wostream& operator << (std::wostream& stream, CComplex const& obj){
		stream << L"(" << obj[Re] << L") + j(" << obj[Im] << L")";
		return stream;
	}

}
}
}

#endif	//	#ifndef	LIB_MATH_COMPLEX_CCOMPLEX_HPP
