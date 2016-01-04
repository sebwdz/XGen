
lst = []

def BCL(x, length, val):
    global lst
    it = 0
    while it < length:
        lst[x].append(val)
        #print x, it
        it += 1

val = 5
length = 100
x = 0

while x < length:
    lst.append([])
    BCL(x, length, val)
    x += 1
