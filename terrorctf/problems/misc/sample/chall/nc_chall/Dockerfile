FROM pwn.red/jail
RUN mkdir /srv/app
COPY container_files/ /srv/app/
COPY container_files/SAMPLE_BINARY /srv/app/run
# RUN mv /srv/app/SAMPLE_BINARY /srv/app/run

# Allow each connection to last 1 min and
# allow up to 10 pids, increase the limit
# from the default of 5 if you have errors
ENV JAIL_TIME=60 JAIL_PIDS=10

