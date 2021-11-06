procedure test_regcoef()
begin
    x = new(18, double)
    y = new(18, double)
    x = (/ 1190.,1455.,1550.,1730.,1745.,1770. \
       ,  1900.,1920.,1960.,2295.,2335.,2490. \
       ,  2720.,2710.,2530.,2900.,2760.,3010. /)

    y = (/ 1115.,1425.,1515.,1795.,1715.,1710. \
       ,  1830.,1920.,1970.,2300.,2280.,2520. \
       ,  2630.,2740.,2390.,2800.,2630.,2970. /)
    ; x@_FillValue = -999

    rc    = regCoef(x,y)
    print(rc)
    print(sprintf("%.8f", rc@tval))
    print(sprintf("%.8f", rc@yintercept))

end


begin

    test_regcoef()

end

