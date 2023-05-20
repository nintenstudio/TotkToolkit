sudo apt install -y software-properties-common

sudo apt-get update
sudo apt-get install -y clang

chmod +x ./install-devkitpro-pacman.sh
sudo ./install-devkitpro-pacman.sh
sudo dkp-pacman -S switch-dev

git submodule update --init --recursive
