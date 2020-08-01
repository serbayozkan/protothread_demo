#include <stdio.h>

#include "pt.h"

static struct pt led_on_pt, led_off_pt;

typedef enum
{
	SIGNAL_NONE,
	SIGNAL_TIMEOUT
}signal_t;

typedef struct
{
	signal_t sig;
}event_t;

PT_THREAD(led_on_thread(struct pt *pt, event_t *ev))
{
	PT_BEGIN(pt);

	PT_WAIT_UNTIL(pt, ev->sig == SIGNAL_TIMEOUT);
	printf("LED IS ON...\n");

	PT_END(pt);
}

PT_THREAD(led_off_thread(struct pt *pt, event_t *ev))
{
	PT_BEGIN(pt);

	PT_WAIT_UNTIL(pt, ev->sig == SIGNAL_TIMEOUT);
	printf("LED IS OFF...\n");

	PT_END(pt);
}

event_t ev;

int main(void)
{
	PT_INIT(&led_on_pt);
	PT_INIT(&led_off_pt);

	while(1)
	{
		ev.sig = SIGNAL_TIMEOUT;

		led_on_thread(&led_on_pt, &ev);
		led_off_thread(&led_off_pt, &ev);

		return 0;
	}
}
