classdef ParametersMLink < coder.rtiostreamtest.Parameters
    %PARAMETERSMLINK MLink communication parameters for
    %use with rtiostreamtest
    %   Sets the parameters required for testing a rtiostream connection
    %   over MLink
    
    properties (GetAccess = 'public', SetAccess = 'private')
        ipaddr;
    end
    
    methods
        
        function this = ParametersMLink(ipaddr)
        % Initialize the rtiostream implementation with a specified
        % MicroDAQ IP address

        % TODO some sanity checks here
        % Assign for further usage
            this.ipaddr = ipaddr;
        end
        
        function [library, parameters] = getSharedLibrary(this)
            
            % Get the library
            library = [fullfile(...
                getpref('microdaq','TargetRoot'),'MLink','librtiostreamhst'),...
                system_dependent('GetSharedLibExt')];
            
            % Get the parameters
            parameters =  {'-ipaddr', this.ipaddr};
        end
    end
    
end

