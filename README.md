Simulink (Embedded Coder) Target for MicroDAQ Real-Time Measurement System
=============

**Summary:**

MicroDAQ (http://www.embedded-solutions.pl) is a Real-Time Measurement
and Rapid Control Prototyping System.

Simulink (http://www.mathworks.com/products/simulink) is a leading environment
for multidomain simulation and Model-Based Design.

Embedded Coder (http://www.mathworks.com/products/embedded-coder) allows you to
generate C code and deploy your algorithms to target hardware.

**Supported Matlab version:**

This package will work with R2013a and newer Matlab releases. 

**Installation:**

1) Install latest MicroDAQ firmware from: https://github.com/embedded-solutions/microdaq-firmware/releases
Download latest MicroDAQ firmware, unpack it, connect MicroDAQ with USB cable, copy OPK package to 'upgrade' directory on MicroDAQ user-disk. In order to flash new firmware open web interface in web browser by entering MicroDAQ IP addres (10.10.1.1 default) and select Install upgrade. After MicroDAQ reboot you can perform next step.

2) Windows/Linux: Have Code Composer Studio 5.3 - 5.5 installed (http://processors.wiki.ti.com/index.php/Download_CCS). Make sure your installation is full, otherwise you might miss some files (like Device support files for OMAPL137). Code Composer Studio 6 is not supported at the moment.

3) Make sure your toolchain is working (build and download some test project, check connection)
before you proceed! "docs/MicroDAQ Quick Start Guide.pdf" is a useful document that will guide you through this process.
This step is not required, but it is strongly advised to get yourself familiar with some basic concepts.

4) Make sure you have a working/supported host compiler (http://www.mathworks.com/support/compilers/index.html) by running
        
        mex -setup
in MATLAB.
Avoid using the lcc compiler which ships with MATLAB for Windows. It is known to cause problems.

5) Extract this package somewhere. Make sure there are no spaces/non-ASCII characters in path (just in case).

6) Within MATLAB, 'cd' to the directory containing *microdaq_setup.m* and run this script.

You should be good to go.

**What this package already has:**

- Automatic build and download to target using MLink or JTAG (selected by user)
- Standalone execution on target (driven by SYS/BIOS timer)
- Execution in PIL mode
- External Mode support
- PIL mode profiling

- Simulink library blocks for:
        
        * ADC
        * DAC
        * Quadrature Encoder
        * MEMORY R/W
        * DIO
        * Built-in LEDs
        * Built-in KEYs
        * PRU - Real-time processing unit
        * PWM
        * File operations
        * TCP/IP (client) and UDP Send/Receive

**What this package would like to have:**

- Simulink library blocks for:

        * TCP/IP (server) Send/Receive
        * RAW Ethernet
 
- More documentation
