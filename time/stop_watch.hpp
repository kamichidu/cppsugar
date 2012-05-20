#ifndef LIB_CSTOPWATCH_HPP_
#define LIB_CSTOPWATCH_HPP_

namespace lib{

	/**
	 *	高分解能パフォーマンスカウンタを用いた、時間計測用クラス.
	 *
	 *	TODO: windows,unix両方で使えるように書き換える
	 *
	 *	@author  kamichidu
	 *	@version 2012-05-20 (日)
	 */
	class stop_watch{
		public:
			explicit stop_watch(double unit);
			explicit stop_watch(stop_watch const& obj);
			~stop_watch();
		public:
			void start();
			void stop();
			double time() const;
			double offset() const;
			double precision() const;
			double unit() const;
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
	stop_watch::stop_watch(double unit= 1.0e-3) : _unit(unit), _offset(0.0){
		bool supported;
		
		try{
			_freq= new LARGE_INTEGER;
			_start_time= new LARGE_INTEGER;
			_stop_time= new LARGE_INTEGER;
		}
		catch(std::bad_alloc const&){
			throw exception(L"メモリの確保に失敗しました。");
		}
		
		supported= QueryPerformanceFrequency(_freq);
		
		if(_unit <= 0)
			throw exception(L"単位には、正の実数を指定してください。");
		if(!supported)
			throw exception(L"エラーが起きました。ハードウェアが高分解能パフォーマンスカウンタをサポートしていない可能性があります。");
		
		//	オフセット値を計算
		start();
		stop();
		_offset= time();
	}
	
	/**
	 *	コピーコンストラスタ.
	 *
	 *	@since	0.01
	 *	@param	obj	被コピーオブジェクト
	 */
	stop_watch::stop_watch(stop_watch const& obj) : _unit(obj._unit), _offset(obj._offset){
		try{
			_freq= new LARGE_INTEGER;
			_start_time= new LARGE_INTEGER;
			_stop_time= new LARGE_INTEGER;
		}
		catch(std::bad_alloc const&){
			throw exception(L"メモリの確保に失敗しました。");
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
	stop_watch::~stop_watch(){
		delete _freq;
		_freq= nullptr;
		
		delete _start_time;
		_start_time= nullptr;
		
		delete _stop_time;
		_stop_time= nullptr;
	}
	
	/**
	 *	計測開始.
	 *
	 *	@since	0.01
	 */
	inline
	void stop_watch::start(){
		QueryPerformanceCounter(_start_time);
	}
	
	/**
	 *	計測停止.
	 *
	 *	@since	0.01
	 */
	inline
	void stop_watch::stop(){
		QueryPerformanceCounter(_stop_time);
	}
	
	/**
	 *	直近の計測時間.
	 *
	 *	@since	0.01
	 *	@return	直近の計測時間を表すdouble型の値
	 */
	inline
	double stop_watch::time() const{
		double time, unit;
		
		unit= 1.0 / (_unit * _freq->QuadPart);
		time= static_cast<double>(_stop_time->QuadPart - _start_time->QuadPart);
		
		return time * unit;
	}
	
	/**
	 *	時間計測にかかるオフセット値.
	 *	単位はtime()と同様。
	 *
	 *	@since	0.03
	 *	@return	オフセット値
	 */
	inline
	double stop_watch::offset() const{
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
	double stop_watch::precision() const{
		return 1.0 / (_freq->QuadPart * _unit);
	}
	
	/**
	 *	単位.
	 *
	 *	time()で返される値の桁。
	 *
	 *	@since	0.02
	 *	@return	単位
	 */
	inline
	double stop_watch::unit() const{
		return _unit;
	}

}

#endif

