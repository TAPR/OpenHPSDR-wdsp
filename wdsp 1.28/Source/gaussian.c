/*  gaussian.c

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2025 Warren Pratt, NR0V

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

The author can be reached by email at

warren@pratt.one
*/

#define _CRT_SECURE_NO_WARNINGS

#include "comm.h"


int calc_nc (double sigma, double nsigma, double rate)
{
	unsigned int nc;
	nc = (unsigned int)ceil(2.0 * nsigma * sigma * rate);
	nc--;
	nc |= nc >> 1;
	nc |= nc >> 2;
	nc |= nc >> 4;
	nc |= nc >> 8;
	nc |= nc >> 16;
	nc++;
	return nc;
}

double* build_gaussian (int nc, double rate, double f, double fwhm, double scale)
{
    // nc - number of impulse response values, an EVEN value
	//      IF 'nc' is entered as zero, it will be computed below.
    // rate - sample_rate (samples/second)
    // f - center frequency (Hz)
    // fwhm - half-power bandwidth (Hz)
	// scale - scale factor to apply to impulse function

	// **********  Generate the Low-Pass Gaussian Impulse Response  **********

    double fsigma = fwhm / 2.35482;
	double sigma = 1.0 / (2.0 * PI * fsigma);
	if (nc == 0) nc = calc_nc(sigma, 3.0, rate);
    double* impulse = (double*)malloc0(nc * sizeof(double));
	double delta = 1.0 / rate;
    int i, j;
    double x, y;
    double gmult = 1.0 / (sqrt(2.0 * PI) * sigma);
    double gdiv = 1.0 / (2.0 * sigma * sigma);
    double sum = 0.0;
	for (i = 0, y = -((double)(nc - 1) / 2.0); i < nc; i++, y += 1.0)
	{
		x = y * delta;
		impulse[i] = gmult * exp(-(x * x) * gdiv);
		sum += impulse[i];
	}
    for (i = 0; i < nc; i++)
    {
        impulse[i] *= (scale / sum);
    }
	// print_impulse("gaussian.txt", nc, impulse, 0, 0);

	// **********  Shift the center frequency  **********

	double* c_impulse = (double*)malloc0(nc * sizeof(complex));
	double w_osc = - 2.0 * PI * f / rate;
	double m = 0.5 * (double)(nc - 1);
	double posi, posj;
	double coef;
	for (i = (nc + 1) / 2, j = nc / 2 - 1; i < nc; i++, j--)
	{
		posi = (double)i - m;
		posj = (double)j - m;
		coef = impulse[j];
		c_impulse[2 * i + 0] = +coef * cos(posi * w_osc);
		c_impulse[2 * i + 1] = -coef * sin(posi * w_osc);
		c_impulse[2 * j + 0] = +coef * cos(posj * w_osc);
		c_impulse[2 * j + 1] = -coef * sin(posj * w_osc);
	}
	// print_impulse("c_gaussian.txt", nc, c_impulse, 1, 0);
	_aligned_free(impulse);
	return c_impulse;
}
