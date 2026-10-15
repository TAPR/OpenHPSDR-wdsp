# OpenHPSDR-wdsp

WDSP is a full‐featured signal processing library for Software Defined Radio.

For change logs see the WDSP Guide documentation provided with each release.

GNU General Public License (GPL) applies to this software (see license file).

Copyright © 2016 ‐ 2026, Warren C. Pratt, NR0V

## Release Notes

2.11 2026-10-15

* CW Models (Standard & Premium) for NNR Noise Reduction added.
* Enhancement of SetChannelState(...) function.  Hosts should call SetChannelState(ch, 0, 1) before CloseChannel(ch).
* Porting aids:  New #includes in several files; wdsp_align.h added; enums now in wdsp.h.
* Bug fixes in fmd.c, emph.c, emnr.c, and nnet.c.
* Bounds checking added for data files and buffer sizes; WDSPwisdom() can now return -1 (see Manual).
* Several other minor improvements and additions.
* "WDSP Reference Manual" - NNR section expanded to include discussion of new CW models.

2.10 2026-09-04

* Deep Neural Network Noise Reduction (NNR) - minimal UI.

   * Added a second 'Premium' neural model, choices are now 'Standard' or 'Premium'.
   * The Premium model requires significant CPU resources. It may not be suitable for Pi CPUs.
   * CPU performance profiling code is included in this release for developers.
   * Testing has demonstrated favorable results compared to DeepFilterNet3 and RNNoise.

* PureSignal:  Algorithm tuning and performance tuning - no UI changes.
* Performance improvements in Filter Generation - no UI changes.
* Auto-generated wdsp.h - let me know if there are bugs or what should be added.
* New Appendix D on Predistortion and PureSignal in the WDSP Reference Manual.

2.00 2026-07-01

> [!IMPORTANT]
> ### This is a major release with many new functions

* **PureSignal 3.0**

  * New NURBS internal data structures and calibration algorithms.
  * Improved robustness to handle systems with significant memory effects, noisy feedback data, low bias, over-drive situations, and other difficult conditions.
  * Simpler setup and control.

* **Free-curve Control of Equalizers, CFC, and Post-equalizer**

  * Shape audio response and compression with complete control of response curves from linear to 16th degree.
  * Virtually unlimited control points with weights.
  * Provides graphical output data for display of filter response in the console.

* **Phase Rotator Pre/post Asymmetry Measurement**

  * Measures symmetry of the audio pre and post Phase Rotator.
  * Provides graphical output data for a pre/post Asymmetry Display in the console.

* **Phase Rotator Automatic Optimizer**

  * Uses the new asymmetry measurement function to automatically optimize phase rotator settings for maximum symmetry.

* **Broadcast FM Stereo Demodulator**

  * High-quality FM analog demodulation with squelch and stereo indicator.

* **Receive Input Decimator**

  * Improved bandwidth.
  * Increased alias rejection.
  * Supports input rates extending up to 6144 KHz.

* Continued CW APF Improvements

* **WDSP Reference Manual Appendices**

  * Three new appendices of interest to both operators and developers.
    1. Higher-Degree Curve Interpolation (NURBS/B-Spline).
    2. Phase Response in Audio Filters (linear phase vs. minimum phase).
    3. The Transmit Audio Chain (each stage is described, how it works, and how to use it effectively).

> [!NOTE]
> FFTW Wisdom will be recomputed for this version of WDSP.

1.29 2026-01-21

Added new filter options to the CW audio peak filter (APF): DoublePole, Matched, and Gaussian.

1.28 2025-10-21

Minimum Phase filter caching problem resolved and added back in.
Added impulse response generation for Gaussian filters for future testing and potential inclusion in the receiver.

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

### Porting considerations for v1.20
(1) There are two new files that must be included in the build - calculus.c and calculus.h

(2) For the display, setup for calls to SetAnalyzer(...) is somewhat different for optimum results and parameters fscLin and fscHin should be passed as doubles--see the WDSP Guide.