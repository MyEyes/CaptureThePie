socat -dd TCP4-LISTEN:9000,fork,reuseaddr EXEC:./a.out,pty,setuid=ctf,echo=0,raw,iexten=0 &
