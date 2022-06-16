/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 18 Septemper 2021                    */
/* Version     : V01                                  */
/* Description : ADC1                    		      */
/******************************************************/


/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/* ADDRESSES */
/* ADC1 ADDRESS ( ADC1 ON APB2 ) */
#define ADC_ADDRESS    0x40012400

#define CR1_SCAN 			8
#define	CR2_CONT   	    	1
#define	CR2_CAL   	    	2
#define SR_EOC              1
#define CR1_EOCIE       	5
#define	CR2_ALIGN			11
#define SMPR2_SMP5_0		15
#define SMPR2_SMP5_1		16
#define SMPR2_SMP5_2		17
#define	CR2_ADON            0
#define CR2_SWSTART 		22

typedef struct
{
	volatile u32	SR	  ;
	volatile u32	CR1	  ;
	volatile u32	CR2	  ;
	volatile u32	SMPR1 ;
	volatile u32	SMPR2 ;
	volatile u32	JOFR1 ;
	volatile u32	JOFR2 ;	
	volatile u32	JOFR3 ;	
	volatile u32	JOFR4 ;
	volatile u32	HTR   ;  
	volatile u32	LTR   ;  
	volatile u32	SQR1  ;
	volatile u32	SQR2  ;
	volatile u32	SQR3  ;
	volatile u32	JSQR  ;
	volatile u32	JDR1  ;
	volatile u32	JDR2  ;
	volatile u32	JDR3  ;
	volatile u32	JDR4  ;
	volatile u32	DR    ;
}ADC_t;

#define ADC1 ((volatile ADC_t *) ADC_ADDRESS)				



#endif
