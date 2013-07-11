Simulink (Embedded Coder) Target for MicroDAQ Real-Time Measurement System
=============

**Summary:**

MicroDAQ (http://www.embedded-solutions.pl) is a Real-Time Measurement
and Rapid Control Prototyping System.

Simulink (http://www.mathworks.com/products/simulink) is a leading environment
for multidomain simulation and Model-Based Design.

Embedded Coder (http://www.mathworks.com/products/embedded-coder) allows you to
generate C code and deploy your algorithms to target hardware.

**Installation:**

1) Windows/Linux: Have Code Composer Studio 5.3 or 5.4 installed (http://processors.wiki.ti.com/index.php/Download_CCS).

2) Windows: Install Device support files for OMAPL137:
http://processors.wiki.ti.com/index.php/Device_support_files (download version for C6-Integra).
Perhaps my CCS installation on Windows was not full, but I couldn't connect to the board without these support files.

3) Make sure your toolchain is working (build and download some test project, check connection)
before you proceed! "docs/MicroDAQ Quick Start Guide.pdf" is a useful document that will guide you through this process.
This step is not required, but it is strongly advised to get yourself familiar with some basic concepts.

4) Make sure you have a working/supported host compiler (http://www.mathworks.com/support/compilers/R2013a/index.html) by running
        
        mex -setup
in MATLAB.
Avoid using the lcc compiler which ships with MATLAB 32-bit for Windows. It is known to cause problems.

5) Extract this package somewhere. Make sure there are no spaces/non-ASCII characters in path (just in case).

6) Within MATLAB, 'cd' to the directory containing microdaq_setup.m and run this script.

You should be good to go.

**What this package already has:**

- Automatic build and download to target using MLink or JTAG (selected by user)
- Standalone execution on target (driven by SYS/BIOS timer)
- Execution in PIL mode
- Simulink library blocks for:
        
        * Built-in LEDs

**What this package would like to have:**

- Simulink library blocks for:

        * ADC, DAC, GPIO, PWM, Quadrature Encoder, PRU (for additional processing units)
- More documentation
- External Mode support
- PIL mode profiling
