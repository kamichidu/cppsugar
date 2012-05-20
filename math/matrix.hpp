#ifndef LIB_MATH_MATRIX_HPP_
#define LIB_MATH_MATRIX_HPP_

#include <memory>
#include "vector.hpp"

namespace lib{
namespace math{

/**
 * N行M列の行列クラス<br>
 *
 * @author  kamichidu
 * @version 2012-05-20 (日)
 * @param <N>   行数
 * @param <M>   列数
 * @param <Elm> 要素の型
 */
template<int N, int M, class Elm= double>
class matrix{
	public:
		matrix<N, M, Elm> const operator + (matrix<N, M, Elm> const& r) const;
		matrix<N, M, Elm> const operator - (matrix<N, M, Elm> const& r) const;
		template<int O>
			matrix<N, O, Elm> const operator * (matrix<M, O, Elm> const& r) const;
		vector<M> const& operator [] (int row) const;
		vector<M>& operator [] (int row);
	public: // copy semantics
		matrix(matrix<N, M, Elm> const& obj);
		matrix<N, M, Elm>& operator = (matrix<N, M, Elm> const& r);
	public: // move semantics
		matrix(matrix<N, M, Elm>&& obj);
		matrix<N, M, Elm>& operator = (matrix<N, M, Elm>&& r);
	private:
		std::unique_ptr<vector<N, vector<M, Elm>>> _mat;
};

template<int N, int M, class Elm>
inline
matrix<N, M, Elm> const matrix<N, M, Elm>::operator + (matrix<N, M, Elm> const& r) const{
	
}

}
}

#endif // #ifndef LIB_MATH_MATRIX_HPP_

