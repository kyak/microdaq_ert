function tc = microdaq_tc
% Create a toolchain object
tc = coder.make.ToolchainInfo('Name', 'MicroDAQ Toolchain');

% Specify source file and object file extension used by the C compiler
tool = tc.getBuildTool('C Compiler');
tool.setFileExtension(  'Source', '.c');
tool.setFileExtension(  'Header', '.h');
tool.setFileExtension(  'Object', '.out');
