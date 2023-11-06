#include "button.h"

#define GPIO_READ_PIN(port) gpio_get_level(port)

int debounceButtonBuffer2[NUM_OF_BTN];
int debounceButtonBuffer1[NUM_OF_BTN];
int buttonBuffer[NUM_OF_BTN];
int lastStateButton[NUM_OF_BTN];
int flagForButtonPress[NUM_OF_BTN];
int flagForButtonPress1s[NUM_OF_BTN];
int counterForButtonPress1s[NUM_OF_BTN];

#ifdef USE_DOUBLE_CLICK
int click_count[NUM_OF_BTN];
int increased_click_count[NUM_OF_BTN];
int time_out_btn_click[NUM_OF_BTN];
int flagForDoubleClicked[NUM_OF_BTN];
#endif

uint8_t BTN_GPIO_Port[NUM_OF_BTN];

void BTN_INIT(gpio_num_t port, uint8_t idx)
{
    BTN_GPIO_Port[idx] = port;
    debounceButtonBuffer1[idx] = NORMAL_STATE;
    debounceButtonBuffer2[idx] = NORMAL_STATE;
    buttonBuffer[idx] = NORMAL_STATE;
    lastStateButton[idx] = NORMAL_STATE;
    flagForButtonPress1s[idx] = 0;

    counterForButtonPress1s[idx] = 1000;
#ifdef USE_DOUBLE_CLICK
    flagForDoubleClicked[idx] = 0;
    click_count[idx] = 0;
    increased_click_count[idx] = 0;
    time_out_btn_click[idx] = DOUBLE_CLICK_INTERVAL;
    flagForDoubleClicked[idx] = 0;
#endif
}

void button_reading(int idx)
{
    debounceButtonBuffer2[idx] = debounceButtonBuffer1[idx];
    debounceButtonBuffer1[idx] = GPIO_READ_PIN(BTN_GPIO_Port[idx]);
    if (debounceButtonBuffer1[idx] == debounceButtonBuffer2[idx])
        buttonBuffer[idx] = debounceButtonBuffer1[idx];

    if (buttonBuffer[idx] == PRESSED_STATE)
    {
        if (lastStateButton[idx] != buttonBuffer[idx])
        {
            flagForButtonPress[idx] = 1;
        }
        lastStateButton[idx] = buttonBuffer[idx];
        // if a button is pressed, we start counting
        if (counterForButtonPress1s[idx] > 0)
        {
            counterForButtonPress1s[idx] = counterForButtonPress1s[idx] - TIMER_CYCLE;
        }
        else
        {
            // the flag is turned on when 1 second has passed
            // since the button is pressed.
            flagForButtonPress1s[idx] = 1;
        }

#ifdef USE_DOUBLE_CLICK
        if (increased_click_count[idx] == 0)
        {
            click_count[idx]++;
            increased_click_count[idx] = 1;
        }
        time_out_btn_click[idx] = DOUBLE_CLICK_INTERVAL;
        if (click_count[idx] == 2)
        {
            flagForDoubleClicked[idx] = 1;
            click_count[idx] = 0;
        }
#endif
    }
    else if (buttonBuffer[idx] == NORMAL_STATE)
    {
        /* BUTTON PRESSED START */
        lastStateButton[idx] = buttonBuffer[idx];
        counterForButtonPress1s[idx] = 1000;
        flagForButtonPress[idx] = 0;
        flagForButtonPress1s[idx] = 0;

        /* BUTTON PRESSED END */

#ifdef USE_DOUBLE_CLICK
        increased_click_count[idx] = 0;
        flagForDoubleClicked[idx] = 0;
        if (click_count[idx] == 1)
        {
            if (time_out_btn_click[idx] > 0)
                time_out_btn_click[idx] = time_out_btn_click[idx] - TIMER_CYCLE;
            if (time_out_btn_click[idx] <= 0)
            { // TIME OUT FOR DOUBLE CLICK
                click_count[idx] = 0;
            }
        }
#endif
    }
}

int button_pressed(int idx)
{
    return flagForButtonPress[idx];
}

void reset_button_flag(int idx)
{
    flagForButtonPress[idx] = 0;
}

int button_pressed_1s(int idx)
{
    return (flagForButtonPress1s[idx] == 1);
}

#ifdef USE_DOUBLE_CLICK
int button_doubleClicked(int idx)
{
    return flagForDoubleClicked[idx] == 1;
}
#endif