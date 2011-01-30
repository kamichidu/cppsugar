#ifndef	LIB_CHASH_HPP
#define	LIB_CHASH_HPP

#include	<tchar.h>
#include	<crtdbg.h>

namespace Lib{
	/**
	 *	ハッシュ用クラス.
	 *
	 *	@author	Chiduru
	 *	@version	0.02
	 */
	template<class Ttype>
	class CHash{
		private:
			typedef	_TCHAR*			LPTSTR;
			typedef	const _TCHAR*	LPCTSTR;
			/**
			 *	単方向リスト.
			 *
			 *	@since0.02
			 */
			struct CELL{
				LPTSTR	key;
				Ttype	value;
				CELL*	next;
			};
			typedef	CELL*	LPCELL;
			
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
			const Ttype& Get(LPCTSTR key) const;
			
			/**
			 *	keyに対応づけてデータをハッシュテーブルに格納.
			 *
			 *	@since	0.01
			 *	@param	key		ハッシュキー
			 *	@param	data	格納するデータ
			 *	@return	格納に失敗した場合のみ0
			 */
			int Set(LPCTSTR key, const Ttype& data);
			
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
			int CalculateHash(LPCTSTR key) const;
			
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
			LPCELL* m_hash_table;
			
	};

	/**
	 *	デフォルトコンストラクタ.
	 *	ハッシュテーブルの大きさ10で初期化。.
	 *
	 *	@since	0.02
	 */
	template<class Ttype> CHash<Ttype>::CHash(){
		m_hash_table=	new LPCELL[m_default_hash_table_size];
		
		for(int i= 0; i < m_default_hash_table_size; ++i)
			m_hash_table[i]=	NULL;
		
		//	ハッシュテーブルのサイズを保存
		m_hash_table_size=	m_default_hash_table_size;
	}
	
	/**
	 *	コンストラクタ.
	 *	ハッシュテーブルの大きさを指定して初期化。.
	 *
	 *	@since	0.02
	 *	@param	hash_table_size	ハッシュテーブルの大きさ
	 */
	template<class Ttype> CHash<Ttype>::CHash(int hash_table_size){
		m_hash_table=	new LPCELL[hash_table_size];
		
		for(int i= 0; i < hash_table_size; ++i)
			m_hash_table[i]=	NULL;
		
		//	ハッシュテーブルのサイズを保存
		m_hash_table_size=	hash_table_size;
	}
	
	/**
	 *	デストラクタ.
	 *
	 *	解放忘れをチェック.
	 *
	 *	@since	0.02
	 */
	template<class Ttype> CHash<Ttype>::~CHash(){
		//	メモリ領域を確保
		LPCELL	next=		NULL;
		LPCELL	free_ptr=	NULL;
		
		for(int i= 0; i < m_hash_table_size; ++i, next= NULL, free_ptr= NULL){
			next=	m_hash_table[i];
			
			while(next){
				free_ptr=	next;
				next=		next->next;
				
//				delete [] free_ptr->key;
				free(free_ptr->key);
				free_ptr->key=	NULL;
				delete free_ptr;
				free_ptr=	NULL;
			}
			
			m_hash_table[i]=	NULL;
		}
		
		//	ポインタ用の領域を開放
		delete [] m_hash_table;
	}
	
	/**
	 *	keyに対応するデータを返す.
	 *
	 *	課題、例外処理の追加.
	 *
	 *	@since	0.02
	 *	@param	key	ハッシュキー
	 *	@return	keyに対応したデータ。見つからなければ0を返す。
	 */
	template<class Ttype> const Ttype& CHash<Ttype>::Get(LPCTSTR key) const{
		int		index=	CalculateHash(key) % m_hash_table_size;
		LPCELL	next=	NULL;
		
		if(m_hash_table[index]){
			next=	m_hash_table[index];
			while(next){
				if(!_tcscmp(next->key, key))
					break;
				next=	next->next;
			}
			
			if(next)
				return next->value;
		}
		
		//	keyに対応するデータが見つからなかった場合、0を返す
		return 0;
	}

	/**
	 *	keyに対応づけてデータをハッシュテーブルに格納.
	 *
	 *	課題、例外処理の追加.
	 *
	 *	@since	0.02
	 *	@param	key		ハッシュキー
	 *	@param	data	格納するデータ
	 *	@return	格納に失敗した場合のみ0、成功したら1
	 */
	template<class Ttype> int CHash<Ttype>::Set(LPCTSTR key, const Ttype& data){
		int		index=	CalculateHash(key) % m_hash_table_size;
		LPCELL*	next=	NULL;
		
		next=	&m_hash_table[index];
		
		while(*next){
			if(!_tcscmp((*next)->key, key))
				break;
			
			next=	&((*next)->next);
		}
		
		if(*next)
			(*next)->value=	data;
		else{
//			int	length=	_tcsclen(key) + 1;
			
			*next=	new CELL;
			
//			next->key=	new _TCHAR[length * sizeof(_TCHAR)];
//			_tcscpy_s(next->key, length, key);
			(*next)->key=	_tcsdup(key);
			(*next)->value=	data;
			(*next)->next=	NULL;
			
//			m_hash_table[index]=	next;
		}
		
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
	template<class Ttype> int CHash<Ttype>::CalculateHash(LPCTSTR key) const{
		int	average=	0;
		int	count=		0;
		
		while(*key){
			average+=	static_cast<int>(*key);
			++count;
			++key;
		}
		
		if(count)
			average/=	count;
		
		if(average < 0)
			average=	-average;
		
		return average;
	}
}

#endif	//	LIB_CHASH_HPP
