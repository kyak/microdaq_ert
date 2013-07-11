function microdaq_make_rtw_hook(hookMethod,modelName,~,~,~,~)
switch hookMethod
    case 'before_make'
        microdaqBeforeMakeHook(modelName);
    case 'after_make'
        microdaqAfterMakeHook(modelName);
end