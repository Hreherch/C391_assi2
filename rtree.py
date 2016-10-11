class Square:
    def __init__( self, leftx, lefty, rightx, righty, name ):
        self.leftx = leftx
        self.lefty = lefty
        self.rightx = rightx
        self.righty = righty
        self.name = name
        
    def getArea( self ):
        return (self.rightx - self.leftx) * (self.lefty - self.righty)
        
    def getContainingArea( self, otherSquare ):
        minX = min( otherSquare.leftx, self.leftx )
        minY = min( otherSquare.righty, self.righty )
        maxX = max( otherSquare.rightx, self.rightx )
        maxY = max( otherSquare.lefty, self.lefty )
        return ((maxX - minX) * (maxY - minY))
        
    def getContainingSquare( self, otherSquare ):
        minX = min( otherSquare.leftx, self.leftx )
        minY = min( otherSquare.righty, self.righty )
        maxX = max( otherSquare.rightx, self.rightx )
        maxY = max( otherSquare.lefty, self.lefty )
        return Square( minX, maxY, maxX, minY, self.name + " and " + otherSquare.name )
        
    def __str__(self):
        lx = str(self.leftx)
        ly = str(self.lefty)
        rx = str(self.rightx)
        ry = str(self.righty)
        return self.name
        

r1 = Square(  2, 25,  5, 23, "r1" )
r2 = Square(  3, 20,  7, 17, "r2" )
r3 = Square(  1, 13,  4, 15, "r3" )
r4 = Square(  1,  3,  4,  0, "r4" )
r5 = Square(  6, 24,  9, 21, "r5" )
r6 = Square(  7, 20,  9, 15, "r6" )
r7 = Square(  6,  8, 13,  3, "r7" )
r8 = Square( 17, 22, 20,  9, "r8" )
r9 = Square( 19, 12, 24,  9, "r9" )
r10 = Square(19,  8, 23,  6, "r10" )
r11 = Square(21, 25, 26, 21, "r11" )
r12 = Square(20, 17, 30, 15, "r12" )

# THIS SQUARE WAS BACKWARDS CHECK THE FORUMS
r13 = Square(25, 16, 28, 12, "r13" )

r14 = Square(13, 22, 17, 19, "r14" )

# SETUP WHAT YOU WISH TO LOOK AT <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# MAX 5!!
l = [r6, r8, r9, r10, r11]


# PERFORMS PickSeeds >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
maxi = -1
maxj = -1
maxSize = -1
for i in range(5):
    for j in range( i+1, 5):
        test = l[i].getContainingArea(l[j])
        test -= l[i].getArea()
        test -= l[j].getArea()
        if test > maxSize:
            maxi = i + 1 
            maxj = j + 1
            maxSize = test
        print( str(l[i]) + " with " + str(l[j]) + " = " + str(test) )
        
print( "worst with " + str(l[maxi-1]) + " and " + str(l[maxj-1]) )

n1 = [l[maxi-1]]
n1_square = n1[0]
n2 = [l[maxj-1]]
n2_square = n2[0]
r = []

for i in range(5):
    if i != maxi-1 and i != maxj-1:
        r.append( l[i] )
        
# PERMORMS done check >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
for alphang in range(3):
    if (len(n1) == 1 or len(n2) == 1) and len(r) == 1:
        if len(n1) == 1:
            n1.append( r.pop(0) )
        else:
            n2.append( r.pop(0) )
        continue
        
    d1_list = []
    d2_list = []
    # d1 = the area increase for adding a square to n1 
    # d2 = same for n2
    for square in r:
        d1_list.append( n1_square.getContainingArea(square) - n1_square.getArea() )
        d2_list.append( n2_square.getContainingArea(square) - n2_square.getArea() )
    
    # choose the one with max difference between d1 and d2
    maxElm = -1
    maxVal = -1
    for index in range( len(d1_list)):
        print(index)
        val = abs(d1_list[index] - d2_list[index])
        if val > maxVal:
            maxElm = index
            maxVal = val
            
    if d1_list[maxElm] > d2_list[maxElm]:
        n2.append( r.pop(maxElm) )
        n2_square = n2_square.getContainingSquare(n2[-1])
    else:
        n1.append( r.pop(maxElm) )
        n1_square = n1_square.getContainingSquare(n1[-1])
        
print( "nodes in n1:" )
for square in n1:
    print( square )
    
print( "" )
print( "nodes in n2:" )
for square in n2:
    print( square )