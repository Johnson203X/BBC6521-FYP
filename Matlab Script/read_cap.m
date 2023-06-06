function cap = read_cap(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('2'),"uint8");
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
        ch0_cap = readline(serialcommunication);
        ch1_cap = readline(serialcommunication);
        ch2_cap = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    cap = [ch0_cap ch1_cap ch2_cap];

    if pause == 1
        clc;
        disp('ch0_cap:' + ch0_cap);
        disp('ch1_cap:' + ch1_cap);
        disp('ch2_cap:' + ch2_cap);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end