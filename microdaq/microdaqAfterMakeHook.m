function [ ] = microdaqAfterMakeHook( modelName )
% Check the model if a target_paths.mk should be created
if (strcmp(get_param(modelName,'SystemTargetFile')  ,'microdaq.tlc') && ...
    strcmp(get_param(modelName,'TemplateMakefile')  ,'microdaq.tmf') && ...
    strcmp(get_param(modelName,'TargetHWDeviceType'),'Texas Instruments->C6000'))
  
    % Check if user chose to Download to MicroDAQ in Settings
    if verLessThan('matlab', '8.1')
        makertwObj = get_param(modelName, 'MakeRTWSettingsObject');
        makertwArgs = makertwObj.BuildInfo.BuildArgs;
    else
        % See R2013a Simulink Coder release notes.
        makertwObj = rtwprivate('get_makertwsettings',modelName,'BuildInfo');
        makertwArgs = makertwObj.BuildArgs;
    end
    
    downloadToMicroDAQ = 1;
    for i=1:length(makertwArgs)
        if strcmp(makertwArgs(i).DisplayLabel,'MICRODAQ_DOWNLOAD')
            downloadToMicroDAQ = str2double(makertwArgs(i).Value);
        end
    end
    
    % allow a back door for tests to skip download to hardware
    if evalin('base','exist(''downloadToMicroDAQ'')')
        downloadToMicroDAQ = evalin('base', 'downloadToMicroDAQ' );
    end
    
    if ~i_isPilSim && ~i_isModelReferenceBuild(modelName) &&...
            downloadToMicroDAQ
        microdaq_download(modelName,makertwObj)
    end

end

end

function isPilSim = i_isPilSim
    s = dbstack;
    isPilSim = false;
    for i=1:length(s)
        if strfind(s(i).name,'build_pil_target')
            isPilSim=true;
            break;
        end
    end
end
    
function isMdlRefBuild = i_isModelReferenceBuild(modelName)
    mdlRefTargetType = get_param(modelName, 'ModelReferenceTargetType');
    isMdlRefBuild = ~strcmp(mdlRefTargetType, 'NONE');
end