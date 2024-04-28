#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

// KEY_CTRL = 0x01,
// KEY_SHIFT = 0x02,
// KEY_ALT = 0x04,
// KEY_LOGO = 0x08,
// KEY_RCTRL = 0x10,
// KEY_RSHIFT = 0x20,
// KEY_RALT = 0x40,
// KEY_RLOGO = 0x80,

//  KEY_NEXT_TRACK,     /*!< next Track Button */
// KEY_PREVIOUS_TRACK, /*!< Previous track Button */
// KEY_STOP,           /*!< Stop Button */
// KEY_PLAY_PAUSE,     /*!< Play/Pause Button */
// KEY_MUTE,           /*!< Mute Button */
// KEY_VOLUME_UP,      /*!< Volume Up Button */
// KEY_VOLUME_DOWN,    /*!< Volume Down Button */

// KEY_F1 = 128,   /* F1 key */
//   KEY_F2,         /* F2 key */
//   KEY_F3,         /* F3 key */
//   KEY_F4,         /* F4 key */
//   KEY_F5,         /* F5 key */
//   KEY_F6,         /* F6 key */
//   KEY_F7,         /* F7 key */
//   KEY_F8,         /* F8 key */
//   KEY_F9,         /* F9 key */
//   KEY_F10,        /* F10 key */
//   KEY_F11,        /* F11 key */
//   KEY_F12,        /* F12 key */
//   KEY_F13,        /* F13 key */
//   KEY_F14,        /* F14 key */
//   KEY_F15,        /* F15 key */
//   KEY_F16,        /* F16 key */
//   KEY_F17,        /* F17 key */
//   KEY_F18,        /* F18 key */
//   KEY_F19,        /* F19 key */
//   KEY_F20,        /* F20 key */
//   KEY_F21,        /* F21 key */
//   KEY_F22,        /* F22 key */
//   KEY_F23,        /* F23 key */
//   KEY_F24,        /* F24 key */

//   KEY_PRINT_SCREEN,   /* Print Screen key */
//   KEY_SCROLL_LOCK,    /* Scroll lock */
//   KEY_CAPS_LOCK,      /* caps lock */
//   KEY_NUM_LOCK,       /* num lock */
//   KEY_INSERT,         /* Insert key */
//   KEY_HOME,           /* Home key */
//   KEY_PAGE_UP,        /* Page Up key */
//   KEY_PAGE_DOWN,      /* Page Down key */

//   RIGHT_ARROW,        /* Right arrow */
//   LEFT_ARROW,         /* Left arrow */
//   DOWN_ARROW,         /* Down arrow */
//   UP_ARROW,           /* Up arrow */

USBKeyboard Keyboard;

struct customKey
{
    uint8_t pinId;
    uint8_t key;
    bool isPressed;
    uint32_t nextEvent;
};

customKey keyList[] = {{.pinId = 0, .key = 'a', .isPressed = false, .nextEvent = 0},
                       {.pinId = 1, .key = 'b', .isPressed = false, .nextEvent = 0},
                       {.pinId = 2, .key = 'c', .isPressed = false, .nextEvent = 0},
                       {.pinId = 6, .key = '9', .isPressed = false, .nextEvent = 0},
                       {.pinId = 3, .key = 'd', .isPressed = false, .nextEvent = 0}};

#define KEY_LIST_SIZE (sizeof(keyList) / sizeof(customKey))

#define PRESSED LOW
#define RELEASED HIGH
#define APP_KEYBOARD
#define FILTER_MS 20

void setup()
{
    pinMode(10, OUTPUT);
    delay(1000);
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW);

    delay(2000);
    printf("init\n");
    // put your setup code here, to run once:
#ifdef APP_KEYBOARD
    for (uint8_t idx = 0; idx < KEY_LIST_SIZE; idx++)
    {
        pinMode(keyList[idx].pinId, INPUT);
    }
#endif

    delay(2000);
    printf("Ready\n");
    // Keyboard.printf("Test OK\r\n");
    //  Keyboard.key_code(RIGHT_ARROW, KEY_SHIFT | KEY_ALT);
}

void loop()
{
#ifdef APP_KEYBOARD
    for (uint8_t idx = 0; idx < KEY_LIST_SIZE; idx++)
    {
        if (millis() > keyList[idx].nextEvent)
        {
            if (!keyList[idx].isPressed)
            {
                if (digitalRead(keyList[idx].pinId) == PRESSED)
                {
                    keyList[idx].nextEvent = millis() + FILTER_MS;
                    printf("%d:%c pressed!\n", digitalRead(keyList[idx].pinId), digitalRead(keyList[idx].key));
                    // Keyboard.key_code(RIGHT_ARROW, KEY_SHIFT | KEY_ALT);
                    Keyboard.key_code(keyList[idx].key);
                    // Keyboard.printf("%c", keyList[idx].key);

                    keyList[idx].isPressed = true;
                    digitalWrite(10, HIGH);
                }
            }
            else
            {
                if (digitalRead(keyList[idx].pinId) == RELEASED)
                {
                    keyList[idx].isPressed = false;
                    digitalWrite(10, LOW);
                }
            }
        }
    }
#endif
}
