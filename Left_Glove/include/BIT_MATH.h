/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 12 August 2021                       */
/* Version     : V01                                  */
/******************************************************/

/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/


#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(VAR,BIT_NO)    (VAR = (VAR) | (1<<BIT_NO))

#define CLR_BIT(VAR,BIT_NO)    (VAR = (VAR) & (~(1<<BIT_NO)))

#define TOGGLE_BIT(VAR,BIT_NO) (VAR = (VAR) ^ (1<<BIT_NO))

#define GET_BIT(VAR,BIT_NO)    ((VAR>>BIT_NO) & 1)


#endif
