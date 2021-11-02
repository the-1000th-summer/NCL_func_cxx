
procedure test_stat2()
begin
    x = (/1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999/)
    x@_FillValue = -999
    xmean   = new(1, float)
    xvar    = new(1, float)
    npts    = new(1, integer)

    stat2(x,xmean,xvar,npts)
    print(xmean)
    print(xvar)
    print(npts)
end


begin

    test_stat2()

end

