/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following team_t struct
 */
team_t team = {
        "CumaKitliMÇGidemiyoz",    /* Team Name */

        "e2448975",      /* First student ID */
        "Barış Türnüklü",       /* First student name */

        "e2448850",             /* Second student ID */
        "Cem Meriç Şefikoğulları",           /* Second student name */

        "",             /* Third student ID */
        ""            /* Third student Name */
};


/********************
 * CONVOLUTION KERNEL
 ********************/

/***************************************************************
 * Your different versions of the convolution functions  go here
 ***************************************************************/

/*
 * naive_conv - The naive baseline version of convolution
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";




 ///ORIGINAL
 
void naive_conv(int dim, pixel *src, pixel *ker, unsigned *dst) {
    int i,j,k,l;

    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            dst[RIDX(i, j, dim)] = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].red * ker[RIDX(k, l, 8)].red;
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].green * ker[RIDX(k, l, 8)].green;
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].blue * ker[RIDX(k, l, 8)].blue;
                }

        }
}




//2.6
/*
void naive_conv(int dim, pixel *src, pixel *ker, unsigned *dst) {
    int i,j,ridx,size=dim-7;int temp_blue,temp_green,temp_red;
    


    pixel *spoint,*kpoint; 
    //pixel *spoint1,*kpoint1; pixel *spoint2,*kpoint2; pixel *spoint3,*kpoint3; pixel *spoint4,*kpoint4; pixel *spoint5,*kpoint5; pixel *spoint6,*kpoint6; pixel *spoint7,*kpoint7;

    ridx=0;
    for(i = 0; i < size; i++)
    {      
        for(j=0;j<size;j++)
        {
            
            temp_red=0,temp_green = 0,temp_blue=0;
  
            
            //ridx=RIDX((i),(j), dim);  //ridx == i*dim + j
            spoint= src+ridx;
            kpoint= ker; //+RIDX(0, 0, 8) == 0

            //spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            //kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //00000000000000000000000000000
            
            temp_red = (*spoint).red * (*kpoint).red + (*(spoint+1)).red * (*(kpoint+1)).red +(*(spoint+2)).red * (*(kpoint+2)).red +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+5)).red * (*(kpoint+5)).red +(*(spoint+6)).red * (*(kpoint+6)).red+(*(spoint+7)).red * (*(kpoint+7)).red;
            temp_green = (*spoint).green * (*kpoint).green + (*(spoint+1)).green * (*(kpoint+1)).green +(*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+4)).green * (*(kpoint+4)).green + (*(spoint+5)).green * (*(kpoint+5)).green +(*(spoint+6)).green * (*(kpoint+6)).green+(*(spoint+7)).green * (*(kpoint+7)).green;
            temp_blue = (*spoint).blue * (*kpoint).blue + (*(spoint+1)).blue * (*(kpoint+1)).blue +(*(spoint+2)).blue * (*(kpoint+2)).blue +(*(spoint+3)).blue * (*(kpoint+3)).blue + (*(spoint+4)).blue * (*(kpoint+4)).blue + (*(spoint+5)).blue * (*(kpoint+5)).blue +(*(spoint+6)).blue * (*(kpoint+6)).blue+(*(spoint+7)).blue * (*(kpoint+7)).blue;

 
            spoint= spoint+dim;
            kpoint= kpoint+8;

            //spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            //kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //1111111111111111111111111111111111
           
            temp_red += (*spoint).red * (*kpoint).red + (*(spoint+1)).red * (*(kpoint+1)).red +(*(spoint+2)).red * (*(kpoint+2)).red +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+5)).red * (*(kpoint+5)).red +(*(spoint+6)).red * (*(kpoint+6)).red+(*(spoint+7)).red * (*(kpoint+7)).red;
            temp_green += (*spoint).green * (*kpoint).green + (*(spoint+1)).green * (*(kpoint+1)).green +(*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+4)).green * (*(kpoint+4)).green + (*(spoint+5)).green * (*(kpoint+5)).green +(*(spoint+6)).green * (*(kpoint+6)).green+(*(spoint+7)).green * (*(kpoint+7)).green;
            temp_blue += (*spoint).blue * (*kpoint).blue + (*(spoint+1)).blue * (*(kpoint+1)).blue +(*(spoint+2)).blue * (*(kpoint+2)).blue +(*(spoint+3)).blue * (*(kpoint+3)).blue + (*(spoint+4)).blue * (*(kpoint+4)).blue + (*(spoint+5)).blue * (*(kpoint+5)).blue +(*(spoint+6)).blue * (*(kpoint+6)).blue+(*(spoint+7)).blue * (*(kpoint+7)).blue;


            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            //spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            //kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //2222222222222222222222222
            
            
            temp_red += (*spoint).red * (*kpoint).red + (*(spoint+1)).red * (*(kpoint+1)).red +(*(spoint+2)).red * (*(kpoint+2)).red +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+5)).red * (*(kpoint+5)).red +(*(spoint+6)).red * (*(kpoint+6)).red+(*(spoint+7)).red * (*(kpoint+7)).red;
            temp_green += (*spoint).green * (*kpoint).green + (*(spoint+1)).green * (*(kpoint+1)).green +(*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+4)).green * (*(kpoint+4)).green + (*(spoint+5)).green * (*(kpoint+5)).green +(*(spoint+6)).green * (*(kpoint+6)).green+(*(spoint+7)).green * (*(kpoint+7)).green;
            temp_blue += (*spoint).blue * (*kpoint).blue + (*(spoint+1)).blue * (*(kpoint+1)).blue +(*(spoint+2)).blue * (*(kpoint+2)).blue +(*(spoint+3)).blue * (*(kpoint+3)).blue + (*(spoint+4)).blue * (*(kpoint+4)).blue + (*(spoint+5)).blue * (*(kpoint+5)).blue +(*(spoint+6)).blue * (*(kpoint+6)).blue+(*(spoint+7)).blue * (*(kpoint+7)).blue;


            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            //spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            //kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //3333333333333333333333333333333
            
            
            temp_red += (*spoint).red * (*kpoint).red + (*(spoint+1)).red * (*(kpoint+1)).red +(*(spoint+2)).red * (*(kpoint+2)).red +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+5)).red * (*(kpoint+5)).red +(*(spoint+6)).red * (*(kpoint+6)).red+(*(spoint+7)).red * (*(kpoint+7)).red;
            temp_green += (*spoint).green * (*kpoint).green + (*(spoint+1)).green * (*(kpoint+1)).green +(*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+4)).green * (*(kpoint+4)).green + (*(spoint+5)).green * (*(kpoint+5)).green +(*(spoint+6)).green * (*(kpoint+6)).green+(*(spoint+7)).green * (*(kpoint+7)).green;
            temp_blue += (*spoint).blue * (*kpoint).blue + (*(spoint+1)).blue * (*(kpoint+1)).blue +(*(spoint+2)).blue * (*(kpoint+2)).blue +(*(spoint+3)).blue * (*(kpoint+3)).blue + (*(spoint+4)).blue * (*(kpoint+4)).blue + (*(spoint+5)).blue * (*(kpoint+5)).blue +(*(spoint+6)).blue * (*(kpoint+6)).blue+(*(spoint+7)).blue * (*(kpoint+7)).blue;


            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            //spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            //kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //444444444444444444444444444444444444
            
            
            temp_red += (*spoint).red * (*kpoint).red + (*(spoint+1)).red * (*(kpoint+1)).red +(*(spoint+2)).red * (*(kpoint+2)).red +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+5)).red * (*(kpoint+5)).red +(*(spoint+6)).red * (*(kpoint+6)).red+(*(spoint+7)).red * (*(kpoint+7)).red;
            temp_green += (*spoint).green * (*kpoint).green + (*(spoint+1)).green * (*(kpoint+1)).green +(*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+4)).green * (*(kpoint+4)).green + (*(spoint+5)).green * (*(kpoint+5)).green +(*(spoint+6)).green * (*(kpoint+6)).green+(*(spoint+7)).green * (*(kpoint+7)).green;
            temp_blue += (*spoint).blue * (*kpoint).blue + (*(spoint+1)).blue * (*(kpoint+1)).blue +(*(spoint+2)).blue * (*(kpoint+2)).blue +(*(spoint+3)).blue * (*(kpoint+3)).blue + (*(spoint+4)).blue * (*(kpoint+4)).blue + (*(spoint+5)).blue * (*(kpoint+5)).blue +(*(spoint+6)).blue * (*(kpoint+6)).blue+(*(spoint+7)).blue * (*(kpoint+7)).blue;


            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            //spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            //kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //55555555555555555555555555555555
           
            
            temp_red += (*spoint).red * (*kpoint).red + (*(spoint+1)).red * (*(kpoint+1)).red +(*(spoint+2)).red * (*(kpoint+2)).red +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+5)).red * (*(kpoint+5)).red +(*(spoint+6)).red * (*(kpoint+6)).red+(*(spoint+7)).red * (*(kpoint+7)).red;
            temp_green += (*spoint).green * (*kpoint).green + (*(spoint+1)).green * (*(kpoint+1)).green +(*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+4)).green * (*(kpoint+4)).green + (*(spoint+5)).green * (*(kpoint+5)).green +(*(spoint+6)).green * (*(kpoint+6)).green+(*(spoint+7)).green * (*(kpoint+7)).green;
            temp_blue += (*spoint).blue * (*kpoint).blue + (*(spoint+1)).blue * (*(kpoint+1)).blue +(*(spoint+2)).blue * (*(kpoint+2)).blue +(*(spoint+3)).blue * (*(kpoint+3)).blue + (*(spoint+4)).blue * (*(kpoint+4)).blue + (*(spoint+5)).blue * (*(kpoint+5)).blue +(*(spoint+6)).blue * (*(kpoint+6)).blue+(*(spoint+7)).blue * (*(kpoint+7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            //spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            //kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //66666666666666666666666666666666666
            
            
            temp_red += (*spoint).red * (*kpoint).red + (*(spoint+1)).red * (*(kpoint+1)).red +(*(spoint+2)).red * (*(kpoint+2)).red +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+5)).red * (*(kpoint+5)).red +(*(spoint+6)).red * (*(kpoint+6)).red+(*(spoint+7)).red * (*(kpoint+7)).red;
            temp_green += (*spoint).green * (*kpoint).green + (*(spoint+1)).green * (*(kpoint+1)).green +(*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+4)).green * (*(kpoint+4)).green + (*(spoint+5)).green * (*(kpoint+5)).green +(*(spoint+6)).green * (*(kpoint+6)).green+(*(spoint+7)).green * (*(kpoint+7)).green;
            temp_blue += (*spoint).blue * (*kpoint).blue + (*(spoint+1)).blue * (*(kpoint+1)).blue +(*(spoint+2)).blue * (*(kpoint+2)).blue +(*(spoint+3)).blue * (*(kpoint+3)).blue + (*(spoint+4)).blue * (*(kpoint+4)).blue + (*(spoint+5)).blue * (*(kpoint+5)).blue +(*(spoint+6)).blue * (*(kpoint+6)).blue+(*(spoint+7)).blue * (*(kpoint+7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;

            //spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            //kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //77777777777777777777777777777777777
           
            
            temp_red += (*spoint).red * (*kpoint).red + (*(spoint+1)).red * (*(kpoint+1)).red +(*(spoint+2)).red * (*(kpoint+2)).red +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+5)).red * (*(kpoint+5)).red +(*(spoint+6)).red * (*(kpoint+6)).red+(*(spoint+7)).red * (*(kpoint+7)).red;
            temp_green += (*spoint).green * (*kpoint).green + (*(spoint+1)).green * (*(kpoint+1)).green +(*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+4)).green * (*(kpoint+4)).green + (*(spoint+5)).green * (*(kpoint+5)).green +(*(spoint+6)).green * (*(kpoint+6)).green+(*(spoint+7)).green * (*(kpoint+7)).green;
            temp_blue += (*spoint).blue * (*kpoint).blue + (*(spoint+1)).blue * (*(kpoint+1)).blue +(*(spoint+2)).blue * (*(kpoint+2)).blue +(*(spoint+3)).blue * (*(kpoint+3)).blue + (*(spoint+4)).blue * (*(kpoint+4)).blue + (*(spoint+5)).blue * (*(kpoint+5)).blue +(*(spoint+6)).blue * (*(kpoint+6)).blue+(*(spoint+7)).blue * (*(kpoint+7)).blue;

            //dst[ridx]=temp_red+temp_green+temp_blue+temp_red1+temp_green1+temp_blue1+temp_red2+temp_green2+temp_blue2+temp_red3+temp_green3+temp_blue3+temp_red4+temp_green4+temp_blue4+temp_red5+temp_green5+temp_blue5+temp_red6+temp_green6+temp_blue6+temp_red7+temp_green7+temp_blue7;  // RIDX((i),(j), dim) == i*dim + j == ridx
            dst[ridx] = temp_red+temp_green+temp_blue;
            ridx++;
        }
        //ridx = ridx - size +dim;
        ridx = ridx + 7;
    }
    
}
*/


