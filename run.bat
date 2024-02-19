@echo off

set SCRIPT_PATH=%~dp0
set "CTF_PATH=%SCRIPT_PATH%terrorctf"

rem Removing the old docker images...
docker compose -f %CTF_PATH%\docker-compose.yml rm -f

rem Pulling the latest version of the docker images...
docker compose -f %CTF_PATH%\docker-compose.yml pull

rem Running the services!
docker compose -f %CTF_PATH%\docker-compose.yml up --build
