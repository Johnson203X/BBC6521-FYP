function id = read_id(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('0'),"uint8");
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
        device_id = readline(serialcommunication);
        manufacturer_id = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    id = [device_id manufacturer_id];

    if pause == 1
        clc;
        disp('device_id:' + device_id);
        disp('manufacturer_id:' + manufacturer_id);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end