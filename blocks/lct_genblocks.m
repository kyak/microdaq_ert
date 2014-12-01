function lct_genblocks
%% LED
% Populate legacy_code structure with information
MDAQLED = legacy_code('initialize');
MDAQLED.SFunctionName = 'sfun_MDAQLED';
MDAQLED.HeaderFiles = {'mdaqled.h'};
MDAQLED.SourceFiles = {'mdaqled.c','gpio.c'};
MDAQLED.IncPaths = {'mdaq'};
MDAQLED.SrcPaths = {'mdaq'};
MDAQLED.OutputFcnSpec = 'mdaqled_set(uint32 p1, uint8 u1)';
% Support calling from within For-Each subsystem
MDAQLED.Options.supportsMultipleExecInstances = true;

%% ADC
MDAQADC = legacy_code('initialize');
MDAQADC.SFunctionName = 'sfun_MDAQADC';
MDAQADC.HeaderFiles = {'mdaqadc.h'};
MDAQADC.SourceFiles = {'mdaqadc.c','mdaq_ain.c','ltc185x.c','ads8568.c','spi.c','gpio.c','utils.c'};
MDAQADC.IncPaths = {'mdaq'};
MDAQADC.SrcPaths = {'mdaq'};
MDAQADC.StartFcnSpec = 'ADCInit(uint8 p1, uint8 p2[], uint8 p3, uint8 p4, uint8 p5, uint8 p6)';
MDAQADC.OutputFcnSpec = 'ADCStep(uint16 y1[p3], double y2[p3], uint8 p2[], uint8 p3)';
MDAQADC.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQADC.Options.supportsMultipleExecInstances = true;

%% DAC
MDAQDAC = legacy_code('initialize');
MDAQDAC.SFunctionName = 'sfun_MDAQDAC';
MDAQDAC.HeaderFiles = {'mdaqdac.h'};
MDAQDAC.SourceFiles = {'mdaqdac.c','mdaq_aout.c','dac7568.c','spi.c','gpio.c','utils.c'};
MDAQDAC.IncPaths = {'mdaq'};
MDAQDAC.SrcPaths = {'mdaq'};
MDAQDAC.StartFcnSpec = 'DACInit(uint8 p1, uint8 p2[], uint8 p3, uint8 p4, uint8 p5 )';
MDAQDAC.OutputFcnSpec = 'DACStep(double u1[p3], uint8 p2[], uint8 p3)';
MDAQDAC.TerminateFcnSpec = 'DACTerminate(single p7[], uint8 p3, uint8 p6 )';
MDAQDAC.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQDAC.Options.supportsMultipleExecInstances = true;

%% QEP
MDAQQEP = legacy_code('initialize');
MDAQQEP.SFunctionName = 'sfun_MDAQQEP';
MDAQQEP.HeaderFiles = {'mdaqenc.h'};
MDAQQEP.SourceFiles = {'mdaqenc.c','eqep.c','utils.c','pru.c', 'mdaq_dio.c', 'gpio.c'};
MDAQQEP.IncPaths = {'mdaq'};
MDAQQEP.SrcPaths = {'mdaq'};
MDAQQEP.StartFcnSpec = 'ENCInit(uint8 p1)';
MDAQQEP.OutputFcnSpec = 'ENCStep(uint8 p1, int32 y1[1], uint8 y2[1], uint8 u1)';
MDAQQEP.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQQEP.Options.supportsMultipleExecInstances = true;

%% Encoder
MDAQENC = legacy_code('initialize');
MDAQENC.SFunctionName = 'sfun_MDAQENC';
MDAQENC.HeaderFiles = {'mdaqenc.h'};
MDAQENC.SourceFiles = {'mdaqenc.c','eqep.c','utils.c','pru.c', 'mdaq_dio.c', 'gpio.c'};
MDAQENC.IncPaths = {'mdaq'};
MDAQENC.SrcPaths = {'mdaq'};
MDAQENC.StartFcnSpec = 'ENC2Init()';
MDAQENC.OutputFcnSpec = 'ENC2Step(uint8 u1, uint8 u2, uint8 u3, uint8 u4, int32 y1[1], uint8 y2[1], int32 y3[1], uint8 y4[1], int32 y5[1], uint8 y6[1], int32 y7[1], uint8 y8[1])';
MDAQENC.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQENC.Options.supportsMultipleExecInstances = true;

