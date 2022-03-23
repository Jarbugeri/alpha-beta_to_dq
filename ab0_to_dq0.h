/**
 * @file ab0_to_dq0.c
 * @author José Augusto Arbugeri (jose@domain.com)
 * @brief Perform transformation from αβ0 stationary reference frame to dq0 rotating reference frame or the inverse
 * @version 1.0
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 *
 */

#ifndef AB0_TO_DQ0_H
#define AB0_TO_DQ0_H

/*-------------------------------------------------------------*/
/*		Includes and dependencies			                   */
/*-------------------------------------------------------------*/
#include <math.h>

/*-------------------------------------------------------------*/
/*		Macros and definitions				                   */
/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			                   */
/*-------------------------------------------------------------*/

/**
 * Structure of transformation 
 */
typedef struct _ab0_to_dq0_ {

	float alpha;    //!< The vectorized α signal
	float beta;     //!< The vectorized β signal
    float zero;     //!< The vectorized 0 signal
    float wt;       //!< The angular position, in radians, of the dq rotating frame relative to the stationary frame.
	float d;        //!< The vectorized d signal
	float q;        //!< The vectorized q signal

} ab0_to_dq0;


/*-------------------------------------------------------------*/
/*		Function prototypes				                       */
/*-------------------------------------------------------------*/

	void alpha_beta_to_dq(ab0_to_dq0 *transforme, float alpha, float beta, float zero, float wt);

    void dq_to_alpha_beta(ab0_to_dq0 *transforme, float d, float q, float zero, float wt);




// End of Header file