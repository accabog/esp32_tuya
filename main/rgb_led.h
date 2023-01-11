/*
 * rgb_led.h
 *
 *  Created on: Jan 11, 2023
 *      Author: alexandru.bogdan
 */

#ifndef MAIN_RGB_LED_H_
#define MAIN_RGB_LED_H_

typedef enum
{
	eRgbLed_state_init,
	eRgbLed_state_wifiConnected,
	eRgbLed_state_mqttActivation,
	eRgbLed_state_allOn,
	eRgbLed_state_allOff,
}eRgbLed_state_t;

void rgb_led_init(void);
void rgb_led_setState(eRgbLed_state_t state);


#endif /* MAIN_RGB_LED_H_ */
