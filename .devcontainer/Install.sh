sudo apt install -y software-properties-common

sudo apt-get update
sudo apt-get install -y clang

wget https://apt.devkitpro.org/install-devkitpro-pacman
chmod +x ./install-devkitpro-pacman
sudo ./install-devkitpro-pacman
rm ./install-devkitpro-pacman
sudo dkp-pacman -S switch-dev

git submodule update --init --recursive
