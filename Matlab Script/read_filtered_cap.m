function filtered_cap = read_filtered_cap(serialcommunication,pause)
    try
        write(serialcommunication,[63,13,10],"uint8");
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
        ch0_filtered_cap = readline(serialcommunication);
        ch1_filtered_cap = readline(serialcommunication);
        ch2_filtered_cap = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    filtered_cap = [ch0_filtered_cap ch1_filtered_cap ch2_filtered_cap];

    if pause == 1
        clc;
        disp('ch0_filtered_cap:' + ch0_filtered_cap);
        disp('ch1_filtered_cap:' + ch1_filtered_cap);
        disp('ch2_filtered_cap:' + ch2_filtered_cap);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end