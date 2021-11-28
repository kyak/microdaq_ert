function microdaq_tc_refresh

%Make sure we are in the right directory
current_dir = cd(fileparts(mfilename('fullpath')));

%% Create a new configuration
tc = microdaq_tc;

%% Save the toolchain info to the .mat file
save(['microdaq_tc_',computer('arch'),'.mat'], 'tc');

%% Refresh customisations
RTW.TargetRegistry.getInstance('reset');

%% Return to directory
cd(current_dir)
