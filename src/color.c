/**
 * @file        color.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Finds the correct color code for an amount in summary output.
 *          Printing amounts in color to the terminal window
 *          makes the output prettier than otherwise. Negative amounts
 *          are printed in one color, positive amounts in another,
 *          and zeroes in a third color. Colors are defined in the
 *          Printing_Macros module.
 */
color_t color(double d, int usecolor){ 
  if(!usecolor)
    return "";
  
  if(d > EPS)
    return POSITIVE_COLOR;
  else if(d < -EPS)
    return NEGATIVE_COLOR;
  else 
    return ZERO_COLOR;
}
