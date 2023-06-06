function data = read_data(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('1'),"uint8");
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
        ch0_data = readline(serialcommunication);
        ch1_data = readline(serialcommunication);
        ch2_data = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    data = [ch0_data ch1_data ch2_data];

    if pause == 1
        clc;
        disp('ch0_data:' + ch0_data);
        disp('ch1_data:' + ch1_data);
        disp('ch2_data:' + ch2_data);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end