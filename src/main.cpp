#include <Arduino.h>

/*
 *  Project 01-blink_proj_02
 *      IntroCom - Austral - 2022 - EAM
 * 
 *      Each "sample' time, reads both pushbuttons as an integer number named "num"
 *      After reading, prints num in serial monitor and blinks LED num+1 number of periods of "pulse" time on and off
 *      Tact switch connected to +VDD so must engage pulldown resistor, subsequents reads gives a HIGH for a push botton closed
 *      Austral 2022 - IntroCom - EAM
 */

#define SizeOf(x)   (sizeof(x)/sizeof(*x))

#define ON_TIME 5000
#define TRANS_TIME 1000

#define NUM_LIGHTS  3

typedef struct
{
    int light;
    int ms;
} tlight_t;

static tlight_t traffic_lights[NUM_LIGHTS] =
{
    { NS_RED, ON_TIME },
    { NS_YELLOW, Y_TIME },
    { NS_GREEN, ON_TIME }
};

static void
set_light( int x )
{
    digitalWrite( traffic_lights[x].light, HIGH );
    delay( traffic_lights[x].ms );
}

static void
clr_light( int x )
{
    digitalWrite( traffic_lights[x].light, LOW );
}

void
setup(void)
{
    int i;

    for( i = 0; i < NUM_LIGHTS; ++i )
    {
        pinMode( traffic_lights[i].light, OUTPUT );
        digitalWrite( traffic_lights[i].light, LOW );
    }
    pinMode( PUSH_NS, INPUT_PULLUP );
    pinMode( PUSH_EW, INPUT_PULLUP );
    Serial.begin(BAUD);

    set_light(0);
}

void
loop(void)
{
    int i;

    for( i = 1; i < NUM_LIGHTS; ++i )
    {
        clr_light(i-1);
        set_light(i);
    }


    for( i-=2 ; i >= 0; --i )
    {
        clr_light(i+1);
        set_light(i);
    }
}
