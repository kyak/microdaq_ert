classdef TargetApplicationFramework < rtw.pil.RtIOStreamApplicationFramework
%MicroDAQ application framework for PIL
  
    methods
        % constructor
        function this = TargetApplicationFramework(componentArgs)
            error(nargchk(1, 1, nargin, 'struct'));
            % call super class constructor
            this@rtw.pil.RtIOStreamApplicationFramework(componentArgs);

            % TODO rtIOStreamClose is never called at the of simulation.
            % Use shipping PIL main when some day the bug is fixed.
            % this.addPILMain('target');

            % Additional source and library files to include in the build
            % must be added to the BuildInfo property

            % Get the BuildInfo object to update
            buildInfo = this.getBuildInfo;

            % Add device driver files to implement the target-side of the
            % host-target rtIOStream communications channel
            buildInfo.addSourceFiles('pil_main.c',...
				fullfile(getpref('microdaq','TargetRoot'),'rtiostream'));
            buildInfo.addSourceFiles('rtiostreamtgt.c',...
				fullfile(getpref('microdaq','TargetRoot'),'rtiostream'));
            buildInfo.addIncludePaths(...
                fullfile(getpref('microdaq','TargetRoot'),'..','blocks','mdaq'));
        end
    end
end
