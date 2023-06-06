function calculated_cap_pF = calculate_cap(data)
    l_internal = 18e-6;
    c_internal = 33e-12;
    c_parasite = 0;
    c_offset = c_internal + c_parasite;
    f_clk_internal = 36e6;
    chx_fref_divider = 1;
    f_ref = f_clk_internal/chx_fref_divider;
    chx_fin_sel = 2;
    
%     chx_settlecount = 10;
%     chx_settlecount_hex = dec2hex(chx_settlecount);
%     t_sensor_activation = chx_settlecount*16/f_ref;
%     % ENOB
%     enob = 13;
%     chx_rount = 2^enob;
%     chx_rount_hex = dec2hex(chx_rount);
%     t_conversion = (chx_rount*16+4)/f_ref;
%     t_channel_switch = 692e-9+5/f_ref;
%     t_per_channel = t_sensor_activation + t_conversion + t_channel_switch;
%     t_tot = t_per_channel * 3

    f_sensor = chx_fin_sel * f_ref * data / 2^28;
    calculated_cap = 1/(l_internal*(2*pi*f_sensor)^2);
    calculated_cap_pF = calculated_cap*10^12;
    Weight = 2^56*chx_fref_divider^2/(l_internal*4*pi^2*chx_fin_sel^2*f_clk_internal^2);
end