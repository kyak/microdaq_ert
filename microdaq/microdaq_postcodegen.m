function microdaq_postcodegen(buildInfo)

makertwArgs = buildInfo.BuildArgs;

for i=1:length(makertwArgs)
    if strcmp(makertwArgs(i).DisplayLabel,'EXT_MODE')
        externalMode = str2double(makertwArgs(i).Value);
    end
end

% See comments in microdaq_main.tlc as to why i'm doing this
if (externalMode == 1)
    buildInfo.addSourceFiles('ext_main.c',fullfile(getpref('microdaq','TargetRoot'),'ext_mode','target'),'CustomCode');
end