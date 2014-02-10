function mdaq_pru_exec(pru_firmware)

% MLink library name
if ispc
    arch = computer('arch');
    suffix = arch(end-1:end);
    mlinklib = ['MLink',suffix];
else
    mlinklib = 'libmlink64';
end
% Load MLink library
TargetRoot = getpref('microdaq','TargetRoot');
loadlibrary([TargetRoot,'/MLink/',mlinklib],[TargetRoot,'/MLink/MLink.h']);
%libfunctionsview mlinklib
% Pointer to link fd
link_fd = libpointer('int32Ptr',0);
% Connect to MicroDAQ
TargetIP = getpref('microdaq','TargetIP');
disp('### Connecting to MicroDAQ...');
result = calllib(mlinklib,'mlink_connect',TargetIP,4343,link_fd);
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error connecting to MicroDAQ: %s',out);
end
% Load DSP binary to MicroDAQ
disp('### Executing PRU firmware on MicroDAQ...');
result = calllib(mlinklib,'mlink_pru_exec',link_fd.Value,pru_firmware,1);
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error executing PRU firmware on MicroDAQ: %s',out);
end
% Unload MLink library
unloadlibrary(mlinklib);
