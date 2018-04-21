import os
import IlocSim as sim

def getIloc():
    with open('iloc.out', 'r') as code:
        iloc = code.read()
    return iloc

os.system("make")
os.system("codegen < testcases/demo1")
os.system("codegen -O < testcases/demo1")
sim.start(getIloc())