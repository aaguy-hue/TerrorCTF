FROM pwn.red/jail
RUN mkdir /srv/app
COPY files/ /srv/app/
COPY files/ac /srv/app/run

ENV JAIL_TIME=60 JAIL_PIDS=10
