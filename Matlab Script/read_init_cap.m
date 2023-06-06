function init_cap = read_init_cap(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('7'),"uint8");
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
        ch0_init_cap = readline(serialcommunication);
        ch1_init_cap = readline(serialcommunication);
        ch2_init_cap = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    init_cap = [ch0_init_cap ch1_init_cap ch2_init_cap];

    if pause == 1
        clc;
        disp('ch0_init_cap:' + ch0_init_cap);
        disp('ch1_init_cap:' + ch1_init_cap);
        disp('ch2_init_cap:' + ch2_init_cap);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end