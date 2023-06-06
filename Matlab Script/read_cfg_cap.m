function cfg_cap = read_cfg_cap(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('5'),"uint8");
        if pause == 1
            disp(">> Process << Data Writing Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Writing Failed");
        end
        delete(serialcommunication);
    end

    try
        ch0_cfg_cap = readline(serialcommunication);
        ch1_cfg_cap = readline(serialcommunication);
        ch2_cfg_cap = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    cfg_cap = [ch0_cfg_cap ch1_cfg_cap ch2_cfg_cap];

    if pause == 1
        clc;
        disp('ch0_cfg_cap:' + ch0_cfg_cap);
        disp('ch1_cfg_cap:' + ch1_cfg_cap);
        disp('ch2_cfg_cap:' + ch2_cfg_cap);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end