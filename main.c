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
// Author...........: Othman Bouyahiaoui - Head of saawokc company
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
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
//  device consumptions program */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
#include "mysql.h"
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "main.h"
char emax_filename[TMPSIZ];
char mmc_filepath[TMPSIZ] ;
int traceID;
char pathWin1[140]= "C:\\Users\\m\\Documents\\VSDev-Project\\FirstDatabase\\test\\db\\year";

typedef struct vehicle
{
    char name[100];
    int roll;
    int salary;
    char address[100];
    int join_year;
}record;


int createEmaxDirsNFiles(char *pBuf, size_d n) {
    time_t t;
    struct tm *ts;
    int fileStat;
    FILE *fp;
    char **p;
    int z;
    char format[TMPSIZ];
    //snprintf(pBuf, n, "%s", &pathWin[0]);
    fileStat = _mkdir(pBuf);
    printf("created directory %s %d\n ", pBuf, fileStat);
    if (access(pBuf, W_OK) != 0) {	// return 0 is success, all requested (write) permissions granted
        printf("no write permission\n");
        ERR("SD-Card %s", "no write permission");
        return 0;
    } else {
        t = time(NULL);
        ts = localtime(&t);
        sprintf(&format[0], "%s\\%%Y", &mmc_filepath[0]);
        strftime(pBuf, n, &format[0], ts);
        strcat(pathWin1,pBuf);
        printf("format1 %s \n ", pathWin1);
        fileStat = _mkdir(pathWin1);
        if (access(pBuf, F_OK) != 0) {	// return 0 is success, all requested (exists) permissions granted, Jahresverzeichnis existiert nicht
            fileStat = _mkdir(pBuf);
            printf("permissions directory2\n");
			ERR("mkdir(%s)=%d", pBuf, fileStat);
        }
        sprintf(&format[0], "\\%s", &mmc_filepath[0], EMAXPATH);
        strftime(pBuf, n, &format[0], ts);
        printf("strcat befpre pBuf %s pathWin %s\n ", pBuf, pathWin1);
        strcat(pathWin1,EMAXPATH);
        printf("strcat after pBuf %s pathWin %s\n ", pBuf, pathWin1);
        fileStat = _mkdir(pathWin1);
        printf("format2 %s \n ", pathWin1);
        if (access(pBuf, F_OK) != 0) {	// return 0 is success, all requested (exists) permissions granted, emax Verzeichnis existiert nicht
            printf("permissions directory3\n");
            fileStat = _mkdir(pBuf);
			ERR("mkdir(%s)=%d", pBuf, fileStat);
        }
        sprintf(&format[0], "\\%%Y.%%m.%%d.emax", &mmc_filepath[0], EMAXPATH);
        strftime(pBuf, n, &format[0], ts);
        strcat(pathWin1,pBuf);
        printf("format3 %s \n ", pathWin1);
        if (access(pathWin1, F_OK) != 0) {	// return 0 is success, all requested (exists) permissions granted, emax Datei existiert nicht
            // emax Datei mit Überschrift anlegen
            printf("permissions directory4\n");
            fp = fopen(pathWin1, "w");  // Truncate file to zero length or create text file for writing. The stream is positioned at the beginning of the file.
			ERR("fopen(%s, w)=%p", pathWin1, fp);
			if (fp) {
                for (z = 0, p = getTitle(z); **p != '\0'; z++, p = getTitle(z)) {   // log Datei mit Überschriften anlegen
                    fputs(*p, fp);                               // write the string to stream, without its terminating null byte.
                }
   	        fclose(fp);
    	    }
        }
        if (access(pathWin1, F_OK) != 0) {  // return 0 is success, all requested (exists) permissions granted, lastEmaxFile Datei existiert nicht
            //LOG("modified=%s", MODIFIED);
            // store last filename, falls lastEmaxFile nicht existiert (z.B. bei neuer emax Datei)
            printf("permissions directory5\n");
            fp = fopen(pathWin1, "w");  // Truncate file to zero length or create text file for writing. The stream is positioned at the beginning of the file.
            ERR("fopen(%s)=%p\n", pathWin1, fp);             // emax Datei in lastEmaxFile schreiben
            if (fp) {
                fputs(pBuf, fp);                                 // write the string to stream, without its terminating null byte.
                fclose(fp);
            }
        }
        return 1;
    }
}

