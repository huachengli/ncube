//
// Created by huacheng on 12/16/21.
//

//#include "shape.h"

#include "pp_macros.h"
#define IpVPM_0(N) PP_GET_N(N,+,-,-,+,+,-,-,+)
#define IpVPM_1(N) PP_GET_N(N,+,+,-,-,+,+,-,-)
#define IpVPM_2(N) PP_GET_N(N,-,-,-,-,+,+,+,+)
#define IpVPM(M,N) PP_CONCAT(IpVPM_,M)(N)

/*
#define DO_PROD(VAR, IDX, CTX) PP_STAR_IF(IDX)(1. IpVPM(VAR,CTX) xl[VAR])
#define DeclareIpVFunc(k,type) type IpV##k(type * xl){return 0.125*PP_FOR_EACH_INNER(DO_PROD, k,0,1,2);};
#define DO_DECLARE_FUNC(VAR,IDX,CTX) DeclareIpVFunc(IDX,CTX)
PP_FOR_EACH(DO_DECLARE_FUNC,double,0,1,2,3,4,5,6,7)
#undef DO_DECLARE_FUNC
#undef DeclareIpVFunc
#undef DO_PROD
*/

#define PRED(VAL) PP_GET_TUPLE(1, VAL)
#define OP(VAL) (PP_GET_TUPLE(0, VAL) + PP_GET_TUPLE(1, VAL), PP_DEC(PP_GET_TUPLE(1, VAL)))

#define DO_PROD_X0 PP_STAR_IF(IDX)PP_IF