/*
 * Filename:    getfloat.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


/* getfloat:  get next float from input into *pn */
int getfloat(FILE *stream, float *pn)
{
    //double power;
    float power;
    int c, sign, exp, esign, bigE;

    while (isspace(c = getc(stream)))   /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetc(c, stream);              /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getc(stream);
        if (!isdigit(c)) {              /* + or - not followed by a digit */
            ungetc(c, stream);          /* ungetc non-digit */
            if(sign == 1) 
                ungetc('+', stream);
            else 
                ungetc('-', stream);    /* ungetch + or - */
            return 0;
        }
    }
    for (*pn = 0.0; isdigit(c); c = getc(stream))     /* integer part */
        *pn = 10.0 * *pn + (c - '0');
    if (c == '.')
        c = getc(stream);
    for (power = 1.0; isdigit(c); c = getc(stream)) { /* fractional part */
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }
    bigE = (c == 'E') ? 1 : 0;
    if (c == 'e' || c == 'E') {
        c = getc(stream);
        esign = (c == '-') ? -1 : 1;
        if (c == '+' || c == '-') {
            c = getc(stream);
            if (!isdigit(c)) { /* + or - not followed by a digit */
                ungetc(c,stream);
                ungetc((sign == 1 ? '+' : '-'), stream);
            }
        } else if (!isdigit(c)) { /* e or E not followed by an int */
            ungetc(c, stream);
            ungetc((bigE == 0 ? 'e' : 'E'), stream);
        }
        for (exp = 0; isdigit(c); c = getc(stream)) /* exponent part */
            exp = 10 * exp + (c - '0');
        *pn *= (sign / power) * powf(10, esign* exp);
    } else {
        *pn *= (sign / power);
    }
    if (c != EOF)
        ungetc(c,stream);
    return c;
}


/*

/* sample implementation of getfloat 
int main(void)
{
    float *floatval;
    int r;
    FILE *fp;

    r = getfloat(fp, floatval);
    if (r > 0)
        printf("(%c) %f\n", r, *floatval);
    else if (r == 0)
        printf("not a number\n");
    else if (r == EOF)
        printf("end of file\n");
    else
        printf("wtf happend?\n");
    return EXIT_SUCCESS;
}*/

