function [ ] = microdaqBeforeMakeHook( modelName, buildOpts )

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
    % Use target paths makefile to pass information about sample time
    Ts = str2double(get_param(modelName,'FixedStep'));
    % User timer is in microseconds
    if isnan(Ts)
        % 'auto' in model
        Ts = 0.2*1e6;
    else
        Ts = Ts*1e6;
    end
    fprintf(fid,'SAMPLE_TIME = %s\n',num2str(Ts));
    fclose(fid);
    if buildOpts.codeWasUpToDate
        % Perform hook actions for up to date model
    else
        % Perform hook actions for full code generation
        % Force rebuild of static external mode main (ext_main.c)
        if exist('ext_main.o','file')
            delete('ext_main.o');
        end
    end
end
