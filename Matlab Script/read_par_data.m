function par_data = read_par_data(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('3'),"uint8");
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
        ch0_par_data = readline(serialcommunication);
        ch1_par_data = readline(serialcommunication);
        ch2_par_data = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    par_data = [ch0_par_data ch1_par_data ch2_par_data];

    if pause == 1
        clc;
        disp('ch0_par_data:' + ch0_par_data);
        disp('ch1_par_data:' + ch1_par_data);
        disp('ch2_par_data:' + ch2_par_data);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end