/*
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */

char convolution_descr[] = "Convolution: Current working version";

//2.9 *(point + 1)

void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i,j,ridx,size=dim-7; //int temp_blue,temp_green,temp_red;
    int temp;

    pixel *spoint,*kpoint; 

    ridx=0;
    for(i = 0; i < size; i++)
    {      
        for(j=0;j<size;j++)
        {
            temp = 0;
            
            
            spoint= src+ridx;
            kpoint= ker; 

            //00000000000000000000000000000
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint+1)).red * (*(kpoint+1)).red + (*(spoint+1)).green * (*(kpoint+1)).green + (*(spoint+1)).blue * (*(kpoint+1)).blue
            +(*(spoint+2)).red * (*(kpoint+2)).red + (*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+2)).blue * (*(kpoint+2)).blue
            +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+3)).blue * (*(kpoint+3)).blue
            +(*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+4)).green * (*(kpoint+4)).green  + (*(spoint+4)).blue * (*(kpoint+4)).blue
            + (*(spoint+5)).red * (*(kpoint+5)).red + (*(spoint+5)).green * (*(kpoint+5)).green + (*(spoint+5)).blue * (*(kpoint+5)).blue
            + (*(spoint+6)).red * (*(kpoint+6)).red +(*(spoint+6)).green * (*(kpoint+6)).green +(*(spoint+6)).blue * (*(kpoint+6)).blue
            + (*(spoint+7)).red * (*(kpoint+7)).red +(*(spoint+7)).green * (*(kpoint+7)).green + (*(spoint+7)).blue * (*(kpoint+7)).blue;
                
           

 
            spoint= spoint+dim;
            kpoint= kpoint+8;

            //1111111111111111111111111111111111
           
           temp  += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint+1)).red * (*(kpoint+1)).red + (*(spoint+1)).green * (*(kpoint+1)).green + (*(spoint+1)).blue * (*(kpoint+1)).blue
            +(*(spoint+2)).red * (*(kpoint+2)).red + (*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+2)).blue * (*(kpoint+2)).blue
            +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+3)).blue * (*(kpoint+3)).blue
            +(*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+4)).green * (*(kpoint+4)).green  + (*(spoint+4)).blue * (*(kpoint+4)).blue
            + (*(spoint+5)).red * (*(kpoint+5)).red + (*(spoint+5)).green * (*(kpoint+5)).green + (*(spoint+5)).blue * (*(kpoint+5)).blue
            + (*(spoint+6)).red * (*(kpoint+6)).red +(*(spoint+6)).green * (*(kpoint+6)).green +(*(spoint+6)).blue * (*(kpoint+6)).blue
            + (*(spoint+7)).red * (*(kpoint+7)).red +(*(spoint+7)).green * (*(kpoint+7)).green + (*(spoint+7)).blue * (*(kpoint+7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            //2222222222222222222222222
            
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint+1)).red * (*(kpoint+1)).red + (*(spoint+1)).green * (*(kpoint+1)).green + (*(spoint+1)).blue * (*(kpoint+1)).blue
            +(*(spoint+2)).red * (*(kpoint+2)).red + (*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+2)).blue * (*(kpoint+2)).blue
            +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+3)).blue * (*(kpoint+3)).blue
            +(*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+4)).green * (*(kpoint+4)).green  + (*(spoint+4)).blue * (*(kpoint+4)).blue
            + (*(spoint+5)).red * (*(kpoint+5)).red + (*(spoint+5)).green * (*(kpoint+5)).green + (*(spoint+5)).blue * (*(kpoint+5)).blue
            + (*(spoint+6)).red * (*(kpoint+6)).red +(*(spoint+6)).green * (*(kpoint+6)).green +(*(spoint+6)).blue * (*(kpoint+6)).blue
            + (*(spoint+7)).red * (*(kpoint+7)).red +(*(spoint+7)).green * (*(kpoint+7)).green + (*(spoint+7)).blue * (*(kpoint+7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
    
            //3333333333333333333333333333333
            
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint+1)).red * (*(kpoint+1)).red + (*(spoint+1)).green * (*(kpoint+1)).green + (*(spoint+1)).blue * (*(kpoint+1)).blue
            +(*(spoint+2)).red * (*(kpoint+2)).red + (*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+2)).blue * (*(kpoint+2)).blue
            +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+3)).blue * (*(kpoint+3)).blue
            +(*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+4)).green * (*(kpoint+4)).green  + (*(spoint+4)).blue * (*(kpoint+4)).blue
            + (*(spoint+5)).red * (*(kpoint+5)).red + (*(spoint+5)).green * (*(kpoint+5)).green + (*(spoint+5)).blue * (*(kpoint+5)).blue
            + (*(spoint+6)).red * (*(kpoint+6)).red +(*(spoint+6)).green * (*(kpoint+6)).green +(*(spoint+6)).blue * (*(kpoint+6)).blue
            + (*(spoint+7)).red * (*(kpoint+7)).red +(*(spoint+7)).green * (*(kpoint+7)).green + (*(spoint+7)).blue * (*(kpoint+7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
       
            //444444444444444444444444444444444444
            
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint+1)).red * (*(kpoint+1)).red + (*(spoint+1)).green * (*(kpoint+1)).green + (*(spoint+1)).blue * (*(kpoint+1)).blue
            +(*(spoint+2)).red * (*(kpoint+2)).red + (*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+2)).blue * (*(kpoint+2)).blue
            +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+3)).blue * (*(kpoint+3)).blue
            +(*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+4)).green * (*(kpoint+4)).green  + (*(spoint+4)).blue * (*(kpoint+4)).blue
            + (*(spoint+5)).red * (*(kpoint+5)).red + (*(spoint+5)).green * (*(kpoint+5)).green + (*(spoint+5)).blue * (*(kpoint+5)).blue
            + (*(spoint+6)).red * (*(kpoint+6)).red +(*(spoint+6)).green * (*(kpoint+6)).green +(*(spoint+6)).blue * (*(kpoint+6)).blue
            + (*(spoint+7)).red * (*(kpoint+7)).red +(*(spoint+7)).green * (*(kpoint+7)).green + (*(spoint+7)).blue * (*(kpoint+7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            

            //55555555555555555555555555555555
           
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint+1)).red * (*(kpoint+1)).red + (*(spoint+1)).green * (*(kpoint+1)).green + (*(spoint+1)).blue * (*(kpoint+1)).blue
            +(*(spoint+2)).red * (*(kpoint+2)).red + (*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+2)).blue * (*(kpoint+2)).blue
            +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+3)).blue * (*(kpoint+3)).blue
            +(*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+4)).green * (*(kpoint+4)).green  + (*(spoint+4)).blue * (*(kpoint+4)).blue
            + (*(spoint+5)).red * (*(kpoint+5)).red + (*(spoint+5)).green * (*(kpoint+5)).green + (*(spoint+5)).blue * (*(kpoint+5)).blue
            + (*(spoint+6)).red * (*(kpoint+6)).red +(*(spoint+6)).green * (*(kpoint+6)).green +(*(spoint+6)).blue * (*(kpoint+6)).blue
            + (*(spoint+7)).red * (*(kpoint+7)).red +(*(spoint+7)).green * (*(kpoint+7)).green + (*(spoint+7)).blue * (*(kpoint+7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            

            //66666666666666666666666666666666666
            
            
           temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint+1)).red * (*(kpoint+1)).red + (*(spoint+1)).green * (*(kpoint+1)).green + (*(spoint+1)).blue * (*(kpoint+1)).blue
            +(*(spoint+2)).red * (*(kpoint+2)).red + (*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+2)).blue * (*(kpoint+2)).blue
            +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+3)).blue * (*(kpoint+3)).blue
            +(*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+4)).green * (*(kpoint+4)).green  + (*(spoint+4)).blue * (*(kpoint+4)).blue
            + (*(spoint+5)).red * (*(kpoint+5)).red + (*(spoint+5)).green * (*(kpoint+5)).green + (*(spoint+5)).blue * (*(kpoint+5)).blue
            + (*(spoint+6)).red * (*(kpoint+6)).red +(*(spoint+6)).green * (*(kpoint+6)).green +(*(spoint+6)).blue * (*(kpoint+6)).blue
            + (*(spoint+7)).red * (*(kpoint+7)).red +(*(spoint+7)).green * (*(kpoint+7)).green + (*(spoint+7)).blue * (*(kpoint+7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;


            //77777777777777777777777777777777777
           
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint+1)).red * (*(kpoint+1)).red + (*(spoint+1)).green * (*(kpoint+1)).green + (*(spoint+1)).blue * (*(kpoint+1)).blue
            +(*(spoint+2)).red * (*(kpoint+2)).red + (*(spoint+2)).green * (*(kpoint+2)).green +(*(spoint+2)).blue * (*(kpoint+2)).blue
            +(*(spoint+3)).red * (*(kpoint+3)).red + (*(spoint+3)).green * (*(kpoint+3)).green + (*(spoint+3)).blue * (*(kpoint+3)).blue
            +(*(spoint+4)).red * (*(kpoint+4)).red + (*(spoint+4)).green * (*(kpoint+4)).green  + (*(spoint+4)).blue * (*(kpoint+4)).blue
            + (*(spoint+5)).red * (*(kpoint+5)).red + (*(spoint+5)).green * (*(kpoint+5)).green + (*(spoint+5)).blue * (*(kpoint+5)).blue
            + (*(spoint+6)).red * (*(kpoint+6)).red +(*(spoint+6)).green * (*(kpoint+6)).green +(*(spoint+6)).blue * (*(kpoint+6)).blue
            + (*(spoint+7)).red * (*(kpoint+7)).red +(*(spoint+7)).green * (*(kpoint+7)).green + (*(spoint+7)).blue * (*(kpoint+7)).blue;

            dst[ridx] = temp;
            ridx++;
        }
        //ridx = ridx - size +dim;
        ridx = ridx + 7;
    }

}


