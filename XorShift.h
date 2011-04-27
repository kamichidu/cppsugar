#ifndef	XORSHIFT_H
#define	XORSHIFT_H

#include<time.h>

#ifdef	__cplusplus
extern "C"{
#endif

typedef struct{
	unsigned long x;
	unsigned long y;
	unsigned long z;
	unsigned long w;
}XorShift;

//	プロトタイプ
void xsInitialize(XorShift*);
void xsInitializeWith(XorShift*, unsigned long);
unsigned long xsGenerate(XorShift*);

/**
 *	構造体初期化.
 */
void xsInitialize(XorShift* lpxs){
	xsInitializeWith(lpxs, (unsigned long)time(NULL));
}

void xsInitializeWith(XorShift* lpxs, unsigned long s){
	lpxs->x= s;
	lpxs->y= (1234 * lpxs->x + 5678);
	lpxs->z= (1234 * lpxs->y + 5678);
	lpxs->w= (1334 * lpxs->z + 5678);
}

unsigned long xsGenerate(XorShift* lpxs){
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
