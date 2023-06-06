function liquid_level = read_liquid_level(serialcommunication,pause)
    try
        write(serialcommunication,to_written_command('8'),"uint8");
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
        liquid_level = readline(serialcommunication);
        if pause == 1
            disp(">> Process << Data Reading Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Data Reading Failed");
        end
        delete(serialcommunication);
    end

    if pause == 1
        clc;
        disp('liquid_level:' + liquid_level);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end