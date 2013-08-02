function sl_customization(cm)
% MicroDAQ Connectivity Config

cm.registerTargetInfo(@loc_createMDAQConfig);
%External mode
cm.ExtModeTransports.add('microdaq.tlc', 'MicroDAQ TCP/IP', 'ext_comm', 'Level1');

function config = loc_createMDAQConfig

config = rtw.connectivity.ConfigRegistry;
config.ConfigName = 'MicroDAQ connectivity using TCP/IP';
config.ConfigClass = 'microdaq.ConnectivityConfig';

% matching system target file
config.SystemTargetFile = {'microdaq.tlc'};

% matching template makefile
config.TemplateMakefile = {'microdaq.tmf'};

% matching hardware configuration
config.TargetHWDeviceType = {'Texas Instruments->C6000'};
