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
MDAQADC.SourceFiles = {'mdaqadc.c','mdaq_ain.c','ltc185x.c','spi.c','gpio.c','utils.c'};
MDAQADC.IncPaths = {'mdaq'};
MDAQADC.SrcPaths = {'mdaq'};
MDAQADC.StartFcnSpec = 'ADCInit(uint8 p1, uint8 p2, uint8 p3, uint8 p4)';
MDAQADC.OutputFcnSpec = 'ADCStep(uint8 p1, uint16 y1[1], single y2[1])';
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
MDAQDAC.StartFcnSpec = 'DACInit()';
MDAQDAC.OutputFcnSpec = 'DACStep(uint8 p1, uint16 u1)';
MDAQDAC.TerminateFcnSpec = 'DACTerminate(uint8 p1, uint16 p2)';
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
%% Put multiple registration files together
def = [MDAQLED(:);MDAQADC(:);MDAQDAC(:);MDAQQEP(:)];
%% Legacy Code Tool
% Generate, compile and link S-function for simulation
legacy_code('generate_for_sim', def);
% Generate TLC file for Code Generation
legacy_code('sfcn_tlc_generate', def);
% Generate according Simulink Block
%legacy_code('slblock_generate', def);
% Generate rtwmakecfg.m file to automatically set up some build options
legacy_code('rtwmakecfg_generate', def);