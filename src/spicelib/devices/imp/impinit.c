#include "ngspice/config.h"

#include "ngspice/devdefs.h"

#include "impinit.h"
#include "impext.h"


SPICEdev IMPinfo = {
    .DEVpublic = {
        .name = "Impedance",
        .description = "Simple linear impedance",
        .terms = &IMPnSize,
        .numNames = &IMPnSize,
        .termNames = IMPnames,
        .numInstanceParms = &IMPpTSize,
        .instanceParms = IMPpTable,
        .numModelParms = &IMPmPTSize,
        .modelParms = IMPmPTable,
        .flags = 0,

#ifdef XSPICE
        .cm_func = NULL,
        .num_conn = 0,
        .conn = NULL,
        .num_param = 0,
        .param = NULL,
        .num_inst_var = 0,
        .inst_var = NULL,
#endif
    },

    .DEVparam = IMPparam,
    .DEVmodParam = NULL,
    .DEVload = IMPload,
    .DEVsetup = IMPsetup,
    .DEVunsetup = NULL,
    .DEVpzSetup = NULL,
    .DEVtemperature = NULL,
    .DEVtrunc = NULL,
    .DEVfindBranch = NULL,
    .DEVacLoad = IMPacload,
    .DEVaccept = NULL,
    .DEVdestroy = NULL,
    .DEVmodDelete = NULL,
    .DEVdelete = NULL,
    .DEVsetic = NULL,
    .DEVask = NULL,
    .DEVmodAsk = NULL,
    .DEVpzLoad = NULL,
    .DEVconvTest = NULL,
    .DEVsenSetup = NULL,
    .DEVsenLoad = NULL,
    .DEVsenUpdate = NULL,
    .DEVsenAcLoad = NULL,
    .DEVsenPrint = NULL,
    .DEVsenTrunc = NULL,
    .DEVdisto = NULL,
    .DEVnoise = NULL,
    .DEVsoaCheck = NULL,
    .DEVinstSize = &IMPiSize,
    .DEVmodSize = &IMPmSize,

#ifdef CIDER
    .DEVdump = NULL,
    .DEVacct = NULL,
#endif
};


SPICEdev *
get_imp_info(void)
{
    return &IMPinfo;
}
