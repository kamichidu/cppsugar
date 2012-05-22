#ifndef	LIB_MATH_STATISTIC_HPP_
#define	LIB_MATH_STATISTIC_HPP_

#include <cmath>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

namespace lib{
namespace math{

/**
 *	統計処理クラス。.<br>
 *
 *	@version 2012-05-22 (火)
 *	@author  kamichidu
 */
template<class Elm>
class statistic{
	public:
		template<class InputIterator>
			statistic(InputIterator first, InputIterator last);
		statistic(std::initializer_list<Elm> const& init);
		explicit statistic(statistic const& obj);
		~statistic();
	public:
		int size() const;
		Elm const& max() const;
		Elm const& min() const;
		double sum() const;
		double mean() const;
		Elm const& mode() const;
		double median() const;
		double variance() const;
		double standard_deviation() const;
	private:
		typedef std::unique_ptr<std::vector<Elm>> lp_vector;
		lp_vector _data;
};

template<class Elm>
template<class InputIterator>
inline
statistic<Elm>::statistic(InputIterator first, InputIterator last) : 
	_data(lp_vector(new std::vector<Elm>(first, last))){
	
	std::sort(_data->begin(), _data->end());
}

template<class Elm>
inline
statistic<Elm>::statistic(std::initializer_list<Elm> const& init) : 
	_data(lp_vector(new std::vector<Elm>(init.begin(), init.end()))){

	std::sort(_data->begin(), _data->end());
}

template<class Elm>
inline
statistic<Elm>::~statistic(){
	_data= lp_vector();
}

template<class Elm>
inline
int statistic<Elm>::size() const{
	return _data->size();
}

template<class Elm>
inline
Elm const& statistic<Elm>::max() const{
	return _data->back();
}

template<class Elm>
inline
Elm const& statistic<Elm>::min() const{
	return _data->front();
}

template<class Elm>
inline
double statistic<Elm>::sum() const{
	double sum;

	sum= 0.;
	for(auto const& elm : *_data)
		sum+= elm;

	return sum;
}

template<class Elm>
inline
double statistic<Elm>::mean() const{
	return sum() / static_cast<double>(size());
}

template<class Elm>
inline
double statistic<Elm>::median() const{
	double const med= _data->at(size() / 2);

	if(size() % 2 == 0)
		return (med + _data->at(size() / 2 + 1)) / 2.;

	return med;
}

template<class Elm>
inline
double statistic<Elm>::variance() const{
	double average, variance;
	
	average= mean();
	
	variance= 0.0;
	for(auto const& elm : *_data){
		variance+= (elm - average) * (elm - average);
	}
	variance/= static_cast<double>(_data->size());
	
	return variance;
}

template<class Elm>
inline
double statistic<Elm>::standard_deviation() const{
	return sqrt(variance());
}

}
}

#endif	//	LIB_MATH_STATISTIC_HPP_

