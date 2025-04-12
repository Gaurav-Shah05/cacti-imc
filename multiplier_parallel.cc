
/*------------------------------------------------------------
*                              CACTI IMC                      

 * Alok Parmar       Nanditha Rao    IIIT Bangalore           
 *Kailash Prasad    Joycee Mekie    IIT Gandhinagar           

*------------------------------------------------------------*/

#include "multiplier_parallel.h" 

double Mat::compute_delaymultiplier_parallel(double inrisetime)
{

double outrisetime ;
outrisetime = compute_multiplier_delay_parallel(outrisetime);
return outrisetime;
}

double Mat:: compute_multiplier_delay_parallel(double inrisetime)
{

//num_bits_multipy_subarray = subarray.num_cols / deg_bl_muxing;
if (g_ip->operation_type == 1)
{


 //Calculation of Overall Area
multiplier_area = 0;
    multiplier_area = 2 * (adder_area); 
    //Calculatioon of Overall Delay

//    delay_multiplier_compute = this_delay_and_gate + ((2 * num_bits_multipy_subarray) - 2) * delay_adder_carry + (num_bits_multipy_subarray - 1) * delay_adder_sum; 
   delay_multiplier_compute = delay_adder_compute ; 
    //Calculation of Final Dynamic Energy

//    power_multiplier.computeOp.dynamic = power_adder.computeOp.dynamic * num_bits_multipy_subarray * (num_bits_multipy_subarray -  1 )
//     +  energy_and * num_bits_multipy_subarray * num_bits_multipy_subarray ;
    power_multiplier.computeOp.dynamic = power_adder.computeOp.dynamic ;

    //Calculation of Final Leakage Power

   power_multiplier.computeOp.leakage = 0;




}

return inrisetime ;

}