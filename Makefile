all: q4 q5

q4: q4.c
	gcc -g q4.c -o q4 sqlite3.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1

q5: q5.c 
	gcc -g q5.c -o q5 sqlite3.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1

clean: q4 q5
	rm -i q4 q5