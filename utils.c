//K
//! @brief
//!
//! @file utils.c
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul Name......: utils.c
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

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	<locale.h>
#include	<stdarg.h>
#include	"utils.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                 Prototypen
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
long           GetFileSize(FILE *fp);
char *         stringToLower(char *string);
char *         stringToUpper(char *string);
void           strmaxcpy(char *strDst, char *strSrc, short siMaxLen);
void           SplitFilename(char *strPath, char *strFile);
char *         strcasestr(const char *haystack, const char *needle);
int            strncasecmp(const char *s1, const char *s2, size_t n);
long           TimeDelta(struct timeval *s_Diff, struct timeval *s_Time1, struct timeval *s_Time2);
unsigned short swap_word(unsigned short usiVal);
               //inline unsigned short swap_word(unsigned short usiVal);
char *         stringReplace(char *strSource, int iSourceMaxLen, char *strSearch, char *strReplace);
int            Get32ulValue(char *strBuffer, unsigned long *ulValue);

char *         Util_CutEndingSpaces(char *Str);
char *         Util_CutSpaces(char *Str);
int            Util_FileExist(char *FileName);
char *         Util_strtolower(char *str);         // ‰hnlich zu stringToLower
char *         Util_CutQuotes(char *Str);

int            Util_LogOpen(char * strFilePath, char * strMode);
void           Util_LogClose(void);
int            Util_LogMsg(char *msg, ...);

#define STATSTRINGLEN 255
static char   stat_String[STATSTRINGLEN];
static FILE * stat_fpLogfile = NULL;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul name:	GetFileSize()
//
// Function :	Calculates file size without change to pointer
//
// Input  :	FILE *	Pointer File
//
// Output  :	long	File size in Bytes
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
long GetFileSize(FILE *fp)
{
	long curpos, length;

	if (!fp)
		return 0L;

	curpos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, curpos, SEEK_SET);
	return (length);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul name:	stringToLower()
