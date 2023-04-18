//K
//! @brief
//!
//! @file consumer.h
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul Name......: consumer.h
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
#include "redefs.h"
/*
<pre>
Consumers: List of consumers properties
 */
 /**************************
 *                        *
 *   struct Consumers   *
 *                        *
 **************************/
 typedef struct Consumers
{
    byte RASPADR[4];//2Bytes CurrentBox nr, 2Bytes raspberry pi device nr
    byte SUIFRQ;//Monitoring frequency
    /*This performance maximum - limitation is for different transfer
    * Counter laid out in preparation.
    * In order to be able to differentiate between processing for gas/water
    * (regarding units etc.) this consumption counter identification
    * included in the SASTOP list.*/
    byte SVZKG;
    byte SAIVNT[2];
    byte SAIVHT[2];
    byte SAIVDA[6];
    byte SZWTGW[8];
    byte SMPFGA[6];
    byte STKFGA[6];
    byte SVZFGA[6];
    byte SAKTIV;
    byte SRESER;

} consumers;
