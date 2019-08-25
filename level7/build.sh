if [[ -n "`gcc -v -E 2>&1 | grep 'Configured with' | sed 's/--/\n--/g' | grep enable-default-pie`" ]]; 
	then
		gcc level7.c -Wno-deprecated-declarations
	else
		gcc level7.c -Wno-deprecated-declarations -pie
fi
