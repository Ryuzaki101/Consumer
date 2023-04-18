//K
//! @brief
//!
//! @file utils.h
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul Name......: utils.h
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
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  changes:
//                  Function TimeDelta():
//                  + normalize returned time
//                  + Calculation with missing pointer to Diff struct
//                  Log-Functions
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __UTILS_H__
#define __UTILS_H__

#include    <sys/time.h>
#include    <sys/time.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Definitionen
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define	UTILS_SW_VERSION_MAJOR		1	// Software Version Major		Softwaregeneration
#define	UTILS_SW_VERSION_MINOR		0	// Software Version Minor		Servicepacks
#define	UTILS_SW_REVISION_NUMBER	1	// Software Revision Number		Erweiterungen
#define	UTILS_SW_BUILD_NUMBER		0	// Software Build Number		Bugfixes

// Defines fuer Dateioperationen
#define FILE_OPEN_MODE_R		"r"		// Open text file for reading.
										// The stream is positioned at the beginning of the file.

#define FILE_OPEN_MODE_RW		"r+"	// Open for reading and writing.
										// The stream is positioned at the beginning of the file.

#define FILE_OPEN_MODE_WC		"w"		// Truncate file to zero length or create text file for writing.
										// The stream is positioned at the beginning of the file.

#define FILE_OPEN_MODE_RWC		"w+"	// Open for reading and writing.
										// The file is created if it does not exist, otherwise it is truncated.
										// The stream is positioned at the beginning of the file.

#define FILE_OPEN_MODE_AC		"a"		// Open for appending (writing at end of file).
										// The file is created if it does not exist.
										// The stream is positioned at the end of the file.

#define FILE_OPEN_MODE_RAC		"a+"	// Open for reading and appending (writing at end of file).
										// The file is created if it does not exist.
										// The initial file position for reading is at the beginning of the file,
										// but output is always appended to the end of the file.

// Define fuer
#define	MAX_LEN_FILEPATH		256

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Strukturen, Unions und Typdeklarationen
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Makros
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Prototypen
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern long           GetFileSize(FILE *fp);
extern char *         stringToLower(char *string);
extern char *         stringToUpper(char *string);
extern void           strmaxcpy(char *strDst, char *strSrc, short siMaxLen);
extern void           SplitFilename(char *strPath, char *strFile);
extern char *         strcasestr(const char *haystack, const char *needle);
extern int            strncasecmp(const char *s1, const char *s2, size_t n);
extern long	          TimeDelta(struct timeval *s_Diff, struct timeval *s_Time1, struct timeval *s_Time2);
extern unsigned short swap_word(unsigned short usiVal);
                      //inline unsigned short swap_word(unsigned short usiVal);
extern char *         stringReplace(char *strSource, int iSourceMaxLen, char *strSearch, char *strReplace);
extern int	          Get32ulValue(char *strBuffer, unsigned long *ulValue);

extern char *         Util_CutEndingSpaces(char *Str);
extern char *         Util_CutSpaces(char *Str);
extern int            Util_FileExist(char *FileName);
extern char *         Util_strtolower(char *str);         // ähnlich zu stringToLower
extern char *         Util_CutQuotes(char *Str);

extern int            Util_LogOpen(char * strFilePath, char * strMode);
extern void           Util_LogClose(void);
extern int            Util_LogMsg(char *msg, ...);

#endif // __UTILS_H__
