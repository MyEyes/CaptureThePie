if [[ -n "`gcc -v -E 2>&1 | grep 'Configured with' | sed 's/--/\n--/g' | grep enable-default-pie`" ]]; 
	then
		gcc level5.c -Wno-deprecated-declarations -fno-stack-protector
	else
		gcc level5.c -Wno-deprecated-declarations -pie -fno-stack-protector
fi