//2.9 but spoint1 = (spoint+1)
/*
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i,j,ridx,size=dim-7; //int temp_blue,temp_green,temp_red;
    int temp;

    pixel *spoint,*kpoint; 
    pixel *spoint1,*kpoint1; pixel *spoint2,*kpoint2; pixel *spoint3,*kpoint3; pixel *spoint4,*kpoint4; pixel *spoint5,*kpoint5; pixel *spoint6,*kpoint6; pixel *spoint7,*kpoint7;

    ridx=0;
    
    for(j=0;j<size;j++)
    {      
        for(i = 0; i < size; i++)
        {
            temp = 0;
            //temp_red=0,temp_green = 0,temp_blue=0;
            
            
            //ridx=RIDX((i),(j), dim);  //ridx == i*dim + j
            spoint= src+ridx;
            kpoint= ker; //+RIDX(0, 0, 8) == 0

            spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //00000000000000000000000000000
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
            +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
            +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
            +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
            + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
            + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
            + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;
                
           

 
            spoint= spoint+dim;
            kpoint= kpoint+8;

            spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //1111111111111111111111111111111111
           
           temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
            +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
            +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
            +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
            + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
            + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
            + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //2222222222222222222222222
            
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
            +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
            +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
            +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
            + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
            + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
            + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //3333333333333333333333333333333
            
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
            +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
            +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
            +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
            + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
            + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
            + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //444444444444444444444444444444444444
            
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
            +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
            +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
            +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
            + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
            + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
            + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //55555555555555555555555555555555
           
            
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
            +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
            +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
            +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
            + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
            + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
            + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;
            
            spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //66666666666666666666666666666666666
            
            
           temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
            +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
            +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
            +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
            + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
            + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
            + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

            spoint= spoint+dim;
            kpoint= kpoint+8;

            spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
            kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
            //77777777777777777777777777777777777
           
            temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
            + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
            +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
            +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
            +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
            + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
            + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
            + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

                //dst[ridx]=temp_red+temp_green+temp_blue+temp_red1+temp_green1+temp_blue1+temp_red2+temp_green2+temp_blue2+temp_red3+temp_green3+temp_blue3+temp_red4+temp_green4+temp_blue4+temp_red5+temp_green5+temp_blue5+temp_red6+temp_green6+temp_blue6+temp_red7+temp_green7+temp_blue7;  // RIDX((i),(j), dim) == i*dim + j == ridx
            //dst[ridx] = temp_red+temp_green+temp_blue;
            dst[ridx] = temp;
            ridx++;
        }
        //ridx = ridx - size +dim;
        ridx = ridx + 7;
    }

}
*/


