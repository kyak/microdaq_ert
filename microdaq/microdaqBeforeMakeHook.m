function [ ] = microdaqBeforeMakeHook( modelName )

% Check the model if a target_paths.mk should be created
if (strcmp(get_param(modelName,'SystemTargetFile')  ,'microdaq.tlc') && ...
    strcmp(get_param(modelName,'TemplateMakefile')  ,'microdaq.tmf') && ...
    strcmp(get_param(modelName,'TargetHWDeviceType'),'Texas Instruments->C6000'))

    TargetRoot = getpref('microdaq','TargetRoot');
	CompilerRoot = getpref('microdaq','CompilerRoot');
    CCSRoot = getpref('microdaq','CCSRoot');
    XDCRoot = getpref('microdaq','XDCRoot');
    BIOSRoot = getpref('microdaq','BIOSRoot');
    
    % Create the target paths makefile
    makefileName = 'target_paths.mk';
    fid = fopen(makefileName,'w');
    fwrite(fid, sprintf('%s\n\n', '# MicroDAQ paths'));
    fwrite(fid, sprintf('CompilerRoot  = %s\n', CompilerRoot));
    fwrite(fid, sprintf('TargetRoot    = %s\n', TargetRoot));
    fwrite(fid, sprintf('CCSRoot       = %s\n', CCSRoot));
    fwrite(fid, sprintf('XDCRoot       = %s\n', XDCRoot));
    fwrite(fid, sprintf('BIOSRoot      = %s\n', BIOSRoot));
    fclose(fid);

    % Run XDC Tools on SYS/BIOS configuration file
    copyfile([TargetRoot,'/clock.cfg']);
    Ts = str2double(get_param(modelName,'FixedStep'));
    % Clock.tickPeriod is in microseconds
    if isnan(Ts)
        % 'auto' in model
        Ts = 0.2*1e6;
    else
        Ts = Ts*1e6;
    end
    fd = fopen('clock.cfg','a');
    fprintf(fd,'Clock.tickPeriod = %s;',num2str(Ts));
    fclose(fd);
    syscmd = [XDCRoot,'/xs --xdcpath="',BIOSRoot,'/packages;',CCSRoot,...
        'ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p ti.platforms.evmOMAPL137 -r release -c "',...
        CompilerRoot,'" --compileOptions "-g --optimize_with_debug" clock.cfg'];
    system(syscmd);
end
 
