#!/usr/bin/python
from os import listdir
from os.path import isfile, join

filenames = [f for f in listdir("./") if isfile(join("./", f))]

for filename in filenames:
    with open(filename) as file:
        lines = file.readlines()
        with open("../"+filename,'w') as out:
            out.write("NAME : " + filename.split('.')[0] + "\n" );
            out.write("COMMENT : " + str(len(lines)) + " locations in Brazil\n")
            out.write("COMMENT : Derived from IBGE datasets\n")
            out.write("TYPE : TSP\n")
            out.write("DIMENSION : " + str(len(lines)) + "\n")
            out.write("EDGE_WEIGHT_TYPE : EUC_2D\n")
            out.write("NODE_COORD_SECTION\n")
            for line in lines:
                out.write(line.replace(',',' '))
            out.write("EOF")


