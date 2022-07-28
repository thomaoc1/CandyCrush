with open('ModelLog.txt', 'r') as Model, open('ViewLog.txt', 'r') as View:
    same = True
    counter = 0
    while same:
        lineV = View.readline()
        lineM = Model.readline()
        counter += 1
        if counter > 1 and lineM != lineV:
            print("Model: " + lineM + "\n" + "View: " + lineV)
            same = False
        elif lineV == "" or lineM == "":
            same = False
            print("You good bro")

print(counter)            