//TILE SIZE CODE 2.7 with convo
/*
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst) {
    int tile_size = 2 ,ridx,tdim=dim<<1,j; // Adjust this value based on the cache size of the processor
    int temp;
    pixel *spoint,*kpoint; pixel *spoint1,*kpoint1; pixel *spoint2,*kpoint2; pixel *spoint3,*kpoint3; pixel *spoint4,*kpoint4; pixel *spoint5,*kpoint5; pixel *spoint6,*kpoint6; pixel *spoint7,*kpoint7;


    int size= dim-7;
    //pixel *spoint,*kpoint;

    ridx=0;
    for (int i = 0; i < size; i += tile_size) 
    {
        
        for ( j = 0; j <size; j += tile_size) 
        {
            
            for (int ii = i; ii < i + tile_size; ii++) 
            {
                for (int jj = j; jj < j + tile_size; jj++) 
                {
                    temp = 0;
                    //temp_red=0,temp_green = 0,temp_blue=0;
                    
                    
                    //ridx=RIDX((i),(j), dim);  //ridx == i*dim + j
                    spoint= src+ridx;
                    kpoint= ker; //+RIDX(0, 0, 8) == 0

                    spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
                    kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
                    //00000000000000000000000000000
                    
                    temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
                    + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
                    +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
                    +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
                    +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
                    + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
                    + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
                    + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;
                        
                

        
                    spoint= spoint+dim;
                    kpoint= kpoint+8;

                    spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
                    kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
                    //1111111111111111111111111111111111
                
                    temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
                    + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
                    +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
                    +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
                    +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
                    + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
                    + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
                    + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

                    spoint= spoint+dim;
                    kpoint= kpoint+8;
                    
                    spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
                    kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
                    //2222222222222222222222222
                    
                    
                    temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
                    + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
                    +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
                    +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
                    +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
                    + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
                    + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
                    + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

                    spoint= spoint+dim;
                    kpoint= kpoint+8;
                    
                    spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
                    kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
                    //3333333333333333333333333333333
                    
                    
                    temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
                    + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
                    +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
                    +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
                    +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
                    + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
                    + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
                    + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

                    spoint= spoint+dim;
                    kpoint= kpoint+8;
                    
                    spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
                    kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
                    //444444444444444444444444444444444444
                    
                    
                    temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
                    + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
                    +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
                    +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
                    +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
                    + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
                    + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
                    + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

                    spoint= spoint+dim;
                    kpoint= kpoint+8;
                    
                    spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
                    kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
                    //55555555555555555555555555555555
                
                    
                    temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
                    + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
                    +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
                    +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
                    +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
                    + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
                    + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
                    + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

                    spoint= spoint+dim;
                    kpoint= kpoint+8;
                    
                    spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
                    kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
                    //66666666666666666666666666666666666
                    
                    
                    temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
                    + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
                    +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
                    +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
                    +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
                    + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
                    + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
                    + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

                    spoint= spoint+dim;
                    kpoint= kpoint+8;

                    spoint1 = (spoint+1) ; spoint2 = (spoint+2) ; spoint3 = (spoint+3); spoint4 = (spoint+4) ; spoint5 = (spoint+5); spoint6 = (spoint+6); spoint7 = (spoint+7);
                    kpoint1 = (kpoint+1) ; kpoint2 = (kpoint+2) ; kpoint3 = (kpoint+3); kpoint4 = (kpoint+4) ; kpoint5 = (kpoint+5); kpoint6 = (kpoint+6); kpoint7 = (kpoint+7);
                    //77777777777777777777777777777777777
                
                    temp += (*spoint).red * (*kpoint).red + (*spoint).green * (*kpoint).green+ (*spoint).blue * (*kpoint).blue 
                    + (*(spoint1)).red * (*(kpoint1)).red + (*(spoint1)).green * (*(kpoint1)).green + (*(spoint1)).blue * (*(kpoint1)).blue
                    +(*(spoint2)).red * (*(kpoint2)).red + (*(spoint2)).green * (*(kpoint2)).green +(*(spoint2)).blue * (*(kpoint2)).blue
                    +(*(spoint3)).red * (*(kpoint3)).red + (*(spoint3)).green * (*(kpoint3)).green + (*(spoint3)).blue * (*(kpoint3)).blue
                    +(*(spoint4)).red * (*(kpoint4)).red + (*(spoint4)).green * (*(kpoint4)).green  + (*(spoint4)).blue * (*(kpoint4)).blue
                    + (*(spoint5)).red * (*(kpoint5)).red + (*(spoint5)).green * (*(kpoint5)).green + (*(spoint5)).blue * (*(kpoint5)).blue
                    + (*(spoint6)).red * (*(kpoint6)).red +(*(spoint6)).green * (*(kpoint6)).green +(*(spoint6)).blue * (*(kpoint6)).blue
                    + (*(spoint7)).red * (*(kpoint7)).red +(*(spoint7)).green * (*(kpoint7)).green + (*(spoint7)).blue * (*(kpoint7)).blue;

                        //dst[ridx]=temp_red+temp_green+temp_blue+temp_red1+temp_green1+temp_blue1+temp_red2+temp_green2+temp_blue2+temp_red3+temp_green3+temp_blue3+temp_red4+temp_green4+temp_blue4+temp_red5+temp_green5+temp_blue5+temp_red6+temp_green6+temp_blue6+temp_red7+temp_green7+temp_blue7;  // RIDX((i),(j), dim) == i*dim + j == ridx
                    //dst[ridx] = temp_red+temp_green+temp_blue;
                    dst[ridx] = temp;
                    ridx++;



                }
                //ridx = ridx - size +dim;
                
                ridx +=dim;
                ridx -=tile_size;
            }
            //printf("%d\n",ridx);
            ridx+=tile_size;
            ridx-=tdim;

        }
        
        ridx-=j;
        ridx+=tdim;
        //printf("%d\n",ridx);
    }
    
        

}
*/



