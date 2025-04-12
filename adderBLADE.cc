
/*------------------------------------------------------------
*                              CACTI IMC                      

 * Alok Parmar       Nanditha Rao    IIIT Bangalore           
 *Kailash Prasad    Joycee Mekie    IIT Gandhinagar           

*------------------------------------------------------------*/

#include "adderBLADE.h" 

double Mat::compute_delayadder_BLADE(double inrisetime)
{

double outrisetime ;
outrisetime = compute_adder_delay_BLADE(outrisetime);
return outrisetime;
}


double Mat:: compute_adder_delay_BLADE(double inrisetime)
{

int num_adderBLADE_subarray = subarray.num_cols / deg_bl_muxing;
int num_adder_subarray = subarray.num_cols / deg_bl_muxing;
if  (g_ip->adder_type == 2)
{
// CACTI 6.5 INCOMPUTE CIRCUIT AUTOMATED TOOLKIT 

// Difining the Sizes of the Transistors

double WNOR1_p1    =  145 * g_ip->F_sz_um;
double WNOR1_p2    =  145 * g_ip->F_sz_um;
double WNOR2_p1    =  145 * g_ip->F_sz_um;
double WNOR2_p2    =  145 * g_ip->F_sz_um;
double WNOR3_p1    =  145 * g_ip->F_sz_um;
double WNOR3_p2    =  145 * g_ip->F_sz_um;
double WNOR1_n1    =  100 * g_ip->F_sz_um;
double WNOR1_n2    =  100 * g_ip->F_sz_um;
double WNOR2_n1    =  100 * g_ip->F_sz_um;
double WNOR2_n2    =  100 * g_ip->F_sz_um;
double WNOR3_n1    =  100 * g_ip->F_sz_um;
double WNOR3_n2    =  100 * g_ip->F_sz_um;
double WDFF1_p1    =  145 * g_ip->F_sz_um;
double WDFF1_p2    =  145 * g_ip->F_sz_um;
double WINV2_p1    =  145 * g_ip->F_sz_um;
double WDFF1_p3    =  145 * g_ip->F_sz_um;
double WDFF1_p4    =  145 * g_ip->F_sz_um;
double WINV3_p1    =  145 * g_ip->F_sz_um;
double WXOR1_p1    =  145 * g_ip->F_sz_um;
double WXOR1_p2    =  145 * g_ip->F_sz_um;
double WXOR1_p3    =  145 * g_ip->F_sz_um;
double WXOR1_p4    =  145 * g_ip->F_sz_um;
double WDFF1_n1    =  100 * g_ip->F_sz_um;
double WDFF1_n2    =  100 * g_ip->F_sz_um;
double WINV2_n1    =  100 * g_ip->F_sz_um;
double WDFF1_n3    =  100 * g_ip->F_sz_um;
double WDFF1_n4    =  100 * g_ip->F_sz_um;
double WINV3_n1    =  100 * g_ip->F_sz_um;
double WXOR1_n1    =  100 * g_ip->F_sz_um;
double WXOR1_n3    =  100 * g_ip->F_sz_um;
double WXOR1_n2    =  100 * g_ip->F_sz_um;
double WXOR1_n4    =  100 * g_ip->F_sz_um;
double WINV4_n1    =  100 * g_ip->F_sz_um;
double WINV4_p1    =  145 * g_ip->F_sz_um;
double WINV1_p1    =  145 * g_ip->F_sz_um;
double WINV1_n1    =  100 * g_ip->F_sz_um;

// Leakage Calculation of Individual Gates

double I_WNOR1_p1 = simplified_pmos_leakage(WNOR1_p1, is_dram);
double I_WNOR1_p2 = simplified_pmos_leakage(WNOR1_p2, is_dram);
double I_WNOR2_p1 = simplified_pmos_leakage(WNOR2_p1, is_dram);
double I_WNOR2_p2 = simplified_pmos_leakage(WNOR2_p2, is_dram);
double I_WNOR3_p1 = simplified_pmos_leakage(WNOR3_p1, is_dram);
double I_WNOR3_p2 = simplified_pmos_leakage(WNOR3_p2, is_dram);
double I_WNOR1_n1 = simplified_nmos_leakage(WNOR1_n1, is_dram);
double I_WNOR1_n2 = simplified_nmos_leakage(WNOR1_n2, is_dram);
double I_WNOR2_n1 = simplified_nmos_leakage(WNOR2_n1, is_dram);
double I_WNOR2_n2 = simplified_nmos_leakage(WNOR2_n2, is_dram);
double I_WNOR3_n1 = simplified_nmos_leakage(WNOR3_n1, is_dram);
double I_WNOR3_n2 = simplified_nmos_leakage(WNOR3_n2, is_dram);
double I_WDFF1_p1 = simplified_pmos_leakage(WDFF1_p1, is_dram);
double I_WDFF1_p2 = simplified_pmos_leakage(WDFF1_p2, is_dram);
double I_WINV2_p1 = simplified_pmos_leakage(WINV2_p1, is_dram);
double I_WDFF1_p3 = simplified_pmos_leakage(WDFF1_p3, is_dram);
double I_WDFF1_p4 = simplified_pmos_leakage(WDFF1_p4, is_dram);
double I_WINV3_p1 = simplified_pmos_leakage(WINV3_p1, is_dram);
double I_WXOR1_p1 = simplified_pmos_leakage(WXOR1_p1, is_dram);
double I_WXOR1_p2 = simplified_pmos_leakage(WXOR1_p2, is_dram);
double I_WXOR1_p3 = simplified_pmos_leakage(WXOR1_p3, is_dram);
double I_WXOR1_p4 = simplified_pmos_leakage(WXOR1_p4, is_dram);
double I_WDFF1_n1 = simplified_nmos_leakage(WDFF1_n1, is_dram);
double I_WDFF1_n2 = simplified_nmos_leakage(WDFF1_n2, is_dram);
double I_WINV2_n1 = simplified_nmos_leakage(WINV2_n1, is_dram);
double I_WDFF1_n3 = simplified_nmos_leakage(WDFF1_n3, is_dram);
double I_WDFF1_n4 = simplified_nmos_leakage(WDFF1_n4, is_dram);
double I_WINV3_n1 = simplified_nmos_leakage(WINV3_n1, is_dram);
double I_WXOR1_n1 = simplified_nmos_leakage(WXOR1_n1, is_dram);
double I_WXOR1_n3 = simplified_nmos_leakage(WXOR1_n3, is_dram);
double I_WXOR1_n2 = simplified_nmos_leakage(WXOR1_n2, is_dram);
double I_WXOR1_n4 = simplified_nmos_leakage(WXOR1_n4, is_dram);
double I_WINV4_n1 = simplified_nmos_leakage(WINV4_n1, is_dram);
double I_WINV4_p1 = simplified_pmos_leakage(WINV4_p1, is_dram);
double I_WINV1_p1 = simplified_pmos_leakage(WINV1_p1, is_dram);
double I_WINV1_n1 = simplified_nmos_leakage(WINV1_n1, is_dram);

// Calculation of Area of Adder Circuit

adder_area_circuit_dff = 0;

adder_area_circuit += compute_gate_area(NOR, 2, WNOR1_p1, WNOR1_n1,  g_tp.cell_h_def);

adder_area_circuit += compute_gate_area(NOR, 2, WNOR2_p1, WNOR2_n1,  g_tp.cell_h_def);

adder_area_circuit += compute_gate_area(NOR, 2, WNOR3_p1, WNOR3_n1,  g_tp.cell_h_def);

adder_area_circuit_dff += 2 * compute_gate_area(DFF, 2, WDFF1_p1, WDFF1_n1,  g_tp.cell_h_def)* num_adderBLADE_subarray * num_subarrays_per_mat ;
adder_area_circuit += compute_gate_area(INV, 1, WINV1_p1, WINV1_n1,  g_tp.cell_h_def);
adder_area_circuit += compute_gate_area(INV, 1, WINV2_p1, WINV2_n1,  g_tp.cell_h_def);
adder_area_circuit += compute_gate_area(INV, 1, WINV3_p1, WINV3_n1,  g_tp.cell_h_def);
adder_area_circuit += compute_gate_area(INV, 1, WINV4_p1, WINV4_n1,  g_tp.cell_h_def);
adder_area_circuit += compute_gate_area(XOR, 4, WXOR1_p1, WXOR1_n1,  g_tp.cell_h_def);

adder_area_circuit_final = adder_area_circuit * num_adderBLADE_subarray * num_subarrays_per_mat ;

// Calculation of Final Leakage Current

double adderlkg_NOR1 = (I_WNOR1_n1) * NOR2_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;
double adderlkg_NOR2 = (I_WNOR2_n1) * NOR2_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;
double adderlkg_NOR3 = (I_WNOR3_n1) * NOR2_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;
double adderlkg_DFF1 = (I_WDFF1_n1) * DFF2_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;
double adderlkg_INV1 = (I_WINV1_n1) * INV_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;
double adderlkg_INV2 = (I_WINV2_n1) * INV_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;
double adderlkg_INV3 = (I_WINV3_n1) * INV_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;
double adderlkg_INV4 = (I_WINV4_n1) * INV_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;
double adderlkg_XOR1 = (I_WXOR1_n1) * XOR2_LEAK_STACK_FACTOR * num_adderBLADE_subarray * num_subarrays_per_mat;

// Calculation of Dynamic Energy and Delay


 // For NOR1
double C_load_NOR1 = drain_C_(WNOR1_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNOR1_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNOR1_n2, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WXOR1_p1, 0 , is_dram)
 + gate_C(WXOR1_n3, 0 , is_dram)
 + gate_C(WINV1_p1, 0 , is_dram)
 + gate_C(WINV1_n1, 0 , is_dram)
;
double rd_NOR1 = tr_R_on(WINV1_n1, NCH, 1, is_dram) ;
double tf_NOR1 = rd_NOR1 * (C_load_NOR1); 
double this_delay_NOR1 = horowitz(inrisetime, tf_NOR1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NOR1/(1.0 - 0.5); 


 // For NOR2
double C_load_NOR2 = drain_C_(WNOR2_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNOR3_p1, 0 , is_dram)
 + drain_C_(WNOR2_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNOR2_n2, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNOR3_n1, 0 , is_dram)
;
double rd_NOR2 = tr_R_on(WNOR3_n1, NCH, 1, is_dram) ;
double tf_NOR2 = rd_NOR2 * (C_load_NOR2); 
double this_delay_NOR2 = horowitz(inrisetime, tf_NOR2, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NOR2/(1.0 - 0.5); 


 // For NOR3
double C_load_NOR3 = drain_C_(WNOR3_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNOR3_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNOR3_n2, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WDFF1_p1, 0 , is_dram)
 + gate_C(WDFF1_n2, 0 , is_dram)
;
double rd_NOR3 = tr_R_on(WDFF1_n2, NCH, 1, is_dram) ;
double tf_NOR3 = rd_NOR3 * (C_load_NOR3); 
double this_delay_NOR3 = horowitz(inrisetime, tf_NOR3, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NOR3/(1.0 - 0.5); 


 // For DFF1
double C_load_DFF1 = drain_C_(WDFF1_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV2_p1, 0 , is_dram)
 + drain_C_(WDFF1_p4, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WDFF1_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV2_n1, 0 , is_dram)
 + drain_C_(WDFF1_n3, NCH, 2, 1, g_tp.cell_h_def, is_dram)
;
double rd_DFF1 = tr_R_on(WDFF1_n3, NCH, 2, is_dram) ;
double tf_DFF1 = rd_DFF1 * (C_load_DFF1); 
double this_delay_DFF1 = horowitz(inrisetime, tf_DFF1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_DFF1/(1.0 - 0.5); 


 // For INV1
double C_load_INV1 = gate_C(WXOR1_p3, 0 , is_dram)
 + gate_C(WXOR1_n1, 0 , is_dram)
 + drain_C_(WINV1_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WINV1_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
;
double rd_INV1 = tr_R_on(WINV1_n1, NCH, 1, is_dram) ;
double tf_INV1 = rd_INV1 * (C_load_INV1); 
double this_delay_INV1 = horowitz(inrisetime, tf_INV1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV1/(1.0 - 0.5); 


 // For INV2
double C_load_INV2 = gate_C(WNOR2_p2, 0 , is_dram)
 + gate_C(WNOR2_n2, 0 , is_dram)
 + drain_C_(WINV2_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WDFF1_p3, 0 , is_dram)
 + gate_C(WINV3_p1, 0 , is_dram)
 + gate_C(WXOR1_p2, 0 , is_dram)
 + drain_C_(WINV2_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WDFF1_n4, 0 , is_dram)
 + gate_C(WINV3_n1, 0 , is_dram)
 + gate_C(WXOR1_n2, 0 , is_dram)
;
double rd_INV2 = tr_R_on(WXOR1_n2, NCH, 1, is_dram) ;
double tf_INV2 = rd_INV2 * (C_load_INV2); 
double this_delay_INV2 = horowitz(inrisetime, tf_INV2, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV2/(1.0 - 0.5); 


 // For INV3
double C_load_INV3 = drain_C_(WINV3_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WXOR1_p4, 0 , is_dram)
 + drain_C_(WINV3_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WXOR1_n4, 0 , is_dram)
;
double rd_INV3 = tr_R_on(WXOR1_n4, NCH, 1, is_dram) ;
double tf_INV3 = rd_INV3 * (C_load_INV3); 
double this_delay_INV3 = horowitz(inrisetime, tf_INV3, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV3/(1.0 - 0.5); 


 // For INV4
double C_load_INV4 = drain_C_(WINV4_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WINV4_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
;
double rd_INV4 = tr_R_on(WINV4_p1, PCH, 1, is_dram) ;
double tf_INV4 = rd_INV4 * (C_load_INV4); 
double this_delay_INV4 = horowitz(inrisetime, tf_INV4, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV4/(1.0 - 0.5); 


 // For XOR1
double C_load_XOR1 = drain_C_(WXOR1_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR1_p4, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR1_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR1_n3, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV4_n1, 0 , is_dram)
 + gate_C(WINV4_p1, 0 , is_dram)
;
double rd_XOR1 = tr_R_on(WINV4_p1, NCH, 2, is_dram) ;
double tf_XOR1 = rd_XOR1 * (C_load_XOR1); 
double this_delay_XOR1 = horowitz(inrisetime, tf_XOR1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_XOR1/(1.0 - 0.5); 


//
if (g_ip->operation_type == 0)
{
    //Calculation of Final Dynamic Energy

power_adder.computeOp.dynamic = 0;
power_adder.computeOp.leakage = 0;

// power_adder.computeOp.dynamic += 0.5 *(C_load_XOR1  + C_load_INV4  + C_load_INV3  + C_load_INV2  + C_load_INV1  
// + C_load_DFF1  + C_load_NOR3  + C_load_NOR2  + C_load_NOR1  )* g_tp.peri_global.Vdd 
// * g_tp.peri_global.Vdd  * num_adder_subarray * num_subarrays_per_mat; 

power_adder.computeOp.dynamic = 43.17 * 1e-15 * num_adder_subarray * num_subarrays_per_mat;

//Calculation of Final Leakage Power

power_adder.computeOp.leakage += (adderlkg_XOR1 + adderlkg_INV4 + adderlkg_INV3 + adderlkg_INV2 + adderlkg_INV1 
+ adderlkg_DFF1 + adderlkg_NOR3 + adderlkg_NOR2 + adderlkg_NOR1 ) * g_tp.peri_global.Vdd; 

    adder_area = (adder_area_circuit_final + adder_area_circuit_dff);

    delay_adder_compute =  this_delay_NOR3 + this_delay_NOR2 + this_delay_INV2 + this_delay_DFF1; //this has to be changed
    //delay_adder_compute = 0.39 * 1e-9;
        
}

if (g_ip->operation_type == 1)
    {
        // Calculation of Delay of the Ripple Adder Circuitary"
        //The Delay is limited by the Carry Operation
        //Hence the delay of the circuit is:  (num_addder_subarrayy - 1)*Tcarry + Tsum;
        //delay_adder_compute = (num_adder_subarray - 1)*delay_adder_carry + delay_adder_sum;
        power_adder.computeOp.dynamic = 0;
        power_adder.computeOp.leakage = 0;
        delay_adder_carry = 0; 
        delay_adder_sum = 0;
        int num_of_parallel_computations = subarray.num_cols / (deg_bl_muxing * g_ip->n_bit);
        
        delay_adder_carry = 0.3578 * 1e-9;
        
        delay_adder_sum = 0.39 * 1e-9;

        
        delay_adder_compute = (g_ip->n_bit -1) * delay_adder_carry + delay_adder_sum;

        power_adder.computeOp.dynamic = (g_ip->n_bit ) * 43.17 * 1e-15 * num_of_parallel_computations* num_subarrays_per_mat;


        adder_area = adder_area_circuit_final;

        //Calculation of Final Leakage Power

        power_adder.computeOp.leakage = (adderlkg_XOR1 + adderlkg_INV4 + adderlkg_INV3 + adderlkg_INV1 + 
        adderlkg_NOR3 + adderlkg_NOR2 + adderlkg_NOR1 ) * g_tp.peri_global.Vdd; 
    }

}

return inrisetime ;
}