% PRU REG GET
MDAQPRUREGSET = legacy_code('initialize');
MDAQPRUREGSET.SFunctionName = 'sfun_MDAQPRUREGSET';
MDAQPRUREGSET.SourceFiles = {'mdaqpru.c','pru.c'};
MDAQPRUREGSET.IncPaths = {'mdaq'};
MDAQPRUREGSET.SrcPaths = {'mdaq'};
MDAQPRUREGSET.StartFcnSpec = 'PRUInit()';
MDAQPRUREGSET.OutputFcnSpec = 'PRURegSetStep(uint8 p1, uint32 u1)';
MDAQPRUREGSET.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQPRUREGSET.Options.supportsMultipleExecInstances = true;

% PRU REG SET
MDAQPRUREGGET = legacy_code('initialize');
MDAQPRUREGGET.SFunctionName = 'sfun_MDAQPRUREGGET';
MDAQPRUREGGET.SourceFiles = {'mdaqpru.c','pru.c'};
MDAQPRUREGGET.IncPaths = {'mdaq'};
MDAQPRUREGGET.SrcPaths = {'mdaq'};
MDAQPRUREGGET.StartFcnSpec = 'PRUInit()';
MDAQPRUREGGET.OutputFcnSpec = 'PRURegGetStep(uint8 p1, uint32 y1[1])';
MDAQPRUREGGET.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQPRUREGGET.Options.supportsMultipleExecInstances = true;

% MEM Write
MDAQMEMWR = legacy_code('initialize');
MDAQMEMWR.SFunctionName = 'sfun_MDAQMEMRW';
MDAQMEMWR.SourceFiles = {'mdaqmemwr.c'};
MDAQMEMWR.IncPaths = {'mdaq'};
MDAQMEMWR.SrcPaths = {'mdaq'};
MDAQMEMWR.StartFcnSpec = 'MEMWRInit(uint32 p1, uint8 p2)';
MDAQMEMWR.OutputFcnSpec = 'MEMWRStep(single u1[], uint8 p2)';
MDAQMEMWR.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQMEMWR.Options.supportsMultipleExecInstances = true;

%% MEM Read
MDAQMEMRD = legacy_code('initialize');
MDAQMEMRD.SFunctionName = 'sfun_MDAQMEMRD';
% MDAQMEMWR.HeaderFiles = {'mdaqenc.h'};
MDAQMEMRD.SourceFiles = {'mdaqmemrd.c'};
MDAQMEMRD.IncPaths = {'mdaq'};
MDAQMEMRD.SrcPaths = {'mdaq'};
MDAQMEMRD.StartFcnSpec = 'MEMRDInit(uint32 p1, uint8 p2 )';
MDAQMEMRD.OutputFcnSpec = 'MEMRDStep(single y1[p2], uint8 p2)';
MDAQMEMRD.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQMEMRD.Options.supportsMultipleExecInstances = true;

%% MOTOR
MDAQMOTOR = legacy_code('initialize');
MDAQMOTOR.SFunctionName = 'sfun_MDAQMOTOR';
MDAQMOTOR.HeaderFiles = {'mdaqmotor.h'};
MDAQMOTOR.SourceFiles = {'mdaqmotor.c','pru.c'};
MDAQMOTOR.IncPaths = {'mdaq'};
MDAQMOTOR.SrcPaths = {'mdaq'};
MDAQMOTOR.StartFcnSpec = 'MOTORInit(uint8 p1, uint8 p2, uint8 p3)';
MDAQMOTOR.OutputFcnSpec = 'MOTORStep(uint8 p1, uint8 u1, uint8 u2, uint32 u3)';
MDAQMOTOR.TerminateFcnSpec = 'MOTORTerminate(uint8 p1)';
MDAQMOTOR.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQMOTOR.Options.supportsMultipleExecInstances = true;

