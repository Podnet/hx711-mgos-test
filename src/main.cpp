#include "mgos_hx711.h"

#include "mgos.h"
struct HX711_ADC *hx;



void read_values(){
  float value = mgos_hx711_get_data(hx);
  LOG(LL_INFO, ("TCU: Load cell value : %.2f", value));
}
extern "C"{
enum mgos_app_init_result mgos_app_init(void) {
  LOG(LL_INFO, ("TCU: Fetching Loadcell readings"));
  hx = mgos_hx711_create(10,13);
  mgos_hx711_set_gain(hx, 128);
  mgos_hx711_begin(hx);
  mgos_hx711_set_cal_factor(hx, 12546); // Need to be calculated as per our load cell
  mgos_hx711_tare(hx); // Reset the tare to zero
  read_values();
  return MGOS_APP_INIT_SUCCESS;

}

}