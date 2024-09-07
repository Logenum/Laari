/*   hw.h     28.08.94 */
int  getflags(void);            /* get flags (interrupt state) */
int  GetFlagsDisable(void);	/* get flags (interrupt state) and disable interrupts */
void setflags(int flags);       /* set flags (interrupt state) */
void disable(void);		/* disable interrupts */
void enable(void);		/* enable interrupts */

#ifdef BIT_32
  #define LEDS
#endif

#ifdef LEDS
  #define LED_ON (_outb(0x400,0x941))
  #define LED_OFF (_outb(0x400,0x940))
#else
  #define LED_ON
  #define LED_OFF
#endif