/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_conv_functions() {
    add_conv_function(&naive_conv, naive_conv_descr);
    add_conv_function(&convolution, convolution_descr);
    /* ... Register additional test functions here */
}




/************************
 * AVERAGE POOLING KERNEL
 ************************/

/*********************************************************
 * Your different versions of the average pooling  go here
 *********************************************************/

/*
 * naive_average_pooling - The naive baseline version of average pooling
 */
char naive_average_pooling_descr[] = "Naive Average Pooling: Naive baseline implementation";

void naive_average_pooling(int dim, pixel *src, pixel *dst) {
    int i,j,k,l;

    for(i = 0; i < dim/2; i++)
        for(j = 0; j < dim/2; j++) {
            dst[RIDX(i, j, dim/2)].red = 0;
            dst[RIDX(i, j, dim/2)].green = 0;
            dst[RIDX(i, j, dim/2)].blue = 0;
            for(k = 0; k < 2; k++) {
                for (l = 0; l < 2; l++) {
                    dst[RIDX(i, j, dim/2)].red += src[RIDX(i*2 + k, j*2 + l, dim)].red;
                    dst[RIDX(i, j, dim/2)].green += src[RIDX(i*2 + k, j*2 + l, dim)].green;
                    dst[RIDX(i, j, dim/2)].blue += src[RIDX(i*2 + k, j*2 + l, dim)].blue;
                }
            }
            dst[RIDX(i, j, dim/2)].red /= 4;
            dst[RIDX(i, j, dim/2)].green /= 4;
            dst[RIDX(i, j, dim/2)].blue /= 4;
        }   
}

