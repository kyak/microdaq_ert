% function uses MLink to upload data to MicroDAQ memory
% exampe: mdaq_mem_upload(hex2dec('c200000', data, 'single')

function mdaq_mem_upload(address, user_data, data_type)
data_type_size = 0;
if strcmp(data_type, 'double') == 1
    data_type_size = 8;    
end

if strcmp(data_type, 'single') == 1
    data_type_size = 4;    
end

if data_type_size == 0
    error('Wrong data type, use single or double');
end

[row_count, col_count] = size(user_data);

if col_count > 1 
    error('You can upload data only in one column!');
end

if row_count < 1 
    error('No data to upload!');
end

len =  row_count; 

if len < 1
    error('Data count should be grater than 0!');
end

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
%disp('### Connecting to MicroDAQ...');
result = calllib(mlinklib,'mlink_connect',TargetIP,4343,link_fd);
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error connecting to MicroDAQ: %s',out);
end

% Open memory location
result = calllib(mlinklib,'mlink_mem_open',link_fd, address,len*data_type_size );
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error during MicroDAQ memory access %s',out);
end

% Read DSP memory from specified address
% data_init = int8(zeros(len*data_type_size, 1')); % preallocate buffer of len
user_data_cast = typecast(user_data, 'int8');
dsp_ptr = libpointer('int8Ptr', user_data_cast); % data_ptr is a pointer to data 
result = calllib(mlinklib,'mlink_mem_set',link_fd, address, dsp_ptr, len*data_type_size );
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error during MicroDAQ memory access %s',out);
end

% Close memory location
result = calllib(mlinklib,'mlink_mem_close',link_fd, address, len*data_type_size );
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error during MicroDAQ memory access %s',out);
end

result = calllib(mlinklib,'mlink_disconnect',link_fd.Value );
if result < 0
    out = calllib(mlinklib,'mlink_error',result);
    unloadlibrary(mlinklib);
    error('Error during disconnecting %s',out);
end

% Unload MLink library
unloadlibrary(mlinklib);
