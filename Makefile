all: shell ls cat date mkdir rm

shell: shell.c
mkdir: mkdir.c
cat: cat.c
date: date.c
ls: ls.c
rm: rm.c
delete= ls cat date mkdir rm
clean:
		rm -f $(delete) *.o
