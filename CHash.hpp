#ifndef	LIB_CHASH_HPP
#define	LIB_CHASH_HPP

#include	"CException.hpp"
#include	<tchar.h>
#include	<crtdbg.h>

namespace Lib{
	/**
	 *	ハッシュ用クラス.
	 *
	 *	コピーコンストラクタが呼ばれた場合の挙動が未実装。.
	 *	
	 *
	 *	@author	Chiduru
	 *	@version	0.03
	 */
	template<class Ttype>
	class CHash{
		private:
			typedef	_TCHAR*			LPTSTR;
			typedef	const _TCHAR*	LPCTSTR;
			typedef	int				INT32;
			typedef	long long		INT64;
			
			/**
			 *	単方向リスト.
			 *
			 *	@since	0.02
			 */
			struct CELL{
				LPTSTR	key;
				Ttype	value;
				CELL*	next;
			};
			typedef	CELL*	LPCELL;
			
			/**
			 *	デフォルトのハッシュテーブルサイズ.
			 *
			 *	@since	0.01
			 */
			static const INT32 m_default_hash_table_size=	64;
			
			/**
			 *	確保されたハッシュテーブルのサイズ.
			 *
			 *	@since	0.01
			 */
			INT32	m_hash_table_size;
			
			/**
			 *	ハッシュテーブル.
			 *
			 *	@since	0.01
			 */
			LPCELL* m_hash_table;
			
		public:
			explicit CHash();
			explicit CHash(INT32 hash_table_size);
			~CHash();
			const Ttype& Get(LPCTSTR key) const;
			void Set(LPCTSTR key, const Ttype& data);
			const Ttype& operator [] (LPCTSTR key) const;
			
		private:
			bool Initialize(INT32 hash_table_size);
			LPCELL FindCell(LPCTSTR key) const;
		public:
			INT32 CalculateHash(LPCTSTR key) const;
			
	};

	/**
	 *	デフォルトコンストラクタ.
	 *	ハッシュテーブルの大きさm_default_hash_table_sizeで初期化。.
	 *
	 *	@since	0.01
	 *	@version	0.03
	 */
	template<class Ttype>
	inline CHash<Ttype>::CHash(){
		Initialize(m_default_hash_table_size);
	}
	
	/**
	 *	コンストラクタ.
	 *	ハッシュテーブルの大きさを指定して初期化。.
	 *
	 *	@since	0.01
	 *	@version	0.03
	 *	@param	hash_table_size	ハッシュテーブルの大きさ
	 */
	template<class Ttype>
	inline CHash<Ttype>::CHash(INT32 hash_table_size){
		Initialize(hash_table_size);
	}
	
	/**
	 *	初期化関数.
	 *	コンストラクタの処理をこの関数に委譲。
	 *
	 *	@since	0.02
	 *	@version	0.01
	 *	@return	初期化に成功すれば1、失敗なら0
	 */
	template<class Ttype>
	inline bool CHash<Ttype>::Initialize(INT32 hash_table_size){
		try{
			m_hash_table=	new LPCELL[hash_table_size];
			
			for(INT32 i= 0; i < hash_table_size; ++i)
				m_hash_table[i]=	NULL;
			
			//	ハッシュテーブルのサイズを保存
			m_hash_table_size=	hash_table_size;
			
			return true;
		}
		catch(...){
			return false;
		}
	}
	
