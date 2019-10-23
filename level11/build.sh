if [[ -n "`gcc -v -E 2>&1 | grep 'Configured with' | sed 's/--/\n--/g' | grep enable-default-pie`" ]]; 
	then
		gcc level11.c -Wno-deprecated-declarations -Wno-discarded-qualifiers -fstack-protector-strong
	else
		gcc level11.c -Wno-deprecated-declarations -Wno-discarded-qualifiers -pie -fstack-protector-strong
fi
