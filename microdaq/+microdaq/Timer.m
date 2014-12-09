classdef Timer < coder.profile.Timer
    methods
function this = Timer
            
            % Configure data type returned by timer reads
            this.setTimerDataType('uint32');
            
            ticksPerSecond = 300e6;
            this.setTicksPerSecond(ticksPerSecond);
            
            % The timer counts upwards
            this.setCountDirection('up');
            
            % Configure source files required to access the timer
            timerSourceFile = fullfile(getpref('microdaq','TargetRoot'),...
                'rtiostream','microdaq_timer.c');
                       
            this.setSourceFile(timerSourceFile);
            
            % Configure the expression used to read the timer
            readTimerExpression = 'profileTimerRead()';
            this.setReadTimerExpression(readTimerExpression);
        end
    end
end