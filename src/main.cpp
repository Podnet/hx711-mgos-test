#include "mgos_hx711.h"
#include "mgos.h"
struct HX711_ADC *hx; 

/*! \mainpage Hx711 testing
 *
 * \section Documentation
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

void read_values(void *arg)
{

    if (mgos_hx711_update(hx))
    {
        float reading = mgos_hx711_get_data(hx); // Get reading from loadcell 
        LOG(LL_INFO, ("TCU: Load cell: Reading %.2f", reading));
    }

    else
    {
        LOG(LL_INFO, ("TCU: Load cell: mgos_hx711_update function returned false."));
        mgos_hx711_refresh_data_set(hx);  // Refresh the data buffered 
    }
}
/**<  Function to read values from Load cells */


extern "C"
{
    enum mgos_app_init_result mgos_app_init(void)
    {
        LOG(LL_INFO, ("TCU: Fetching Loadcell readings"));
        hx = mgos_hx711_create(15, 13); // HX711 class object  
        mgos_hx711_set_gain(hx, 128); // Set appropriate gain from loadcell readings 
        mgos_hx711_begin(hx);    // Begin conversion of loadcell to hx711 values 
        mgos_hx711_set_cal_factor(hx, 2230); // Need to be calculated as per our load cell 
        mgos_hx711_tare(hx); // Reset the values to zero again 

        mgos_set_timer(3000, MGOS_TIMER_REPEAT, read_values, NULL); // Getting loadcell values every 3000ms 

        return MGOS_APP_INIT_SUCCESS;
    }
    /**< Mongoose OS app intialization function */
}