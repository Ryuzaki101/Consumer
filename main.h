//K
//! @brief
//!
//! @file main.h
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul Name......: main.h
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
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/********************
 *                  *
 *   main.h        *
 *                  *
 *   main header   *
 *                  *
 ********************/

#ifndef _EMAX2_H_
#define _EMAX2_H_

#include <stdarg.h>
#include    "redefs.h"

#define TMPSIZ	1024
extern int LINE;
#define GOTO_ERROR	{ LINE = __LINE__; goto Error; }
// zwatsk.c
extern int traceID;
#define ARE_INIFILE "/etc/areadat.conf"
extern char mmc_filepath[TMPSIZ];

// AR12, AC60 default
#ifdef TEXAS_AM4372
#   define MMCPATH  "/run/media/mmcblk1p1"
#else
#   define MMCPATH  "/media/mmcblk0p1"
#endif

#define EMAXPATH	"\\emax"
extern char emax_filename[TMPSIZ];
#define LASTEMAXFILE	"lastEmaxFile"

// zwatsk2_file.c
#define ERR(format, ...) err(format, __FILE__, __LINE__, __func__, __VA_ARGS__)
void verr(char *format, va_list args);
void err(char *, ...);
#define LOG(format, ...) securityLog(format, __FILE__, __LINE__, __func__, __VA_ARGS__)
void securityLog(char *, ...);

#define OUT(format, ...) out(format, __FILE__, __LINE__, __func__, __VA_ARGS__)
void out(char *, ...);

void newline(void);
void timestamp(void);
void runMySQLCode(void);
// emax2_create.c
int createEmaxDirsNFiles(char *, size_d);

// emax2.c
char **getUeberschrift(int);
void fileUpdate(vz_t);


// emax-statistic.c
typedef unsigned char   con;
void recVstastikV(con connr);
#endif	// _EMAX2_H_

