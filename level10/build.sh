if [[ -n "`gcc -v -E 2>&1 | grep 'Configured with' | sed 's/--/\n--/g' | grep enable-default-pie`" ]]; 
	then
		gcc level10.c -Wno-deprecated-declarations -Wno-discarded-qualifiers -Wl,-z,relro,-z,now -fstack-protector-strong
	else
		gcc level10.c -Wno-deprecated-declarations -Wno-discarded-qualifiers -pie -Wl,-z,relro,-z,now -fstack-protector-strog
fi
