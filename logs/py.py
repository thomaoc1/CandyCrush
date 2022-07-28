differenceV = []
differenceM = []

with open('ModelLog.txt', 'r') as Model, open('ViewLog.txt', 'r') as View:
    same = True
    counter = 0
    while same:
        lineV = View.readline()
        lineM = Model.readline()
        counter += 1
        if counter > 1 and lineM != lineV:
            differenceM.append((counter, lineM))
            differenceV.append((counter,lineV))
        elif lineV == "" or lineM == "":
            same = False
            print("You good bro")

for i in range(len(differenceV)):
    print("View(" + str(differenceV[i][0]) + "):  " + differenceV[i][1])  
    print("Model(" + str(differenceM[i][0]) + "):  " + differenceM[i][1])  