all: q4 q5 q7 q8

q3: q3db.txt
	./sqlite3 q3db.db < q3db.txt

q4: q4.c
	gcc -g q4.c -o q4 sqlite3.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1

q5: q5.c 
	gcc -g q5.c -o q5 sqlite3.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1

q7: q7.c sqlite3.c NearestNeighbour.c 
	gcc -g q7.c -o q7 sqlite3.c NearestNeighbour.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1

q8: q8.c sqlite3.c NearestNeighbour.c 
	gcc -g q8.c -o q8 sqlite3.c NearestNeighbour.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1
    
A2.db: q0.txt q1.txt
	./sqlite3 A2.db < q0.txt

clean:
	rm -f q4 q5 q7 q8 A2.db
    
QFiles = q0.txt q1.txt q2.pdf q3.txt q3db.txt q4.c q5.c q6.txt q7.c q8.c
extra = NearestNeighbour.c NearestNeighbour.h
SQLite = sqlite3.c sqlite3.h A2.db q3db.txt readme.txt Makefile
    
zip:
	zip temp.zip $(QFiles) $(extra) $(LFFiles) $(SQLite)