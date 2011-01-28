#ifndef	__CHASH_HPP__
#define	__CHASH_HPP__

#include	<string.h>
#include	"CBucket.hpp"

/**
 *	ハッシュ用クラス.
 *
 *	課題
 *	チェイン法を実装する
 *
 *	@author	Chiduru
 *	@version	0.01
 */
template<class Ttype>
class CHash{
	public:
		/**
		 *	デフォルトコンストラクタ.
		 *	ハッシュテーブルの大きさ10で初期化。.
		 *
		 *	@since	0.01
		 */
		explicit CHash();
		
		/**
		 *	コンストラクタ.
		 *	ハッシュテーブルの大きさを指定して初期化。.
		 *
		 *	@since	0.01
		 *	@param	hash_table_size	ハッシュテーブルの大きさ
		 */
		explicit CHash(int hash_table_size);
		
		/**
		 *	デストラクタ.
		 *
		 *	@since	0.01
		 */
		~CHash();
		
		/**
		 *	keyに対応するデータを返す.
		 *
		 *	@since	0.01
		 *	@param	key	ハッシュキー
		 *	@return	データ
		 */
		const Ttype& Get(const char* key) const;
		
		/**
		 *	keyに対応づけてデータをハッシュテーブルに格納.
		 *
		 *	@since	0.01
		 *	@param	key		ハッシュキー
		 *	@param	data	格納するデータ
		 *	@return	格納に失敗した場合のみ0
		 */
		int Set(const char* key, const Ttype& data);
		
	private:
		/**
		 *	ハッシュ関数.
		 *	渡したキーに対応したハッシュ値を生成して返す。.
		 *	ver0.01では、keyで渡された文字列の平均値を取る。.
		 *
		 *	@since	0.01
		 *	@param	key	ハッシュキー
		 *	@return	生成されたハッシュ値
		 */
		int CalculationHash(const char* key) const;
		
		/**
		 *	デフォルトのハッシュテーブルサイズ.
		 *
		 *	@since	0.01
		 */
		static const int m_default_hash_table_size=	10;
		
		/**
		 *	確保されたハッシュテーブルのサイズ.
		 *
		 *	@since	0.01
		 */
		int	m_hash_table_size;
		
		/**
		 *	ハッシュテーブル.
		 *
		 *	@since	0.01
		 */
		CBucket<Ttype>* m_hash_table;
		
};

/**
 *	デフォルトコンストラクタ.
 *	ハッシュテーブルの大きさ10で初期化。.
 *
 *	@since	0.01
 */
template<class Ttype> CHash<Ttype>::CHash(){
	m_hash_table=	new CBucket<Ttype>[m_default_hash_table_size];
	
	//	ハッシュテーブルのサイズを保存
	m_hash_table_size=	m_default_hash_table_size;
}

/**
 *	コンストラクタ.
 *	ハッシュテーブルの大きさを指定して初期化。.
 *
 *	@since	0.01
 *	@param	hash_table_size	ハッシュテーブルの大きさ
 */
template<class Ttype> CHash<Ttype>::CHash(int hash_table_size){
	m_hash_table=	new CBucket<Ttype>[hash_table_size];
	
	//	ハッシュテーブルのサイズを保存
	m_hash_table_size=	hash_table_size;
}

/**
 *	デストラクタ.
 *
 *	@since	0.01
 */
template<class Ttype> CHash<Ttype>::~CHash(){
	delete [] m_hash_table;
}

/**
 *	keyに対応するデータを返す.
 *
 *	@since	0.01
 *	@param	key	ハッシュキー
 *	@return	データ
 */
template<class Ttype> const Ttype& CHash<Ttype>::Get(const char* key) const{
	int	index=	CalculationHash(key) % m_hash_table_size;
	
	return m_hash_table[index].GetData();
}

/**
 *	keyに対応づけてデータをハッシュテーブルに格納.
 *
 *	@since	0.01
 *	@param	key		ハッシュキー
 *	@param	data	格納するデータ
 *	@return	格納に失敗した場合のみ0
 */
template<class Ttype> int CHash<Ttype>::Set(const char* key, const Ttype& data){
	int	index=	CalculationHash(key) % m_hash_table_size;
	
	m_hash_table[index].Set(key, data);
	
	return 1;
}

/**
 *	ハッシュ関数.
 *	渡したキーに対応したハッシュ値を生成して返す。.
 *	ver0.01では、keyで渡された文字列の平均値を取る。.
 *
 *	@since	0.01
 *	@param	key	ハッシュキー
 *	@return	生成されたハッシュ値
 */
template<class Ttype> int CHash<Ttype>::CalculationHash(const char* key) const{
	int	average=	0;
	int	count=		0;
	
	while(*key){
		average+=	static_cast<int>(*key);
		++count;
		++key;
	}
	
	average/=	count;
	
	return average;
}

#endif	//	__CHASH_HPP__
