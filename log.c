//K
//! @brief
//!
//! @file log.c
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul Name......: log.c
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
#include <stdio.h>
#include <io.h>
#include "main.h"
#include "utils.h"

/**************************
 *                        *
 *   static Variables   *
 *                        *
 **************************/
static char lastFormat[TMPSIZ];

/***************************************************************
 *                                                             *
 *   verr(format, args)                                        *
 *   err(format, __FILE__, __LINE__, __func__, ...)            *
 *                                                             *
 *   output to:                                                *
 *   - stderr if (traceID <= IDTRACE)                          *
 *                                                             *
 *   securityLog(format, __FILE__, __LINE__, __func__, ...)    *
 *                                                             *
 *   output to:                                                *
 *   - stderr (unconditional)                                  *
 *                                                             *
 ***************************************************************/
void verr(char *format, va_list args) {
    char buf[TMPSIZ];

    strncpy(&buf[0], "%s %d %s: ", sizeof(buf));
    strncat(&buf[0], format, sizeof(buf));
    strncat(&buf[0], "\n", sizeof(buf));
    /*
     * output to stderr
     */
    vfprintf(stderr, &buf[0], args);    // fprintf(va_list)
}

void err(char *format, /* __FILE__, __LINE__, __func__, */ ...) {
    va_list args;

    if (traceID) {
        va_start(args, format);                 // initializes va_list for subsequent use by va_arg() and va_end()
        verr(format, args);                     // output va_list to stderr
        va_end(args);                           // match va_start()
    }
}

void securityLog(char *format, /* __FILE__, __LINE__, __func__, */ ...) {
    va_list args;

    va_start(args, format);                 // initializes va_list for subsequent use by va_arg() and va_end()
    verr(format, args);                     // output va_list to stderr
    va_end(args);                           // match va_start()
}

/*********************************************************
 *                                                       *
 *   vfileOut(format, args)                              *
 *   fileOut(format, ...)                                *
 *                                                       *
 *   output to:                                          *
 *   - file /media/mmcblk0p1/YYYY/emax/YYYY.MM.DD.emax   *
 *                                                       *
 *********************************************************/
void vfileOut(char *format, va_list args) {
    char buf[TMPSIZ];
    char tmp[TMPSIZ];
    FILE *fp;
    char *pc;

    /*
     * output to file
     */
    if (createEmaxDirsNFiles(&buf[0], sizeof(buf))) {
        if (access(&buf[0], F_OK) == 0) {	// return 0 is success, all requested (exists) permissions granted, file already exists
        	// attach to emax File
            fp = fopen(&buf[0], "a");   // Open for appending (writing at end of file). The file is created if it does not exist. The stream is positioned at the end of the file.
			//ERR("fopen(%s, a)=%p", &buf[0], fp);
			if (fp) {
				vsnprintf(&tmp[0], sizeof(tmp), format, args);                  // Write Notification in emax File, snprintf(va_list)
                while ((pc = strchr(&tmp[1], '\t')) != NULL) { *pc = ' '; }     // no TAB in Write-String, first TAB reserved for .csv
                while ((pc = strchr(&tmp[0], '\r')) != NULL) { *pc = ' '; }     // no CR  in Notification-String
                while ((pc = strchr(&tmp[0], '\n')) != NULL) {
                    if (strlen(pc) > 1) {                                       // no LF at End of the Line
                        *pc = ' ';                                              // no LF  in Notification-String
                    } else {
                        break;
                    }
                }
                fputs(&tmp[0], fp);                                             // write the string to stream, without its terminating null byte.
                fclose(fp);
            }
            // store last filename if date misaligned
            fp = fopen(&emax_filename[0], "r");  // Open text file for reading. The stream is positioned at the beginning of the file.
            ERR("fopen(%s, r)=%p\n", &emax_filename[0], fp);            // emax File in lastEmaxFile write
            if (fp) {
                if (fgets(&tmp[0], sizeof(tmp), fp) == NULL) {
                    ERR("fgets(%s)\n", &emax_filename[0]);           // emax File lastEmaxFile Read
                }
                fclose(fp);
                if (strcmp(&tmp[0], &buf[0]) != 0) {            // no useless Write operations in Flash-Drive
                    fp = fopen(&emax_filename[0], "w");  // Truncate file to zero length or create text file for writing. The stream is positioned at the beginning of the file.
                    ERR("fopen(%s, w)=%p\n", &emax_filename[0], fp);
                    if (fp) {
                        fputs(&buf[0], fp);
                        fclose(fp);
                    }
                }
            }
        }
    }
}
void fileOut(char *format, ...) {
    va_list args;

    va_start(args, format); // initializes va_list for subsequent use by va_arg() and va_end()
    vfileOut(format, args); // output va_list to file
    va_end(args);           // match va_start()
}

/*********************************************************
 *                                                       *
 *   out(format, __FILE__, __LINE__, __func__, ...)      *
 *                                                       *
 *   output to:                                          *
 *   - stderr                                            *
 *   - file /media/mmcblk0p1/YYYY/emax/YYYY.MM.DD.emax   *
 *                                                       *
 *********************************************************/
void out(char *format, /* __FILE__, __LINE__, __func__, */ ...) {
    va_list args1;
    va_list args2;
    char buf[TMPSIZ];
    char *p;

    /*
     * output to stderr
     */
    va_start(args1, format);        // initializes for subsequent use by va_arg() and va_end()
    va_copy(args2, args1);          // copy va_list
    verr(format, args1);            // output va_list to stderr
    va_end(args1);                  // match va_start()

    /*
     * output to file
     */
    if (strcmp(format, &lastFormat[0]) != 0) {
    	strcpy(&lastFormat[0], format);
	    strcpy(&buf[0], "\t");      // format TAB separated values
    } else {					    // same format
	    strcpy(&buf[0], " ");       // concatinate strings
    }
    if ((p = strchr(format, '='))) {
        strcat(&buf[0], ++p);       // nur Wert
    } else {
        strcat(&buf[0], format);
    }
    va_arg(args2, char *);	        // kein __FILE__
    va_arg(args2, int);		        // kein __LINE__
    va_arg(args2, char *);	        // kein __func__
    vfileOut(&buf[0], args2);       // output va_list to file
    va_end(args2);                  // match va_copy()
}

/*********************************************************
 *                                                       *
 *   newline()                                           *
 *                                                       *
 *   output newline to:                                  *
 *   - file /media/mmcblk0p1/YYYY/emax/YYYY.MM.DD.emax   *
 *                                                       *
 *********************************************************/
void newline(void) {
    /*
     * output to file
     */
	fileOut("%s", "\n");
}

char **getTitle(int z) {

    static char buf[TMPSIZ];
    static char *p = &buf[0];
    p = &buf[0];
    return &p;
}

/*********************************************************
 *                                                       *
 *   timestamp()                                         *
 *                                                       *
 *   output timestamp to:                                *
 *   - file /media/mmcblk0p1/YYYY/emax/YYYY.MM.DD.emax   *
 *                                                       *
 *********************************************************/
void timestamp(void) {
    char buf[TMPSIZ];
    time_t nowtime;
    struct tm *ts;
    struct timeval tv;

    /*
     * output to file
     */
    //nowtime = time(NULL);
    gettimeofday(&tv, NULL);
    nowtime = tv.tv_sec;
    ts = localtime(&nowtime);
    strftime(&buf[0], sizeof(buf), "%Y/%m/%d %H:%M:%S", ts);
    sprintf(&buf[strlen(&buf[0])], ".%03d", (int)tv.tv_usec/1000); // append ms
    fileOut("%s", &buf[0]);
}
