/* sf_modf.c -- float version of s_modf.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

#include "fdlibm.h"

#ifdef __STDC__
static const float one = 1.0;
#else
static float one = 1.0;
#endif

#ifdef __STDC__
	float modff(float x, float *iptr)
#else
	float modff(x, iptr)
	float x,*iptr;
#endif
{
	__int32_t i0,j_0;
	__uint32_t i;
	if (isnan(x)) {
	    *iptr = x;
	    return x;
	}
	GET_FLOAT_WORD(i0,x);
	j_0 = ((i0>>23)&0xff)-0x7f;	/* exponent of x */
	if(j_0<23) {			/* integer part in x */
	    if(j_0<0) {			/* |x|<1 */
	        SET_FLOAT_WORD(*iptr,i0&0x80000000U);	/* *iptr = +-0 */
		return x;
	    } else {
		i = (0x007fffff)>>j_0;
		if((i0&i)==0) {			/* x is integral */
		    __uint32_t ix;
		    *iptr = x;
		    GET_FLOAT_WORD(ix,x);
		    SET_FLOAT_WORD(x,ix&0x80000000U);	/* return +-0 */
		    return x;
		} else {
		    SET_FLOAT_WORD(*iptr,i0&(~i));
		    return x - *iptr;
		}
	    }
	} else {			/* no fraction part */
	    __uint32_t ix;
	    *iptr = x*one;
	    GET_FLOAT_WORD(ix,x);
	    SET_FLOAT_WORD(x,ix&0x80000000U);	/* return +-0 */
	    return x;
	}
}

#ifdef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double modf(double x, double *iptr)
#else
	double modf(x, iptr)
	double x,*iptr;
#endif
{
	return (double) modff((float) x, (float *) iptr);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
