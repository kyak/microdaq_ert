function lct_genblocks
%% LED
% Populate legacy_code structure with information
MDAQLED = legacy_code('initialize');
MDAQLED.SFunctionName = 'sfun_MDAQLED';
MDAQLED.HeaderFiles = {'mdaqled.h'};
MDAQLED.SourceFiles = {'mdaqled.c','gpio.c'};
MDAQLED.OutputFcnSpec = 'mdaqled_set(uint32 p1, uint8 u1)';
% Support calling from within For-Each subsystem
MDAQLED.Options.supportsMultipleExecInstances = true;
%% ADC
% Populate legacy_code structure with information
MDAQADC = legacy_code('initialize');
MDAQADC.SFunctionName = 'sfun_MDAQADC';
MDAQADC.HeaderFiles = {'mdaqadc.h'};
MDAQADC.SourceFiles = {'mdaqadc.c','mdaq-ain.c','ltc185x.c','spi.c','gpio.c','utils.c'};
MDAQADC.StartFcnSpec = 'ADCInit(uint8 p1, uint8 p2, uint8 p3, uint8 p4)';
MDAQADC.OutputFcnSpec = 'ADCStep(uint8 p1, uint16 y1[1], single y2[1])';
MDAQADC.SampleTime = 'parameterized';
% Support calling from within For-Each subsystem
MDAQADC.Options.supportsMultipleExecInstances = true;
%% Put multiple registration files together
def = [MDAQLED(:);MDAQADC(:)];
%% Legacy Code Tool
% Generate, compile and link S-function for simulation
legacy_code('generate_for_sim', def);
% Generate TLC file for Code Generation
legacy_code('sfcn_tlc_generate', def);
% Generate according Simulink Block
%legacy_code('slblock_generate', def);
% Generate rtwmakecfg.m file to automatically set up some build options
legacy_code('rtwmakecfg_generate', def);