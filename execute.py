import os
import IlocSim as sim

def getIloc():
    with open('iloc.out', 'r') as code:
        iloc = code.read()
    return iloc

def saveILOC(filename, data):
    with open(filename, 'w+') as file:
        file.write(data)

testcase = "testcases/demo4"
os.system("make")
os.system("codegen < "+testcase)
data = getIloc()
saveILOC('iloc1.out', data)
os.system("codegen -O < "+testcase)
data1 = getIloc()
sim.start(data)
sim.start(data1)
# print(data)
# print(data1)