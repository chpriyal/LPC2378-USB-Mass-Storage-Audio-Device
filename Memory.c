/*-----------------------------------------------------------------------------
 *      RL-ARM - USB
 *-----------------------------------------------------------------------------
 *      Name:    Memory.c
 *      Purpose: USB Memory Storage Demo
 *      Rev.:    V4.70
 *-----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC23xx.H>                    /* LPC23xx definitions                */
#include <stdint.h>
#include <RTL.h>
#include <File_Config.h>
#include <rl_usb.h>
#include <stdio.h>

#include "Memory.h"
#include "LCD.h"
#include "LED.h"


#define INT0      1

#define SEL_TERM  0
#define SEL_PC    1

OS_TID stask;                        /* Terminal task ID                   */

FAT_VI *mc0;                            /* FAT Media Control Block            */
Media_INFO info;                        /* Media information                  */ 

U64 user_stack[800/4];                  




/*-----------------------------------------------------------------------------
  Setup LCD and print out example title
 *----------------------------------------------------------------------------*/
static void LCD_Setup (void) {
  lcd_init ();
  lcd_clear();

  lcd_print ("    Song Name   ");
  set_cursor (0, 1);
  lcd_print ("Current:");  
}



/*-----------------------------------------------------------------------------
  Interface selection task
 *----------------------------------------------------------------------------*/
__task void setrun (void) {
	int32_t usb_rx_ch = -1;
	uint8_t x = 0;
	char str[1];

      mc0 = ioc_getcb (NULL);
      if (ioc_init (mc0) == 0) {
        ioc_read_info (&info, mc0);
        usbd_msc_init ();               /* Init USB MSC Global Variables      */
        usbd_connect(__TRUE);           /* USB Device Connect                 */
        set_cursor (9, 1);
        lcd_print ("PC     ");
      }
      else {
        set_cursor (9, 1);
        lcd_print ("Mem err");
      }
			set_cursor(0,0);
			lcd_print("               ");
			while (!usbd_configured ());          /* Wait for device to configure       */

  while (1) {                           /* Loop forever                       */
                                      
    if (usb_rx_ch == -1) {
      usb_rx_ch = USBD_CDC_ACM_GetChar ();
    }
    if (usb_rx_ch != -1) {
    		if (x == 0){
    			lcd_print("                ");
    		}
			set_cursor(x,0);
			sprintf(str,"%c",usb_rx_ch);
			lcd_print(str);
			if (++x > 15 || str == '\n'){
				x = 0;
			}
      usb_rx_ch = -1;
    }
       
}
}


/*-----------------------------------------------------------------------------
  Init peripheral and create application tasks
 *----------------------------------------------------------------------------*/
__task void init (void) {

  LCD_Setup  ();                        /* Init and setup LCD                 */
  usbd_init  ();                        /* Init USB Device                    */
  

  os_tsk_prio_self (10);
  
  stask = os_tsk_create_user (setrun, 1, &user_stack, sizeof (user_stack));
  os_tsk_delete_self ();  
}


/*-----------------------------------------------------------------------------
  Main Entry
 *----------------------------------------------------------------------------*/
int main (void) {
  os_sys_init (init);                   /* Init RTX and start application     */
}

/*-----------------------------------------------------------------------------
 * End of file
 *----------------------------------------------------------------------------*/
