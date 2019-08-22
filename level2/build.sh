if [[ -n "`gcc -v -E 2>&1 | grep 'Configured with' | sed 's/--/\n--/g' | grep enable-default-pie`" ]]; 
	then
		gcc level2.c -Wno-deprecated-declarations -no-pie
	else
		gcc level2.c -Wno-deprecated-declarations
fi
