function microdaq_download(modelName,makertwObj)

disp(['### Downloading ', modelName, ' to MicroDAQ...']);

TargetRoot = getpref('microdaq','TargetRoot');
CCSRoot = getpref('microdaq','CCSRoot');

%MLink is a:
% default download method and
% always used in PIL
downloadMethod = '"MLink"';
if (ischar(makertwObj)) %String 'PIL'
    outfile = modelName;
else
    outfile = [modelName, '.out'];
    % Check the MicroDAQ download method
    if verLessThan('matlab', '8.1')
        makertwObj = get_param(gcs, 'MakeRTWSettingsObject');
        makertwArgs = makertwObj.BuildInfo.BuildArgs;
    else
        % See R2013a Simulink Coder release notes.
        makertwObj = rtwprivate('get_makertwsettings',gcs,'BuildInfo');
        makertwArgs = makertwObj.BuildArgs;
    end

    for i=1:length(makertwArgs)
        if strcmp(makertwArgs(i).DisplayLabel,'MICRODAQ_DOWNLOAD_METHOD')
            downloadMethod = makertwArgs(i).Value;
        end
    end
end


if strcmp(downloadMethod,'"JTAG"')
    disp('### Using JTAG for download...');
    if isunix
        system(['LD_PRELOAD="',CCSRoot,'/ccs_base/DebugServer/bin/libti_xpcom.so" "',CCSRoot,'/ccs_base/scripting/examples/loadti/loadti.sh" -a -r ',...
            '-c "',TargetRoot,'/MicroDAQ.ccxml" ',...
            '"',outfile,'" 2> /dev/null']);
    else
        system(['"',CCSRoot,'/ccs_base/scripting/examples/loadti/loadti.bat" -a -r ',...
            '-c "',TargetRoot,'/MicroDAQ.ccxml" ',...
            '"',outfile,'"']);
    end
else
    disp('### Using MLink for download...');
    mlink_download(outfile,TargetRoot,0);
end
end
