#ifndef LIB_CSTOPWATCH_HPP_
#define LIB_CSTOPWATCH_HPP_

#include <sys/time.h>

namespace lib{
namespace time{

/**
 * 時間計測クラス。.<br>
 * 
 * TODO: windows,unix両方で使えるように書き換える
 * 
 * @author  kamichidu
 * @version 2012-05-26 (土)
 */
class stop_watch{
	public:
		typedef double unit_type;
	public:
		stop_watch(unit_type unit);
		~stop_watch();
	public:
		void start();
		void stop();
	public:
		time_t time() const;
		unit_type unit() const;
	private:
		time_t interval(timeval const& start_snap, timeval const& stop_snap) const;
	private:
		unit_type _unit;
		time_t _last_time;
		timeval _snap;
};

inline
stop_watch::stop_watch(unit_type unit) : _unit(unit){
	_snap.tv_sec=  0;
	_snap.tv_usec= 0;
	_last_time=    0;
}

inline
stop_watch::~stop_watch(){
	_unit=         0.;
	_snap.tv_sec=  0;
	_snap.tv_usec= 0;
	_last_time=    0;
}

inline
void stop_watch::start(){
	gettimeofday(&_snap, nullptr);
}

inline
void stop_watch::stop(){
	timeval const tmp= _snap;
	
	gettimeofday(&_snap, nullptr);

	_last_time= interval(tmp, _snap);
}

inline
time_t stop_watch::time() const{
	return _last_time;
}

inline
time_t stop_watch::interval(timeval const& start_snap, timeval const& stop_snap) const{
	time_t const delta_sec=  stop_snap.tv_sec - start_snap.tv_sec;
	time_t const delta_usec= stop_snap.tv_usec - start_snap.tv_usec;

	return delta_sec * 1000 * 1000 + delta_usec;
}

}
}

#endif

