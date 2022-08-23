#include <Arduino.h>

/*
 *  Project 01-blink_proj_02
 *      IntroCom - Austral - 2022 - EAM
 * 
 *      Austral 2022 - IntroCom - EAM
 * 
 *      Traffic light project
 *      Manages an intersection NS and EW; both traffic lights are
 *      complementary, i.e., when one is read the other is green and viceversa
 *      Also, there are two tact switches that simulates cars waiting in each
 *      one of the intersections, named "PUSH_NS" and "PUSH_EW"
 *      As a first intent, only sequences traffic light with "ON_TIME" for
 *      red and green and "Y_TIME" for yellow; also, only shows in serial monitor
 *      tact switch states
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
read_switches(void)
{
    Serial.printf("NS = %d, EW = %d\n\r",
        digitalRead(PUSH_NS), digitalRead(PUSH_EW) );
}

static void
set_light( int x )
{
    digitalWrite( traffic_lights[x].light, HIGH );
    delay( traffic_lights[x].ms );
}

static void
clr_light( int x )
{
    read_switches();
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
