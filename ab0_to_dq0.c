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

/*-------------------------------------------------------------*/
/*		Includes and dependencies			                   */
/*-------------------------------------------------------------*/

#include "ab0_to_dq0.h"
#include <math.h>

/*-------------------------------------------------------------*/
/*		Function prototypes				                       */
/*-------------------------------------------------------------*/

	/**
	 * @brief Alpha-Beta-Zero to dq0
	 *
	 * The Alpha-Beta-Zero to dq0 block performs a transformation
     * of αβ0 Clarke components in a fixed reference frame to dq0
     * Park components in a rotating reference frame.
	 *
	 * @param alpha The vectorized α signal
	 * @param beta The vectorized β signal
	 * @param zero The vectorized 0 signal
	 * @param wt The angular position, in radians, of the dq rotating frame relative to the stationary frame.
	 */
	void alpha_beta_to_dq(ab0_to_dq0 *transforme, float alpha, float beta, float zero, float wt){
        
        transforme->alpha = alpha;
        transforme->beta = beta;
        transforme->zero = zero;
        transforme->wt = wt;

        transforme->d = + alpha * cos(wt) + beta * sin(wt);
        transforme->q = - alpha * sin(wt) + beta * cos(wt);

    }

    /**
	 * @brief dq0 to Alpha-Beta-Zero
	 *
     * The dq0 to Alpha-Beta-Zero block performs a transformation of
     * dq0 Park components in a rotating reference frame to αβ0 Clarke
     * components in a fixed reference frame.
	 *
	 * @param d The vectorized d signal
	 * @param q The vectorized q signal
	 * @param zero The vectorized 0 signal
	 * @param wt The angular position, in radians, of the dq rotating frame relative to the stationary frame.
	 */
	void dq_to_alpha_beta(ab0_to_dq0 *transforme, float d, float q, float zero, float wt){
        
        transforme->d = d;
        transforme->q = q;
        transforme->zero = zero;
        transforme->wt = wt;

        transforme->d = d * cos(wt) - q * sin(wt);
        transforme->q = d * sin(wt) + q * cos(wt);

    }