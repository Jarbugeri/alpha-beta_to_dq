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

//#include <math.h>

/*-------------------------------------------------------------*/
/*		Macros and definitions				                   */
/*-------------------------------------------------------------*/

#define POWER_INVARIANTE   0
#define VOLTAGE_INVARIANTE 1
#define FRAM_ALIGNMENT_90  0
#define FRAM_ALIGNMENT_0   1

/**
 * @brief Init transformation struct
 * 
 * @param frame frame_alignment = 0 => Phase = 90 egrees, frame_alignment = 1 => Phase = 0 egrees
 * @param type_invariante power_invariant = 0 => Power invariant transformation, power_invariant = 1 => Voltage invariant transformation 
 */
#define TRANSFORMATION_INIT(frame, type_invariante) {0,0,0,0,0,0,0,0,0,Frame,Type_invariante}

/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			                   */
/*-------------------------------------------------------------*/

/** Structure of transformation **/

typedef struct _transformation_ {

	float a;		//!< The vectorized a signal
	float b;		//!< The vectorized b signal
	float c;		//!< The vectorized c signal

	float alpha;    //!< The vectorized α signal
	float beta;     //!< The vectorized β signal
    float zero;     //!< The vectorized 0 signal

    float wt;       //!< The angular position, in radians, of the dq rotating frame relative to the stationary frame.
	float d;        //!< The vectorized d signal
	float q;        //!< The vectorized q signal
					
	//!<When you select Aligned with phase A axis, the dq0 components are d = 0, q = −1, and zero = 0.
	//!<When you select 90 degrees behind phase A axis, the default option, the dq0 components are d = 1, q = 0, and zero = 0.
	int frame_alignment;	//!, frame_alignment = 0 => Phase = 90 egrees, frame_alignment = 1 => Phase = 0 egrees
	int power_invariant;	//!< power_invariant = 0 => Power invariant transformation, power_invariant = 1 => Voltage invariant transformation 

} _transformation;


/*-------------------------------------------------------------*/
/*		Function prototypes				                       */
/*-------------------------------------------------------------*/

	void alpha_beta_to_dq(_transformation *transforme, float alpha, float beta, float zero, float wt);
    void dq_to_alpha_beta(_transformation *transforme, float d, float q, float zero, float wt);

	void abc_to_alpha_beta(_transformation *transforme, float a, float b, float c);
	void alpha_beta_to_abc(_transformation *transforme, float alpha, float beta, float zero);

	abc_to_dq(_transformation *transforme, float a, float b, float c, float wt);
	dq_to_abc(_transformation *transforme, float d, float q, float zero, float wt);
	
	ab_to_alpha_beta(_transformation *transforme, float a, float b);



#endif
// End of Header file