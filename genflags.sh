for d in level*; do
    echo -n "#define FLAG \"CTF{" > "$d/flag.h"
    head -c 6 /dev/urandom | base64 | tr -d '\n' >> "$d/flag.h"
    echo "}\"" >> "$d/flag.h"
done