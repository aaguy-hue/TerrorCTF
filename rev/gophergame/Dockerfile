FROM pwn.red/jail
RUN mkdir /srv/app
COPY gameflag.txt /srv/app/
COPY game /srv/app/run
ENV JAIL_TIME=60 JAIL_PIDS=10
