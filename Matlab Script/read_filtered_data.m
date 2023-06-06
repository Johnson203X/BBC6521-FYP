function filtered_data = read_filtered_data(serialcommunication,pause)
    try
        write(serialcommunication,[61,13,10],"uint8");
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
        ch0_filtered_data = readline(serialcommunication);
        ch1_filtered_data = readline(serialcommunication);
        ch2_filtered_data = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    filtered_data = [ch0_filtered_data ch1_filtered_data ch2_filtered_data];

    if pause == 1
        clc;
        disp('ch0_filtered_data:' + ch0_filtered_data);
        disp('ch1_filtered_data:' + ch1_filtered_data);
        disp('ch2_filtered_data:' + ch2_filtered_data);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end