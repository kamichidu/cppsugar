#ifndef	LIB_CHASH_HPP
#define	LIB_CHASH_HPP

#include	<tchar.h>
#include	<crtdbg.h>

namespace Lib{
	/**
	 *	ハッシュ用クラス.
	 *
	 *	文字列へのポインタをTtypeとして渡された時にバグが発現する。
	 *		解決法　テンプレートの部分特殊化を使ってポインタ用の汎用クラスを定義
	 *
	 *	コピーコンストラクタが呼ばれた場合の挙動が未実装。
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
			static const int m_default_hash_table_size=	64;
			
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
			
		public:
			/**
			 *	デフォルトコンストラクタ.
			 *	ハッシュテーブルの大きさm_default_hash_table_sizeで初期化。.
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
			 *	クラスの初期化.
			 *
			 *	コンストラクタからのみ呼ばれる。
			 *
			 *	@since	0.03
			 *	@param	hash_table_size	ハッシュテーブルのサイズ
			 */
			int Initialize(int hash_table_size);
			
			/**
			 *	渡されたkeyを持つCELLを検索.
			 *	見つからなかった場合、NULLを返す.
			 *
			 *	@since	0.03
			 *	@param	key	ハッシュキー
			 *	@return	CELLが見つかった場合、見つかったCELLへのポインタ。見つからなかった場合、NULL
			 */
			LPCELL FindCell(LPCTSTR key) const;
			
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
			
	};

	/**
	 *	デフォルトコンストラクタ.
	 *	ハッシュテーブルの大きさm_default_hash_table_sizeで初期化。.
	 *
	 *	@since	0.03
	 */
	template<class Ttype>
	CHash<Ttype>::CHash(){
		Initialize(m_default_hash_table_size);
	}
	
	/**
	 *	コンストラクタ.
	 *	ハッシュテーブルの大きさを指定して初期化。.
	 *
	 *	@since	0.03
	 *	@param	hash_table_size	ハッシュテーブルの大きさ
	 */
	template<class Ttype>
	CHash<Ttype>::CHash(int hash_table_size){
		Initialize(hash_table_size);
	}
	
	/**
	 *	初期化関数.
	 *	コンストラクタの処理をこの関数に委譲。
	 *
	 *	@return	初期化に成功すれば1、失敗なら0
	 */
	template<class Ttype>
	int CHash<Ttype>::Initialize(int hash_table_size){
		try{
			m_hash_table=	new LPCELL[hash_table_size];
			
			for(int i= 0; i < hash_table_size; ++i)
				m_hash_table[i]=	NULL;
			
			//	ハッシュテーブルのサイズを保存
			m_hash_table_size=	hash_table_size;
			
			return 1;
		}
		catch(...){
			return 0;
		}
	}
	
	/**
	 *	デストラクタ.
	 *
	 *	解放忘れをチェック.
	 *
	 *	@since	0.02
	 */
	template<class Ttype>
	CHash<Ttype>::~CHash(){
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
	 *	渡されたkeyが登録されていなければ、例外を発生させる.
	 *
	 *	@since	0.02
	 *	@param	key	ハッシュキー
	 *	@return	keyに対応したデータ
	 */
	template<class Ttype>
	const Ttype& CHash<Ttype>::Get(LPCTSTR key) const{
		LPCELL	cell=	FindCell(key);
		
		if(cell)
			return cell->value;
		else{
			std::basic_string<_TCHAR>	exception_message(_T("Use of unregistered key : "));
			
			exception_message+=	key;
			
			throw exception_message.c_str();
		}
	}

	/**
	 *	keyに対応づけてデータをハッシュテーブルに格納.
	 *
	 *	課題、例外処理の追加.
	 *
	 *	@since	0.01
	 *	@version	0.03
	 *	@param	key		ハッシュキー
	 *	@param	data	格納するデータ
	 *	@return	格納に失敗した場合のみ0、成功したら1
	 */
	template<class Ttype>
	int CHash<Ttype>::Set(LPCTSTR key, const Ttype& data){
		try{
			LPCELL	cell=	FindCell(key);
			
			if(cell){
				cell->value=	data;
			}
			else{
				int		index=	CalculateHash(key) % m_hash_table_size;
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
			
			return 1;
		}
		catch(...){
			return 0;
		}
	}
	
	/**
	 *	渡されたkeyを持つCELLを検索.
	 *	見つからなかった場合、NULLを返す.
	 *
	 *	@since	0.03
	 *	@param	key	ハッシュキー
	 *	@return	CELLが見つかった場合、見つかったCELLへのポインタ。見つからなかった場合、NULL
	 */
	template<class Ttype>
	typename CHash<Ttype>::LPCELL CHash<Ttype>::FindCell(LPCTSTR key) const{
		int		index=	CalculateHash(key) % m_hash_table_size;
		LPCELL	p=		m_hash_table[index];
		
		//	p->keyとkeyが一致すればfalseとなり、ループを抜ける
		//	pがNULLになればループを抜ける
		while(p){
			//	ループ先頭でpがNULLになるのはおかしい
			_ASSERT(p);
			
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
	 *
	 *	@since	0.01
	 *	@param	key	ハッシュキー
	 *	@return	生成されたハッシュ値
	 */
	template<class Ttype>
	int CHash<Ttype>::CalculateHash(LPCTSTR key) const{
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
