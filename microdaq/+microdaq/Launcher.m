classdef Launcher < rtw.connectivity.Launcher
%MicroDAQ class for launching a PIL application

    methods
        % constructor
        function this = Launcher(componentArgs, builder)
            narginchk(2, 2);
            % call super class constructor
            this@rtw.connectivity.Launcher(componentArgs, builder);
        end

        % destructor
        function delete(this) %#ok
        end

        % Start the application
        function startApplication(this)
            % get name of the executable file
            exe = this.getBuilder.getApplicationExecutable; 
            % allow a back door for tests to skip download to hardware
            downloadToMicroDAQ = 1;
            if evalin('base','exist(''downloadToMicroDAQ'')')
                downloadToMicroDAQ = evalin('base', 'downloadToMicroDAQ' );
            end
            if downloadToMicroDAQ
                microdaq_download(exe,'PIL');
            else
                %error('Skipped download to MicroDAQ, therefore not starting PIL simulation');
            end
			disp('### Starting PIL execution on MicroDAQ');
        end

        % Stop the application
        function stopApplication(~)
            disp('### Stopping PIL execution on MicroDAQ')
        end
    end
end
