function calibrate_liquid_level_fast(serialcommunication)
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

    reset_filter_idf = reset_filter(serialcommunication,0);

    clc;
    disp('>> Process << Finished initialization, continue to calibrate');
    disp(' ');
    resolution = input('>> Process << Please enter resolution:');
    disp(' ');
    samples = input('>> Process << Please enter required calibrating samples:');

    % chx_data = [];
    chx_cap = [];
    % chx_par_data = [];
    chx_par_cap = [];
    % chx_init_data = [];
    chx_init_cap = [];
    chx_cfg_cap = [];
    % chx_filtered_data = [];
    % chx_filtered_cap = [];
    chx_filt_cfg_cap = [];

    chx_filt_cfg_cap_avg = [];

    disp(' ');
    disp('Please mannually input the current liquid level');
    disp(' ');
    liquid_level_init = input('>> Process << Initial Height: ');

    for i = 1:samples
        sum = 0;
        disp(' ');
        fprintf('>> Process << Calibrating %d / %d \n',i,samples);
        for k = 1:5
            motor_ratio(serialcommunication,1,0);
        end
        for j= 1:resolution
            % chx_data = [chx_data;read_data(serialcommunication,0)];
            % chx_cap = [chx_cap;read_cap(serialcommunication,0)];
            % chx_par_data = [chx_par_data;read_par_data(serialcommunication,0)];
            % chx_par_cap = [chx_par_cap;read_par_cap(serialcommunication,0)];
            % chx_init_data = [chx_init_data;read_init_data(serialcommunication,0)];
            % chx_init_cap = [chx_init_cap;read_init_cap(serialcommunication,0)];
            % chx_cfg_cap = [chx_cfg_cap;read_cfg_cap(serialcommunication,0)];
            % chx_filtered_data = [chx_filtered_data;read_filtered_data(serialcommunication,0)];
            % chx_filtered_cap = [chx_filtered_cap;read_filtered_cap(serialcommunication,0)];
            load = read_filt_cfg_cap(serialcommunication,0);
            % disp(load);
            chx_filt_cfg_cap = [chx_filt_cfg_cap;load];
            sum = sum + str2num(load(:,2));
            % disp(sum);
        end
        mean = sum/resolution;
        % disp(mean);
        chx_filt_cfg_cap_avg = [chx_filt_cfg_cap_avg;mean];
    end

    disp(' ');
    disp('Please mannually input the current liquid level');
    disp(' ');
    liquid_level_finished = input('>> Process << Finished Height: ');
    % liquid_level = liquid_level_init:liquid_level_finished:(samples*resolution);
    % disp(liquid_level);
    % input(' ');

    % data = [chx_data chx_cap chx_par_data chx_par_cap...
    %     chx_init_data chx_init_cap chx_cfg_cap...
    %     chx_filtered_data chx_filtered_cap chx_filt_cfg_cap];

    data = [chx_filt_cfg_cap];

    % data = [chx_cap chx_par_cap chx_init_cap chx_cfg_cap chx_filt_cfg_cap];

    data_avg = [chx_filt_cfg_cap_avg];

    clc;
    data_num = input('>> Process << Please enter detailed file number:');
    name = strcat(num2str(data_num),'.csv');
    folder = '..\Data\';
    path = strcat(folder,name);
    writematrix(data,path);

    data_avg_num = input('>> Process << Please enter average file number:');
    name = strcat(num2str(data_avg_num),'.csv');
    folder = '..\Data\';
    path = strcat(folder,name);
    writematrix(data_avg,path);
end