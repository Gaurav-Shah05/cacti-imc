
/*------------------------------------------------------------
*                              CACTI IMC                      

 * Alok Parmar       Nanditha Rao    IIIT Bangalore           
 *Kailash Prasad    Joycee Mekie    IIT Gandhinagar           

*------------------------------------------------------------*/

#include "multiplier_serial_new.h" 

double Mat::compute_delaymultiplier_serial_new(double inrisetime)
{

double outrisetime ;
outrisetime = compute_multiplier_delay_serial_new(outrisetime);
return outrisetime;
}

double Mat:: compute_multiplier_delay_serial_new(double inrisetime)
{

int num_multiplier_serial_NEW_subarray = subarray.num_cols / deg_bl_muxing;

int num_bits_multipy_subarray = subarray.num_cols / deg_bl_muxing;


if (g_ip->operation_type == 0)
{
if  (g_ip->adder_type == 1)
{
// CACTI 6.5 INCOMPUTE CIRCUIT AUTOMATED TOOLKIT 

// Difining the Sizes of the Transistors

double WNOR1_p1    =  200 * g_ip->F_sz_um;
double WNOR1_p2    =  200 * g_ip->F_sz_um;
double WNAND1_p1    =  200 * g_ip->F_sz_um;
double WNAND1_p2    =  200 * g_ip->F_sz_um;
double WINV1_p1    =  200 * g_ip->F_sz_um;
double WINV2_p1    =  200 * g_ip->F_sz_um;
double WNOR1_n1    =  100 * g_ip->F_sz_um;
double WNOR1_n2    =  100 * g_ip->F_sz_um;
double WNAND1_n1    =  100 * g_ip->F_sz_um;
double WNAND1_n2    =  100 * g_ip->F_sz_um;
double WINV1_n1    =  100 * g_ip->F_sz_um;
double WINV2_n1    =  100 * g_ip->F_sz_um;
double WDFF1_p1    =  200 * g_ip->F_sz_um;
double WDFF1_p2    =  200 * g_ip->F_sz_um;
double WINV3_p1    =  200 * g_ip->F_sz_um;
double WDFF1_p3    =  200 * g_ip->F_sz_um;
double WDFF1_p4    =  200 * g_ip->F_sz_um;
double WINV4_p1    =  200 * g_ip->F_sz_um;
double WDFF1_n1    =  100 * g_ip->F_sz_um;
double WDFF1_n2    =  100 * g_ip->F_sz_um;
double WINV3_n1    =  100 * g_ip->F_sz_um;
double WDFF1_n3    =  100 * g_ip->F_sz_um;
double WDFF1_n4    =  100 * g_ip->F_sz_um;
double WINV4_n1    =  100 * g_ip->F_sz_um;
double WXOR1_p1    =  200 * g_ip->F_sz_um;
double WXOR1_p2    =  200 * g_ip->F_sz_um;
double WXOR1_p3    =  200 * g_ip->F_sz_um;
double WXOR1_p4    =  200 * g_ip->F_sz_um;
double WXOR2_p1    =  200 * g_ip->F_sz_um;
double WXOR2_p2    =  200 * g_ip->F_sz_um;
double WXOR2_p3    =  200 * g_ip->F_sz_um;
double WXOR2_p4    =  200 * g_ip->F_sz_um;
double WXOR1_n1    =  100 * g_ip->F_sz_um;
double WXOR1_n2    =  100 * g_ip->F_sz_um;
double WXOR1_n3    =  100 * g_ip->F_sz_um;
double WXOR1_n4    =  100 * g_ip->F_sz_um;
double WXOR2_n1    =  100 * g_ip->F_sz_um;
double WXOR2_n3    =  100 * g_ip->F_sz_um;
double WXOR2_n2    =  100 * g_ip->F_sz_um;
double WXOR2_n4    =  100 * g_ip->F_sz_um;
double WINV5_n1    =  100 * g_ip->F_sz_um;
double WINV6_n1    =  100 * g_ip->F_sz_um;
double WINV5_p1    =  200 * g_ip->F_sz_um;
double WINV6_p1    =  200 * g_ip->F_sz_um;
double WNAND2_p1    =  200 * g_ip->F_sz_um;
double WNAND2_p2    =  200 * g_ip->F_sz_um;
double WNAND2_n1    =  100 * g_ip->F_sz_um;
double WNAND2_n2    =  100 * g_ip->F_sz_um;
double WNAND3_p1    =  200 * g_ip->F_sz_um;
double WNAND3_p2    =  200 * g_ip->F_sz_um;
double WNAND3_n1    =  100 * g_ip->F_sz_um;
double WNAND3_n2    =  100 * g_ip->F_sz_um;
double WNAND5_p1    =  200 * g_ip->F_sz_um;
double WNAND5_p2    =  200 * g_ip->F_sz_um;
double WNAND5_n1    =  100 * g_ip->F_sz_um;
double WNAND5_n2    =  100 * g_ip->F_sz_um;
double WNAND6_p1    =  200 * g_ip->F_sz_um;
double WNAND6_p2    =  200 * g_ip->F_sz_um;
double WNAND6_n1    =  100 * g_ip->F_sz_um;
double WNAND6_n2    =  100 * g_ip->F_sz_um;
double WNAND4_p1    =  200 * g_ip->F_sz_um;
double WNAND4_p2    =  200 * g_ip->F_sz_um;
double WNAND4_n1    =  100 * g_ip->F_sz_um;
double WNAND4_n2    =  100 * g_ip->F_sz_um;
double WNAND7_p1    =  200 * g_ip->F_sz_um;
double WNAND7_p2    =  200 * g_ip->F_sz_um;
double WNAND7_n1    =  100 * g_ip->F_sz_um;
double WNAND7_n2    =  100 * g_ip->F_sz_um;
double WNAND8_p1    =  200 * g_ip->F_sz_um;
double WNAND8_p2    =  200 * g_ip->F_sz_um;
double WNAND8_n1    =  100 * g_ip->F_sz_um;
double WNAND8_n2    =  100 * g_ip->F_sz_um;
double WNAND9_p1    =  200 * g_ip->F_sz_um;
double WNAND9_p2    =  200 * g_ip->F_sz_um;
double WNAND9_n1    =  100 * g_ip->F_sz_um;
double WNAND9_n2    =  100 * g_ip->F_sz_um;
double WNAND10_p1    =  200 * g_ip->F_sz_um;
double WNAND10_p2    =  200 * g_ip->F_sz_um;
double WNAND10_n1    =  100 * g_ip->F_sz_um;
double WNAND10_n2    =  100 * g_ip->F_sz_um;
double WNAND12_p1    =  200 * g_ip->F_sz_um;
double WNAND12_p2    =  200 * g_ip->F_sz_um;
double WNAND12_n1    =  100 * g_ip->F_sz_um;
double WNAND12_n2    =  100 * g_ip->F_sz_um;
double WNAND11_p1    =  200 * g_ip->F_sz_um;
double WNAND11_p2    =  200 * g_ip->F_sz_um;
double WNAND11_n1    =  100 * g_ip->F_sz_um;
double WNAND11_n2    =  100 * g_ip->F_sz_um;
double WINV8_p1    =  200 * g_ip->F_sz_um;
double WINV8_n1    =  100 * g_ip->F_sz_um;
double WNAND13_p1    =  200 * g_ip->F_sz_um;
double WNAND13_p2    =  200 * g_ip->F_sz_um;
double WNAND13_n1    =  100 * g_ip->F_sz_um;
double WNAND13_n2    =  100 * g_ip->F_sz_um;
double WNAND14_p1    =  200 * g_ip->F_sz_um;
double WNAND14_p2    =  200 * g_ip->F_sz_um;
double WINV9_p1    =  200 * g_ip->F_sz_um;
double WNAND14_n1    =  100 * g_ip->F_sz_um;
double WNAND14_n2    =  100 * g_ip->F_sz_um;
double WINV9_n1    =  100 * g_ip->F_sz_um;
double WDFF2_p2    =  200 * g_ip->F_sz_um;
double WDFF2_n1    =  100 * g_ip->F_sz_um;
double WDFF2_n2    =  100 * g_ip->F_sz_um;
double WINV7_p1    =  200 * g_ip->F_sz_um;
double WDFF2_p3    =  200 * g_ip->F_sz_um;
double WDFF2_p4    =  200 * g_ip->F_sz_um;
double WINV7_n1    =  100 * g_ip->F_sz_um;
double WDFF2_n3    =  100 * g_ip->F_sz_um;
double WDFF2_n4    =  100 * g_ip->F_sz_um;
double WDFF2_p1    =  200 * g_ip->F_sz_um;


// Leakage Calculation of Individual Gates

double I_WNOR1_p1 = simplified_pmos_leakage(WNOR1_p1, is_dram);
double I_WNOR1_p2 = simplified_pmos_leakage(WNOR1_p2, is_dram);
double I_WNAND1_p1 = simplified_pmos_leakage(WNAND1_p1, is_dram);
double I_WNAND1_p2 = simplified_pmos_leakage(WNAND1_p2, is_dram);
double I_WINV1_p1 = simplified_pmos_leakage(WINV1_p1, is_dram);
double I_WINV2_p1 = simplified_pmos_leakage(WINV2_p1, is_dram);
double I_WNOR1_n1 = simplified_nmos_leakage(WNOR1_n1, is_dram);
double I_WNOR1_n2 = simplified_nmos_leakage(WNOR1_n2, is_dram);
double I_WNAND1_n1 = simplified_nmos_leakage(WNAND1_n1, is_dram);
double I_WNAND1_n2 = simplified_nmos_leakage(WNAND1_n2, is_dram);
double I_WINV1_n1 = simplified_nmos_leakage(WINV1_n1, is_dram);
double I_WINV2_n1 = simplified_nmos_leakage(WINV2_n1, is_dram);
double I_WDFF1_p1 = simplified_pmos_leakage(WDFF1_p1, is_dram);
double I_WDFF1_p2 = simplified_pmos_leakage(WDFF1_p2, is_dram);
double I_WINV3_p1 = simplified_pmos_leakage(WINV3_p1, is_dram);
double I_WDFF1_p3 = simplified_pmos_leakage(WDFF1_p3, is_dram);
double I_WDFF1_p4 = simplified_pmos_leakage(WDFF1_p4, is_dram);
double I_WINV4_p1 = simplified_pmos_leakage(WINV4_p1, is_dram);
double I_WDFF1_n1 = simplified_nmos_leakage(WDFF1_n1, is_dram);
double I_WDFF1_n2 = simplified_nmos_leakage(WDFF1_n2, is_dram);
double I_WINV3_n1 = simplified_nmos_leakage(WINV3_n1, is_dram);
double I_WDFF1_n3 = simplified_nmos_leakage(WDFF1_n3, is_dram);
double I_WDFF1_n4 = simplified_nmos_leakage(WDFF1_n4, is_dram);
double I_WINV4_n1 = simplified_nmos_leakage(WINV4_n1, is_dram);
double I_WXOR1_p1 = simplified_pmos_leakage(WXOR1_p1, is_dram);
double I_WXOR1_p2 = simplified_pmos_leakage(WXOR1_p2, is_dram);
double I_WXOR1_p3 = simplified_pmos_leakage(WXOR1_p3, is_dram);
double I_WXOR1_p4 = simplified_pmos_leakage(WXOR1_p4, is_dram);
double I_WXOR2_p1 = simplified_pmos_leakage(WXOR2_p1, is_dram);
double I_WXOR2_p2 = simplified_pmos_leakage(WXOR2_p2, is_dram);
double I_WXOR2_p3 = simplified_pmos_leakage(WXOR2_p3, is_dram);
double I_WXOR2_p4 = simplified_pmos_leakage(WXOR2_p4, is_dram);
double I_WXOR1_n1 = simplified_nmos_leakage(WXOR1_n1, is_dram);
double I_WXOR1_n2 = simplified_nmos_leakage(WXOR1_n2, is_dram);
double I_WXOR1_n3 = simplified_nmos_leakage(WXOR1_n3, is_dram);
double I_WXOR1_n4 = simplified_nmos_leakage(WXOR1_n4, is_dram);
double I_WXOR2_n1 = simplified_nmos_leakage(WXOR2_n1, is_dram);
double I_WXOR2_n3 = simplified_nmos_leakage(WXOR2_n3, is_dram);
double I_WXOR2_n2 = simplified_nmos_leakage(WXOR2_n2, is_dram);
double I_WXOR2_n4 = simplified_nmos_leakage(WXOR2_n4, is_dram);
double I_WINV5_n1 = simplified_nmos_leakage(WINV5_n1, is_dram);
double I_WINV6_n1 = simplified_nmos_leakage(WINV6_n1, is_dram);
double I_WINV5_p1 = simplified_pmos_leakage(WINV5_p1, is_dram);
double I_WINV6_p1 = simplified_pmos_leakage(WINV6_p1, is_dram);
double I_WNAND2_p1 = simplified_pmos_leakage(WNAND2_p1, is_dram);
double I_WNAND2_p2 = simplified_pmos_leakage(WNAND2_p2, is_dram);
double I_WNAND2_n1 = simplified_nmos_leakage(WNAND2_n1, is_dram);
double I_WNAND2_n2 = simplified_nmos_leakage(WNAND2_n2, is_dram);
double I_WNAND3_p1 = simplified_pmos_leakage(WNAND3_p1, is_dram);
double I_WNAND3_p2 = simplified_pmos_leakage(WNAND3_p2, is_dram);
double I_WNAND3_n1 = simplified_nmos_leakage(WNAND3_n1, is_dram);
double I_WNAND3_n2 = simplified_nmos_leakage(WNAND3_n2, is_dram);
double I_WNAND5_p1 = simplified_pmos_leakage(WNAND5_p1, is_dram);
double I_WNAND5_p2 = simplified_pmos_leakage(WNAND5_p2, is_dram);
double I_WNAND5_n1 = simplified_nmos_leakage(WNAND5_n1, is_dram);
double I_WNAND5_n2 = simplified_nmos_leakage(WNAND5_n2, is_dram);
double I_WNAND6_p1 = simplified_pmos_leakage(WNAND6_p1, is_dram);
double I_WNAND6_p2 = simplified_pmos_leakage(WNAND6_p2, is_dram);
double I_WNAND6_n1 = simplified_nmos_leakage(WNAND6_n1, is_dram);
double I_WNAND6_n2 = simplified_nmos_leakage(WNAND6_n2, is_dram);
double I_WNAND4_p1 = simplified_pmos_leakage(WNAND4_p1, is_dram);
double I_WNAND4_p2 = simplified_pmos_leakage(WNAND4_p2, is_dram);
double I_WNAND4_n1 = simplified_nmos_leakage(WNAND4_n1, is_dram);
double I_WNAND4_n2 = simplified_nmos_leakage(WNAND4_n2, is_dram);
double I_WNAND7_p1 = simplified_pmos_leakage(WNAND7_p1, is_dram);
double I_WNAND7_p2 = simplified_pmos_leakage(WNAND7_p2, is_dram);
double I_WNAND7_n1 = simplified_nmos_leakage(WNAND7_n1, is_dram);
double I_WNAND7_n2 = simplified_nmos_leakage(WNAND7_n2, is_dram);
double I_WNAND8_p1 = simplified_pmos_leakage(WNAND8_p1, is_dram);
double I_WNAND8_p2 = simplified_pmos_leakage(WNAND8_p2, is_dram);
double I_WNAND8_n1 = simplified_nmos_leakage(WNAND8_n1, is_dram);
double I_WNAND8_n2 = simplified_nmos_leakage(WNAND8_n2, is_dram);
double I_WNAND9_p1 = simplified_pmos_leakage(WNAND9_p1, is_dram);
double I_WNAND9_p2 = simplified_pmos_leakage(WNAND9_p2, is_dram);
double I_WNAND9_n1 = simplified_nmos_leakage(WNAND9_n1, is_dram);
double I_WNAND9_n2 = simplified_nmos_leakage(WNAND9_n2, is_dram);
double I_WNAND10_p1 = simplified_pmos_leakage(WNAND10_p1, is_dram);
double I_WNAND10_p2 = simplified_pmos_leakage(WNAND10_p2, is_dram);
double I_WNAND10_n1 = simplified_nmos_leakage(WNAND10_n1, is_dram);
double I_WNAND10_n2 = simplified_nmos_leakage(WNAND10_n2, is_dram);
double I_WNAND12_p1 = simplified_pmos_leakage(WNAND12_p1, is_dram);
double I_WNAND12_p2 = simplified_pmos_leakage(WNAND12_p2, is_dram);
double I_WNAND12_n1 = simplified_nmos_leakage(WNAND12_n1, is_dram);
double I_WNAND12_n2 = simplified_nmos_leakage(WNAND12_n2, is_dram);
double I_WNAND11_p1 = simplified_pmos_leakage(WNAND11_p1, is_dram);
double I_WNAND11_p2 = simplified_pmos_leakage(WNAND11_p2, is_dram);
double I_WNAND11_n1 = simplified_nmos_leakage(WNAND11_n1, is_dram);
double I_WNAND11_n2 = simplified_nmos_leakage(WNAND11_n2, is_dram);
double I_WINV8_p1 = simplified_pmos_leakage(WINV8_p1, is_dram);
double I_WINV8_n1 = simplified_nmos_leakage(WINV8_n1, is_dram);
double I_WNAND13_p1 = simplified_pmos_leakage(WNAND13_p1, is_dram);
double I_WNAND13_p2 = simplified_pmos_leakage(WNAND13_p2, is_dram);
double I_WNAND13_n1 = simplified_nmos_leakage(WNAND13_n1, is_dram);
double I_WNAND13_n2 = simplified_nmos_leakage(WNAND13_n2, is_dram);
double I_WNAND14_p1 = simplified_pmos_leakage(WNAND14_p1, is_dram);
double I_WNAND14_p2 = simplified_pmos_leakage(WNAND14_p2, is_dram);
double I_WINV9_p1 = simplified_pmos_leakage(WINV9_p1, is_dram);
double I_WNAND14_n1 = simplified_nmos_leakage(WNAND14_n1, is_dram);
double I_WNAND14_n2 = simplified_nmos_leakage(WNAND14_n2, is_dram);
double I_WINV9_n1 = simplified_nmos_leakage(WINV9_n1, is_dram);
double I_WDFF2_p2 = simplified_pmos_leakage(WDFF2_p2, is_dram);
double I_WDFF2_n1 = simplified_nmos_leakage(WDFF2_n1, is_dram);
double I_WDFF2_n2 = simplified_nmos_leakage(WDFF2_n2, is_dram);
double I_WINV7_p1 = simplified_pmos_leakage(WINV7_p1, is_dram);
double I_WDFF2_p3 = simplified_pmos_leakage(WDFF2_p3, is_dram);
double I_WDFF2_p4 = simplified_pmos_leakage(WDFF2_p4, is_dram);
double I_WINV7_n1 = simplified_nmos_leakage(WINV7_n1, is_dram);
double I_WDFF2_n3 = simplified_nmos_leakage(WDFF2_n3, is_dram);
double I_WDFF2_n4 = simplified_nmos_leakage(WDFF2_n4, is_dram);
double I_WDFF2_p1 = simplified_pmos_leakage(WDFF2_p1, is_dram);


// Calculation of Area of Multiplier Circuit

multiplier_area += compute_gate_area(INV, 1, WINV1_p1, WINV1_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(INV, 1, WINV2_p1, WINV2_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(INV, 1, WINV3_p1, WINV3_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(INV, 1, WINV4_p1, WINV4_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(INV, 1, WINV5_p1, WINV5_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(INV, 1, WINV6_p1, WINV6_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(INV, 1, WINV7_p1, WINV7_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(INV, 1, WINV8_p1, WINV8_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(INV, 1, WINV9_p1, WINV9_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(DFF, 2, WDFF1_p1, WDFF1_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(DFF, 2, WDFF2_p1, WDFF2_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND1_p1, WNAND1_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND2_p1, WNAND2_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND3_p1, WNAND3_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND4_p1, WNAND4_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND5_p1, WNAND5_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND6_p1, WNAND6_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND7_p1, WNAND7_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND8_p1, WNAND8_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND9_p1, WNAND9_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND10_p1, WNAND10_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND11_p1, WNAND11_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND12_p1, WNAND12_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND13_p1, WNAND13_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NAND, 2, WNAND14_p1, WNAND14_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(NOR, 2, WNOR1_p1, WNOR1_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(XOR, 4, WXOR1_p1, WXOR1_n1,  g_tp.cell_h_def);
multiplier_area += compute_gate_area(XOR, 4, WXOR2_p1, WXOR2_n1,  g_tp.cell_h_def);

multiplier_area = multiplier_area * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat ;

// Calculation of Final Leakage Power

double  multiplierlkg_INV1 = (I_WINV1_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_INV2 = (I_WINV2_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_INV3 = (I_WINV3_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_INV4 = (I_WINV4_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_INV5 = (I_WINV5_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_INV6 = (I_WINV6_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_INV7 = (I_WINV7_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_INV8 = (I_WINV8_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_INV9 = (I_WINV9_n1) * INV_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_DFF1 = (I_WDFF1_n1) * DFF2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_DFF2 = (I_WDFF2_n1) * DFF2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND1 = (I_WNAND1_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND2 = (I_WNAND2_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND3 = (I_WNAND3_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND4 = (I_WNAND4_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND5 = (I_WNAND5_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND6 = (I_WNAND6_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND7 = (I_WNAND7_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND8 = (I_WNAND8_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND9 = (I_WNAND9_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND10 = (I_WNAND1_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND11 = (I_WNAND1_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND12 = (I_WNAND1_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND13 = (I_WNAND1_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NAND14 = (I_WNAND1_n1) * NAND2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_NOR1 = (I_WNOR1_n1) * NOR2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_XOR1 = (I_WXOR1_n1) * XOR2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;
double  multiplierlkg_XOR2 = (I_WXOR2_n1) * XOR2_LEAK_STACK_FACTOR * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;

// Calculation of Dynamic Energy and Delay


 // For INV1
double C_load_INV1 = gate_C(WNAND1_p2, 0 , is_dram)
 + drain_C_(WINV1_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND1_n1, 0 , is_dram)
 + drain_C_(WINV1_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
;
double rd_INV1 = tr_R_on(WINV1_n1, NCH, 1, is_dram) ;
double tf_INV1 = rd_INV1 * (C_load_INV1); 
double this_delay_INV1 = horowitz(inrisetime, tf_INV1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV1/(1.0 - 0.5); 


 // For INV2
double C_load_INV2 = gate_C(WNAND1_p1, 0 , is_dram)
 + drain_C_(WINV2_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND1_n2, 0 , is_dram)
 + drain_C_(WINV2_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WXOR2_p2, 0 , is_dram)
 + gate_C(WXOR2_n3, 0 , is_dram)
;
double rd_INV2 = tr_R_on(WXOR2_n3, NCH, 1, is_dram) ;
double tf_INV2 = rd_INV2 * (C_load_INV2); 
double this_delay_INV2 = horowitz(inrisetime, tf_INV2, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV2/(1.0 - 0.5); 


 // For INV3
double C_load_INV3 = drain_C_(WINV3_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WDFF1_p3, 0 , is_dram)
 + gate_C(WINV4_p1, 0 , is_dram)
 + drain_C_(WINV3_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WDFF1_n4, 0 , is_dram)
 + gate_C(WINV4_n1, 0 , is_dram)
 + gate_C(WXOR1_p4, 0 , is_dram)
 + gate_C(WXOR2_p4, 0 , is_dram)
 + gate_C(WXOR1_n4, 0 , is_dram)
 + gate_C(WXOR2_n4, 0 , is_dram)
 + gate_C(WNAND3_p1, 0 , is_dram)
 + gate_C(WNAND3_n1, 0 , is_dram)
;
double rd_INV3 = tr_R_on(WNAND3_n1, NCH, 1, is_dram) ;
double tf_INV3 = rd_INV3 * (C_load_INV3); 
double this_delay_INV3 = horowitz(inrisetime, tf_INV3, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV3/(1.0 - 0.5); 


 // For INV4
double C_load_INV4 = drain_C_(WINV4_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WINV4_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WXOR1_p3, 0 , is_dram)
 + gate_C(WXOR2_p3, 0 , is_dram)
 + gate_C(WXOR1_n2, 0 , is_dram)
 + gate_C(WXOR2_n2, 0 , is_dram)
;
double rd_INV4 = tr_R_on(WXOR2_n2, NCH, 1, is_dram) ;
double tf_INV4 = rd_INV4 * (C_load_INV4); 
double this_delay_INV4 = horowitz(inrisetime, tf_INV4, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV4/(1.0 - 0.5); 


 // For INV5
double C_load_INV5 = drain_C_(WINV5_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WINV5_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND2_p1, 0 , is_dram)
 + gate_C(WNAND2_n1, 0 , is_dram)
;
double rd_INV5 = tr_R_on(WNAND2_n1, PCH, 1, is_dram) ;
double tf_INV5 = rd_INV5 * (C_load_INV5); 
double this_delay_INV5 = horowitz(inrisetime, tf_INV5, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV5/(1.0 - 0.5); 


 // For INV6
double C_load_INV6 = gate_C(WDFF1_p1, 0 , is_dram)
 + gate_C(WDFF1_n2, 0 , is_dram)
 + drain_C_(WINV6_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WINV6_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
;
double rd_INV6 = tr_R_on(WINV6_p1, PCH, 1, is_dram) ;
double tf_INV6 = rd_INV6 * (C_load_INV6); 
double this_delay_INV6 = horowitz(inrisetime, tf_INV6, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV6/(1.0 - 0.5); 


 // For INV7
double C_load_INV7 = gate_C(WNAND6_p1, 0 , is_dram)
 + gate_C(WNAND6_n1, 0 , is_dram)
 + gate_C(WINV8_p1, 0 , is_dram)
 + gate_C(WINV8_n1, 0 , is_dram)
 + drain_C_(WINV7_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WDFF2_p3, 0 , is_dram)
 + drain_C_(WINV7_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WDFF2_n4, 0 , is_dram)
;
double rd_INV7 = tr_R_on(WDFF2_n4, NCH, 1, is_dram) ;
double tf_INV7 = rd_INV7 * (C_load_INV7); 
double this_delay_INV7 = horowitz(inrisetime, tf_INV7, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV7/(1.0 - 0.5); 


 // For INV8
double C_load_INV8 = drain_C_(WINV8_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WINV8_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND13_p1, 0 , is_dram)
 + gate_C(WNAND13_n1, 0 , is_dram)
;
double rd_INV8 = tr_R_on(WNAND13_n1, NCH, 1, is_dram) ;
double tf_INV8 = rd_INV8 * (C_load_INV8); 
double this_delay_INV8 = horowitz(inrisetime, tf_INV8, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV8/(1.0 - 0.5); 


 // For INV9
double C_load_INV9 = drain_C_(WINV9_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WINV9_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
;
double rd_INV9 = tr_R_on(WINV9_n1, NCH, 1, is_dram) ;
double tf_INV9 = rd_INV9 * (C_load_INV9); 
double this_delay_INV9 = horowitz(inrisetime, tf_INV9, 0.5, 0.5, RISE) ;
inrisetime = this_delay_INV9/(1.0 - 0.5); 


 // For DFF1
double C_load_DFF1 = drain_C_(WDFF1_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV3_p1, 0 , is_dram)
 + drain_C_(WDFF1_p4, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WDFF1_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV3_n1, 0 , is_dram)
 + drain_C_(WDFF1_n3, NCH, 2, 1, g_tp.cell_h_def, is_dram)
;
double rd_DFF1 = tr_R_on(WDFF1_n3, NCH, 2, is_dram) ;
double tf_DFF1 = rd_DFF1 * (C_load_DFF1); 
double this_delay_DFF1 = horowitz(inrisetime, tf_DFF1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_DFF1/(1.0 - 0.5); 


 // For DFF2
double C_load_DFF2 = drain_C_(WDFF2_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WDFF2_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV7_p1, 0 , is_dram)
 + drain_C_(WDFF2_p4, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV7_n1, 0 , is_dram)
 + drain_C_(WDFF2_n3, NCH, 2, 1, g_tp.cell_h_def, is_dram)
;
double rd_DFF2 = tr_R_on(WDFF2_n3, NCH, 2, is_dram) ;
double tf_DFF2 = rd_DFF2 * (C_load_DFF2); 
double this_delay_DFF2 = horowitz(inrisetime, tf_DFF2, 0.5, 0.5, RISE) ;
inrisetime = this_delay_DFF2/(1.0 - 0.5); 


 // For NAND1
double C_load_NAND1 = drain_C_(WNAND1_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND1_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND1_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WXOR1_p2, 0 , is_dram)
 + gate_C(WXOR1_n3, 0 , is_dram)
;
double rd_NAND1 = tr_R_on(WXOR1_n3, NCH, 2, is_dram) ;
double tf_NAND1 = rd_NAND1 * (C_load_NAND1); 
double this_delay_NAND1 = horowitz(inrisetime, tf_NAND1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND1/(1.0 - 0.5); 


 // For NAND2
double C_load_NAND2 = drain_C_(WNAND2_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND2_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND2_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND4_p1, 0 , is_dram)
 + gate_C(WNAND4_n1, 0 , is_dram)
;
double rd_NAND2 = tr_R_on(WNAND4_n1, NCH, 2, is_dram) ;
double tf_NAND2 = rd_NAND2 * (C_load_NAND2); 
double this_delay_NAND2 = horowitz(inrisetime, tf_NAND2, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND2/(1.0 - 0.5); 


 // For NAND3
double C_load_NAND3 = drain_C_(WNAND3_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND3_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND3_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND4_p2, 0 , is_dram)
 + gate_C(WNAND4_n2, 0 , is_dram)
;
double rd_NAND3 = tr_R_on(WNAND4_n2, NCH, 2, is_dram) ;
double tf_NAND3 = rd_NAND3 * (C_load_NAND3); 
double this_delay_NAND3 = horowitz(inrisetime, tf_NAND3, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND3/(1.0 - 0.5); 


 // For NAND4
double C_load_NAND4 = drain_C_(WNAND4_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND4_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND4_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND8_p1, 0 , is_dram)
 + gate_C(WNAND8_n1, 0 , is_dram)
;
double rd_NAND4 = tr_R_on(WNAND8_n1, NCH, 2, is_dram) ;
double tf_NAND4 = rd_NAND4 * (C_load_NAND4); 
double this_delay_NAND4 = horowitz(inrisetime, tf_NAND4, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND4/(1.0 - 0.5); 


 // For NAND5
double C_load_NAND5 = drain_C_(WNAND5_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND5_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND5_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND7_p1, 0 , is_dram)
 + gate_C(WNAND7_n1, 0 , is_dram)
;
double rd_NAND5 = tr_R_on(WNAND7_n1, NCH, 2, is_dram) ;
double tf_NAND5 = rd_NAND5 * (C_load_NAND5); 
double this_delay_NAND5 = horowitz(inrisetime, tf_NAND5, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND5/(1.0 - 0.5); 


 // For NAND6
double C_load_NAND6 = drain_C_(WNAND6_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND6_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND6_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND7_p2, 0 , is_dram)
 + gate_C(WNAND7_n2, 0 , is_dram)
;
double rd_NAND6 = tr_R_on(WNAND7_n2, NCH, 2, is_dram) ;
double tf_NAND6 = rd_NAND6 * (C_load_NAND6); 
double this_delay_NAND6 = horowitz(inrisetime, tf_NAND6, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND6/(1.0 - 0.5); 


 // For NAND7
double C_load_NAND7 = drain_C_(WNAND7_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND7_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND7_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND9_p1, 0 , is_dram)
 + gate_C(WNAND9_n1, 0 , is_dram)
;
double rd_NAND7 = tr_R_on(WNAND9_n1, NCH, 2, is_dram) ;
double tf_NAND7 = rd_NAND7 * (C_load_NAND7); 
double this_delay_NAND7 = horowitz(inrisetime, tf_NAND7, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND7/(1.0 - 0.5); 


 // For NAND8
double C_load_NAND8 = drain_C_(WNAND8_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND8_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND8_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND10_p1, 0 , is_dram)
 + gate_C(WNAND10_n1, 0 , is_dram)
;
double rd_NAND8 = tr_R_on(WNAND10_n1, NCH, 2, is_dram) ;
double tf_NAND8 = rd_NAND8 * (C_load_NAND8); 
double this_delay_NAND8 = horowitz(inrisetime, tf_NAND8, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND8/(1.0 - 0.5); 


 // For NAND9
double C_load_NAND9 = drain_C_(WNAND9_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND9_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND9_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND10_p2, 0 , is_dram)
 + gate_C(WNAND10_n2, 0 , is_dram)
;
double rd_NAND9 = tr_R_on(WNAND10_n2, NCH, 2, is_dram) ;
double tf_NAND9 = rd_NAND9 * (C_load_NAND9); 
double this_delay_NAND9 = horowitz(inrisetime, tf_NAND9, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND9/(1.0 - 0.5); 


 // For NAND10
double C_load_NAND10 = drain_C_(WNAND10_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND10_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND10_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
;
double rd_NAND10 = tr_R_on(WNAND10_n1, NCH, 2, is_dram) ;
double tf_NAND10 = rd_NAND10 * (C_load_NAND10); 
double this_delay_NAND10 = horowitz(inrisetime, tf_NAND10, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND10/(1.0 - 0.5); 


 // For NAND11
double C_load_NAND11 = gate_C(WNAND2_p2, 0 , is_dram)
 + gate_C(WNAND2_n2, 0 , is_dram)
 + gate_C(WNAND5_p2, 0 , is_dram)
 + gate_C(WNAND5_n2, 0 , is_dram)
 + drain_C_(WNAND11_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND11_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND11_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
;
double rd_NAND11 = tr_R_on(WNAND11_n1, NCH, 2, is_dram) ;
double tf_NAND11 = rd_NAND11 * (C_load_NAND11); 
double this_delay_NAND11 = horowitz(inrisetime, tf_NAND11, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND11/(1.0 - 0.5); 


 // For NAND12
double C_load_NAND12 = gate_C(WNAND8_p2, 0 , is_dram)
 + gate_C(WNAND8_n2, 0 , is_dram)
 + drain_C_(WNAND12_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND12_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND12_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
;
double rd_NAND12 = tr_R_on(WNAND12_n1, NCH, 2, is_dram) ;
double tf_NAND12 = rd_NAND12 * (C_load_NAND12); 
double this_delay_NAND12 = horowitz(inrisetime, tf_NAND12, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND12/(1.0 - 0.5); 


 // For NAND13
double C_load_NAND13 = drain_C_(WNAND13_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND13_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND13_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WNAND14_p1, 0 , is_dram)
 + gate_C(WNAND14_n1, 0 , is_dram)
;
double rd_NAND13 = tr_R_on(WNAND14_n1, NCH, 2, is_dram) ;
double tf_NAND13 = rd_NAND13 * (C_load_NAND13); 
double this_delay_NAND13 = horowitz(inrisetime, tf_NAND13, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND13/(1.0 - 0.5); 


 // For NAND14
double C_load_NAND14 = drain_C_(WNAND14_p1, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNAND14_p2, PCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV9_p1, 0 , is_dram)
 + drain_C_(WNAND14_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV9_n1, 0 , is_dram)
;
double rd_NAND14 = tr_R_on(WINV9_n1, NCH, 2, is_dram) ;
double tf_NAND14 = rd_NAND14 * (C_load_NAND14); 
double this_delay_NAND14 = horowitz(inrisetime, tf_NAND14, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NAND14/(1.0 - 0.5); 


 // For NOR1
double C_load_NOR1 = drain_C_(WNOR1_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNOR1_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WNOR1_n2, NCH, 1, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WXOR1_p1, 0 , is_dram)
 + gate_C(WXOR1_n1, 0 , is_dram)
;
double rd_NOR1 = tr_R_on(WXOR1_n1, NCH, 1, is_dram) ;
double tf_NOR1 = rd_NOR1 * (C_load_NOR1); 
double this_delay_NOR1 = horowitz(inrisetime, tf_NOR1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_NOR1/(1.0 - 0.5); 


 // For XOR1
double C_load_XOR1 = drain_C_(WXOR1_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR1_p4, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR1_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR1_n3, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV5_n1, 0 , is_dram)
 + gate_C(WINV5_p1, 0 , is_dram)
;
double rd_XOR1 = tr_R_on(WINV5_p1, NCH, 2, is_dram) ;
double tf_XOR1 = rd_XOR1 * (C_load_XOR1); 
double this_delay_XOR1 = horowitz(inrisetime, tf_XOR1, 0.5, 0.5, RISE) ;
inrisetime = this_delay_XOR1/(1.0 - 0.5); 


 // For XOR2
double C_load_XOR2 = drain_C_(WXOR2_p2, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR2_p4, PCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR2_n1, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + drain_C_(WXOR2_n3, NCH, 2, 1, g_tp.cell_h_def, is_dram)
 + gate_C(WINV6_n1, 0 , is_dram)
 + gate_C(WINV6_p1, 0 , is_dram)
;
double rd_XOR2 = tr_R_on(WINV6_p1, NCH, 2, is_dram) ;
double tf_XOR2 = rd_XOR2 * (C_load_XOR2); 
double this_delay_XOR2 = horowitz(inrisetime, tf_XOR2, 0.5, 0.5, RISE) ;
inrisetime = this_delay_XOR2/(1.0 - 0.5); 


//caculation of delay
delay_multiplier_compute = (this_delay_INV1 + this_delay_INV7 + this_delay_XOR2 +  this_delay_INV6
+  this_delay_DFF1 + this_delay_INV4 +  this_delay_NAND2 +  this_delay_NAND5 +  this_delay_NAND7 +
this_delay_NAND9) ;
// delay_multiplier_compute = 0.388 * 1e-9;
//Calculation of Final Dynamic Energy

power_multiplier.computeOp.dynamic = 0.5 *(C_load_XOR2  + C_load_XOR1  + C_load_NOR1  + C_load_NAND14  
+ C_load_NAND13  + C_load_NAND12  + C_load_NAND11  + C_load_NAND10  + C_load_NAND9  + C_load_NAND8  
+ C_load_NAND7  + C_load_NAND6  + C_load_NAND5  + C_load_NAND4  + C_load_NAND3  + C_load_NAND2  
+ C_load_NAND1  + C_load_DFF2  + C_load_DFF1  + C_load_INV9  + C_load_INV8  + C_load_INV7  
+ C_load_INV6  + C_load_INV5  + C_load_INV4  + C_load_INV3  + C_load_INV2  + C_load_INV1  )* g_tp.peri_global.Vdd * g_tp.peri_global.Vdd * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat; 

// power_multiplier.computeOp.dynamic = 48.3 * 1e-15 * num_multiplier_serial_NEW_subarray * num_subarrays_per_mat;




//Calculation of Final Leakage Power

power_multiplier.computeOp.leakage = ( multiplierlkg_XOR2 +  multiplierlkg_XOR1 +  multiplierlkg_NOR1 
+  multiplierlkg_NAND1 +  multiplierlkg_NAND1 +  multiplierlkg_NAND1 +  multiplierlkg_NAND1 
+  multiplierlkg_NAND1 +  multiplierlkg_NAND9 +  multiplierlkg_NAND8 +  multiplierlkg_NAND7 
+  multiplierlkg_NAND6 +  multiplierlkg_NAND5 +  multiplierlkg_NAND4 +  multiplierlkg_NAND3 
+  multiplierlkg_NAND2 +  multiplierlkg_NAND1 +  multiplierlkg_DFF2 +  multiplierlkg_DFF1 
+  multiplierlkg_INV9 +  multiplierlkg_INV8 +  multiplierlkg_INV7 +  multiplierlkg_INV6 
+  multiplierlkg_INV5 +  multiplierlkg_INV4 +  multiplierlkg_INV3 +  multiplierlkg_INV2 
+  multiplierlkg_INV1 ) * g_tp.peri_global.Vdd; 

}
}
return inrisetime ;

}