differenceV = []
differenceM = []

with open('logs/ModelLog.txt', 'r') as Model, open('logs/ViewLog.txt', 'r') as View:
    same = True
    counter = 0
    while same:
        lineV = View.readline()
        lineM = Model.readline()
        counter += 1
        if counter > 1 and lineM != lineV:
            differenceM.append((counter, lineM))
            differenceV.append((counter,lineV))
        elif not lineV or not lineM:
            same = False
            print("EOF Reached")

if len(differenceM) == 0:
    print("No differences, chilliiinnn")
else:
    print("Uh oh")
    for i in range(len(differenceV)):
        print("View(" + str(differenceV[i][0]) + "):  " + differenceV[i][1])  
        print("Model(" + str(differenceM[i][0]) + "):  " + differenceM[i][1])  