// capslock light (0 = esc, 50 = caps lock default)
#ifdef CAPS_LOCK_INDEX
#    undef CAPS_LOCK_INDEX
#endif
#define CAPS_LOCK_INDEX 50

// layer config
#define DYNAMIC_KEYMAP_LAYER_COUNT 7

// rgb matrix config
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define RGB_MATRIX_DEFAULT_HUE 223
#define RGB_MATRIX_DEFAULT_SAT 181
#define RGB_MATRIX_DEFAULT_VAL 102
#define RGB_MATRIX_DEFAULT_SPD 85

// wired bat level check
#define WIRED_BAT_LEVEL

// volume leds
#define VOL_LEVEL_LED_LIST \
        { 34, 35, 36, 37, 38, 39, 40, 41, 42, 43 }
