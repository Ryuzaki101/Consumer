//K
//! @brief
//!
//! @file redefs.h
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Modul Name......: redefs.h
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
#ifndef REDEFS_H_INCLUDED
#define REDEFS_H_INCLUDED

# ifdef LINUX

/* far is special for cc86 */
#  ifdef FAR
#undef FAR
#define FAR                     ///< CC86 compatible
#  endif
#define far

/*!
 * NOTE:
 * This SW is compiled for different LINUXes:
 * - cygwin at W2000
 * - LINUX at PC (kubuntu and openSUSE)
 * - DIGI embedded LINUX, arch ARM (in DIGI-ESP)
 * This may request more or other definitions, can put here
 */

# endif /* LINUX */

# ifdef PC
#define	readonly
# endif

/*!
 * Due to compability issues btwn readonly and const in (CAD_UL Compiler)
 * we must change all C-source readonly with a adequate const
 * define	readonly const
 */

/* Address-Operations */

#define  ref      &                  	///< Address-operator
#define  cont     *                  	///< Content-operator
#define  ptr      *                  	///< Pointer

/* Bit-operations  */

#define  band     &
#define  bor      |
#define  bxor     ^
#define  bnot     ~

/* Compare-operations  */

#define  ne       !=
#define  eq       ==
#define  and      &&
#define  or       ||
#define  not      !

/* Modulo-operation             */

#define  mod      %                  	///< Modulo-Operation

/* Constants  */

#define  ZERO     0                  	///< Null-Pointer

/* Controls Definitions  */

#define Begin           {
#define End             }

#define If              if
#define Then            {
#define Else            } else {
#define Endif           }

#define While           while
#define Do              {
#define Endwhile        }

#define For             for
#define Endfor          }

#define Switch(c)       switch(c) {
#define Case            break; case
#define Default         break; default
#define Endswitch       }

#define Forever         for(; ;){
#define Endforever      }

#define Repeat          do  {
#define Until(b)        } while(not (b))

/* Functions- and. Variable types */

// //comeback to this type later and correct error conflicting for
typedef unsigned int size_d;
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long longword;
# ifndef _STDBOOL_H_

typedef unsigned char bool;
enum boolean { false=0 , true=1 };
# endif /* notdef _STDBOOL_H_ */

#define ENUM_BOOLEAN    enum boolean


#endif // REDEFS_H_INCLUDED
