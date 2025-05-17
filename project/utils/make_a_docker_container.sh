#!/usr/bin/env bash

# ========== STYLING Linux: ==========
# BOLD=$(tput bold)
# RESET=$(tput sgr0)
# RED="\e[1;31m"
# GREEN="\e[1;32m"
# YELLOW="\e[1;33m"
# BLUE="\e[1;34m"
# CYAN="\e[1;36m"

# ========== STYLING Mac: ==========
RESET="\033[0m"
BOLD="\033[1m"
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
CYAN="\033[1;36m"

# ========== USER INPUT ==========
# printf "\n${BOLD}${CYAN}Enter Project Root Directory${RESET}\n"
printf "\n${BOLD}${RED}You must have a utils folder in your root folder${RESET}\n"
read -e -p "Enter Project Root Directory... " PROJECT_DIR


if [ -z "$PROJECT_DIR" ]; then
	PROJECT_DIR="$(dirname "$PWD")"
	echo -e "${YELLOW}Using default:${RESET} $PROJECT_DIR"
else
	echo -e "${GREEN}Using custom folder:${RESET} $PROJECT_DIR"
fi

# Ensure utils/ exists
if [ ! -d "${PROJECT_DIR}/utils" ]; then
	printf "\n${BOLD}${YELLOW}⚠️  'utils/' folder not found in project root. Creating it...${RESET}\n"
	mkdir -p "${PROJECT_DIR}/utils"
	sleep 0.2
else
	printf "\n${GREEN}✅ 'utils/' folder found.${RESET}\n"
fi

# Docker status check
if docker info > /dev/null 2>&1; then
	printf "${GREEN}✅ Docker is already running. Skipping setup.${RESET}\n\n"
	cd "${PROJECT_DIR}/utils" || exit 1
	docker run -it -v "$PROJECT_DIR":/home leak_finder
	exit 0
fi
# Else... full Docker setup below

sleep 0.2

# ========== CHECK DOCKER INSTALLATION ==========
docker_destination="/goinfre/$USER/docker"

if [ ! -d "/Applications/Docker.app" ] && [ ! -d "$HOME/Applications/Docker.app" ]; then
	echo -e "\n${YELLOW}⚠️  Docker is not installed${RESET}"
	echo -e "Please install Docker via ${BLUE}Managed Software Center${RESET}, then press Enter to continue..."
	open -a "Managed Software Center"
	read -n 1
fi

sleep 0.2

# ========== RESET DOCKER CONFIG ==========
echo -e "\n${CYAN}🔧 Resetting Docker configuration...${RESET}"
pkill Docker 2> /dev/null

rm -rf ~/Library/Containers/com.docker.{docker,helper} ~/.docker > /dev/null 2>&1
mkdir -p "$docker_destination"/{com.docker.{docker,helper},.docker} > /dev/null 2>&1

ln -sf "$docker_destination"/com.docker.docker ~/Library/Containers/com.docker.docker
ln -sf "$docker_destination"/com.docker.helper ~/Library/Containers/com.docker.helper
ln -sf "$docker_destination"/.docker ~/.docker

echo -e "✅ Docker linked to: ${GREEN}$docker_destination${RESET}"

sleep 0.2

# ========== START DOCKER ==========
echo -e "\n${CYAN}🚀 Starting Docker...${RESET}"
open -g -a Docker

# ========== WAIT FOR DOCKER ==========
until docker info > /dev/null 2>&1; do
	echo -e "${YELLOW}⏳ Waiting for Docker daemon...${RESET}"
	sleep 5
done

# ========== BUILD DOCKER IMAGE ==========
cd "$PROJECT_DIR"/utils || exit 1

printf "\n${CYAN}🔨 Building Docker image...${RESET}"
cat <<EOF > Dockerfile
FROM alpine:latest
RUN apk add apt gcc make cmake valgrind vim clang g++ gdb
EOF

docker build -t leak_finder .

# ========== RUN CONTAINER ==========
cd .. || exit 1
printf "\n${GREEN}🐳 Running container...${RESET}"
docker run -it -v "$PROJECT_DIR":/home leak_finder