% Digital IO set 
MDAQDIOSET = legacy_code('initialize');
MDAQDIOSET.SFunctionName = 'sfun_MDAQDIOSET';
MDAQDIOSET.HeaderFiles = {'mdaqdio.h'};
MDAQDIOSET.SourceFiles = {'mdaqdio.c', 'mdaq_dio.c','gpio.c'};
MDAQDIOSET.IncPaths = {'mdaq'};
MDAQDIOSET.SrcPaths = {'mdaq'};
MDAQDIOSET.StartFcnSpec = 'DIOInit(uint8 p1, uint8 p2, uint8 p3)';
MDAQDIOSET.OutputFcnSpec = 'DIOSetStep(uint8 p1, uint8 u1)';
MDAQDIOSET.TerminateFcnSpec = 'DIOSetTerminate(uint8 p1, uint8 p4)';
MDAQDIOSET.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQDIOSET.Options.supportsMultipleExecInstances = true;

% Digital IO get 
MDAQDIOGET = legacy_code('initialize');
MDAQDIOGET.SFunctionName = 'sfun_MDAQDIOGET';
MDAQDIOGET.HeaderFiles = {'mdaqdio.h'};
MDAQDIOGET.SourceFiles = {'mdaqdio.c','mdaq_dio.c','gpio.c'};
MDAQDIOGET.IncPaths = {'mdaq'};
MDAQDIOGET.SrcPaths = {'mdaq'};
MDAQDIOGET.StartFcnSpec = 'DIOInit(uint8 p1, uint8 p2, uint8 p3)';
MDAQDIOGET.OutputFcnSpec = 'DIOGetStep(uint8 p1, uint8 y1[1])';
MDAQDIOGET.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQDIOGET.Options.supportsMultipleExecInstances = true;

% Function key 
MDAQFNCKEY = legacy_code('initialize');
MDAQFNCKEY.SFunctionName = 'sfun_MDAQFNCKEY';
MDAQFNCKEY.HeaderFiles = {'mdaqdio.h'};
MDAQFNCKEY.SourceFiles = {'mdaqdio.c','mdaq_dio.c','gpio.c'};
MDAQFNCKEY.IncPaths = {'mdaq'};
MDAQFNCKEY.SrcPaths = {'mdaq'};
MDAQFNCKEY.StartFcnSpec = 'DIOFncKeyInit(uint8 p1)';
MDAQFNCKEY.OutputFcnSpec = 'DIOFncKeyStep(uint8 p1, uint8 y1[1])';
MDAQFNCKEY.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQFNCKEY.Options.supportsMultipleExecInstances = true;

% UART Config 
MDAQUARTCONF = legacy_code('initialize');
MDAQUARTCONF.SFunctionName = 'sfun_MDAQUARTCONF';
MDAQUARTCONF.HeaderFiles = {'mdaquart.h'};
MDAQUARTCONF.SourceFiles = {'mdaquart.c', 'mdaq_uart.c', 'rpc.c', 'utils.c'};
MDAQUARTCONF.IncPaths = {'mdaq'};
MDAQUARTCONF.SrcPaths = {'mdaq'};
MDAQUARTCONF.StartFcnSpec = 'UARTConfig(uint8 p1, uint8 p2, uint8 p3, uint8 p4, uint8 p5, uint8 p6)';
%%MDAQUARTCONF.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQUARTCONF.Options.supportsMultipleExecInstances = true;

% UART Send 
MDAQUARTSEND = legacy_code('initialize');
MDAQUARTSEND.SFunctionName = 'sfun_MDAQUARTSEND';
MDAQUARTSEND.HeaderFiles = {'mdaquart.h'};
MDAQUARTSEND.SourceFiles = {'mdaquart.c', 'mdaq_uart.c', 'rpc.c', 'utils.c'};
MDAQUARTSEND.IncPaths = {'mdaq'};
MDAQUARTSEND.SrcPaths = {'mdaq'};
MDAQUARTSEND.OutputFcnSpec = 'UARTSend(uint8 p1, uint8 u1[p2], uint8 p2)';
MDAQUARTSEND.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQUARTSEND.Options.supportsMultipleExecInstances = true;

