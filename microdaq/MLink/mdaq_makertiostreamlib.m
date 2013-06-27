function mdaq_makertiostreamlib
% Compile and link librtiostreamhst.dll/.so libraries for PIL

%For testing.
%rtiostream_wrapper([pwd,'/librtiostreamhst.so'],'unloadlibrary')
%rtiostream_wrapper([pwd,'/librtiostreamhst.dll'],'unloadlibrary')
if isunix
    mex('-c','CFLAGS=$CFLAGS -Wall -fPIC',['-I',fullfile(matlabroot,'rtw','c','src')],'rtiostreamhst.c');
    mex('LDFLAGS=-shared','CLIBS=','LDEXTENSION=.so',...
        '-output','librtiostreamhst.so','rtiostreamhst.o','libmlink64.a');
    delete('rtiostreamhst.o');
else
    arch = computer('arch');
    suffix = arch(end-1:end);
    mlinklib = ['MLink',suffix,'.lib'];
    mex('-c','COMPFLAGS=$COMPFLAGS -Wall',['-I',fullfile(matlabroot,'rtw','c','src')],'rtiostreamhst.c');
    mex('LINKFLAGS=/DLL','MEX_EXT=.dll',...
        'POSTLINK_CMDS=','POSTLINK_CMDS1=','POSTLINK_CMDS2=','POSTLINK_CMDS3=',...
        'NAME_OUTPUT=/out:librtiostreamhst.dll',...
        '-output','librtiostreamhst.dll','rtiostreamhst.obj',mlinklib,'ws2_32.lib','winmm.lib');
    delete('rtiostreamhst.obj','librtiostreamhst.exp','librtiostreamhst.lib');
end
