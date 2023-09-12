import datetime
 
# Returns the current local date
today = datetime.datetime.now
ahora = f'{datetime.datetime.now():%Y-%m-%d_%H:%M}'
rawSerialOutFile = open(r"output.txt","r")
newCSV = open("CSV_out/test"+ahora+".csv","a")
currentline = "A"
while (currentline[0] == "0") or (currentline[0] == "A"):
    currentline = rawSerialOutFile.readline()

for char in currentline: