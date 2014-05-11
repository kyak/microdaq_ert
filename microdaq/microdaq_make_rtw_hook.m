function microdaq_make_rtw_hook(hookMethod,modelName,~,~,buildOpts,~)
switch hookMethod
    case 'before_make'
        microdaqBeforeMakeHook(modelName,buildOpts);
    case 'after_make'
        microdaqAfterMakeHook(modelName);
end