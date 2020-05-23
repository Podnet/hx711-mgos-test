#include "mgos_hx711.h"

#include "mgos.h"
struct HX711_ADC *hx;

void read_values(void *arg)
{
    float value = mgos_hx711_get_data(hx);
    LOG(LL_INFO, ("TCU: Load cell value : %.2f", value));
}

void read_values2(void *arg)
{

    if (mgos_hx711_update(hx))
    {
        float reading = mgos_hx711_get_data(hx);
        LOG(LL_INFO, ("TCU: Load cell: Reading %.2f", reading));
    }

    else
    {
        LOG(LL_INFO, ("TCU: Load cell: mgos_hx711_update function returned false."));
    }
}

extern "C"
{
    enum mgos_app_init_result mgos_app_init(void)
    {
        LOG(LL_INFO, ("TCU: Fetching Loadcell readings"));
        hx = mgos_hx711_create(15, 13);
        mgos_hx711_set_gain(hx, 128);
        mgos_hx711_begin(hx);
        mgos_hx711_set_cal_factor(hx, 12201); // Need to be calculated as per our load cell
        mgos_hx711_tare(hx);                  // Reset the tare to zero

        mgos_set_timer(3000, MGOS_TIMER_REPEAT, read_values2, NULL);

        return MGOS_APP_INIT_SUCCESS;
    }
}