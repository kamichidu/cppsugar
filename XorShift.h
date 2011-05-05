#ifndef	XORSHIFT_H
#define	XORSHIFT_H

#include <stdlib.h>
#include <time.h>

#ifdef	__cplusplus
extern "C"{
#endif

typedef struct{
	unsigned long x;
	unsigned long y;
	unsigned long z;
	unsigned long w;
}XorShift, *lpXorShift;

//	プロトタイプ
void XorShift_New(lpXorShift*);
void XorShift_NewWith(lpXorShift*, unsigned long);
void XorShift_Delete(lpXorShift*);
unsigned long XorShift_Generate(lpXorShift);

/**
 *	構造体初期化.
 *
 *	@param	lpxs	XorShift構造体へのポインタのポインタ
 */
void XorShift_New(lpXorShift* lpxs){
	XorShift_NewWith(lpxs, (unsigned long)time(NULL));
}

/**
 *	構造体初期化.
 *
 *	@param	lpxs	XorShift構造体へのポインタのポインタ
 *	@param	s		乱数の種
 */
void XorShift_NewWith(lpXorShift* lpxs, unsigned long s){
	*lpxs= (lpXorShift)calloc(1, sizeof(XorShift));
	
	(*lpxs)->x= s;
	(*lpxs)->y= (1234 * (*lpxs)->x + 5678);
	(*lpxs)->z= (1234 * (*lpxs)->y + 5678);
	(*lpxs)->w= (1334 * (*lpxs)->z + 5678);
}

/**
 *	構造体破棄.
 *
 *	@param	lpxs	XorShift構造体へのポインタのポインタ
 */
void XorShift_Delete(lpXorShift* lpxs){
	free(*lpxs);
	*lpxs= NULL;
}

/**
 *	乱数生成.
 *
 *	@param	lpxs	XorShift構造体へのポインタ
 *	@return	32bitの乱数
 */
unsigned long XorShift_Generate(lpXorShift lpxs){
	unsigned long t;
	
	t= lpxs->x ^ (lpxs->x << 11);
	lpxs->x= lpxs->y;
	lpxs->y= lpxs->z;
	lpxs->z= lpxs->w;
	
	lpxs->w= (lpxs->w ^ (lpxs->w >> 19)) ^ (t ^ (t >> 8));
	
	return lpxs->w;
}

#ifdef	__cplusplus
}
#endif

#endif	//	#ifndef	XORSHIFT_H
