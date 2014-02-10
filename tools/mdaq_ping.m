% This function test if MicroDAQ is connected  
function mdaq_con_test()

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
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    
    fprintf(' FAILED!\nUnable to connect to MicroDAQ device, check your configuration!\n');
    fprintf('Simulink is configured to connect to MicroDAQ with following settings:\n');
    fprintf('IP address: %s, port %d\n', TargetIP, 4343); 
    fprintf('If MicroDAQ has different IP address use mdaq_ip_set to set correct address.\n\n'); 
    error('Error during connecting to MicroDAQ device %s',out);
end

fprintf(' SUCCESS!\n'); 
result = calllib(mlinklib,'mlink_disconnect',link_fd.Value );
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error during disconnecting %s',out);
end

% Unload MLink library
unloadlibrary(mlinklib);

