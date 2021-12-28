/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
Modified: Apr 2000 - Paolo Nenzi
**********/

#include "ngspice/ngspice.h"
#include "ngspice/cktdefs.h"
#include "impdefs.h"
#include "ngspice/sperror.h"

/* actually load the current resistance value into the sparse matrix
 * previously provided */
int
IMPload(GENmodel *inModel, CKTcircuit *ckt)
{
    IMPmodel *model = (IMPmodel *)inModel;

    /*  loop through all the resistor models */
    for( ; model != NULL; model = IMPnextModel(model)) {
        IMPinstance *here;

        /* loop through all the instances of the model */
        for (here = IMPinstances(model); here != NULL ;
                here = IMPnextInstance(here)) {

            double norm2 = pow((here->IMPimpedance).real, 2) + pow((here->IMPimpedance).imag, 2);
            (here->IMPposPosPtr)->Real += (here->IMPimpedance).real / norm2;
            (here->IMPposPosPtr)->Imag += -(here->IMPimpedance).imag / norm2;
            (here->IMPnegNegPtr)->Real += (here->IMPimpedance).real / norm2;
            (here->IMPnegNegPtr)->Imag += -(here->IMPimpedance).imag / norm2;
            (here->IMPposNegPtr)->Real -= (here->IMPimpedance).real / norm2;
            (here->IMPposNegPtr)->Imag -= -(here->IMPimpedance).imag / norm2;
            (here->IMPnegPosPtr)->Real -= (here->IMPimpedance).real / norm2;
            (here->IMPnegPosPtr)->Imag -= -(here->IMPimpedance).imag / norm2;
        }
    }
    return(OK);
}


/* actually load the current resistance value into the sparse matrix
 * previously provided */
int
IMPacload(GENmodel *inModel, CKTcircuit *ckt)
{
    IMPmodel *model = (IMPmodel *)inModel;
    double g;

    NG_IGNORE(ckt);

    /*  loop through all the resistor models */
    for( ; model != NULL; model = IMPnextModel(model)) {
        IMPinstance *here;

        /* loop through all the instances of the model */
        for (here = IMPinstances(model); here != NULL ;
             here = IMPnextInstance(here)) {

            double norm2 = pow((here->IMPimpedance).real, 2) + pow((here->IMPimpedance).imag, 2);
            (here->IMPposPosPtr)->Real += (here->IMPimpedance).real / norm2;
            (here->IMPposPosPtr)->Imag += - (here->IMPimpedance).imag / norm2;
            (here->IMPnegNegPtr)->Real += (here->IMPimpedance).real / norm2;
            (here->IMPnegNegPtr)->Imag += - (here->IMPimpedance).imag / norm2;
            (here->IMPposNegPtr)->Real -= (here->IMPimpedance).real / norm2;
            (here->IMPposNegPtr)->Imag -= - (here->IMPimpedance).imag / norm2;
            (here->IMPnegPosPtr)->Real -= (here->IMPimpedance).real / norm2;
            (here->IMPnegPosPtr)->Imag -= - (here->IMPimpedance).imag / norm2;
        }
    }
    return(OK);
}