int main(void)
{
    runMySQLCode();
    char pathWin[140]= "C:\\Users\\m\\Documents\\VSDev-Project\\FirstDatabase\\test\\db\\year";
    int i , choice;
    FILE *fp1,*fp2;
    char oname[100];
    record det;
    int recsize;
    char c;
    char format[TMPSIZ];
    printf("Run Dir and File creation\n");
    //recVstastikV(15);
    createEmaxDirsNFiles(pathWin, sizeof(pathWin));
//    sprintf(&format[0], "%s\\%s", &pathWin[0], EMAXPATH);

    printf("main format %s \n ", pathWin1);
    fp1 = fopen(pathWin1 , "r+");

    if(fp1 == NULL)
    {
        fp1 = fopen(format , "w+");
        if(fp1 == NULL)
        {
            printf("error in opening file : \n");
            return -1;
        }
    }
    recsize = sizeof(det);

    fseek(fp1 , 0 ,SEEK_END);
    printf("Enter employee Name : ");
    scanf("%[^\n]" , det.name);
    printf("Enter roll number   : ");
    scanf("%d" , &det.roll);
    printf("Enter the salary    : ");
    scanf("%d" , &det.salary);
    scanf("%c" , &c);
    printf("Enter address   : ");
    scanf("%[^\n]" , det.address);
    printf("Enter joining year  : ");
    scanf("%d" , &det.join_year);
    fwrite(&det,recsize,1,fp1);
    return 0;
}
void runMySQLCode(void){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    srand(time(0)); //Seed the random number generator with the current time

    int num = 120;
    num = rand() * 100 ;
    char *server = "localhost";
    char *user = "root";
    char *password = "root"; /*password is not set in this example*/
    char *database = "labordb1";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server,
    user, password, database, 0, NULL, 0))
    {
    printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
    return 0;
    }

    /* Execute SQL query to fetch all table names.*/
    if (mysql_query(conn, "show tables"))
    {
    printf("Failed to execute querry. Error: %s\n", mysql_error(conn));
    return 0;
    }

    res = mysql_use_result(conn);

    /* Output table name */
    printf("MySQL Tables in mydb database:\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s \n", row[0]);
    /* send SQL query */
    if (mysql_query(conn, "SHOW COLUMNS FROM labordb1.consumers"))
    {
        printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
    }
    int i = 0;
    int columns = mysql_num_fields(res);
    res = mysql_store_result(conn);
    while(row = mysql_fetch_row(res))
    {
    for ( i = 0; i < columns; i++)
    {
     printf("%s ", row[i] ? row[i] : "NULL");
    }
    }
    printf("\n");
    char query[1000];
    char input[32],input5[10];
    int input2,input1,input4,input6;
    double input3;
    printf("give new ConsumerID");
    scanf("%s", &input);
    printf("give new Floor");
    scanf("%d", &input1);
    printf("give new MainCounter");
    scanf("%d", &input2);
    printf("give new Counter");
    scanf("%f", &input3);
    printf("give new MonitorFreq");
    scanf("%d", &input4);
    printf("give new ActiveLvl");
    scanf("%s", &input5);
    printf("give new Priority");
    scanf("%d", &input6);

    sprintf(query, "INSERT INTO `labordb1`.`consumers` (`ConsumerID`,`Floor`,`MainCounter`,`Counter`,`MonitorFreq`,`ActiveLvl`,`Priority`) VALUES ('%s','%d','%d','%f','%d','%s','%d');", input, input1, input2, input3, input4, input5, input6);
    mysql_query(conn, query);
    if (mysql_query(conn, "select * from consumers"))
    {
        printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
        return 0;
    }
    /* free results */
    mysql_free_result(res);
    res = mysql_store_result(conn);
    if (res == NULL)
    {
    return 0;
    }

    columns = mysql_num_fields(res);
    while(row = mysql_fetch_row(res))
    {
    for (i = 0; i < columns; i++)
    {
     printf("%s ", row[i] ? row[i] : "NULL");
    }
    printf("\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
 }