	/**
	 *	デストラクタ.
	 *
	 *	解放忘れをチェック.
	 *
	 *	@since	0.01
	 *	@version	0.03
	 */
	template<class Ttype>
	CHash<Ttype>::~CHash(){
		//	メモリ領域を確保
		LPCELL	next=		NULL;
		LPCELL	free_ptr=	NULL;
		
		for(INT32 i= 0; i < m_hash_table_size; ++i, next= NULL, free_ptr= NULL){
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
		m_hash_table=	NULL;
	}
	
	/**
	 *	keyに対応するデータを返す.
	 *
	 *	例外条件:
	 *		keyが存在しない。.
	 *		keyがNULL。.
	 *
	 *	@since	0.01
	 *	@version	0.03
	 *	@param	key	ハッシュキー
	 *	@return	keyに対応したデータ
	 */
	template<class Ttype>
	inline const Ttype& CHash<Ttype>::Get(LPCTSTR key) const{
		if(key){
			LPCELL	cell=	FindCell(key);
			
			if(cell)
				return cell->value;
			else{
				std::basic_string<_TCHAR>	message(_T("存在しないハッシュキーが使用されました。 : key == "));
				message+=	key;
				throw message.c_str();
			}
		}
		else{
			std::basic_string<_TCHAR>	message(_T("NULLポインタが渡されました。"));
			throw message.c_str();
		}
	}
	
	/**
	 *	keyに対応するデータを返す。.
	 *
	 *	例外条件:.
	 *		keyが存在しない。.
	 *		keyがNULL。.
	 *
	 *	@since	0.03
	 *	@version	0.01
	 *	@param	key	ハッシュキー
	 *	@return keyに対応したデータ
	 */
	template<class Ttype>
	inline const Ttype& CHash<Ttype>::operator [] (LPCTSTR key) const{
		try{
			return Get(key);
		}
		catch(_TCHAR* e){
			throw e;
		}
	}

	/**
	 *	keyに対応づけてデータをハッシュテーブルに格納.
	 *
	 *	デバッグモード時、key==NULLならばアサート。.
	 *
	 *	
	 *
	 *	@since	0.01
	 *	@version	0.03
	 *	@param	key		ハッシュキー
	 *	@param	data	格納するデータ
	 */
	template<class Ttype>
	void CHash<Ttype>::Set(LPCTSTR key, const Ttype& data){
		try{
			_ASSERT(key);
			INT32	index=	CalculateHash(key) % m_hash_table_size;
			LPCELL	cell=	FindCell(key);
			
			if(cell){
				cell->value=	data;
			}
			else{
				LPCELL*	last=	&m_hash_table[index];
				
				//	CELLの末尾を検索
				while(*last)
					last=	&((*last)->next);
				
				//	*lastがNULLでなければならない
				_ASSERT(!(*last));
				
				//	CELLを追加
				*last=			new CELL;
				(*last)->key=	_tcsdup(key);
				(*last)->value=	data;
				(*last)->next=	NULL;
			}
		}
		catch(_TCHAR* e){ throw e; }
		catch(std::bad_alloc& e){ throw e; }
		catch(...){ throw; }
	}
	
	/**
	 *	渡されたkeyを持つCELLを検索.
	 *	見つからなかった場合、NULLを返す.
	 *
	 *	@since	0.03
	 *	@version	0.01
	 *	@param	key	ハッシュキー
	 *	@return	CELLが見つかった場合、見つかったCELLへのポインタ。見つからなかった場合、NULL
	 */
	template<class Ttype>
	inline typename CHash<Ttype>::LPCELL CHash<Ttype>::FindCell(LPCTSTR key) const{
		INT32	index=	CalculateHash(key) % m_hash_table_size;
		LPCELL	p=		m_hash_table[index];
		
		//	p->keyとkeyが一致すればfalseとなり、ループを抜ける
		//	pがNULLになればループを抜ける
		while(p){
			if(!_tcscmp(p->key, key))
				break;
			else
				p=	p->next;
		}
		
		return p;
	}

	/**
	 *	ハッシュ関数.
	 *	渡したキーに対応したハッシュ値を生成して返す。.
	 *	ver0.01では、keyで渡された文字列の平均値を取る。.
	 *	ver0.02では、平方採中法。.
	 *
	 *	@since	0.01
	 *	@version	0.02
	 *	@param	key	ハッシュキー
	 *	@return	生成されたハッシュ値
	 */
	template<class Ttype>
	inline INT32 CHash<Ttype>::CalculateHash(LPCTSTR key) const{
		_ASSERT(key);
		INT64	sum=		0;
		INT64	mask=		0xFFFFFFFF << 16;
		INT32	hash_value=	0;
		
		while(*key){
			sum+=	static_cast<INT64>(*key);
			++key;
		}
		
		hash_value=	static_cast<INT32>(((sum * sum) & mask) >> 16);
		
		_ASSERT(hash_value >= 0);
		
		return hash_value;
	}
}

#endif	//	LIB_CHASH_HPP
