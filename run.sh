SCRIPT_PATH=$(readlink -f "$0")
CTF_PATH="$SCRIPT_PATH/terrorctf"

docker-compose -f $CTF_PATH/docker-compose.yml rm -f
docker-compose -f $CTF_PATH/docker-compose.yml pull
docker-compose -f $CTF_PATH/docker-compose.yml up --build -d
