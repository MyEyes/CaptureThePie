FROM python:3.11.0b1-alpine3.16
RUN apk add --no-cache socat gcc musl-dev
RUN pip3 install flask
COPY . /work
WORKDIR /work

RUN [ "/bin/sh", "-c", "cd /work; ls -al; ./build.sh"]

RUN apk del gcc musl-dev
RUN adduser -S ctf

ENTRYPOINT [ "/bin/sh", "-c",  "./run.sh & cd web; ./start.sh"]
#docker build -t capthepie
#docker run -t --rm -p 4444:5000 -p 9000-9020:9000-9020 capthepie