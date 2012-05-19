#ifndef	LIB_MATH_COMPLEX_HPP
#define	LIB_MATH_COMPLEX_HPP

#define	_USE_MATH_DEFINES

#include <cmath>
#include "Math/Complex/CComplex.hpp"
#include "CException.hpp"

namespace Lib{
namespace Math{
namespace Complex{

	/**
	 *	2次元離散空間フーリエ変換.
	 *
	 *	@version	0.01
	 *	@param	dest	周波数成分
	 *	@param	data	離散空間信号
	 *	@param	width	幅
	 *	@param	height	高さ
	 */
	void DoDSFT(CComplex dest[], CComplex const data[], int width, int height){
		try{
			//	引数チェック
			if(dest == NULL || data == NULL || width <= 0 || height <= 0)
				throw _T("不正な値が引数として渡されました。");
			
			//	DSFT実行
			for(int f2= 0; f2 < height; ++f2){
				for(int f1= 0; f1 < width; ++f1){
					int dest_idx;
					double W_C, H_C;
					
					dest_idx= f2 * width + f1;
					
					dest[dest_idx][Re]= dest[dest_idx][Im]= 0.;
					
					W_C= 2. * M_PI * static_cast<double>(f1) / static_cast<double>(width);
					H_C= 2. * M_PI * static_cast<double>(f2) / static_cast<double>(height);
					
					for(int y= 0; y < height; ++y){
						for(int x= 0; x < width; ++x){
							int data_idx;
							double theta;
							
							data_idx= y * width + x;
							theta= W_C * x + H_C * y;
							
							dest[dest_idx][Re]+= data[data_idx][Re] * cos(theta);
							dest[dest_idx][Im]-= data[data_idx][Re] * sin(theta);
						}
					}
				}
			}
		}
		catch(_TCHAR const* msg){
			throw CException(msg);
		}
		catch(CException const& e){
			throw e;
		}
		catch(...){
			throw CException(_T("不明なエラーが発生しました。"));
		}
	}
	
	/**
	 *	2次元離散空間逆フーリエ変換.
	 *
	 *	@version	0.01
	 *	@param	dest	離散空間信号
	 *	@param	data	周波数成分
	 *	@param	width	幅
	 *	@param	height	高さ
	 */
	void DoIDSFT(CComplex dest[], CComplex const data[], int width, int height){
		try{
			throw CException(_T("未実装"));
		}
		catch(CException const& e){
			throw e;
		}
		catch(...){
			throw CException(_T("不明なエラーが発生しました。"));
		}
	}
	
	/**
	 *	1次元離散時間フーリエ変換.
	 *
	 *	@version	0.01
	 *	@param	dest	周波数成分
	 *	@param	data	信号値
	 *	@param	n		サンプル点の個数
	 */
	void DoDFT(CComplex dest[], CComplex const data[], int n){
		try{
			//	引数チェック
			if(dest == NULL || data == NULL || n <= 0)
				throw _T("不正な値が引数として渡されました。");
			
			//	DFT実行
			for(int f= 0; f < n; ++f){
				dest[f][Re]= dest[f][Im]= 0.;
				
				for(int t= 0; t < n; ++t){
					dest[f][Re]+= data[t][Re] * cos(2. * M_PI * f * t / n);
					dest[f][Im]-= data[t][Im] * sin(2. * M_PI * f * t / n);
				}
			}
		}
		catch(_TCHAR const* msg){
			throw CException(msg);
		}
		catch(CException const& e){
			throw e;
		}
		catch(...){
			throw CException(_T("不明なエラーが発生しました。"));
		}
	}
	
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
	 *	2乗根の主値を求める.
	 *
	 *	@version	0.01
	 *	@param	z	底
	 *	@return	zの2乗根の主値
	 */
	CComplex const Root(CComplex const& z){
		double abs, arg;
		CComplex temp;
		
		abs= z.Abs();
		arg= z.Arg();
		
		temp(
			exp(log(abs) / 2.0) * cos(arg / 2.0), 
			exp(log(abs) / 2.0) * sin(arg / 2.0));
		
		return temp;
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
	 *	複素数の自然対数.
	 *
	 *	@version	0.01
	 *	@param	z	複素数
	 *	@return	主値
	 */
	CComplex const Log(CComplex const& z){
		CComplex temp(
			log(z.Abs()), 
			z.Arg());
		
		return temp;
	}
	
//	ここから下、定義を間違えて実装している。
	/**
	 *	複素数の逆正弦関数.
	 *
	 *	@version	0.01
	 *	@param	z	複素数
	 *	@return	逆正弦
	 */
	CComplex const ASin(CComplex const& z){
		CComplex a, b, c, d, temp;
		
		b(0.0, 1.0);
		c(1.0, 0.0);
		
		temp= Log(b * z - Root(c - Power(z, 2))) / b;
		
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
