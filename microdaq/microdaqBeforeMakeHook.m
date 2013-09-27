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
end
 
