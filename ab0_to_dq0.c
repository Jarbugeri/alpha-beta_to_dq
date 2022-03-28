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
//#include <math.h>

/*-------------------------------------------------------------*/
/*		Function prototypes				                       */
/*-------------------------------------------------------------*/

	/**
	 * @brief Alpha-Beta-Zero to dq0 transformation
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
	void alpha_beta_to_dq(_transformation *transforme, float alpha, float beta, float zero, float wt){
        
        transforme->alpha = alpha;
        transforme->beta = beta;
        transforme->zero = zero;
        transforme->wt = wt;

        if(transforme->frame_alignment == 0){
            //!< 90 degrees behind phase A axis
            transforme->d = + alpha * sin(wt) - beta * cos(wt);
            transforme->q = + alpha * cos(wt) + beta * sin(wt);
        }else{
            //!< Aligned with phase A axis
            transforme->d = + alpha * cos(wt) + beta * sin(wt);
            transforme->q = - alpha * sin(wt) + beta * cos(wt);        
        }
    }
    
    /**
	 * @brief dq0 to Alpha-Beta-Zero transformation
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
	void dq_to_alpha_beta(_transformation *transforme, float d, float q, float zero, float wt){
        
        transforme->d = d;
        transforme->q = q;
        transforme->zero = zero;
        transforme->wt = wt;

        if(transforme->frame_alignment == 0){    
            transforme->alpha = + d * sin(wt) + q * cos(wt);
            transforme->beta  = - d * cos(wt) + q * sin(wt);
        }else{
            transforme->alpha = d * cos(wt) - q * sin(wt);
            transforme->beta  = d * sin(wt) + q * cos(wt);            
        }

    }

	/**
	 * @brief abc to alpha-beta-zero transformation
	 *
	 * Perform a Clarke transformation from a three-phase (abc) signal
     * to a alpha-beta-zero stationary reference frame.
	 *
	 * @param alpha The vectorized α signal
	 * @param beta The vectorized β signal
	 * @param zero The vectorized 0 signal
	 */
	void abc_to_alpha_beta(_transformation *transforme, float a, float b, float c){
        
        transforme->a = a;
        transforme->b = b;
        transforme->c = c;

        if(transforme->power_invariant == 0){
            transforme->alpha = (a - 0.5 * (b - c) ) * 0.81649658092772603273242802490196;
            transforme->beta  = (b - c) * 0.70710678118654752440084436210485;
            transforme->zero  = (a + b + c) * 0.40824829046386301636621401245098;
        }else{
            transforme->alpha = (a - 0.5 * (b - c) ) * 0.66666666666666666666666666666667;
            transforme->beta  = (b - c) * 0.57735026918962576450914878050196;
            transforme->zero  = (a + b + c) * 0.33333333333333333333333333333333;
        }
    }

	/**
	 * @brief alpha-beta-zero to abc transformation
	 *
	 * Perform a Clarke inverse transformation from a alpha-beta-zero stationary reference frame
     * to a three-phase (abc) signal.
	 *
	 * @param alpha The vectorized α signal
	 * @param beta The vectorized β signal
	 * @param zero The vectorized 0 signal
	 */
	void alpha_beta_to_abc(_transformation *transforme, float alpha, float beta, float zero){
        
        transforme->alpha = alpha;
        transforme->beta  = beta;
        transforme->zero  = zero;

        if(transforme->power_invariant == 0){
            transforme->a = + alpha * 0.81649658092772603273242802490196 + zero * 0.57735026918962576450914878050196;
            transforme->b = - alpha * 0.40824829046386301636621401245098 + beta + zero * 0.57735026918962576450914878050196;
            transforme->c = - alpha * 0.40824829046386301636621401245098 - beta + zero * 0.57735026918962576450914878050196;
        }else{
            transforme->a = + alpha + zero;
            transforme->b = - alpha * 0.5 + beta * 0.86602540378443864676372317075294 + zero; 
            transforme->c = - alpha * 0.5 - beta * 0.86602540378443864676372317075294 + zero; 
        }
    }

	/**
	 * @brief abc to dq0 transformation
	 *
     * Perform a Park transformation from a three-phase (abc) signal to a dq0 rotating reference frame.
     * Angular position of the rotating frame is given by input wt (rad).
     * 
     * When the rotating frame alignment at wt=0 is 90 degrees behind phase A axis, a positive-sequence
     * signal with Mag=1 & Phase=0 degrees yields the following dq values: d=1, q=0.
	 *
	 * @param a The vectorized a signal
	 * @param b The vectorized b signal
	 * @param c The vectorized c signal
	 * @param wt The angular position, in radians, of the dq rotating frame relative to the stationary frame.
	 */
	void abc_to_dq(_transformation *transforme, float a, float b, float c, float wt){
        
        abc_to_alpha_beta(transforme, a, b, c);
        alpha_beta_to_dq(transforme, transforme->alpha,
                                     transforme->beta,
                                     transforme->zero,
                                     wt);
    }

    /**
	 * @brief dq0 to abc transformation
	 *
     * Perform an inverse Park transformation from a dq0 rotating reference frame to a three-phase (abc) signal.
     * Angular position of the rotating frame is given by input wt (rad).
     * 
     * When the rotating frame alignment at wt=0 is 90 degrees behind phase A axis, 
     * a positive-sequence signal with Mag=1 & Phase = 0 degrees yields the following dq values: d=1, q=0.
	 *
	 * @param a The vectorized d signal
	 * @param b The vectorized q signal
	 * @param c The vectorized zero signal
	 * @param wt The angular position, in radians, of the dq rotating frame relative to the stationary frame.
	 */
	void dq_to_abc(_transformation *transforme, float d, float q, float zero, float wt){
        
        dq_to_alpha_beta(transforme, d, q, zero, wt);
        alpha_beta_to_abc(transforme, transforme->alpha,
                                     transforme->beta,
                                     transforme->zero);
    }

    /**
	 * @brief ab to alpha-beta two phase transformation 
	 *
	 * Perform a Clarke transformation from a two-phase (ab) signal
     * to a alpha-beta stationary reference frame.
	 *
	 * @param alpha The vectorized a signal
	 * @param beta The vectorized b signal
	 */
	void ab_to_alpha_beta(_transformation *transforme, float a, float b){
        
        transforme->a = a;
        transforme->b = b;
        transforme->c = 0;

        if(transforme->power_invariant == 0){
            transforme->alpha = (a - 0.5 * b) * 1.4142135623730950488016887242097;
            transforme->beta  = b * 1.2247448713915890490986420373529;
            transforme->zero  = 0.0;
        }else{
            transforme->alpha = (a - 0.5 * (b) ) * 1.1547005383792515290182975610039;
            transforme->beta  = b;
            transforme->zero  = 0.0;
        }
    }