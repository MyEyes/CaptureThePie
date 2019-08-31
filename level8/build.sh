if [[ -n "`gcc -v -E 2>&1 | grep 'Configured with' | sed 's/--/\n--/g' | grep enable-default-pie`" ]]; 
	then
		gcc level8.c -Wno-deprecated-declarations -Wno-discarded-qualifiers -Wl,-z,norelro
	else
		gcc level8.c -Wno-deprecated-declarations -Wno-discarded-qualifiers -pie
fi
