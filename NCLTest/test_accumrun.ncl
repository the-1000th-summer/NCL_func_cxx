procedure test_dacumrun()
begin

    x        = (/1,2,3,4,5,7,-23/)
    x@_FillValue = -999     
    x_ars    = dim_acumrun_n(x,3,0,0)
    print(x_ars)
    x_ars    = dim_acumrun_n(x,3,1,0)
    print(x_ars)

end

begin

    test_dacumrun()

end

