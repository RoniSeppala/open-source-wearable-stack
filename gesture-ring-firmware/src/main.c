#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>

#define LED_NODE DT_ALIAS(led_strip)

static const struct device *const strip = DEVICE_DT_GET(LED_NODE);

int main(void)
{
    struct led_rgb pixel = {
        .r = 20,
        .g = 0,
        .b = 0,
    };

    if (!device_is_ready(strip)) {
        return 0;
    }

    while (1) {
        led_strip_update_rgb(strip, &pixel, 1);

        k_sleep(K_MSEC(500));

        pixel.r = 0;
        pixel.g = 0;
        pixel.b = 0;

        led_strip_update_rgb(strip, &pixel, 1);

        k_sleep(K_MSEC(500));

        pixel.r = 20;
    }

    return 0;
}