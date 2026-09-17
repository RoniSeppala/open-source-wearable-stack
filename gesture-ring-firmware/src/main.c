#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    while (1) {
        printk("Smart ring is alive!\n");
        k_sleep(K_SECONDS(1));
    }

    return 0;
}