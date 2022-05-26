/*RGB_MATRIX_EFFECT(test_effect_1)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t invert = 0x00;
static uint8_t can_invert = 0x00;
static void test_effect_1_init(effect_params_t *params) {
    invert = 0x00;
    can_invert = 0x00;
}

struct led_color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

static const struct led_color yellow = {.red=0xFF, .green=0xFF, .blue=0x00};
static const struct led_color black = {.red=0x00, .green=0x00, .blue=0x00};
static const struct led_color red = {.red=0xFF, .green=0x00, .blue=0x00};

static struct led_color text_colors[] = {
    yellow, yellow, yellow, black, yellow,  black, yellow, black, yellow,  black, yellow, yellow, yellow, yellow,
    yellow,  black,  black, yellow, black,  yellow, black, yellow, yellow, yellow, black, yellow,  black,  black,
    yellow,  black,  black, yellow, black,  yellow, black, yellow, yellow, yellow, black, yellow,  black,
    yellow, yellow, black, yellow, yellow, black, yellow, black, yellow,  black, black, black,
    red,  red,  red,  red,  red, red, red,  red,
};

static struct led_color text_colors_inverted[] = {
    black, black, black, yellow, black,  yellow, black, yellow, black,  yellow, black, black, black, black,
    black,  yellow,  yellow, black, yellow,  black, yellow, black, black, black, yellow, black,  yellow,  yellow,
    black,  yellow,  yellow, black, yellow,  black, yellow, black, black, black, yellow, black,  yellow,
    black, black, yellow, black, black, yellow, black, yellow, black,  yellow, yellow, yellow,
    red,  red,  red,  red,  red, red, red,  red,
};

static bool test_effect_1_run(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
    for(uint8_t i = led_min; i < led_max; i++) {
        if(invert) {
            rgb_matrix_set_color(i, text_colors_inverted[i].red, text_colors_inverted[i].green, text_colors_inverted[i].blue);
        } else {
            rgb_matrix_set_color(i, text_colors[i].red, text_colors[i].green, text_colors[i].blue);
        }
    }
    if(time > 200 && can_invert) {
        invert = (invert + 1) % 2;
        can_invert = 0;
    }
    if(time < 100) {
        can_invert = 1;
    }

    return rgb_matrix_check_finished_leds(led_max);
}

static bool test_effect_1(effect_params_t *params) {
    if(params->init) {
        test_effect_1_init(params);
    }
    return test_effect_1_run(params);
}

#endif*/
RGB_MATRIX_EFFECT(white_solid)
RGB_MATRIX_EFFECT(white_startup)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

struct led_color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

uint8_t toggleBacklight(void);
uint8_t changeAnimation(void);
void fancyAnim(void);

static const struct led_color white = {.red=0xFF, .green=0xFF, .blue=0xFF};

static bool white_solid(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for(uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, white.red, white.green, white.blue);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

//----------------------------

static uint8_t startup_column = 0x00;
static uint8_t frame = 0x00;
static uint8_t boot = 0x00;
static uint8_t columns[14][7] = {
    {0,14,28,41,53,54,0xFF},
    {1,15,29,42,55,0xFF,0xFF},
    {2,16,30,43,0xFF,0xFF,0xFF},
    {3,17,31,44,0xFF,0xFF,0xFF},
    {4,18,32,45,0xFF,0xFF,0xFF},
    {5,19,33,46,56,0xFF,0xFF},
    {6,20,34,47,0xFF,0xFF,0xFF},
    {7,21,35,48,0xFF,0xFF,0xFF},
    {8,22,36,49,0xFF,0xFF,0xFF},
    {9,23,37,50,57,0xFF,0xFF},
    {10,24,38,51,58,0xFF,0xFF},
    {11,25,39,59,0xFF,0xFF,0xFF},
    {12,26,40,52,60,0xFF,0xFF},
    {13,27,0xFF,0xFF,0xFF,0xFF,0xFF},
};

static bool white_startup_run(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for(uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
    }
    uint8_t j = 0;
    while(columns[startup_column][j] != 0xFF) {
        rgb_matrix_set_color(columns[startup_column][j], 0xFF, 0xFF, 0xFF);
        j++;
    }
    frame++;
    if(frame % 10 == 0) {
        startup_column++;
    }
    if(startup_column == 14) {
        startup_column = 0;
        fancyAnim();
        toggleBacklight();
//        keyrecord_t record = {.event.pressed = 1, .event.key.row = 0, .event.key.col = 10};
//        process_record_kb(15, &record);
/*        led_enabled = 0;
        ap2_led_disable();*/
    }

    return rgb_matrix_check_finished_leds(led_max);
}

static bool white_startup(effect_params_t *params) {
    if(params->init && params->iter == 0) {
        if(boot) {
            changeAnimation();
            return true;
        }
        startup_column = 0;
        boot++;
    }
    return white_startup_run(params);
}

#endif