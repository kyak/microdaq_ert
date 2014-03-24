function mdaq_dsp_model_save()

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
fprintf('Connecting to MicroDAQ......'); 
result = calllib(mlinklib,'mlink_connect',TargetIP,4343,link_fd);
if result < 0
    calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);   
    fprintf(' FAILED!\nUnable to connect to MicroDAQ device, check your configuration!\n');
end

fprintf(' SUCCESS!\n'); 
fprintf('Saving DSP application on target\n'); 
% Unload MLink library
unloadlibrary(mlinklib);

