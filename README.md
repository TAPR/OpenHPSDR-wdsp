# OpenHPSDR-wdsp

WDSP is a full‐featured signal processing library for Software Defined Radio.

For change logs see the WDSP Guide documentation provided with each release.

GNU General Public License (GPL) applies to this software (see license file).

Copyright © 2016 ‐ 2023, Warren C. Pratt, NR0V

## Release Notes

1.27 2025-11-01

### Minimum phase filter responses were improperly cached--this has been removed.

Various code changes to make the CLANG LLVM Static Analyzer checker tool (used for Linux implementations) happier. Addition of psychoacoustic postprocessing
for NR2 noise reduction.

1.26 2025-06-30

Added Bandpass Characterization Utility to provide a graphical characterization of bandpass filter magnitude. Added Filter Impulse Response Caching to speedup
re-use of previously used filters. Removed requirement to use an external file, zetaHat.bin, for Trained NR2 mode. For TX, added pulsed-tone and pulsed two-
tone capability. Added capability to return the largest bin value from a specified band within the display FFT output.

1.25 2024-07-05

Added "Trained" mode for Spectral Noise Reduction along with NSTAT NPE Method.

1.24 2023-11-08

Added time adjustment for TXA carrier up-slew. Added bandwidth adjustment for FM transmit and receive. Added a function that can be used to clear display
buffers. In the phase rotator, added a function to reverse microphone phase (180 degrees).

1.23 2023-06-17

Efficiency improvements.

1.22 2023-05-20

Efficiency improvements: less system calls at the expense of slightly higher average thread and memory allocations.

1.21 2023-04-29

Added a volume limiter to the FM demodulator to balance signal and noise volume during squelch tail or weak signal reception with squelch OFF. Added
voice squelch functionality as an alternative especially for SSB reception.

1.20 2022-02-15

Internal enhancements supporting portability to non-Windows operating systems. Enhanced panadapter/waterfall frequency accuracy for high-zoom
cases.

### Porting considerations
(1) There are two new files that must be included in the build - calculus.c and calculus.h
(2) For the display, setup for calls to SetAnalyzer(...) is somewhat different for optimum results and parameters fscLin and fscHin should be passed as doubles--see the WDSP Guide.