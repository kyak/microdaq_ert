%% LED
% Populate legacy_code structure with information
MDAQLED = legacy_code('initialize');
MDAQLED.SFunctionName = 'sfun_MDAQLED';
MDAQLED.HeaderFiles = {'mdaqled.h'};
MDAQLED.SourceFiles = {'mdaqled.c','gpio.c'};
MDAQLED.OutputFcnSpec = 'mdaqled_set(uint32 p1, uint8 u1)';
% Support calling from within For-Each subsystem
MDAQLED.Options.supportsMultipleExecInstances = true;
%% Put multiple registration files together
def = [MDAQLED(:)];
%% Legacy Code Tool
% Generate, compile and link S-function for simulation
legacy_code('generate_for_sim', def);
% Generate TLC file for Code Generation
legacy_code('sfcn_tlc_generate', def);
% Generate according Simulink Block
%legacy_code('slblock_generate', def);
% Generate rtwmakecfg.m file to automatically set up some build options
legacy_code('rtwmakecfg_generate', def);