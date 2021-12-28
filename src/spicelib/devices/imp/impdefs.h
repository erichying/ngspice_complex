/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
Modified: 2000 AlansFixes
**********/

#ifndef IMPDEFS
#define IMPDEFS

#include "ngspice/ifsim.h"
#include "ngspice/cktdefs.h"
#include "ngspice/gendefs.h"
#include "ngspice/complex.h"
#include "ngspice/noisedef.h"

#define spREAL  double

/* Begin `realNumber'. */
typedef  spREAL  RealNumber, * RealVector;

struct  MatrixElement
{
    RealNumber   Real;
    RealNumber   Imag;
    int          Row;
    int          Col;
    struct MatrixElement* NextInRow;
    struct MatrixElement* NextInCol;
#if INITIALIZE
    void* pInitInfo;
#endif
};
typedef  struct MatrixElement* ElementPtr;
/* information used to describe a single instance */

typedef struct sIMPinstance {
    struct GENinstance gen;

#define IMPmodPtr(inst) ((struct sIMPmodel *)((inst)->gen.GENmodPtr))
#define IMPnextInstance(inst) ((struct sIMPinstance *)((inst)->gen.GENnextInstance))
#define IMPname gen.GENname
#define IMPstate gen.GENstate
    const int IMPposNode;     /* number of positive node of impedance */
    const int IMPnegNode;     /* number of negative node of impedance */

    SPcomplex IMPimpedance;    /* complex number of impedance  */

    ElementPtr IMPposPosPtr;           /* pointer to sparse matrix diagonal at
                                     * (positive,positive) */
    ElementPtr IMPnegNegPtr;           /* pointer to sparse matrix diagonal at
                                     * (negative,negative) */
    ElementPtr IMPposNegPtr;           /* pointer to sparse matrix offdiagonal at
                                     * (positive,negative) */
    ElementPtr IMPnegPosPtr;           /* pointer to sparse matrix offdiagonal at
                                     * (negative,positive) */
} IMPinstance;


/* per model data */

typedef struct sIMPmodel {       /* model structure for a impedance */
    struct GENmodel gen;

#define IMPmodType gen.GENmodType
#define IMPnextModel(inst) ((struct sIMPmodel *)((inst)->gen.GENnextModel))
#define IMPinstances(inst) ((IMPinstance *)((inst)->gen.GENinstances))
#define IMPmodName gen.GENmodName
} IMPmodel;

/* device parameters */
enum {
    IMP_IMPEDANCE = 1
};
#endif /*IMP*/
