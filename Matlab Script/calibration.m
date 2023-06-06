%% Initialization
% clear commands
clc;
% clear all varibles in workspce
clear;
% close all figures
close all;
%% Establish Serial Communication
serialcommunication = init_serial();
%% Function Selection
while 1
    clc;
    disp('>> Process << Function Table');
    disp('1. Elementary functions');
    disp('2. Collecting data');
    disp('3. Calibrate capacitance');
    disp('4. Calibrate liquid level');
    disp('5. Analysis Capacitance');
    disp('6. Analysis Liquid Level');
    disp('7. Actuation');
    disp('0. Exit');
    disp(' ');
    user_selection = input('Please choose a function:');
    disp(' ');
    switch user_selection
        case 0
            disp('>> Process << Exiting...');
            break;   
        case 1
            elementary_functions(serialcommunication);
        case 2
            samples = input('Please enter samples resolution:');
            data = collecting_data(serialcommunication,samples);
            data_num = input('Please enter a file number:');
            name = strcat(num2str(data_num),'.csv');
            path = strcat(folder,name);
            writematrix(data,path);
        case 3
            calibrate_capacitance(serialcommunication);
        case 4
            % calibrate_liquid_level(serialcommunication);
            calibrate_liquid_level_fast(serialcommunication);
        case 5
            analysis_capacitance();
        case 6   
            analysis_liquid_level();
        case 7   
            actuation();
        case 10
            samples = input('Please enter samples resolution:');
            data = data_filter(serialcommunication,samples);
            data_num = input('Please enter a file number:');
            name = strcat(num2str(data_num),'.csv');
            path = strcat(folder,name);
            writematrix(data,path);
        otherwise
            disp('>> Process << Invalid Input -> Returning...');
    end
    disp(' ');
end
%% Close communication and save worksapce
delete(serialcommunication);
save;