socat -dd TCP4-LISTEN:9002,fork,reuseaddr EXEC:./a.out,pty,setuid=firzen,echo=0,raw,iexten=0 &
