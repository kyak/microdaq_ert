function mlink_download(outfile,TargetRoot)
% MLink library name
if ispc
    arch = computer('arch');
    suffix = arch(end-1:end);
    mlinklib = ['MLink',suffix];
else
    mlinklib = 'libmlink64';
end
% Load MLink library
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
disp('### Loading DSP binary to MicroDAQ...');
result = calllib(mlinklib,'mlink_dsp_load',link_fd.Value,outfile,'');
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error loading binary to MicroDAQ: %s',out);
end
% Start DSP binary on MicroDAQ
disp('### Starting DSP binary on MicroDAQ...');
result = calllib(mlinklib,'mlink_dsp_start',link_fd.Value);
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error starting binary on MicroDAQ: %s',out);
end
% Unload MLink library
unloadlibrary(mlinklib);