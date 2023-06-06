function identifier = set_initial_cap(serialcommunication,pause)    
    try
        write(serialcommunication,[60,13,10],"uint8");
        if pause == 1
            disp(">> Process << Set Para Cap Succeeded");
        end
    catch
        if pause == 1
            disp(">> Process << Set Para Cap Failed");
        end
        delete(serialcommunication);
    end

    try
        identifier = readline(serialcommunication);
        if pause == 1
            if identifier == '200'
                disp(">> Process << Set Para Cap Read Succeeded");
            else
                disp(">> Process << Set Para Cap Read Failed");
            end
        end
    catch
        if pause == 1
            disp(">> Process << Set Para Cap Read Failed");
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