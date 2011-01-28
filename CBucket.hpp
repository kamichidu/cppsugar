#ifndef	LIB_CBUCKET_HPP
#define	LIB_CBUCKET_HPP

#include	<string.h>

namespace Lib{
	template<class Ttype>
	class CBucket{
		public:
			/**
			 *	コンストラクタ.
			 *
			 *	@since	0.01
			 */
			explicit CBucket();
			
			/**
			 *	デストラクタ.
			 *
			 *	@since	0.01
			 */
			~CBucket();
			
			/**
			 *	ハッシュキーセット.
			 *
			 *	@since	0.01
			 *	@param	key		ハッシュキー
			 */
			int Set(const char* key, const Ttype& data);
			
			/**
			 *	データセット.
			 *
			 *	@since	0.01
			 *	@param	data	データ
			 */
			int SetData(const Ttype& data);
			
			/**
			 *	ハッシュキー取得.
			 *
			 *	@since	0.01
			 *	@return	ハッシュキー
			 */
			const char* GetKey() const;
			
			/**
			 *	データ取得.
			 *
			 *	@since	0.01
			 *	@return	データ
			 */
			const Ttype& GetData() const;
			
		private:
			/**
			 *	格納するデータ.
			 *
			 *	@since	0.01
			 */
			Ttype	m_data;
			
			/**
			 *	ハッシュキー.
			 *
			 *	@since	0.01
			 */
			char*	m_key;
			
	};

	/**
	 *	コンストラクタ.
	 *
	 *	@since	0.01
	 */
	template<class Ttype>
	CBucket<Ttype>::CBucket(){
		m_key=	new char[0];
	}

	/**
	 *	デストラクタ.
	 *
	 *	@since	0.01
	 */
	template<class Ttype>
	CBucket<Ttype>::~CBucket(){
		delete [] m_key;
	}

	/**
	 *	ハッシュキーと値をセット.
	 *
	 *	@since	0.01
	 *	@param	key		ハッシュキー
	 *	@param	data	データ
	 *	@return	セットが成功したら1、失敗したら0
	 */
	template<class Ttype>
	int CBucket<Ttype>::Set(const char* key, const Ttype& data){
		int	length=	strlen(key) + 1;
		
		delete [] m_key;
		m_key=	new char[length];
		strcpy(m_key, key);
		
		m_data=	data;
		
		return 1;
	}

	/**
	 *	ハッシュキーをゲット.
	 *
	 *	@since	0.01
	 *	@return	ハッシュキー
	 */
	template<class Ttype>
	const char* CBucket<Ttype>::GetKey() const{
		return m_key;
	}

	/**
	 *	データをゲット.
	 *
	 *	@since	0.01
	 *	@return	データ
	 */
	template<class Ttype>
	const Ttype& CBucket<Ttype>::GetData() const{
		return m_data;
	}
}

#endif	//	LIB_CBUCKET_HPP
