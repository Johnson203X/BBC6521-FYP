function init_data = read_init_data(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('6'),"uint8");
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
        ch0_init_data = readline(serialcommunication);
        ch1_init_data = readline(serialcommunication);
        ch2_init_data = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    init_data = [ch0_init_data ch1_init_data ch2_init_data];

    if pause == 1
        clc;
        disp('ch0_init_data:' + ch0_init_data);
        disp('ch1_init_data:' + ch1_init_data);
        disp('ch2_init_data:' + ch2_init_data);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end