/**********
Copyright 2021.  All rights reserved.
Author: 2021 Guanwen Ying
**********/

#include "ngspice/ngspice.h"
#include "ngspice/const.h"
#include "ngspice/ifsim.h"
#include "impdefs.h"
#include "ngspice/sperror.h"
#include "ngspice/missing_math.h"
#include "ngspice/fteext.h"

int
IMPparam(int param, IFvalue *value, GENinstance *inst, IFvalue *select)
{
    double scale;

    IMPinstance *here = (IMPinstance *)inst;

    NG_IGNORE(select);

    if (!cp_getvar("scale", CP_REAL, &scale, 0))
        scale = 1;

    switch(param) {
    case IMP_IMPEDANCE:
        here->IMPimpedance.real = value->cValue.real;
        here->IMPimpedance.imag = value->cValue.imag;
        break;
    default:
        return(E_BADPARM);
    }
    return(OK);
}
