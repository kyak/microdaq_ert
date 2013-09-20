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
% Populate legacy_code structure with information
MDAQADC = legacy_code('initialize');
MDAQADC.SFunctionName = 'sfun_MDAQADC';
MDAQADC.HeaderFiles = {'mdaqadc.h'};
MDAQADC.SourceFiles = {'mdaqadc.c','mdaq_ain.c','ltc185x.c','ads8568.c','spi.c','gpio.c','utils.c'};
MDAQADC.IncPaths = {'mdaq'};
MDAQADC.SrcPaths = {'mdaq'};
MDAQADC.StartFcnSpec = 'ADCInit(uint8 p1, uint8 p2[], uint8 p3, uint8 p4, uint8 p5, uint8 p6)';
MDAQADC.OutputFcnSpec = 'ADCStep(uint16 y1[p3], double y2[p3], uint8 p3)';
MDAQADC.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQADC.Options.supportsMultipleExecInstances = true;
%% DAC
% Populate legacy_code structure with information
MDAQDAC = legacy_code('initialize');
MDAQDAC.SFunctionName = 'sfun_MDAQDAC';
MDAQDAC.HeaderFiles = {'mdaqdac.h'};
MDAQDAC.SourceFiles = {'mdaqdac.c','mdaq_aout.c','dac7568.c','spi.c','gpio.c','utils.c'};
MDAQDAC.IncPaths = {'mdaq'};
MDAQDAC.SrcPaths = {'mdaq'};
MDAQDAC.StartFcnSpec = 'DACInit(uint8 p1, uint8 p2[], uint8 p3, uint8 p4, uint8 p5 )';
MDAQDAC.OutputFcnSpec = 'DACStep(double u1[p3], uint8 p3)';
MDAQDAC.TerminateFcnSpec = 'DACTerminate(single p7[], uint8 p3, uint8 p6 )';
MDAQDAC.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQDAC.Options.supportsMultipleExecInstances = true;
%% QEP
% Populate legacy_code structure with information
MDAQQEP = legacy_code('initialize');
MDAQQEP.SFunctionName = 'sfun_MDAQQEP';
MDAQQEP.HeaderFiles = {'mdaqenc.h'};
MDAQQEP.SourceFiles = {'mdaqenc.c','eqep.c','utils.c'};
MDAQQEP.IncPaths = {'mdaq'};
MDAQQEP.SrcPaths = {'mdaq'};
MDAQQEP.StartFcnSpec = 'ENCInit(uint8 p1)';
MDAQQEP.OutputFcnSpec = 'ENCStep(uint8 p1, int32 y1[1])';
MDAQQEP.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQQEP.Options.supportsMultipleExecInstances = true;
% PRU REG GET
% Populate legacy_code structure with information
MDAQPRUREGSET = legacy_code('initialize');
MDAQPRUREGSET.SFunctionName = 'sfun_MDAQPRUREGSET';
MDAQPRUREGSET.SourceFiles = {'mdaqpru.c'};
MDAQPRUREGSET.IncPaths = {'mdaq'};
MDAQPRUREGSET.SrcPaths = {'mdaq'};
MDAQPRUREGSET.StartFcnSpec = 'PRUInit()';
MDAQPRUREGSET.OutputFcnSpec = 'PRURegSetStep(uint8 p1, uint32 u1)';
MDAQPRUREGSET.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQPRUREGSET.Options.supportsMultipleExecInstances = true;
% PRU REG SET
% Populate legacy_code structure with information
MDAQPRUREGGET = legacy_code('initialize');
MDAQPRUREGGET.SFunctionName = 'sfun_MDAQPRUREGGET';
MDAQPRUREGGET.SourceFiles = {'mdaqpru.c'};
MDAQPRUREGGET.IncPaths = {'mdaq'};
MDAQPRUREGGET.SrcPaths = {'mdaq'};
MDAQPRUREGGET.StartFcnSpec = 'PRUInit()';
MDAQPRUREGGET.OutputFcnSpec = 'PRURegGetStep(uint8 p1, uint32 y1[1])';
MDAQPRUREGGET.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQPRUREGGET.Options.supportsMultipleExecInstances = true;
% MEM Write
% Populate legacy_code structure with information
MDAQMEMWR = legacy_code('initialize');
MDAQMEMWR.SFunctionName = 'sfun_MDAQMEMRW';
% MDAQMEMWR.HeaderFiles = {'mdaqenc.h'};
MDAQMEMWR.SourceFiles = {'mdaqmemwr.c'};
MDAQMEMWR.IncPaths = {'mdaq'};
MDAQMEMWR.SrcPaths = {'mdaq'};
MDAQMEMWR.StartFcnSpec = 'MEMWRInit(uint32 p1, uint8 p2)';
MDAQMEMWR.OutputFcnSpec = 'MEMWRStep(single u1[], uint8 p2)';
MDAQMEMWR.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQMEMWR.Options.supportsMultipleExecInstances = true;
%% MEM Read
% Populate legacy_code structure with information
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
%% Put multiple registration files together
def = [MDAQLED(:);MDAQADC(:);MDAQDAC(:);MDAQQEP(:);MDAQMEMWR(:);MDAQMEMRD(:);MDAQPRUREGGET(:);MDAQPRUREGSET(:)];
%% Legacy Code Tool
% Generate, compile and link S-function for simulation
legacy_code('generate_for_sim', def);
% Generate TLC file for Code Generation
legacy_code('sfcn_tlc_generate', def);
% Generate according Simulink Block
%legacy_code('slblock_generate', def);
% Generate rtwmakecfg.m file to automatically set up some build options
legacy_code('rtwmakecfg_generate', def);
