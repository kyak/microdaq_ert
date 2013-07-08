
%   Copyright 2012 The MathWorks, Inc.

classdef Parameters
    %PARAMETERS	Contains parameters for conducting a test
    %with RTIOSTREAMTEST
    %
    %   Extend this class so that it provides the required initial
    %   parameters for setting up the library that would be used on the
    %   client side. Additional options could be specified for the
    %   different tests that would be performed. As a starting point you
    %   could also refer to the TCP, UDP and serial implementations that
    %   currently exist.
    %
    %   See also PARAMETERSTCP,
    %   PARAMETERSUDP, PARAMETERSSERIAL
    
    methods (Abstract)
        
        %[LIBRARY, PARAMETERS] = GETSHAREDLIBRARY Library initialization
        %
        %   LIBRARY    - The path to the library that would be used for
        %                the rtiostream implementation on the client side
        %                (MATLAB side)
        %   PARAMETERS - The parameters that would be passed to the
        %                library when it is initialized with rtiostreamopen
        [library, parameters] = getSharedLibrary(this)
        
    end
    
    methods (Access = protected)
        
        function parameters = getSymmetricParameters(~)
            %GETSYMMETRICPARAMETERS provide parameters for symmetric test
            %   For list of available parameter names, see SYMMETRICTEST
            %   PARAMETERS should be a cell array of name - value pairs.
            %   Example: PARAMETERS = {'arg1', [1 2 3], 'arg2', false}
            parameters = {};
        end
        
        function parameters = getAsymmetricParameters(~)
            %GETASYMMETRICPARAMETERS provide parameters for asymmetric test
            %   For list of available parameter names, see ASYMMETRICTEST
            %   PARAMETERS should be a cell array of name - value pairs.
            %   Example: PARAMETERS = {'arg1', [1 2 3], 'arg2', false}
            parameters = {};
        end
        
        function parameters = getBufferDetectionParameters(~)
            %GETBUFFERDETECTIONPARAMETERS for buffer size detection
            %   For list of available parameter names, see BUFFERDETECTION
            %   PARAMETERS should be a cell array of name - value pairs.
            %   Example: PARAMETERS = {'arg1', [1 2 3], 'arg2', false}
            parameters = {};
        end
        
    end
    
    methods (Sealed)
        
        function tests = getTests(this)
        %GETTESTS a list of TESTs that would be used for running the suite
        %   If you want to skip a test, delete it from a list. If you
        %   design a test that you want to run, add it to the list.
        
            import coder.rtiostreamtest.*;
            
            tests = { ... 
                SymmetricTest( this.getSymmetricParameters() ), ...                  
                AsymmetricTest( this.getAsymmetricParameters() ), ...                                 
                BufferDetection( this.getBufferDetectionParameters() ), ...
            };
        end

    end
    
    methods (Static)
        function instance = getParameterInstance(tag, input)
            %GETPARAMETERINSTANCE quick way of getting an instance
            %   A lookup table translating a string and a set of parameters
            %   to an instance of PARAMETERS. If you
            %   implement your own PARAMETERS class, you
            %   can add a case in the switch statement with an unique tag
            %   that can get an instance to your class.
  
            switch lower(tag)
                case 'tcp'
                    instance = coder.rtiostreamtest.ParametersTCP(input{1}, input{2});
                case 'udp'
                    instance = coder.rtiostreamtest.ParametersUDP(input{1}, input{2});
                case 'serial'
                    instance = coder.rtiostreamtest.ParametersSerial(input{1}, input{2});
                case 'mlink'
                    instance = microdaq.ParametersMLink(input{1});
                otherwise
                    coder.rtiostreamtest.Test.error('ErrorUnsupportedTag', tag);
            end
        end
    end
    
end