for d in level*; do
    echo -n "const char *FLAG=\"CTF{" > "$d/flag.h"
    head -c 16 /dev/urandom | base64 | tr -d '\n' >> "$d/flag.h"
    echo "}\";" >> "$d/flag.h"
done
