function collected_data = collecting_data(serialcommunication,samples)
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
    liquid_level = [];

    for i = 1:samples
        %clc;
        fprintf('Processing: %d/%d\n',i,samples);
        
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
        liquid_level = [liquid_level;read_liquid_level(serialcommunication,0)];
    end

    collected_data = [chx_data chx_cap chx_par_data chx_par_cap...
        chx_init_data chx_init_cap chx_cfg_cap chx_filtered_data...
        chx_filtered_cap chx_filt_cfg_cap liquid_level];
end