//
// Function :	wandelt Groﬂ- in Kleinbuchstaben um, aber keine Umlaute (UTF-8)
//
// Input  :	char *	Pointer auf Zeichenkette
//
// Output  :	char *	Pointer auf Zeichenkette
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char *stringToLower(char *string)
{
	int i;
	int len = strlen(string);
	for(i=0; i<len; i++)
	{
		if(((string[i] >= 'A') && (string[i] <= 'Z')) ||
			((unsigned char)string[i] == 196) ||	// ƒ	0xC4
			((unsigned char)string[i] == 214) ||	// ÷	0xD6
			((unsigned char)string[i] == 220))		// ‹	0xDC
			string[i] += 32;
	}
	return (string);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modulname:	stringToUpper()
//
// Funktion :	wandelt Klein- in Groﬂbuchstaben um, aber keine Umlaute (UTF-8)
//
// Eingang  :	char *	Pointer auf Zeichenkette
//
// Ausgang  :	char *	Pointer auf Zeichenkette
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char *stringToUpper(char *string)
{
	int i;
	int len = strlen(string);
	for(i=0; i<len; i++)
	{
		if(((string[i] >= 'a') && (string[i] <= 'z')) ||
			((unsigned char)string[i] == 228) ||	// ‰	0xE4
			((unsigned char)string[i] == 246) ||	// ˆ	0xF6
			((unsigned char)string[i] == 252))		// ¸	0xFC
			string[i] -= 32;
	}
	return (string);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modulname:	strmaxcpy()
//
// Funktion :	zusaetzlich zum Standard strncpy wird sichergestellt
//				dass der String immer korrekt mit \0 endet
//
//	Achtung:	es wird davon ausgegangen, dass mind. "maxlen" Zeichen
//				in den strDst passen incl. '\0'
//
// Eingang  :	char *	Ziel-String
// 				char *	Quell-String
// 				char *	max. Laenge des Zielstrings incl. '\0'
//
// Ausgang  :
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void strmaxcpy(char *strDst, char *strSrc, short siMaxLen)
{
	short	n = 0;

	if(NULL == strSrc)
	{
		strDst[0] = '\0';
		return;
	}

	n = strlen(strSrc);

	if(n > (siMaxLen-1))
	{
		n = siMaxLen-1;
	}

	strncpy(strDst, strSrc, n);
	strDst[n] = '\0';
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modulname:	SplitFilename()
//
// Funktion :	liefert den Filenamen ohne Pfad
//
// Eingang  :	char *	Pointer auf Pfadname
//
// Ausgang  :	char *	Pointer auf Anfang Dateiname
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SplitFilename(char *strPath, char *strFile)
{
	short	i = 0;
#ifdef LINUX
	const char cSeparator = '/';
#else
	const char cSeparator = '\\';
#endif

	for(i = (strlen(strPath)-1); i>=0; i--)
	{
		if(strPath[i] == cSeparator)
		{
			strmaxcpy(strFile, &strPath[i+1], MAX_LEN_FILEPATH);
			return;
		}
	}

	strmaxcpy(strFile, strPath, MAX_LEN_FILEPATH);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modulname:	strcasestr()
//
// Funktion :	Findet das erste Vorkommen von needle in haystack ohne Beachtung
// 				der Gross- und Kleinschreibung
//
// Eingang  :	char *	Pointer auf Heuhaufen
// 				char *	Pointer auf Nadel
//
// Ausgang  :	char *	Pointer auf Zeichenkette wenn gefunden, sonst NULL
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char * strcasestr(const char *haystack, const char *needle)
{
	char	c, sc;
	size_t	len;

	if ((c = *needle++) != 0)
	{
		c = tolower((unsigned char)c);
		len = strlen(needle);
		do
		{
			do
			{
				if ((sc = *haystack++) == 0)
					return (NULL);
			}
			while ((char)tolower((unsigned char)sc) != c);
		}
		while (strncasecmp(haystack, needle, len) != 0);
		haystack--;
	}
	return ((char *)haystack);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modulname:	strcasecmp()
//
// Funktion :	Vergleicht zwei Zeichenketten miteinander ohne Beachtung der
// 				Gross- und Kleinschreibung
//
// Eingang  :	char *	Pointer auf Zeichenkette
// 				char *	Pointer auf Zeichenkette
//
// Ausgang  :	char *	Pointer auf Zeichenkette
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int strncasecmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return 0;

	while ((n-- != 0) && (tolower(*s1) == tolower(*s2)))
	{
		if ((n == 0) || (*s1 == '\0') || (*s2 == '\0'))
			break;
		s1++;
		s2++;
	}

	return (tolower(*(unsigned char *)s1) - tolower(*(unsigned char *)s2));
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modulname:	TimeDelta()
//
// Funktion :	Differenz zwischen zwei Zeiten berechnen (Diff = Time1 - Time2)
//
// Eingang  :	struct timeval *	Zeitdifferenz
// 				struct timeval *	Time1
// 				struct timeval *	Time2
//
// Ausgang  :	long		-1	-> 	Time1  <  Time2
//							 0	-> 	Time1  =  Time2
//							+1	-> 	Time1  >  Time2
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
long TimeDelta(struct timeval *s_Diff, struct timeval *s_Time1, struct timeval *s_Time2)
{
	long	lResult = 0;
	struct timeval s_tvTemp;    // wegen Berechnung ohne vorhandenem Zeiger auf Differenz Struktur

	// Normierung der uebergebenen Zeiten
	while (s_Time1->tv_usec >= 1000000L) {
		s_Time1->tv_usec -= 1000000L;
		s_Time1->tv_sec++;
	}
	while (s_Time2->tv_usec >= 1000000L) {
		s_Time2->tv_usec -= 1000000L;
		s_Time2->tv_sec++;
	}

	s_tvTemp.tv_usec	= s_Time1->tv_usec - s_Time2->tv_usec;
	s_tvTemp.tv_sec		= s_Time1->tv_sec - s_Time2->tv_sec;

	if (s_tvTemp.tv_usec < 0L) {
		if (s_tvTemp.tv_sec <= 0L) {
			lResult = -1;
		} else {
			s_tvTemp.tv_sec--;
			s_tvTemp.tv_usec = 1000000L - labs(s_tvTemp.tv_usec);
			lResult = 1;
		}
	} else {
		if ((s_tvTemp.tv_sec == 0L) && (s_tvTemp.tv_usec == 0L)) {
			lResult = 0;
		} else if ( (s_tvTemp.tv_sec > 0L) ||
					((s_tvTemp.tv_sec == 0L) && (s_tvTemp.tv_usec > 0L))) {
			lResult = 1;
		} else if (s_tvTemp.tv_sec < 0L) {
			if (0L != s_tvTemp.tv_usec) {
				s_tvTemp.tv_sec++;
				s_tvTemp.tv_usec = 1000000L - labs(s_tvTemp.tv_usec);
			}
			lResult = -1;
		}
	}
	s_tvTemp.tv_sec = labs(s_tvTemp.tv_sec);
	s_tvTemp.tv_usec = labs(s_tvTemp.tv_usec);

	if (s_Diff != NULL) {
		memcpy(s_Diff, &s_tvTemp, sizeof(struct timeval));
	}

	return (lResult);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modulname:	swap_word()
//
// Funktion :	vertauscht das High- mit dem Low-Byte
//
// Eingang  :	unsigned short		Word
//
// Ausgang  :	unsigned short		gedrehtes Word
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned short swap_word(unsigned short usiVal)
//inline unsigned short swap_word(unsigned short usiVal)
{
    return ((usiVal<<8) & 0xFF00) | ((usiVal>>8) & 0x00FF);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modulname:	stringReplace()
//
// Funktion :	Ersetzt einen Teilstring in einem String.
// 				Der Such- und Ersetzungs-String koennen unterschiedlicher Laenge sein.
// 				Der String, in dem die Ersetzung stattfindet, muss jedoch groﬂ genug sein
// 				um die Ersetzung speichern zu koennen.
//
// Eingang  :	char *	Pointer auf Zeichenkette des Quell/Zielspeichers
//              int		max. Laenge des Quell/Zielspeichers
//              char *	Pointer auf Suchstring
//              char *	Pointer auf Ersetzungsstring
//
// Ausgang  :	char *	Pointer auf Zeichenkette
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char *stringReplace(char *strSource, int iSourceMaxLen, char *strSearch, char *strReplace)
{
	char	*strTemp		= NULL;
	char	*strSearchNew	= NULL;
	char	*strSearchOld	= NULL;
	int		iLenNew			= 0;
	int		iCnt			= 0;

	// pruefe ob Ersetzung sinnvoll ist
	if (strcmp(strSearch, strReplace) == 0)
		return (strSource);

	// preuefe ob Such-String ueberhaupt vorhanden ist
	// wenn ja, Haeufigkeit bestimmen -> das hilft beim Speicher reservieren
	strSearchNew = strSource;
	do
	{
		if ((strSearchNew = strstr(strSearchNew, strSearch)) != NULL)
		{
			iCnt++;
			strSearchNew += strlen(strSearch);
		}
	}
	while (strSearchNew != NULL);

	if (iCnt == 0)
	{
		// es gibt nichts zu tun
		return (strSource);
	}

	if (iSourceMaxLen == 0)
		iSourceMaxLen = strlen(strSource);

	// Speicher reservieren (wenn der String nach der Ersetzung laenger ist)
	iLenNew = strlen(strSource) + (iCnt * (strlen(strReplace) - strlen(strSearch))) + 1;

	if (iSourceMaxLen < iLenNew)
		return NULL;

	strTemp = (char*)malloc(iLenNew * sizeof(char));

	if (!strTemp)
		return NULL;

	memset(strTemp, 0, iLenNew);

	strSearchNew = strSource;
	strSearchOld = strSource;
	do
	{
		if ((strSearchNew = strstr(strSearchNew, strSearch)) != NULL)
		{
			strncat(strTemp, strSearchOld, strSearchNew - strSearchOld);
			strcat(strTemp, strReplace);
			strSearchNew += strlen(strSearch);
			strSearchOld = strSearchNew;
		}
	}
	while (strSearchNew != NULL);

	// den restlichen String nach dem Letzten Suchtreffer anh‰ngen
	strcat(strTemp, strSearchOld);
	memcpy(strSource, strTemp, iLenNew);
	memset(strSource+iLenNew, 0, iSourceMaxLen - iLenNew);
	strSource[iSourceMaxLen-1] = '\0';	// Stringende setzen

	// Speicher wieder freigeben
	free(strTemp);

	return (strSource);
}

//*************************************************************************************************
//*************************************************************************************************
// Modulname:	Get32ulValue()
//
// Funktion :	String in Ganzzahl umwandeln (Komma und Semikolon sind Trennzeichen)
//
// Eingang  :	char *			Pointer auf String
// 				unsigned long	Pointer auf konvertiertem Wert (bei Fehler 0)
//
// Ausgang  :	int				>= 0	-> Konvertierung erfolgreich
// 								<  0	-> Konvertierung nicht moeglich
//*************************************************************************************************
//*************************************************************************************************
int Get32ulValue(char *strBuffer, unsigned long *ulValue)
{
	unsigned char	ucCnt	= 0;
	unsigned char	ucCnt_X	= 0;
	unsigned char	ucBase	= 0;

	*ulValue	= 0L;
	ucBase		= 10;

	// Ein Leerstring kann nicht ausgewertet werden.
	if (0 == strlen(strBuffer))
		return (-1);

	// Eingabe auf Fehler ueberpruefen und Zahlen-Basis erkennen
	// Abbruch beim Auftreten eines Fehlers
	for (ucCnt = 0; ucCnt < strlen(strBuffer); ucCnt++)
	{
		// gueltiges Zeichen ???
		if (!(	((strBuffer[ucCnt] >= 0x30) && (strBuffer[ucCnt] <= 0x39))	||	// 0...9
				((strBuffer[ucCnt] >= 0x41) && (strBuffer[ucCnt] <= 0x46))	||	// A...F
				((strBuffer[ucCnt] >= 0x61) && (strBuffer[ucCnt] <= 0x66))	||	// a...f
				('X' == strBuffer[ucCnt]) 									||	// X
				('x' == strBuffer[ucCnt])))									// x
		{
			return (-2);
		}

		// Basis Hex (16) ???
		if (('x' == strBuffer[ucCnt]) || ('X' == strBuffer[ucCnt]))
		{
			// x oder X als erstes Zeichen
			if (0 == ucCnt)
				return (-3);

			if ('0' != strBuffer[ucCnt-1])
				return (-4);

			ucBase = 16;
			ucCnt_X++;

			if (ucCnt_X > 1)
				return (-5);
		}
	}

	*ulValue = strtoul(strBuffer, NULL, (int) ucBase);

	return (0);
}

/*========================================================================*\
			     Util_CutEndingSpaces
  ------------------------------------------------------------------------

  Funktion      loescht Leerzeichen am Schluss eines Strings

  Parameter: 	- String

  Returnwert:   - String

\*=========================================================================*/
char *Util_CutEndingSpaces(char *Str)
{
   int i;
   for(i=strlen(Str)-1;i>=0;i--)
   {
      if(Str[i]==' ')
      {
         Str[i]='\0';
      }else{
         break;
      }
   }

   return(Str);
}

/*========================================================================*\
			     Util_CutSpaces
  ------------------------------------------------------------------------

  Funktion      loescht Leerzeichen am Anfang und am Schluss eines Strings

  Parameter: 	- String

  Returnwert:   - String

\*=========================================================================*/
char *Util_CutSpaces(char *Str)
{
   int i,j;
   if(Str == NULL)
   {
      return(Str);
   }
   Util_CutEndingSpaces(Str);
   if(Str[0]=='\0')
   {
      return(Str);
   }
   for(i=0;i<(int)strlen(Str);i++)
   {
      if(Str[i]!=' ')
      {
         break;
      }
   }
   if(i!=0)
   {
      for(j=i;j<(int)strlen(Str);j++)
      {
         Str[j-i]=Str[j];
      }
      Str[j-i]='\0';
   }
   return(Str);
}

/*========================================================================*\
			   Util_FileExist()
  ------------------------------------------------------------------------

  Funktion      prueft, ob das File existiert

  Parameter: 	- Filename mit Pfad

  Returnwert:  - 0: File existiert nicht
		           1: File existiert

\*=========================================================================*/
int Util_FileExist(char *FileName)
{
   FILE   *fp;

   if (!(fp = fopen(FileName, "r")))
   {
      /* File konnte nicht geoeffnet werden */
      return(0);
   }

   fclose(fp);
   return(1);
}


/*========================================================================*\
			   Util_strtolower()
  ------------------------------------------------------------------------

  Funktion      wandelt den angegebenen String in Kleinbuchstaben

  Parameter:	- String

  Returnwert:   - String

\*=========================================================================*/
char *Util_strtolower(char *str)
{
   char *pStr;

   for(pStr=str;*pStr;pStr++)
      *pStr=tolower(*pStr);

   return(str);
}

/*========================================================================*\
			   Util_CutQuotes()
  ------------------------------------------------------------------------

  Funktion      entfernt Anfuehrungszeichen am Anfang und Ende

  Parameter:    - String

  Returnwert:   - String

\*=========================================================================*/
char *Util_CutQuotes(char *str)
{
//   char *pStr;
   int len;
   int i;

   if((str == NULL) || (str[0]=='\0'))
      return(str);

   len = strlen(str);
   if(len<2)
      return(str);

   if(str[len-1] == '"')
   {
      str[len-1] = '\0';
      len--;
   }

   if(str[0] == '"')
   {
//      for(pStr=str+1;*pStr;pStr++)
//         *(pStr-1)=*pStr;

      for(i=0; i<len; i++)
          str[i] = str[i+1];

//      for(i=1; str[i]; i++)
//          str[i-1] = str[i];
   }

   return(str);
}

/*****************************************************************
 * Util_LogOpen
 * ---------------------------------------------------------------
 * Funktion:  Logfile oeffnen
 *
 * Parameter: - Filename inkl. Pfad
 *            - File Zugriffstyp
 * ---------------------------------------------------------------
 * Aufrufbeispiel:
 *            Util_LogOpen("/tmp/log.txt", "a+");
 *
 *            "a+" ==> immer anh‰ngen und erzeugen, falls nicht vorhanden
 *            "w"  ==> immer neues File erzeugen
 *
 * Zum Deaktivieren der Meldungen, muss nur die Funktion Util_LogOpen
 * auskommentiert werden:
 *            //Util_LogOpen("/tmp/log.txt", "a+");
 *
 *****************************************************************/
int Util_LogOpen(char * strFilePath, char * strMode)
{
   if (!(stat_fpLogfile = fopen(strFilePath, strMode)))
   {
      /* File konnte nicht geoeffnet werden */
      printf("Logfile %s konnte nicht geoeffnet werden\n", strFilePath);
      stat_fpLogfile = NULL;
      return(0);
   }
   //printf("Logfile %s geoeffnet\n", strFilePath);

   return(1);
}


/*****************************************************************
 * Util_LogClose
 * ---------------------------------------------------------------
 * Funktion:  Logfile schliessen
 *
 * Parameter: -
 *
 *****************************************************************/
void Util_LogClose(void)
{
   if(stat_fpLogfile != NULL)
      fclose(stat_fpLogfile);

   stat_fpLogfile = NULL;
}

/*****************************************************************
 * Util_LogMsg
 * ---------------------------------------------------------------
 * Funktion: Nachricht in Logfile schreiben
 *
 * Parameter: - Text
 *
 *****************************************************************/
int Util_LogMsg(char *msg, ...)
{
   va_list         argptr;

   if(stat_fpLogfile == NULL)
   {
      return(0);
   }

   va_start(argptr,msg);
   vsnprintf(&stat_String[0], sizeof(stat_String), msg, argptr);
   va_end(argptr);

   fprintf(stat_fpLogfile, stat_String);
   fflush(stat_fpLogfile);
   return(1);
}

