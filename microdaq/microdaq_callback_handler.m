function microdaq_callback_handler(hDlg, hSrc)

% Setup the hardware configuration
slConfigUISetVal(hDlg, hSrc, 'ProdHWDeviceType', 'Texas Instruments->C6000');
        
% Set the target language to C and disable modification
slConfigUISetVal(hDlg, hSrc, 'TargetLang', 'C');
slConfigUISetEnabled(hDlg, hSrc, 'TargetLang', 0);

% The target is model reference compliant
slConfigUISetVal(hDlg, hSrc, 'ModelReferenceCompliant', 'on');
slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceCompliant', false); 

% Configure solver
slConfigUISetVal(hDlg, hSrc, 'SolverType', 'Fixed-step');
slConfigUISetVal(hDlg, hSrc, 'Solver', 'FixedStepDiscrete');
slConfigUISetVal(hDlg, hSrc, 'SolverMode', 'SingleTasking');

% Use our own ert_main.c and disable this option at all
slConfigUISetVal(hDlg, hSrc, 'ERTCustomFileTemplate', 'microdaq_main.tlc');
slConfigUISetVal(hDlg, hSrc, 'GenerateSampleERTMain', 'off');
slConfigUISetEnabled(hDlg, hSrc, 'GenerateSampleERTMain',0);

% Use shipping Code Replacement Library for C674x
slConfigUISetVal(hDlg, hSrc, 'CodeReplacementLibrary', 'TI C674x');

% Configure PostCodeGen Command to execute
slConfigUISetVal(hDlg, hSrc, 'PostCodeGenCommand', 'microdaq_postcodegen(buildInfo)');

% External Mode default settings
slConfigUISetVal(hDlg, hSrc, 'ExtModeMexArgs', 'getpref(''microdaq'',''TargetIP'') 1 4344');
slConfigUISetVal(hDlg, hSrc, 'ExtModeStaticAlloc', 'On');
slConfigUISetVal(hDlg, hSrc, 'ExtModeStaticAllocSize', '10485760');