sudo apt install -y software-properties-common

wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
sudo apt-add-repository "deb http://apt.llvm.org/buster/ llvm-toolchain-buster main"
sudo apt-get update
sudo apt-get install -y clang

git submodule update --init --recursive
