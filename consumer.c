//K
//! @brief
//!
//! @file consumer.c
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul Name......: consumer.c
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
#include "consumer.h"
/*
<pre>
Consumers: List of methods to calculate consumption of consumers
 */
struct   taKeytgS {
    char   jahr;
    char   monat;
    char   tag;
    char   stunde;
};

struct  taMinsumS {
    unsigned min :6 ;     // Minute
    unsigned nt  :1 ;     // Spitzenmesszeit aus
    unsigned ht  :1 ;     // Spitzenmesszeit ein
};

struct taVb4aiS {
    short              sum[4];    // Summenverbrauch
    struct taMinsumS   minsum[4]; // Minute und Spitzenmesszeit
    word               abglg[4];  // abgesch. Leistung
};
