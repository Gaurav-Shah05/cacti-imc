
/*------------------------------------------------------------
 *                              CACTI IMC
 * Alok Parmar       Nanditha Rao    IIIT Bangalore
 * Kailash Prasad    Joycee Mekie    IIT Gandhinagar
 *------------------------------------------------------------*/
#include "write_driver.h"


double Mat::compute_delaywrite_driver(double inrisetime)
{
double outrisetime;
outrisetime = compute_write_driver_delay(outrisetime);  //alok
return outrisetime;
}


double Mat::compute_write_driver_delay(double inrisetime)
{
  //int num_write_driver = g_ip->max_op / deg_bl_muxing; //in a subarray
  int num_write_driver = subarray.num_cols / deg_bl_muxing;
  double C_ld, rd, tf, this_delay;
  double p_to_n_sz_r = pmos_to_nmos_sz_ratio(is_dram);

//The sizes of the inverter that it is driving

  double W_invwrite_p1 = 145 * g_ip->F_sz_um;
  double W_invwrite_n1 = 100 * g_ip->F_sz_um;

  double W_invwrite_p2 = 145 * g_ip->F_sz_um;
  double W_invwrite_n2 = 100 * g_ip->F_sz_um;


  ///The Sizes of the Pass Transistors

  double W_write_n1    =  100 * g_ip->F_sz_um;
  double W_write_n2    =  100 * g_ip->F_sz_um;

  double write_driver_area = 0;
  // The delay and Energy of the first inverter
  rd = tr_R_on(W_invwrite_n1, NCH, 1, is_dram);

  C_ld =  drain_C_inv(W_invwrite_n1 , W_invwrite_p1 , is_dram) + gate_C_inv(W_invwrite_p2 ,W_invwrite_n2, is_dram) 
  + drain_C_(W_write_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram) ;
    
  tf = rd * C_ld;
  this_delay = horowitz(inrisetime, tf, 0.5, 0.5, RISE);
  delay_write_driver += this_delay;
  inrisetime = this_delay/(1.0 - 0.5);
  power_write_driver.computeOp.dynamic += C_ld * 0.5 * g_tp.peri_global.Vdd * g_tp.peri_global.Vdd;
  power_write_driver.readOp.leakage += cmos_Ileak(W_invwrite_p1, W_invwrite_n1, is_dram) * 0.5 * g_tp.peri_global.Vdd;
  power_write_driver.computeOp.leakage += cmos_Ileak(W_invwrite_p1, W_invwrite_n1, is_dram) * 0.5 * g_tp.peri_global.Vdd;
  write_driver_area += compute_gate_area(INV, 1, W_invwrite_p1, W_invwrite_n1,  g_tp.cell_h_def);

  // delay of signal through pass-transistor connected to the bitline bar.
  rd = tr_R_on(W_write_n1, NCH, 1, is_dram);
  C_ld = drain_C_(W_write_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram) ;
  tf = rd * C_ld;
  this_delay = horowitz(inrisetime, tf, 0.5, 0.5, RISE);
  delay_write_driver += this_delay;
  inrisetime = this_delay/(1.0 - 0.5);
  power_write_driver.computeOp.dynamic += C_ld * 0.5 * g_tp.peri_global.Vdd * g_tp.peri_global.Vdd;
  power_write_driver.readOp.leakage += 0;  // for now, let leakage of the pass transistor be 0
  power_write_driver.computeOp.leakage += 0;  // for now, let leakage of the pass transistor be 0 alok
  write_driver_area += compute_gate_area(INV, 1, 0, W_invwrite_n1,  g_tp.cell_h_def);
  // delay of signal through 2nd Inverter
  rd = tr_R_on(W_invwrite_n2, NCH, 1, is_dram);

  C_ld =  drain_C_inv(W_invwrite_n2 , W_invwrite_p2 , is_dram) + drain_C_(W_write_n1, NCH, 1, 1, g_tp.cell_h_def, is_dram) ;
    
  tf = rd * C_ld;
  this_delay = horowitz(inrisetime, tf, 0.5, 0.5, RISE);
  delay_write_driver += this_delay;
  inrisetime = this_delay/(1.0 - 0.5);
  power_write_driver.computeOp.dynamic += C_ld * 0.5 * g_tp.peri_global.Vdd * g_tp.peri_global.Vdd;
  power_write_driver.readOp.leakage += cmos_Ileak(W_invwrite_p2, W_invwrite_n2, is_dram) * 0.5 * g_tp.peri_global.Vdd;
  power_write_driver.computeOp.leakage += cmos_Ileak(W_invwrite_p2, W_invwrite_n2, is_dram) * 0.5 * g_tp.peri_global.Vdd;
  write_driver_area += compute_gate_area(INV, 1, W_invwrite_p2, W_invwrite_n2,  g_tp.cell_h_def);


  // delay of signal through pass-transistor connected to the bitline.
  rd = tr_R_on(W_write_n2, NCH, 1, is_dram);
  C_ld = drain_C_(W_write_n2, NCH, 1, 1, g_tp.cell_h_def, is_dram) ;
  tf = rd * C_ld;
  this_delay = horowitz(inrisetime, tf, 0.5, 0.5, RISE);
  delay_write_driver += this_delay;
  inrisetime = this_delay/(1.0 - 0.5);
  power_write_driver.computeOp.dynamic += C_ld * 0.5 * g_tp.peri_global.Vdd * g_tp.peri_global.Vdd;
  power_write_driver.readOp.leakage += 0;  // for now, let leakage of the pass transistor be 0
  power_write_driver.computeOp.leakage += 0;  // for now, let leakage of the pass transistor be 0 alok
  write_driver_area += compute_gate_area(INV, 1,0, W_invwrite_n2,  g_tp.cell_h_def);


  return inrisetime;
}