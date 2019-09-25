if [[ -n "`gcc -v -E 2>&1 | grep 'Configured with' | sed 's/--/\n--/g' | grep enable-default-pie`" ]]; 
	then
		gcc level3.c -Wno-deprecated-declarations -no-pie -fno-stack-protector
	else
		gcc level3.c -Wno-deprecated-declarations -fno-stack-protector
fi
