function microdaq_make_rtw_hook(hookMethod, modelName, rtwRoot, templateMakefile, buildOpts, buildArgs, buildInfo)
switch hookMethod
    case 'before_make'
        microdaqBeforeMakeHook(modelName,buildOpts,buildInfo);
    case 'after_make'
        microdaqAfterMakeHook(modelName);
end