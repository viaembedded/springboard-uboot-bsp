/*++ 
 * linux/drivers/video/wmt/lcd.h
 * WonderMedia video post processor (VPP) driver
 *
 * Copyright c 2012  WonderMedia  Technologies, Inc.
 *
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 2 of the License, or 
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * WonderMedia Technologies, Inc.
 * 4F, 533, Chung-Cheng Road, Hsin-Tien, Taipei 231, R.O.C
--*/

#ifndef LCD_H
/* To assert that only one occurrence is included */
#define LCD_H
/*-------------------- MODULE DEPENDENCY -------------------------------------*/
#include "vpp.h"

/*	following is the C++ header	*/
#ifdef	__cplusplus
extern	"C" {
#endif

/*-------------------- EXPORTED PRIVATE CONSTANTS ----------------------------*/
/* #define  LCD_XXXX  1    *//*Example*/

/*-------------------- EXPORTED PRIVATE TYPES---------------------------------*/
/* typedef  void  lcd_xxx_t;  *//*Example*/
typedef enum {
	LCD_LVDS,
	LCD_TTL,
	LCD_OEM,
	LCD_PANEL_MAX
} lcd_panel_t;

#define LCD_CAP_CLK_HI		BIT(0)
#define LCD_CAP_HSYNC_HI	BIT(1)
#define LCD_CAP_VSYNC_HI	BIT(2)
#define LCD_CAP_DE_LO		BIT(3)
typedef struct {
	char *name;
	int fps;
	int bits_per_pixel;
	unsigned int capability;

	vpp_timing_t timing;

	void (*initial)(void);
	void (*uninitial)(void);
} lcd_parm_t;

/* *************************************************
  * Add for CH7305
  * JerryWang(VIA Embedded)
  * 2013/01/15
  *****************************************************
  */
enum
{
    EN_DITHERING    	= 0x01,
    DUAL_CHANNEL    	= 0x02,
    LDI		    		= 0x04,
    OUTPUT_24	    	= 0x08,
};

typedef struct{
        unsigned char panel_mode; // single channel:0, dual channel:1
	unsigned char deskew_xcmd;
}lcd_setting_t;
static lcd_setting_t lcd_setting;

typedef struct lcd_transmitter_s{
	struct lcd_transmitter_s *next;
	char *name;
	int (*init)(void);
	void (*power_on)(void);
	void (*power_off)(void);
	int (*set_mode)(lcd_setting_t mode);
}lcd_transmitter_t;

/*-------------------- EXPORTED PRIVATE VARIABLES -----------------------------*/
#ifdef LCD_C /* allocate memory for variables only in vout.c */
#define EXTERN
#else
#define EXTERN   extern
#endif /* ifdef LCD_C */

/* EXTERN int      lcd_xxx; *//*Example*/
EXTERN lcd_parm_t *p_lcd;
EXTERN unsigned int lcd_blt_id;
EXTERN unsigned int lcd_blt_level;
EXTERN unsigned int lcd_blt_freq;

#undef EXTERN

/*--------------------- EXPORTED PRIVATE MACROS -------------------------------*/
/* #define LCD_XXX_YYY   xxxx *//*Example*/
/*--------------------- EXPORTED PRIVATE FUNCTIONS  ---------------------------*/
/* extern void  lcd_xxx(void); *//*Example*/
int lcd_transmitter_register(lcd_transmitter_t *ops);

int lcd_panel_register(int no,void (*get_parm)(int mode));
lcd_parm_t *lcd_get_parm(lcd_panel_t id,unsigned int arg);
lcd_parm_t *lcd_get_oem_parm(int resx,int resy);
lcd_parm_t *lcd_get_lvds_parm(int resx,int resy, int fps);
lcd_parm_t *lcd_get_ttl_parm(int resx,int resy, int fps);
//void lcd_set_parm(int id,int bpp);
void lcd_set_parm(int ops, int bpp, int hpixel, int vpixel, int fps);

/* LCD back light */
void lcd_blt_enable(int no,int enable);
void lcd_blt_set_level(int no,int level);
void lcd_blt_set_freq(int no, unsigned int freq);
#ifndef CFG_LOADER
void lcd_blt_set_pwm(int no,unsigned int scalar,unsigned int period,unsigned int duty);
#endif
#ifdef	__cplusplus
}
#endif	
#endif /* ifndef LCD_H */
