function microdaq_setup()

curpath = pwd;
tgtpath = curpath(1:end-length('/microdaq'));
addpath(fullfile(tgtpath, 'microdaq'));
addpath(fullfile(tgtpath, 'demos'));
addpath(fullfile(tgtpath, 'blocks'));
% addpath(fullfile(tgtpath, 'help'));
savepath;
if ispref('microdaq')
	rmpref('microdaq');
end
addpref('microdaq','TargetRoot',fix_slash(curpath));
[CCSRoot, CompilerRoot, XDCRoot, BIOSRoot] = ccs_setup_paths;
addpref('microdaq','CCSRoot',CCSRoot);
addpref('microdaq','CompilerRoot',CompilerRoot);
addpref('microdaq','XDCRoot',XDCRoot);
addpref('microdaq','BIOSRoot',BIOSRoot);
% Ask for Target IP
tip = inputdlg('Enter MicroDAQ IP address:','MicroDAQ IP Address',1,{'10.10.1.1'});
addpref('microdaq','TargetIP',tip{1});

% Generate blocks
cd('../blocks');
lct_genblocks;
cd(curpath);
% Generate help
%cd('../help/source');
%genhelp;
%cd(curpath);
% External mode support
% cd(matlabroot);
% if isunix
%     mexcmd = ['rtw/ext_mode/common/ext_comm.c '...
%         'rtw/ext_mode/common/ext_convert.c '...
%         'rtw/ext_mode/serial/ext_serial_transport.c '...
%         'rtw/ext_mode/serial/ext_serial_pkt.c '...
%         'rtw/ext_mode/serial/rtiostream_serial_interface.c '...
%         'rtw/ext_mode/common/ext_util.c '...
%         '-Irtw/c/src -Irtw/c/src/rtiostream/utils '...
%         '-Irtw/c/src/ext_mode/common '...
%         '-Irtw/c/src/ext_mode/serial -Irtw/ext_mode/common '...
%         '-Irtw/ext_mode/common/include '...
%         '-lmwrtiostreamutils '...
%         '-DEXTMODE_SERIAL_TRANSPORT -DSL_EXT_SO '...
%         '-output ',fullfile(curpath,'../blocks'),'/ext_stellaris_serial'];
% else
%         mexcmd = ['rtw\ext_mode\common\ext_comm.c '...
%         'rtw\ext_mode\common\ext_convert.c '...
%         'rtw\ext_mode\serial\ext_serial_transport.c '...
%         'rtw\ext_mode\serial\ext_serial_pkt.c '...
%         'rtw\ext_mode\serial\rtiostream_serial_interface.c '...
%         'rtw\ext_mode\common\ext_util.c '...
%         '-Irtw\c\src -Irtw\c\src\rtiostream\utils '...
%         '-Irtw\c\src\ext_mode\common '...
%         '-Irtw\c\src\ext_mode\serial -Irtw\ext_mode\common '...
%         '-Irtw\ext_mode\common\include '...
%         '-lmwrtiostreamutils '...
%         '-DEXTMODE_SERIAL_TRANSPORT -DSL_EXT_DLL '...
%         '-output ',fullfile(curpath,'..\blocks'),'\ext_stellaris_serial'];
% end
% eval(['mex ',mexcmd]);
% cd(curpath);
% 
% sl_refresh_customizations;
disp('<strong>MicroDAQ</strong> Target setup is complete!');
disp('Explore <a href="matlab:cd([getpref(''microdaq'',''TargetRoot''),''/../demos''])">demos</a> directory and access <a href="matlab:doc -classic">documentation</a>');
end

function [CCSRoot, CompilerRoot, XDCRoot, BIOSRoot] = ccs_setup_paths()
	% TODO: make it foolproof
    CCSRoot = fix_slash(uigetdir(matlabroot,'CCS root directory: (the one with ccs_base, tools ...)'));
    CompilerRoot = fix_slash(uigetdir(CCSRoot,'CCS Compiler root directory: (tools/compiler/c6000_7.X.X)'));
    XDCRoot = fix_slash(uigetdir(fileparts(CCSRoot),'XDC Tools root directory: (xdctools_X_XX_XX_XX)'));
    BIOSRoot = fix_slash(uigetdir(fileparts(CCSRoot),'SYS/BIOS root directory: (bios_6_XX_XX_XX)'));
end

function path = fix_slash(path0)
path = path0;
if ispc
    path(path=='\')='/';
end
end
