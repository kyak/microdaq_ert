function microdaq_setup()

cd microdaq;
curpath = pwd;
tgtpath = curpath(1:end-length('/microdaq'));
addpath(fullfile(tgtpath, 'microdaq'));
addpath(fullfile(tgtpath, 'demos'));
addpath(fullfile(tgtpath, 'blocks'));
addpath(fullfile(tgtpath, 'microdaq','ext_mode'));
addpath(fullfile(tgtpath, 'tools'));
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
disp('<strong>Generating blocks for MicroDAQ</strong>'); 
cd('../blocks');
lct_genblocks;
cd(curpath);

disp('<strong>Building TI SYS/BIOS real-time operating system for MicroDAQ</strong>'); 
% Fixes errors related to java on some systems
if ispc
	setenv('PATH',[getenv('PATH'),';',fullfile(getpref('microdaq','XDCRoot'),'jre','bin')]);
end

% Run XDC Tools on SYS/BIOS configuration file
cd('sysbios');
% Remove old SYS/BIOS, if existing
if isdir(fullfile(pwd,'configPkg'))
    rmdir('configPkg','s');
end
if isdir(fullfile(pwd,'src'))
    rmdir('src','s');
end
syscmd = [XDCRoot,'/xs --xdcpath="',BIOSRoot,'/packages;',CCSRoot,...
'/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p ti.platforms.evmOMAPL137 -r release -c "',...
CompilerRoot,'" --compileOptions "-g --optimize_with_debug" ','sysbios.cfg'];
system(syscmd);

% Append extra linker section to main linker script 
extra_linker_file_fd = fopen('sysbios_linker.cmd', 'r');
if extra_linker_file_fd > -1
    cd('configPkg'); 
    linker_file_fd = fopen('linker.cmd', 'a');
    if linker_file_fd > -1
        tmp = fread(extra_linker_file_fd, Inf, '*uchar');
        fwrite(linker_file_fd, tmp, 'uchar');
        fclose(extra_linker_file_fd);
        fclose(linker_file_fd);   
    else
        fclose(extra_linker_file_fd);
    end
end

cd(curpath);

% Generate help
%cd('../help/source');
%genhelp;
%cd(curpath);

sl_refresh_customizations;
rehash toolbox;
disp('<strong>MicroDAQ Target setup is complete!</strong>');
disp('Explore <a href="matlab:cd([getpref(''microdaq'',''TargetRoot''),''/../demos''])">demos</a> directory and access <a href="matlab:doc -classic">documentation</a>');
cd([getpref('microdaq','TargetRoot'),'/../demos']);
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
