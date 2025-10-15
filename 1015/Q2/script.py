f = eval(open("flag.txt", "r").read())
for i in f:
    print(i[0], i[-1], end=" ")
