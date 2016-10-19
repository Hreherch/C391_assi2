q4: q4.c
	gcc -g q4.c -o q4 sqlite3.c -lpthread -ldl -DSQLITE_ENABLE_RTREE=1