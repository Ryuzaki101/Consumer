//K
//! @brief
//!
//! @file emax-statistic.c
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul Name......: emax-statistic.c
//
// Created....: 24-03-2023
//
// Autor...........: Othman Bouyahiaoui - Head of saawokc company
//
// $Author:  $
//
// $Revision:  $
//
// $Date:  $
//
// $Source:  $
//
// $State:  $
//
// $Locker:  $
//
// Copyright (c) 2023 Othman Bouyahiaoui - Head of saawokc company
// Bir rami est Al manzah lot 133
//
//++++++++++++++++++++++++++++++

#include "main.h"

//F
/// @addtogroup STATISTIC-RECALCULATE
/// @{
/// ----------------------------------------------------------------------------
///
/// @fn     void recVstastikV(con connr)
///
/// @brief  Update the device consumption maxima-Statistic
///
/// @param  con            Nr. Consumer
///
/// @n NOTE:
/// @n ----------------------------------------------------------------------------
/// @}
//

/*T*/
void recVstastikV(con connr)
{
    byte year, mon, day;
    printf("statistic accessed connr %d ", connr);
    //char fgadr[FGAD_DEFn];

    /*p
     *  update Statistic                                        // 1
     *  update day-Statistic                                              // 2
     *  update Month-Statistic                                             // 3
     *  update year-Statistic                                             // 4
     *
     *  Switch(DateChange)
     *    Case YearChange:                                                   // 5
     *      get date of last AI-Wechsel from SASTOP
     *      get FG-Adresse from SASTOP
     *      send Protocol contract for previous year
     *
     *    Case MonChange:                                                   // 6
     *      get date of last AI-Wechsel from SASTOP
     *      send Protocol contract for previous month
     *
     *    Case DayChange:                                                    // 7
     *      If (autom. Day Protocol for akt VZ is on)
     *      Then
     *        get date of last AI-Wechsel from SASTOP
     *        send Protocol contract for previous day
     *      Endif
     *      NOTE:
     *        saLgtaproF is void! uses access to VZ done before
     *  Endswitch
     */



     /*
    alLaskupdV(vznr);                                                           // 1

    taLstkupdV(vznr);                                                           // 2
    fileUpdate(vznr);

    moLmonupdV(vznr);                                                           // 3

    yeLyeaupdV(vznr);                                                           // 4

    switch(saLchdaweF(ivLgtaiyrF(),ivLgtaimoF(),ivLgtaidaF(),ivLgtaimiF())) {
        case 2:                                                                 // 5
            saLgtolaiV(&year, &mon, &day);
            saLgtvzfgaV(&fgadr[0]);
            ppLlmbtypV(PdDRUCKERn, LMBPRIOn, PuLMBJAHRn, year, 0, 0, &fgadr[0]);
            WAIT_4TEST();
        /*FALLTHROUGH*/
       /* case 4:                                                                 // 6
            saLgtolaiV(&year, &mon, &day);
            saLgtvzfgaV(&fgadr[0]);
            ppLlmbtypV(PdDRUCKERn, LMBPRIOn, PuLMBMONn, year, mon, 0, &fgadr[0]);
            WAIT_4TEST();
        /*FALLTHROUGH*/
      /*  case 6:                                                                 // 7
            if (saLgtaproF(/*vznr*/
        /*        saLgtolaiV(&year, &mon, &day);
                saLgtvzfgaV(&fgadr[0]);
                ppLlmbtypV(PdDRUCKERn, LMBPRIOn, PuLMBTAGn, year, mon, day, &fgadr[0]);
                WAIT_4TEST();
            }
    }*/
}
