sudo apt install -y software-properties-common

sudo apt-get update
sudo apt-get install -y clang

chmod +x ./.devcontainer/install-devkitpro-pacman.sh
sudo ./.devcontainer/install-devkitpro-pacman.sh
printf "\n y" | sudo dkp-pacman -S switch-dev
printf "\n y" | sudo dkp-pacman -S switch-mesa
echo 'export DEVKITPRO=/opt/devkitpro' >> ~/.bashrc

sudo apt install libxrandr-dev -y
sudo apt install libxinerama-dev -y
sudo apt install libxcursor-dev -y
sudo apt install libxi-dev -y
sudo apt install libgl1-mesa-dev -y
sudo apt install libegl1-mesa-dev -y

git submodule update --init --recursive

cp ./.devcontainer/CMakeUserPresets.json ./CMakeUserPresets.json