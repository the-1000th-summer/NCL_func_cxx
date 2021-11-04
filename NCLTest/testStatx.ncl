
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

procedure test_stat4()
begin
    x = (/1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999/)
    x@_FillValue = -999
    xmean   = new(1,float)
    xvar    = new(1,float)
    xskew   = new(1,float)
    xkurt   = new(1,float)
    npts    = new(1,integer)

    stat4(x,xmean,xvar,xskew,xkurt,npts)
    print(xmean)
    print(xvar)
    print(xskew)
    print(xkurt)
    print(npts)
end

procedure test_stat_medrng()
begin
    x = (/-999.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999/)
    x@_FillValue = -999
    xmed    = new(1,float)
    xmrng   = new(1,float)
    xrng    = new(1,float)
    npts    = new(1,integer)

    stat_medrng(x,xmed,xmrng,xrng,npts)
    print(xmed)
    print(xmrng)
    print(xrng)
    print(npts)
end

procedure test_stat_trim()
begin
    x = (/1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999/)
    x@_FillValue = -999
    xmeant  = new(1,float)
    xsdt    = new(1,float)
    npts    = new(1,integer)

    stat_trim(x,0.5,xmeant,xsdt,npts)
    print(xmeant)
    print(xsdt)
    print(npts)

end

procedure test_esacr_esacv()
begin
    x = (/1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999/)
    x@_FillValue = -999

    acr = esacr(x,9)
    acv = esacv(x,9)
    print(acr)
    print(sprintf("%.8f", acv))

end

procedure test_esccr()
begin
    x = new(12,double)
    y = new(12,double)
    x = (/1.,2.,3.,4.,5.,6.,-999,8.,9.,10.,11.,-999/)
    y = (/ -999,11.,10.,9.,8.,-999,6.,5.,4.,3.,2.,1. /)
    x@_FillValue = -999
    y@_FillValue = -999
    ccv = esccv(x,x,9)
    ccr = esccr(x,x,9)
    ccv_2 = esccv(x,y,9)
    ccr_2 = esccr(x,y,9)
    print(ccv)
    print(ccr)
    print(ccv_2)
    print(ccr_2)

end

begin

    ; test_stat2()
    ; test_stat4()
    ; test_stat_medrng()
    ; test_stat_trim()
    ; test_esacr_esacv()
    test_esccr()

end

