function elementary_functions(serialcommunication)
    while 1
    clc;
    disp('>> Process << Elementary Functions Table');
    disp('1.  Manufacturer ID & Device ID');
    disp('2.  Channels Data');
    disp('3.  Channels Capacitance');
    disp('4.  Channels Parasitic Data');
    disp('5.  Channels Parasitic Capacitance');
    disp('6.  Channels Configured Capacitance');
    disp('7.  Channels Initial Data');
    disp('8.  Channels Initial Cap');
    disp('9.  Liquid Level');
    disp('10. Motor Forward');
    disp('11. Motor Backward');
    disp('12. Set Parasitic Data & Capacitance');
    disp('13. Set Initial Data & Capacitance');
    disp('14. Filtered Data');
    disp('15. Filtered Cap');
    disp('16. Filtered Configured Cap');
    disp('17. Reset Filter');
    disp('18. Actuation');
    disp('0.  Return');
    disp(' ');
    elementary_selection = input('Please choose a function:');
    disp(' ');
    switch elementary_selection
            case 1
                id = read_id(serialcommunication,1);
            case 2
                chx_data = read_data(serialcommunication,1);
            case 3
                chx_cap = read_cap(serialcommunication,1);
            case 4
                chx_par_data = read_par_data(serialcommunication,1);
            case 5
                chx_par_cap = read_par_cap(serialcommunication,1);
            case 6
                chx_cfg_cap = read_cfg_cap(serialcommunication,1);
            case 7
                chx_init_data = read_init_data(serialcommunication,1);
            case 8
                chx_init_cap = read_init_cap(serialcommunication,1);
            case 9
                liquid_level = read_liquid_level(serialcommunication,1);
            case 10
                motor_for = motor_ratio(serialcommunication,1,0);
            case 11
                motor_back = motor_ratio(serialcommunication,0,0);
            case 12
                parasitic_cap = set_parasitic_cap(serialcommunication,1);
            case 13
                initial_cap = set_initialcap(serialcommunication,1);
            case 14
                filtered_data = read_filtered_data(serialcommunication,1);
            case 15
                filtered_cap = read_filtered_cap(serialcommunication,1);
            case 16
                filtered_cfg_cap = read_filt_cfg_cap(serialcommunication,1);
            case 17
                reset_filter_idf = reset_filter(serialcommunication,1);
            case 18
                actuation(serialcommunication,1);
            case 0
                break;
            otherwise
        end
    end
end