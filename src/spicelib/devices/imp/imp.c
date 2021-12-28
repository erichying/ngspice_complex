/**********
Copyright 2021 All rights reserved.
Author: 2021 Guanwen Ying
**********/

#include "ngspice/ngspice.h"
#include "ngspice/devdefs.h"
#include "impdefs.h"
#include "ngspice/ifsim.h"

IFparm IMPpTable[] = { /* parameters */
    IOPP("complex", 	IMP_IMPEDANCE, 	     IF_COMPLEX,    "Impedance")
};

IFparm IMPmPTable[] = { /* model parameters */
    IOPP("complex", 	IMP_IMPEDANCE, 	     IF_COMPLEX,    "Impedance")
};

char *IMPnames[] = {
    "ZZ+",
    "ZZ-"
};

int	IMPnSize = NUMELEMS(IMPnames);
int	IMPpTSize = NUMELEMS(IMPpTable);
int	IMPmPTSize = NUMELEMS(IMPmPTable);
int	IMPiSize = sizeof(IMPinstance);
int	IMPmSize = sizeof(IMPmodel);
