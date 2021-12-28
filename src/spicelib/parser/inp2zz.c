/**********
Copyright 2021.  All rights reserved.
Author: 2021 Guanwen Ying
Remarks:  This code is for impedance
**********/

#include "ngspice/ngspice.h"
#include "ngspice/ifsim.h"
#include "ngspice/inpdefs.h"
#include "ngspice/inpmacs.h"
#include "ngspice/fteext.h"
#include "inpxx.h"
#include "ngspice/stringskip.h"
#include "ngspice/compatmode.h"

/* undefine to add tracing to this file */
/* #define TRACE */

void INP2ZZ(CKTcircuit* ckt, INPtables* tab, struct card* current)
{
    /* parse a resistor card */
    /* Rname <node> <node> [<val>][<mname>][w=<val>][l=<val>][ac=<val>] */

    static int mytype = -1;	/* the type we determine resistors are */
    int type = 0;		/* the type the model says it is */
    char* line;			/* the part of the current line left to parse */
    char* saveline;		/* ... just in case we need to go back... */
    char* name;			/* the resistor's name */
    char* model;		/* the name of the resistor's model */
    char* nname1;		/* the first node's name */
    char* nname2;		/* the second node's name */
    CKTnode* node1;		/* the first node's node pointer */
    CKTnode* node2;		/* the second node's node pointer */
    double val;			/* temp to held resistance */
    int error;			/* error code temporary */
    int error1;			/* secondary error code temporary */
    INPmodel* thismodel;	/* pointer to model structure describing our model */
    GENmodel* mdfast = NULL;	/* pointer to the actual model */
    GENinstance* fast;		/* pointer to the actual instance */
    IFvalue ptemp;		/* a value structure to package resistance into */
    int waslead;		/* flag to indicate that funny unlabeled number was found */
    double leadval;		/* actual value of unlabeled number */
    IFuid uid;			/* uid for default model */

    char* s;   /* Temporary buffer and pointer for translation */

#ifdef TRACE
    printf("In INP2R, Current line: %s\n", current->line);
#endif

    if (mytype < 0) {
        if ((mytype = INPtypelook("Impedance")) < 0) {
            LITERR("Device type Impedance not supported by this binary\n");
            return;
        }
    }
    line = current->line;
    INPgetNetTok(&line, &name, 1);			/* Rname */
    INPinsert(&name, tab);
    INPgetNetTok(&line, &nname1, 1);		/* <node> */
    INPtermInsert(ckt, &nname1, tab, &node1);
    INPgetNetTok(&line, &nname2, 1);		/* <node> */
    INPtermInsert(ckt, &nname2, tab, &node2);

    /* enable reading values like 4k7 */
    if (newcompat.lt)
        val = INPevaluateRKM_R(&line, &error1, 1);	/* [<val>] */
    else
        val = INPevaluate(&line, &error1, 1);	/* [<val>] */

    saveline = line;		/* save then old pointer */

    INPgetNetTok(&line, &model, 1);

    if (*model && (strcmp(model, "zz") != 0)) {
        /* token isn't null */
        if (INPlookMod(model)) {
            /* If this is a valid model connect it */
#ifdef TRACE
            printf("In INP2R, Valid R Model: %s\n", model);
#endif
            INPinsert(&model, tab);
            current->error = INPgetMod(ckt, model, &thismodel, tab);
            if (thismodel != NULL) {
                if ((INPtypelook("Impedance") != thismodel->INPmodType)
#ifdef ADMS
                    && (INPtypelook("r2_cmc") != thismodel->INPmodType)
#endif
                    ) {
                    LITERR("incorrect model type for impedance");
                    return;
                }
                mdfast = thismodel->INPmodfast;
                type = thismodel->INPmodType;
            }
        }
        else {
            tfree(model);
            /* It is not a model */
            line = saveline;	/* go back */
            type = mytype;
            if (!tab->defZZmod) {	/* create default ZZ model */
                IFnewUid(ckt, &uid, NULL, "ZZ", UID_MODEL, NULL);
                IFC(newModel, (ckt, type, &(tab->defZZmod), uid));
            }
            mdfast = tab->defZZmod;
        }
        IFC(newInstance, (ckt, mdfast, &fast, name));
    }
    else {
        tfree(model);
        /* The token is null or we have r=val - a default model will be created */
        type = mytype;
        if (!tab->defZZmod) {
            /* create default R model */
            IFnewUid(ckt, &uid, NULL, "ZZ", UID_MODEL, NULL);
            IFC(newModel, (ckt, type, &(tab->defZZmod), uid));
        }
        IFC(newInstance, (ckt, tab->defZZmod, &fast, name));
        if (error1 == 1) {		/* was a r=val construction */
            val = INPevaluate(&line, &error1, 1);	/* [<val>] */
#ifdef TRACE
            printf("In INP2R, R=val construction: val=%g\n", val);
#endif
        }
    }

    if (error1 == 0) {		/* got a resistance above */
        ptemp.rValue = val;
        GCA(INPpName, ("impedance", &ptemp, ckt, type, fast));
    }

    IFC(bindNode, (ckt, fast, 1, node1));
    IFC(bindNode, (ckt, fast, 2, node2));
    PARSECALL((&line, ckt, type, fast, &leadval, &waslead, tab));
    if (waslead) {
        ptemp.rValue = leadval;
        GCA(INPpName, ("impedance", &ptemp, ckt, type, fast));
    }

    return;
}
