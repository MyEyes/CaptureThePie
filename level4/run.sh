socat -dd TCP4-LISTEN:9004,fork,reuseaddr EXEC:./a.out,pty,setuid=firzen,echo=0,raw,iexten=0 &
