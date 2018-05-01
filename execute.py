import os
import IlocSim as sim

def getIloc():
    with open('iloc.out', 'r') as code:
        iloc = code.read()
    return iloc

def saveILOC(filename, data):
    with open(filename, 'w+') as file:
        file.write(data)

for x in range(1,5):
    testcase = "testcases/demo{}".format(x)
    os.system("make")
    os.system("codegen < "+testcase)
    data = getIloc()
    os.system("codegen -O < "+testcase)
    data1 = getIloc()
    if(sim.start(data) == sim.start(data1)):
        saveILOC('testcases/demo{}solution'.format(x), data1)
