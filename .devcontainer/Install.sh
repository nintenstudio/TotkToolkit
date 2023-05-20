sudo apt install -y software-properties-common

sudo apt-get update
sudo apt-get install -y clang

chmod +x ./.devcontainer/install-devkitpro-pacman.sh
sudo ./.devcontainer/install-devkitpro-pacman.sh
printf "\n y" | sudo dkp-pacman -S switch-dev
echo 'DEVKITPRO=/opt/devkitpro' >> /etc/environment 

git submodule update --init --recursive
