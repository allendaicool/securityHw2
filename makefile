CC=g++
CFLAGS=-g -Wall

build: objget   objput  objlist objsetacl objgetacl objtestacl

objget :  objget.o  functionCall.o
	$(CC) $(CFLAGS) -o objget    objget.cpp functionCall.cpp

	

objput	: help.o functionCall.o
	$(CC) $(CFLAGS) -o objput     help.cpp functionCall.cpp

	

objlist : objlist.o functionCall.o
	$(CC) $(CFLAGS)  -o objlist    objlist.cpp functionCall.cpp

	
objsetacl : objsetacl.o functionCall.o
	$(CC) $(CFLAGS)  -o objsetacl    objsetacl.cpp functionCall.cpp



objgetacl : objgetacl.o functionCall.o
	$(CC) $(CFLAGS)  -o objgetacl   objgetacl.cpp functionCall.cpp



objtestacl : objtestacl.o functionCall.o
	$(CC) $(CFLAGS)  -o objtestacl  objtestacl.cpp functionCall.cpp



	
ARG=userfile.txt
fileds='s d v'
exec:	build
	chown god:g2 ./objput
	chmod u+s  ./objput
	chown god:g2 ./objget
	chmod u+s  ./objget
	chown god:g2 ./objlist
	chmod u+s  ./objlist
	chown god:g2 ./objgetacl
	chmod u+s  ./objgetacl
	chown god:g2 ./objsetacl
	chmod u+s  ./objsetacl
	chown god:g2 ./objtestacl
	chmod u+s  ./objtestacl	
	mkdir filesystem	
	# cat $(ARG) > user+group
	#echo ${fileds[0]}
	#forms=abc
	#for i in 1 2 3 4;do \
	#	echo success; \
	#done
	#echo $(printf "%s" "$ARG");
	 #while IFS= read -r line;do \
	#	echo $(printf "%s" "$line"); \
	#	fields=($(printf "%s" "$line")); \		
	#	tlen=${#fields[@]}; \
	#	echo ${tlen}; \
	#	echo  "${fields[0]}" ; \
	#	echo  "${fields[${tlen}-1]}"; \
	#	
	#	for ((i=1; i < ${tlen}; i++));do \
	#			if grep -q -w "${fields[i]}"  /etc/group;then \
	#			  	echo group  already exists ; \
	#			else \
	#		groupadd "${fields[i]}"; \
	#			fi ; \
	#	done
	#
	#	useradd -g "${fields[1]}" "${fields[0]}"
	 #	for ((i=2; i < ${tlen}; i++));
	#		do
	#			usermod -G "${fields[i]}" "${fields[0]}"
	#	        done
	#done < tt

test: 	build	exec	
	./objput -u u1 -g g1 doc < haha
	./objget -u u1 -g g1 doc
	./objlist -u u1
	./objgetacl -u u1 -g g1 doc
	./objsetacl -u u1 -g g1 doc < newacl
	./objtestacl -u u1 -g g3 -a r doc
	./objtestacl -u u1 -g g3 -a x doc
	./objput -u u1 -g g1 doc < haha
	./objput -u u2 -g g1 doc < haha
clean:
	rm *.o   objtestacl objgetacl objsetacl objlist objput objget *.core

	
