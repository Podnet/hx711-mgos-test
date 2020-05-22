#include "mgos.h"
#include "mgos_hx711.h"


void read_values(){
  float value = mgos_hx711_get_data();
  LOG(LL_INFO, ("TCU: Load cell value : %.2f", value));
}

enum mgos_app_init_result mgos_app_init(void) {
  LOG(LL_INFO, ("TCU: Fetching Loadcell readings"));
  // mgos_hx711_create(10,13);
  // mgos_hx711_begin();
  mgos_hx711_set_cal_factor(2230); // Need to be calculated as per our load cell
  mgos_hx711_tare(); // Reset the tare to zero
  read_values();
  return MGOS_APP_INIT_SUCCESS;

}
