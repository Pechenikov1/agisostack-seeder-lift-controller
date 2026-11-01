#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

// --- Дефиниция на пиновете ---
#define PIN_MOSFET_LIFT     11  // MOSFET 1 (Вдигане)
#define PIN_MOSFET_LOWER    12  // MOSFET 2 (Спускане)
#define PIN_MOSFET_FOLD     13  // MOSFET 3 (Прибиране крила)
#define PIN_MOSFET_UNFOLD   14  // MOSFET 4 (Разгъване крила)

#define PIN_BTN_LIFT        4   // Бутон за вдигане
#define PIN_BTN_LOWER       5   // Бутон за спускане
#define PIN_BTN_FOLD        6   // Бутон за прибиране
#define PIN_BTN_UNFOLD      7   // Бутон за разгъване

#define PIN_SENSOR_BIN      8   // Сензор за бункер
#define PIN_LIMIT_UP        9   // Краен изключвач "Вдигнато"
#define PIN_LIMIT_DOWN      10  // Краен изключвач "Спуснато"

// Променливи за таймера
uint64_t lift_start_time = 0;
bool is_lifting = false;
const uint64_t MAX_LIFT_TIME_MS = 5000; // Максимум 5 секунди

// Помощна функция за конфигуриране на изход
void setup_output(gpio_num_t pin) {
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    gpio_set_level(pin, 0); // Започваме изключени
}

// Помощна функция за конфигуриране на вход с pull-up (за бутони и изключвачи)
void setup_input(gpio_num_t pin) {
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE; // Активираме вътрешен pull-up
    gpio_config(&io_conf);
}

extern "C" void app_main(void) {
    printf("Стартиране на хардуерния тест...\n");

    // 1. Конфигуриране на пиновете
    setup_output((gpio_num_t)PIN_MOSFET_LIFT);
    setup_output((gpio_num_t)PIN_MOSFET_LOWER);
    setup_output((gpio_num_t)PIN_MOSFET_FOLD);
    setup_output((gpio_num_t)PIN_MOSFET_UNFOLD);

    // Бутоните и изключвачите са с pull-up, така че неактивно състояние е HIGH (1), активно е LOW (0)
    setup_input((gpio_num_t)PIN_BTN_LIFT);
    setup_input((gpio_num_t)PIN_BTN_LOWER);
    setup_input((gpio_num_t)PIN_BTN_FOLD);
    setup_input((gpio_num_t)PIN_BTN_UNFOLD);
    setup_input((gpio_num_t)PIN_SENSOR_BIN);
    setup_input((gpio_num_t)PIN_LIMIT_UP);
    setup_input((gpio_num_t)PIN_LIMIT_DOWN);

    while (true) {
        // --- Четене на входове ---
        bool btn_lift_pressed = (gpio_get_level((gpio_num_t)PIN_BTN_LIFT) == 0);
        bool limit_up_triggered = (gpio_get_level((gpio_num_t)PIN_LIMIT_UP) == 0);

        // --- ЛОГИКА ЗА ВДИГАНЕ ---
        // Ако бутонът е натиснат И още не сме започнали да вдигаме И не сме на краен изключвач
        if (btn_lift_pressed && !is_lifting && !limit_up_triggered) {
            printf("Започва вдигане...\n");
            gpio_set_level((gpio_num_t)PIN_MOSFET_LIFT, 1); // Отваряме MOSFET-а
            is_lifting = true;
            lift_start_time = esp_timer_get_time() / 1000; // Записваме време в милисекунди
        }

        // Ако сме в процес на вдигане, проверяваме условията за спиране
        if (is_lifting) {
            uint64_t current_time = esp_timer_get_time() / 1000;
            uint64_t elapsed = current_time - lift_start_time;

            // Логика "ИЛИ": Спираме, ако изключвачът е задействан ИЛИ таймерът е изтекъл
            if (limit_up_triggered || elapsed >= MAX_LIFT_TIME_MS) {
                gpio_set_level((gpio_num_t)PIN_MOSFET_LIFT, 0); // Затваряме MOSFET-а
                is_lifting = false;

                if (elapsed >= MAX_LIFT_TIME_MS && !limit_up_triggered) {
                    printf("ВНИМАНИЕ: Таймерът изтече, но изключвачът не е отчетен!\n");
                } else {
                    printf("Вдигането завърши успешно.\n");
                }
            }
        }

        // Тук по-късно ще добавим логиката за спускане и крилата...

        // Малка пауза, за да не товарим процесора на 100%
        vTaskDelay(pdMS_TO_TICKS(10)); 
    }
}