/*
void naive_average_pooling(int dim, pixel *src, pixel *dst) {
    int i,j,k,l,ridx=0,size=dim>>1,red,green,blue,secridx;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++) 
        {
            red = 0;
            green = 0;
            blue = 0;
            secridx=RIDX(i<<1 , j<<1, dim);
            red += src[secridx].red;
            green += src[secridx].green;
            blue += src[secridx].blue;
                
            secridx++;
            red += src[secridx].red;
            green += src[secridx].green;
            blue += src[secridx].blue;

            secridx--;
            secridx+=dim;
            red += src[secridx].red;
            green += src[secridx].green;
            blue += src[secridx].blue;

            secridx++;    
            red += src[secridx].red;
            green += src[secridx].green;
            blue += src[secridx].blue;


            dst[ridx].red=red >> 2;
            dst[ridx].green=green >> 2;
            dst[ridx].blue=blue >> 2;
            ridx++;
        }
        ridx+=size;
        ridx-=size;
    }
}
*/


/*
 * average_pooling - Your current working version of average_pooling
 * IMPORTANT: This is the version you will be graded on
 */
char average_pooling_descr[] = "Average Pooling: Current working version";

void average_pooling(int dim, pixel *src, pixel *dst)
{

    int i,j;
    int dim_half = dim >> 1;
    int temp_dst_red;
    int temp_dst_green;
    int temp_dst_blue;

    for(i = 0; i < dim_half; i++)
    {
        for(j = 0; j < dim_half; j++)
         {
            temp_dst_red=0;
            temp_dst_green=0;
            temp_dst_blue=0;

            //dst[RIDX(i, j, dim/2)].red = 0;
            //dst[RIDX(i, j, dim/2)].green = 0;
            //dst[RIDX(i, j, dim/2)].blue = 0;

            //RIDX(i*2 + k, j*2 + l, dim) = dim*(2i+k) +(2j+l) = dim*2i + dim*k + 2j + l
            int dim_i = dim * i;
            int dim_2i = dim_i << 1;
            int base = dim_2i + (j<<1); // base dim*2i + 2j;

            //dim * k + l  --> dim*0 , l= 0,1  || dim*1 = l = 0,1 
            temp_dst_red = src[base].red ;
            temp_dst_green = src[base].green ;
            temp_dst_blue  = src[base].blue ;

            int base_1 = base + 1;
            //base + 1
            temp_dst_red   += src[base_1].red ;
            temp_dst_green += src[base_1].green; 
            temp_dst_blue  += src[base_1].blue ;

            base += dim;
            //base + dim
            temp_dst_red   += src[base].red ;
            temp_dst_green += src[base].green; 
            temp_dst_blue  += src[base].blue ;

            base += 1;
            //base + dim + 1
            temp_dst_red   += src[base].red ;
            temp_dst_green += src[base].green; 
            temp_dst_blue  += src[base].blue ;

            //value >> 2 == value / 4
            temp_dst_red = temp_dst_red >> 2;
            temp_dst_green = temp_dst_green >> 2;;
            temp_dst_blue = temp_dst_blue >> 2;

            //RIDX(i, j, dim/2) ==> i*dim/2 + j

            int base2 = (dim_i >> 1) + j ;
            dst[base2].red = temp_dst_red;
            dst[base2].green = temp_dst_green;
            dst[base2].blue = temp_dst_blue;


        }
    }

}




/******************************************************************************
 * register_average_pooling_functions - Register all of your different versions
 *     of the average pooling  with the driver by calling the
 *     add_average_pooling_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 ******************************************************************************/

void register_average_pooling_functions() {
    add_average_pooling_function(&naive_average_pooling, naive_average_pooling_descr);
    add_average_pooling_function(&average_pooling, average_pooling_descr);
    /* ... Register additional test functions here */
}

