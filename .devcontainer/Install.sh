sudo apt install -y software-properties-common

sudo apt-get update
sudo apt-get install -y clang

chmod +x ./.devcontainer/install-devkitpro-pacman.sh
sudo ./.devcontainer/install-devkitpro-pacman.sh
printf "\n" | sudo dkp-pacman -S switch-dev

git submodule update --init --recursive
