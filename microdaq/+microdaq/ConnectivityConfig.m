classdef ConnectivityConfig < rtw.connectivity.Config
%MicroDAQ PIL configuration class

    methods
        % Constructor
        function this = ConnectivityConfig(componentArgs)
            
            % An executable framework specifies additional source files and
            % libraries required for building the PIL executable
            targetApplicationFramework = ...
                microdaq.TargetApplicationFramework(componentArgs);
            
            % Filename extension for executable on the target system
            exeExtension = '.out';
            
            % Create an instance of MakefileBuilder; this works in
            % conjunction with our template makefile to build the PIL
            % executable
            builder = rtw.connectivity.MakefileBuilder(componentArgs, ...
                targetApplicationFramework, ...
                exeExtension);
            
            % Launcher
            launcher = microdaq.Launcher(componentArgs, builder);
            
            % File extension for shared libraries (e.g. .dll on Windows)
            sharedLibExt=system_dependent('GetSharedLibExt'); 
            
            % Evaluate name of the rtIOStream shared library
            if ispc
                libname = 'libmwrtiostreamtcpip';
            else
                libname = 'libmwrtiostreamtcpip';
            end
            rtiostreamLib = [libname sharedLibExt];
            
            hostCommunicator = microdaq.Communicator(...
                componentArgs, ...
                launcher, ...
                rtiostreamLib);
            
            % For some targets it may be necessary to set a timeout value
            % for initial setup of the communications channel. For example,
            % the target processor may take a few seconds before it is
            % ready to open its side of the communications channel. If a
            % non-zero timeout value is set then the communicator will
            % repeatedly try to open the communications channel until the
            % timeout value is reached.
            hostCommunicator.setInitCommsTimeout(0);
            
            % Configure a timeout period for reading of data by the host 
            % from the target. If no data is received with the specified 
            % period an error will be thrown.
            timeoutReadDataSecs = 30;
            hostCommunicator.setTimeoutRecvSecs(timeoutReadDataSecs);
            
            % Set up IP address used for PIL communication
            TargetIP = getpref('microdaq','TargetIP');

            % Custom arguments that will be passed to the              
            % rtIOStreamOpen function in the rtIOStream shared        
            % library (this configures the host-side of the           
            % communications channel)                                  
            rtIOStreamOpenArgs = {...
                '-hostname', TargetIP,...
                '-client', '1', ...
                '-port', '4344',...
                };
            
            hostCommunicator.setOpenRtIOStreamArgList(...          
                rtIOStreamOpenArgs); 
            
            % call super class constructor to register components
            this@rtw.connectivity.Config(componentArgs,...
                                         builder,...
                                         launcher,...
                                         hostCommunicator);
            
            % Register a hardware-specific timer. Registering the timer
            % enables the code execution profiling feature.
            if verLessThan('matlab', '8.3')
                % For releases prior to R2014a, use coder.profile.Timer class
                timer = microdaq.Timer;
                this.setTimer(timer)
            else
                % Otherwise, use microdaq_timer.m code replacement library
                this.setTimer(microdaq_timer)
            end
            
        end
    end
end
