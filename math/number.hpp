#ifndef LIB_MATH_NUMBER_HPP_
#define LIB_MATH_NUMBER_HPP_

namespace lib{
namespace math{
namespace number{

/**
 * NumT型に対して任意精度での基本演算を提供するクラス。<br>
 * 
 * @author  kamichidu
 * @version 2012-05-20 (日)
 * @param   <NumT>      基本演算を適用する型
 * @param   <Precision> 小数点以下の演算精度
 */
template<class NumT= double, int Precision= -10>
class number{
	public:
		number(NumT const& value);
		~number();
	public:
		NumT const operator + (NumT const& r) const;
		NumT const operator - (NumT const& r) const;
		NumT const operator * (NumT const& r) const;
		NumT const operator / (NumT const& r) const;
		NumT const operator ^ (NumT const& r) const;
		bool operator == (number<NumT> const& r) const;
		bool operator != (number<NumT> const& r) const;
		bool operator >  (number<NumT> const& r) const;
		bool operator >= (number<NumT> const& r) const;
		bool operator <  (number<NumT> const& r) const;
		bool operator <= (number<NumT> const& r) const;
	public:
		number(number<NumT> const& obj);
		NumT const& operator = (number<NumT> const& r);
	private:
		NumT _value;
};

}
}
}

#endif // #ifndef LIB_MATH_NUMBER_HPP_

