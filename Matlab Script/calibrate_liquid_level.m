function calibrate_liquid_level(serialcommunication)
    clc;
    disp('>> Process << Detecting parasitic capacitor');
    disp('Please do not connect sensor to any other capacitor');
    disp(' ');
    input('>> Process << Press any key to continue when ready');
    set_parasitic_cap(serialcommunication,1);

    clc;
    disp('>> Process << Detecting initial capacitor');
    disp('Please only connect sensor to ambient circuit, including wires');
    disp(' ');
    input('>> Process << Press any key to continue when ready');
    set_initialcap(serialcommunication,1);

    clc;
    disp('>> Process << Finished initialization, continue to calibrate');
    disp(' ');
    resolution = input('>> Process << Please enter resolution:');
    disp(' ');
    samples = input('>> Process << Please enter required calibrating samples:');

    liquid_level = [];
    chx_data = [];
    chx_cap = [];
    chx_par_data = [];
    chx_par_cap = [];
    chx_init_data = [];
    chx_init_cap = [];
    chx_cfg_cap = [];
    chx_filtered_data = [];
    chx_filtered_cap = [];
    chx_filt_cfg_cap = [];

    for i = 1:samples
        while 1
            clc;
            fprintf('>> Process << Calibrating %d / %d \n',i,samples);
            disp('Please mannually configure to the target liquid level');
            disp(' ');
            disp('1. Motor forward  >>>');
            disp('2. Motor backward <<<');
            disp('3. >>>  Continue  >>>');
            disp(' ');
            command = input('>> Process << Command: ');
            if command == 1
                motor_ratio(serialcommunication,0,1);
            elseif command == 2
                motor_ratio(serialcommunication,1,1);
            elseif command == 3
                break;
            else
            end
        end
        disp(' ');
        input_liquid_level = input('>> Process << Liquid Level: ');
        for j= 1:resolution
            liquid_level = [liquid_level;input_liquid_level];
            chx_data = [chx_data;read_data(serialcommunication,0)];
            chx_cap = [chx_cap;read_cap(serialcommunication,0)];
            chx_par_data = [chx_par_data;read_par_data(serialcommunication,0)];
            chx_par_cap = [chx_par_cap;read_par_cap(serialcommunication,0)];
            chx_init_data = [chx_init_data;read_init_data(serialcommunication,0)];
            chx_init_cap = [chx_init_cap;read_init_cap(serialcommunication,0)];
            chx_cfg_cap = [chx_cfg_cap;read_cfg_cap(serialcommunication,0)];
            chx_filtered_data = [chx_filtered_data;read_filtered_data(serialcommunication,0)];
            chx_filtered_cap = [chx_filtered_cap;read_filtered_cap(serialcommunication,0)];
            chx_filt_cfg_cap = [chx_filt_cfg_cap;read_filt_cfg_cap(serialcommunication,0)];
        end
    end

    data = [liquid_level chx_data chx_cap chx_par_data chx_par_cap...
        chx_init_data chx_init_cap chx_cfg_cap...
        chx_filtered_data chx_filtered_cap chx_filt_cfg_cap];

    clc;
    data_num = input('>> Process << Please enter a file number:');
    name = strcat(num2str(data_num),'.csv');
    folder = '..\Data\';
    path = strcat(folder,name);
    writematrix(data,path);
end