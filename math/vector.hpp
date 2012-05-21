#ifndef LIB_MATH_VECTOR_HPP_
#define LIB_MATH_VECTOR_HPP_

#include <vector>
#include <memory>

namespace lib{
namespace math{

/**
 * 多次元ベクトルクラス<br>
 *
 * @author  kamichidu
 * @version 2012-05-20 (日)
 * @param <N>   次元
 * @param <Elm> 要素の型
 */
template<int N, class Elm= double>
class vector{
	public:
		vector();
		template<class InputIterator>
			vector(InputIterator first, InputIterator last);
		~vector();
	public:
		vector<N, Elm> const operator + (vector<N, Elm> const& r) const;
		vector<N, Elm> const operator - (vector<N, Elm> const& r) const;
		Elm const dot_product(vector<N, Elm> const& r) const;
		Elm const& operator [] (int i) const;
		Elm& operator [] (int i);
	public: // copy semantics
		vector(vector<N, Elm> const& obj);
		vector<N, Elm>& operator = (vector<N, Elm> const& r);
	public: // move semantics
		vector(vector<N, Elm>&& obj);
		vector<N, Elm>& operator = (vector<N, Elm>&& r);
	private:
		std::unique_ptr<std::vector<Elm>> _vec;
};

template<int N, class Elm>
inline
vector<N, Elm>::vector(){
	_vec= std::unique_ptr<std::vector<Elm>>(new std::vector<Elm>(N));
}

template<int N, class Elm>
template<class InputIterator>
inline
vector<N, Elm>::vector(InputIterator first, InputIterator last){
	_vec= std::unique_ptr<std::vector<Elm>>(new std::vector<Elm>(first, last));
}

template<int N, class Elm>
inline
vector<N, Elm>::~vector(){
	_vec= std::unique_ptr<std::vector<Elm>>();
}

template<int N, class Elm>
inline
vector<N, Elm> const vector<N, Elm>::operator + (vector<N, Elm> const& r) const{
	vector<N, Elm> buf(_vec->begin(), _vec->end());

	for(int i= 0; i < N; ++i)
		buf[i]+= r._vec->at(i);

	return buf;
}

template<int N, class Elm>
inline
vector<N, Elm> const vector<N, Elm>::operator - (vector<N, Elm> const& r) const{
	vector<N, Elm> buf(_vec->begin(), _vec->end());

	for(int i= 0; i < N; ++i)
		buf[i]-= r._vec->at(i);

	return buf;
}

template<int N, class Elm>
inline
Elm const vector<N, Elm>::dot_product(vector<N, Elm> const& r) const{
	Elm buf;
	
	buf= _vec->front() * r._vec->front();
	for(int i= 1; i < N; ++i)
		buf+= _vec->at(i) * r._vec->at(i);

	return buf;
}

template<int N, class Elm>
inline
Elm const& vector<N, Elm>::operator [] (int i) const{
	return _vec->at(i);
}

template<int N, class Elm>
inline
Elm& vector<N, Elm>::operator [] (int i){
	return _vec->at(i);
}

template<int N, class Elm>
inline
vector<N, Elm>::vector(vector<N, Elm> const& obj){
	_vec= std::unique_ptr<std::vector<Elm>>(new std::vector<Elm>(obj._vec->begin(), obj._vec->end()));
}

template<int N, class Elm>
inline
vector<N, Elm>& vector<N, Elm>::operator = (vector<N, Elm> const& r){
	_vec= std::unique_ptr<std::vector<Elm>>(new std::vector<Elm>(r._vec->begin(), r._vec->end()));
}

template<int N, class Elm>
inline
vector<N, Elm>::vector(vector<N, Elm>&& obj){
	_vec= std::move(obj._vec);
}

template<int N, class Elm>
inline
vector<N, Elm>& vector<N, Elm>::operator = (vector<N, Elm>&& r){
	_vec= std::move(r._vec);

	return *this;
}

}
}

#endif // #ifndef LIB_MATH_VECTOR_HPP_

