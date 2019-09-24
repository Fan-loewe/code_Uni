function [data] = importImuData(path,logName)

    if nargin == 1
        logName = 'new';
    end

    data = [];

    name = sprintf('%s.log',logName);
    filename = sprintf('%s/%s',path,name);

    % read the file
    data.src        = dlmread(filename,' ',0,0); % complete file

    data.n          = length(data.src(:,1));

    % store data
    data.t              = data.src(:,1);
    data.acc(:,1:3)     = data.src(:,2:4);
    data.gyro(:,1:3)  	= data.src(:,5:7);
    data.mag(:,1:3)     = data.src(:,8:10);

    data.t = (data.t - data.t(1))/1000;
    
end