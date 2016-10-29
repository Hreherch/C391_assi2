all: q4 q5 q7

q4: q4.c
	gcc -g q4.c -o q4 sqlite3.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1

q5: q5.c 
	gcc -g q5.c -o q5 sqlite3.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1

q7: q7.c sqlite3.c
	gcc -g q7.c -o q7 sqlite3.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1

clean:
	rm -f q4 q5