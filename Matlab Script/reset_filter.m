function identifier = reset_filter(serialcommunication,pause)    
    try
        write(serialcommunication,[64,13,10],"uint8");
        if pause == 1
            disp(">> Process << Reset filter Write Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Reset filter Write Failed");
        end
        delete(serialcommunication);
    end

    try
        identifier = readline(serialcommunication);
        if pause == 1
            if identifier == '200'
                disp(">> Process << Reset filter Read Succeeded");
            else
                disp(">> Process << Reset filter Read Failed");
            end
        end
    catch
        if pause == 1
            disp(">> Process << Reset filter Read Failed");
        end
        delete(serialcommunication);
    end

    if pause == 1
        clc;
        disp('identifier:' + identifier);
        disp(' ');
        input('>> Process << Press any key to continue');
        disp(' ');
    end
end