function par_cap = read_par_cap(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('4'),"uint8");
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
        ch0_par_cap = readline(serialcommunication);
        ch1_par_cap = readline(serialcommunication);
        ch2_par_cap = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    par_cap = [ch0_par_cap ch1_par_cap ch2_par_cap];

    if pause == 1
        clc;
        disp('ch0_par_cap:' + ch0_par_cap);
        disp('ch1_par_cap:' + ch1_par_cap);
        disp('ch2_par_cap:' + ch2_par_cap);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end