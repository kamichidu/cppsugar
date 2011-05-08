#ifndef LIB_CSTOPWATCH_HPP
#define LIB_CSTOPWATCH_HPP

#include <tchar.h>
#include <windows.h>
#include "CException.hpp"

namespace Lib{

	/**
	 *	高分解能パフォーマンスカウンタを用いた、時間計測用クラス.
	 *
	 *	StopWatch.h ver0.2をベースに作っている。
	 *	使用関数の性能上、StopWatch::Precision()以上の精度は保証されない。
	 *
	 *	@author	Chiduru
	 *	@version	0.03
	 */
	class CStopWatch{
		public:
			explicit CStopWatch(double unit);
			explicit CStopWatch(CStopWatch const& obj);
			~CStopWatch();
		public:
			void Start();
			void Stop();
			double Time() const;
			double Offset() const;
			double Precision() const;
			double Unit() const;
		private:
			double _unit;
			LARGE_INTEGER* _freq;
			LARGE_INTEGER* _start_time;
			LARGE_INTEGER* _stop_time;
			double _offset;
	};
	
	/**
	 *	コンストラクタ.
	 *
	 *	@since	0.01
	 *	@param	unit	使用単位。1msなら1.0e-3、1usなら1.0e-6、1nsなら1.0e-9と指定する。
	 */
	CStopWatch::CStopWatch(double unit= 1.0e-3) : _unit(unit), _offset(0.0){
		BOOL supported;
		
		try{
			_freq= new LARGE_INTEGER;
			_start_time= new LARGE_INTEGER;
			_stop_time= new LARGE_INTEGER;
		}
		catch(std::bad_alloc const&){
			throw CException(_T("メモリの確保に失敗しました。"));
		}
		
		supported= QueryPerformanceFrequency(_freq);
		
		if(_unit <= 0)
			throw CException(_T("単位には、正の実数を指定してください。"));
		if(!supported)
			throw CException(_T("エラーが起きました。ハードウェアが高分解能パフォーマンスカウンタをサポートしていない可能性があります。"));
		
		//	オフセット値を計算
		Start();
		Stop();
		_offset= Time();
	}
	
	/**
	 *	コピーコンストラスタ.
	 *
	 *	@since	0.01
	 *	@param	obj	被コピーオブジェクト
	 */
	CStopWatch::CStopWatch(CStopWatch const& obj) : _unit(obj._unit), _offset(obj._offset){
		try{
			_freq= new LARGE_INTEGER;
			_start_time= new LARGE_INTEGER;
			_stop_time= new LARGE_INTEGER;
		}
		catch(std::bad_alloc const&){
			throw CException(_T("メモリの確保に失敗しました。"));
		}
		
		*_freq= *(obj._freq);
		*_start_time= *(obj._start_time);
		*_stop_time= *(obj._stop_time);
	}
	
	/**
	 *	デストラクタ.
	 *
	 *	@since	0.01
	 */
	inline
	CStopWatch::~CStopWatch(){
		delete _freq;
		_freq= NULL;
		
		delete _start_time;
		_start_time= NULL;
		
		delete _stop_time;
		_stop_time= NULL;
	}
	
	/**
	 *	計測開始.
	 *
	 *	@since	0.01
	 */
	inline
	void CStopWatch::Start(){
		QueryPerformanceCounter(_start_time);
	}
	
	/**
	 *	計測停止.
	 *
	 *	@since	0.01
	 */
	inline
	void CStopWatch::Stop(){
		QueryPerformanceCounter(_stop_time);
	}
	
	/**
	 *	直近の計測時間.
	 *
	 *	@since	0.01
	 *	@return	直近の計測時間を表すdouble型の値
	 */
	inline
	double CStopWatch::Time() const{
		double time, unit;
		
		unit= 1.0 / (_unit * _freq->QuadPart);
		time= static_cast<double>(_stop_time->QuadPart - _start_time->QuadPart);
		
		return time * unit;
	}
	
	/**
	 *	時間計測にかかるオフセット値.
	 *	単位はTime()と同様。
	 *
	 *	@since	0.03
	 *	@return	オフセット値
	 */
	inline
	double CStopWatch::Offset() const{
		return _offset;
	}
	
	/**
	 *	計測精度.
	 *
	 *	[1秒あたりの経過カウント数]^-1のこと。
	 *	1カウントあたり何秒に相当するか。
	 *
	 *	@since	0.01
	 *	@return	計測精度
	 */
	inline
	double CStopWatch::Precision() const{
		return 1.0 / (_freq->QuadPart * _unit);
	}
	
	/**
	 *	単位.
	 *
	 *	Time()で返される値の桁。
	 *
	 *	@since	0.02
	 *	@return	単位
	 */
	inline
	double CStopWatch::Unit() const{
		return _unit;
	}

}

#endif
