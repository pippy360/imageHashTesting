import matplotlib
matplotlib.use('Agg')
import pylab
from pylab import plot,show,subplot, axhline, axis, axes
####### gen points ########
g_name = "image"
g_enable_plotting = True


def plotTwoFuncsVsOrgPoints(tList, fx_t, org_x, fy_t, org_y):
    if not g_enable_plotting:
        return
    #PLOT
    subplot(311)
    plot(org_x, org_y, 'b', color="red")
    plot(fx_t(tList), fy_t(tList), 'b', color="blue")
    subplot(312)
    plot(tList, org_x, 'b', color="red")
    plot(tList, fx_t(tList), 'b', color="blue")
    subplot(313)
    plot(tList, org_y, 'b', color="red")
    plot(tList, fy_t(tList), 'b', color="blue")
    #plot(fx_t(tList), fy_t(tList), 'b', color="blue")
    # show()
    #PLOT

def plotTwoFuncsVsOrgPoints2(sList, tList, fx_t, org_x, fy_t, org_y, fx_s, fy_s, fx_s_no_smooth, fy_s_no_smooth):
    if not g_enable_plotting:
        return
    #PLOT
    subplot(311)
    plot(org_x, org_y, 'b', color="red")
    # plot(fx_t, fy_t, 'b', color="blue")
    plot(fx_s_no_smooth(sList), fy_s_no_smooth(sList), 'x', color="blue")
    plot(fx_s, fy_s, 'b', color="green")
    subplot(312)
    plot(sList, fx_s_no_smooth(sList), 'x', color="blue")
    plot(sList, fx_s, 'b', color="green")
    subplot(313)
    plot(sList, fy_s_no_smooth(sList), 'x', color="blue")
    plot(sList, fy_s, 'b', color="green")
    # show()
    #PLOT

def plotArcVsSmoothedOrg(fx_t, org_x, fy_t, org_y):
    if not g_enable_plotting:
        return
    #PLOT
    subplot(211)
    plot(org_x, org_y, 'b', color="red")
    subplot(212)
    plot(fx_t, fy_t, 'b', color="blue")
    #plot(fx_t(tList), fy_t(tList), 'b', color="blue")
    show()
    #PLOT

def plotItAtIndex(xs, ys, dxdt, dydt, d2xdt, d2ydt, s, curvature, dxcurvature, dx2curvature, idx, fullLength_s):
    fullLen = len(s)
    i = idx


    subplot(321)
    #axis([0.0,20.0,-15.0,15.0])
    #	pylab.axis([0.0,350.0,0.0,100.0])
    #pylab.xlim([0,fullLength_s])
    pylab.axhline(0, color='black')
    pylab.plot(s[0:i+1], curvature[0:i+1], 'b', color="red")


    ax = subplot(322)
    #axis([-1.5,1.5,-1.5,1.5])
    #pylab.xlim([0,fullLength_s])
    pylab.plot(xs[0:i+1], ys[0:i+1], 'b', linewidth=2, color="red")

    pylab.plot(xs[i:fullLen], ys[i:fullLen], 'b', color="grey")
    ax = ax.axes
    div = 100#1/(math.sqrt(dxdt[0:i+1][-1]**2 + dydt[0:i+1][-1]**2))
    #div = div * 0.5
    ax.arrow(xs[0:i+1][-1], ys[0:i+1][-1], dxdt[0:i+1][-1]*div, dydt[0:i+1][-1]*div, head_width=0.05, head_length=0.1, fc='r', ec='r')
    div = 100#1/(math.sqrt((dxdt[0:i+1][-1]+d2xdt[0:i+1][-1])**2 + (dydt[0:i+1][-1]+d2ydt[0:i+1][-1])**2))
    #div = div * 0.5
    ax.arrow(xs[0:i+1][-1], ys[0:i+1][-1], (dxdt[0:i+1][-1]+d2xdt[0:i+1][-1])*div, ((dydt[0:i+1][-1]+d2ydt[0:i+1][-1]))*div, head_width=0.05, head_length=0.1, fc='b', ec='b')

    subplot(323)
    #axis([0.0,20.0,-1.0,1.0])
    #pylab.xlim([0,fullLength_s])
    pylab.axhline(0, color='black')
    pylab.plot(s[0:i+1], dxdt[0:i+1], 'b', linewidth=2, color="red")

    subplot(324)
    #axis([0.0,20.0,-1.0,1.0])
    pylab.axhline(0, color='black')
    pylab.plot(s[0:i+1], dydt[0:i+1], 'b', linewidth=2, color="red")

    subplot(325)
    #axis([0.0,20.0,-2.0,2.0])
    #pylab.xlim([0,fullLength_s])
    pylab.axhline(0, color='black')
    vals = dydt[0:i+1]**2+dxdt[0:i+1]**2
    vals = abs(vals-1)
    pylab.plot(s[0:i+1], abs(dx2curvature[0:i+1]), 'b', linewidth=2, color="red")

    subplot(326)
    #axis([0.0,20.0,-10.0,10.0])
    #pylab.xlim([0,fullLength_s])
    pylab.axhline(0, color='black')
    #pylab.plot(s[0:i+1], d2ydt[0:i+1], 'b', linewidth=2, color="red")
    tempVals = abs(dxcurvature[0:i+1])
    #tempVals = np.log(tempVals)
    pylab.plot(s[0:i+1], (dxdt**2 + dydt**2)[0:i+1], 'b', linewidth=2, color="red")
    print "vals[-1]"
    print vals[-1]
    pylab.savefig('output_debug/'+g_name+'_foo'+str(idx)+'.png')
    pylab.clf()


def plotCurvatureLocalMaximums(s, curvature, arcLengthOfLocalMaximum, curvatureOfLocalMaximum, xs, ys, xCoordsOfLocalMaximum, yCoordsOfLocalMaximum):
    subplot(211)
    plot(s, curvature, 'b', color='b')
    plot(arcLengthOfLocalMaximum, curvatureOfLocalMaximum, 'ro', color='r')
    subplot(212)
    plot(xs, ys, 'b', color='b')
    plot(xCoordsOfLocalMaximum, yCoordsOfLocalMaximum, 'ro', color='r')

    show()









