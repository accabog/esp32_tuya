#include "rgb_led.h"

#include "driver/gpio.h"

void rgb_led_init(void)
{
    gpio_set_direction(GPIO_NUM_0, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);

    rgb_led_setState(eRgbLed_state_init);
}

void rgb_led_setState(eRgbLed_state_t state)
{
	switch(state)
	{
	case eRgbLed_state_init:
	    gpio_set_level(GPIO_NUM_0, 1);
	    gpio_set_level(GPIO_NUM_2, 0);
	    gpio_set_level(GPIO_NUM_4, 0);
		break;
	case eRgbLed_state_wifiConnected:
	    gpio_set_level(GPIO_NUM_0, 0);
	    gpio_set_level(GPIO_NUM_2, 1);
	    gpio_set_level(GPIO_NUM_4, 0);
		break;
	case eRgbLed_state_mqttActivation:
	    gpio_set_level(GPIO_NUM_0, 0);
	    gpio_set_level(GPIO_NUM_2, 0);
	    gpio_set_level(GPIO_NUM_4, 1);
		break;
	case eRgbLed_state_allOn:
	    gpio_set_level(GPIO_NUM_0, 1);
	    gpio_set_level(GPIO_NUM_2, 1);
	    gpio_set_level(GPIO_NUM_4, 1);
		break;
	case eRgbLed_state_allOff:
	    gpio_set_level(GPIO_NUM_0, 0);
	    gpio_set_level(GPIO_NUM_2, 0);
	    gpio_set_level(GPIO_NUM_4, 0);
		break;
	default:
		break;
	}
}