% UART Receive 
MDAQUARTRECV = legacy_code('initialize');
MDAQUARTRECV.SFunctionName = 'sfun_MDAQUARTRECV';
MDAQUARTRECV.HeaderFiles = {'mdaquart.h'};
MDAQUARTRECV.SourceFiles = {'mdaquart.c', 'mdaq_uart.c', 'rpc.c', 'utils.c'};
MDAQUARTRECV.IncPaths = {'mdaq'};
MDAQUARTRECV.SrcPaths = {'mdaq'};
MDAQUARTRECV.OutputFcnSpec = 'UARTRecv(uint8 p1, uint8 y1[p2], int32 y2[1], uint8 p2, uint8 p3, uint8 p4, uint32 p5, uint8 p6)';
MDAQUARTRECV.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQUARTRECV.Options.supportsMultipleExecInstances = true;

% PWM
MDAQPWM = legacy_code('initialize');
MDAQPWM.SFunctionName = 'sfun_MDAQPWM';
MDAQPWM.HeaderFiles = {'mdaqpwm.h'};
MDAQPWM.SourceFiles = {'mdaqpwm.c', 'mdaq_pwm.c', 'ehrpwm.c', 'utils.c'};
MDAQPWM.IncPaths = {'mdaq'};
MDAQPWM.SrcPaths = {'mdaq'};
MDAQPWM.StartFcnSpec = 'PWMInit(uint8 p1, uint32 p2, uint8 p3)';
MDAQPWM.OutputFcnSpec = 'PWMStep(uint8 p1, double u1, double u2)';
MDAQPWM.TerminateFcnSpec = 'PWMTerminate(uint8 p1)';
MDAQPWM.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQPWM.Options.supportsMultipleExecInstances = true;

RCCONTROLLER = legacy_code('initialize');
RCCONTROLLER.SFunctionName = 'sfun_RCCONTROLLER';
RCCONTROLLER.HeaderFiles = {'rc_controller.h'};
RCCONTROLLER.SourceFiles = {'rc_controller.c', 'utils.c','pru.c', 'mdaq_dio.c', 'gpio.c'};
RCCONTROLLER.IncPaths = {'mdaq'};
RCCONTROLLER.SrcPaths = {'mdaq'};
RCCONTROLLER.StartFcnSpec = 'RCControllerInit(uint8 p1)';
RCCONTROLLER.OutputFcnSpec = 'RCControllerStep(uint8 p1, double y1[1], double y2[1], double y3[1], double y4[1] )';
RCCONTROLLER.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
RCCONTROLLER.Options.supportsMultipleExecInstances = true;

TOFILE = legacy_code('initialize');
TOFILE.SFunctionName = 'sfun_TOFILE';
TOFILE.HeaderFiles = {'mdaqfile.h'};
TOFILE.SourceFiles = {'mdaqfile.c', 'mdaq_file.c', 'rpc.c', 'utils.c'};
TOFILE.IncPaths = {'mdaq'};
TOFILE.SrcPaths = {'mdaq'};
TOFILE.StartFcnSpec = 'ToFileInit(int8 p1[], uint8 p2, uint32 p3, uint8 p4, uint8 p5)';
TOFILE.OutputFcnSpec = 'ToFileStep(double u1[], uint32 p3, uint8 p4, uint8 p5)';
TOFILE.TerminateFcnSpec = 'ToFileTerminate()';
TOFILE.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
TOFILE.Options.supportsMultipleExecInstances = true;

FROMFILE = legacy_code('initialize');
FROMFILE.SFunctionName = 'sfun_FROMFILE';
FROMFILE.HeaderFiles = {'mdaqfile.h'};
FROMFILE.SourceFiles = {'mdaqfile.c', 'mdaq_file.c', 'rpc.c', 'utils.c'};
FROMFILE.IncPaths = {'mdaq'};
FROMFILE.SrcPaths = {'mdaq'};
FROMFILE.StartFcnSpec = 'FromFileInit(int8 p1[], uint8 p2, uint32 p3, uint8 p4, uint8 p5)';
FROMFILE.OutputFcnSpec = 'FromFileStep(double y1[p4], uint32 p3, uint8 p4, uint8 p5)';
FROMFILE.TerminateFcnSpec = 'FromFileTerminate()';
FROMFILE.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
FROMFILE.Options.supportsMultipleExecInstances = true;

