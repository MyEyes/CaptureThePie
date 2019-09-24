if [[ -n "`gcc -v -E 2>&1 | grep 'Configured with' | sed 's/--/\n--/g' | grep enable-default-pie`" ]]; 
	then
		gcc level9.c -Wno-deprecated-declarations -Wno-discarded-qualifiers
	else
		gcc level9.c -Wno-deprecated-declarations -Wno-discarded-qualifiers -pie
fi
