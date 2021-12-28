/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
Modified: Apr 2000 Paolo Nenzi
**********/

#include "ngspice/ngspice.h"
#include "ngspice/smpdefs.h"
#include "impdefs.h"
#include "ngspice/sperror.h"


int
IMPsetup(SMPmatrix *matrix, GENmodel *inModel, CKTcircuit*ckt, int *state)
        /* load the resistor structure with those pointers needed later
         * for fast matrix loading
         */
{
    IMPmodel *model = (IMPmodel *)inModel;
    IMPinstance *here;

    NG_IGNORE(state);
    NG_IGNORE(ckt);

    /*  loop through all the resistor models */
    for( ; model != NULL; model = IMPnextModel(model)) {



        /* loop through all the instances of the model */
        for (here = IMPinstances(model); here != NULL ;
                here=IMPnextInstance(here)) {

/* macro to make elements with built in test for out of memory */
#define TSTALLOC(ptr,first,second) \
do { if((here->ptr = SMPmakeComplexElt(matrix, here->first, here->second)) == NULL){\
    return(E_NOMEM);\
} } while(0)

            TSTALLOC(IMPposPosPtr, IMPposNode, IMPposNode);
            TSTALLOC(IMPnegNegPtr, IMPnegNode, IMPnegNode);
            TSTALLOC(IMPposNegPtr, IMPposNode, IMPnegNode);
            TSTALLOC(IMPnegPosPtr, IMPnegNode, IMPposNode);
        }
    }
    return(OK);
}