OUTSTREAM = legacy_code('initialize');
OUTSTREAM.SFunctionName = 'sfun_OUTSTREAM';
OUTSTREAM.HeaderFiles = {'mdaqstream.h'};
OUTSTREAM.SourceFiles = {'mdaqstream.c', 'mdaq_stream.c', 'utils.c'};
OUTSTREAM.IncPaths = {'mdaq'};
OUTSTREAM.SrcPaths = {'mdaq'};
OUTSTREAM.StartFcnSpec = 'OutStreamInit(uint8 p1, uint8 p2)';
OUTSTREAM.OutputFcnSpec = 'OutStreamStep(double u1[p2], uint8 p1, uint8 p2)';
OUTSTREAM.TerminateFcnSpec = 'OutStreamTerminate(uint8 p1)';
OUTSTREAM.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
OUTSTREAM.Options.supportsMultipleExecInstances = true;

%% TCP/UDP support
% UDP Send
MDAQUDPSEND = legacy_code('initialize');
MDAQUDPSEND.SFunctionName = 'sfun_MDAQUDPSEND';
MDAQUDPSEND.HeaderFiles = {'mdaqsocket.h'};
MDAQUDPSEND.SourceFiles = {'mdaq_net.c','mdaqsocket.c','rpc.c','utils.c'};
MDAQUDPSEND.IncPaths = {'mdaq'};
MDAQUDPSEND.SrcPaths = {'mdaq'};
MDAQUDPSEND.StartFcnSpec = 'SocketOpen(int8 p1[], int32 p2, uint8 p3, int32 p4, uint8 p5)';
MDAQUDPSEND.OutputFcnSpec = 'SocketSend(int8 p1[], int32 p2, uint8 u1[], uint32 p6)';
MDAQUDPSEND.TerminateFcnSpec = 'SocketClose(int8 p1[], int32 p2)';
MDAQUDPSEND.SampleTime = 'parameterized';
MDAQUDPSEND.Options.supportsMultipleExecInstances = true;

%%
% UDP Receive
MDAQUDPRECV = legacy_code('initialize');
MDAQUDPRECV.SFunctionName = 'sfun_MDAQUDPRECV';
MDAQUDPRECV.HeaderFiles = {'mdaqsocket.h'};
MDAQUDPRECV.SourceFiles = {'mdaq_net.c','mdaqsocket.c','rpc.c','utils.c'};
MDAQUDPRECV.IncPaths = {'mdaq'};
MDAQUDPRECV.SrcPaths = {'mdaq'};
MDAQUDPRECV.StartFcnSpec = 'SocketOpen(int8 p1[], int32 p2, uint8 p3, int32 p4, uint8 p5)';
MDAQUDPRECV.OutputFcnSpec = 'SocketRecv(int8 p1[], int32 p2, uint8 y1[p6], int32 y2[1], uint32 p6, uint8 p3)';
MDAQUDPRECV.TerminateFcnSpec = 'SocketClose(int8 p1[], int32 p2)';
MDAQUDPRECV.SampleTime = 'parameterized';
MDAQUDPRECV.Options.supportsMultipleExecInstances = true;

%% Put multiple registration files together
def = [MDAQLED(:);MDAQADC(:);MDAQDAC(:);MDAQQEP(:);MDAQENC(:);MDAQMEMWR(:);MDAQMEMRD(:);MDAQPRUREGGET(:);...
       MDAQPRUREGSET(:);MDAQMOTOR(:);MDAQDIOSET(:);MDAQDIOGET(:);MDAQFNCKEY(:);MDAQUARTCONF(:);MDAQUARTSEND(:);...
       MDAQUARTRECV(:);MDAQPWM(:);RCCONTROLLER(:);TOFILE(:);FROMFILE(:);OUTSTREAM(:);MDAQUDPSEND(:);MDAQUDPRECV(:)];

%% Legacy Code Tool
% Generate, compile and link S-function for simulation
legacy_code('generate_for_sim', def);
% Generate TLC file for Code Generation
legacy_code('sfcn_tlc_generate', def);
% Generate according Simulink Block
%legacy_code('slblock_generate', def);
% Generate rtwmakecfg.m file to automatically set up some build options
legacy_code('rtwmakecfg_generate', def);
