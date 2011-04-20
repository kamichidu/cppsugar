#ifndef	LIB_MATH_COMPLEX_HPP
#define	LIB_MATH_COMPLEX_HPP

#define	_USE_MATH_DEFINES

#include <cmath>
#include "CComplex.hpp"

namespace Lib{
namespace Math{
namespace Complex{

	/**
	 *	n乗を求める.
	 *
	 *	@version	0.01
	 *	@param	c	底とする複素数
	 *	@param	n	指数
	 *	@return	cをn乗した結果
	 */
	CComplex const Power(CComplex const& c, int n){
		double abs, arg;
		
		abs= c.Abs();
		arg= c.Arg();
		
		CComplex temp(
			pow(abs, n) * cos(arg * n), 
			pow(abs, n) * sin(arg * n));
		
		return temp;
	}
	
	/**
	 *	累乗(複素数)を求める.
	 *
	 *	@version	0.01
	 *	@param	c	底とする複素数
	 *	@param	n	指数
	 *	@return	cをn乗した結果
	 */
	CComplex const Power(CComplex const& c, CComplex const& n){
		double constant, theta;
		
		constant= exp(n[Re] * log(c.Abs()) - n[Im] * c.Arg());
		theta= n[Re] * c.Arg() + n[Im] * log(c.Abs());
		
		CComplex temp(
			constant * cos(theta), 
			constant * sin(theta));
		
		return temp;
	}
	
	/**
	 *	n乗根を求める.
	 *
	 *	dest[]は、n個分の領域を確保した上でRoot()に渡すこと。
	 *
	 *	@version	0.01
	 *	@param	c		累乗根を求める複素数
	 *	@param	n		整数
	 *	@param	dest	計算したn乗根
	 */
	void Root(CComplex const& c, int n, CComplex dest[]){
		double abs, arg;
		
		abs= c.Abs();
		arg= c.Arg();
		
		for(int i= 0; i < n; ++i){
			dest[i][Re]= exp(log(abs) / n) * cos((arg + 2 * i * M_PI) / n);
			dest[i][Im]= exp(log(abs) / n) * sin((arg + 2 * i * M_PI) / n);
		}
	}
	
	/**
	 *	複素数のexp関数.
	 *
	 *	@version	0.01
	 *	@param	z	指数
	 *	@return	複素数
	 */
	CComplex const Exp(CComplex const& z){
		CComplex temp(
			exp(z[Re]) * cos(z[Im]), 
			exp(z[Re]) * sin(z[Im]));
		
		return temp;
	}
	
	/**
	 *	複素数の正弦関数.
	 *
	 *	@version	0.01
	 *	@param	c	角度
	 *	@return	正弦
	 */
	CComplex const Sin(CComplex const& c){
		CComplex temp(
			0.5 * (exp(-c[Im]) + exp(c[Im])) * sin(c[Re]), 
			-0.5 * (exp(-c[Im]) - exp(c[Im])) * cos(c[Re]));
		
		return temp;
	}
	
	/**
	 *	複素数の余弦関数.
	 *
	 *	@version	0.01
	 *	@param	c	角度
	 *	@return	余弦
	 */
	CComplex const Cos(CComplex const& c){
		CComplex temp(
			0.5 * (exp(-c[Im]) + exp(c[Im])) * cos(c[Re]), 
			0.5 * (exp(-c[Im]) - exp(c[Im])) * sin(c[Re]));
		
		return temp;
	}
	
	/**
	 *	複素数の正接関数.
	 *
	 *	@version	0.01
	 *	@param	c	角度
	 *	@return	正接
	 */
	CComplex const Tan(CComplex const& c){
		CComplex temp;
		
		temp= Sin(c) / Cos(c);
		
		return temp;
	}
	
	/**
	 *	複素数の逆正弦関数.
	 *
	 *	@version	0.01
	 *	@param	z	複素数
	 *	@return	逆正弦
	 */
	CComplex const ASin(CComplex const& z){
		CComplex temp;
		
		temp= 1.0 / Sin(z);
		
		return temp;
	}
	
	/**
	 *	複素数の逆余弦関数.
	 *
	 *	@version	0.01
	 *	@param	z	角度
	 *	@return	逆余弦
	 */
	CComplex const ACos(CComplex const& z){
		CComplex temp;
		
		temp= 1.0 / Cos(z);
		
		return temp;
	}
	
	/**
	 *	複素数の逆正接関数.
	 *
	 *	@version	0.01
	 *	@param	z	角度
	 *	@return	逆正接
	 */
	CComplex const ATan(CComplex const& z){
		CComplex temp;
		
		temp= Cos(z) / Sin(z);
		
		return temp;
	}

}
}
}

#endif	//	#ifndef	LIB_MATH_COMPLEX_HPP
