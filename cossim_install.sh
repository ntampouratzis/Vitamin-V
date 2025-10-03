#Setup on Ubuntu 22.04
sudo apt update

##gem5 prerequisites
sudo apt install build-essential git m4 scons zlib1g zlib1g-dev libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev python3-dev python3-six python-is-python3 libboost-all-dev pkg-config

##certi prerequisites
sudo apt install cmake bison flex libxml2-dev
sudo apt install cmake bison flex libxml2-dev libstdc++-12-dev

##omnet 5.0 prerequisites
sudo add-apt-repository ppa:ubuntuhandbook1/ppa (https://ubuntuhandbook.org/index.php/2020/07/install-qt4-ubuntu-20-04/)
sudo apt install openjdk-8-jdk openjdk-8-jre tcl-dev tk-dev qt4-qmake libqt4-dev libqt4-opengl-dev openmpi-bin libopenmpi-dev clang


#Manual Installation
cd $HOME
git clone https://github.com/ntampouratzis/Vitamin-V.git
mv -f $HOME/Vitamin-V $HOME/COSSIM

##cCERTI & Our SynchServer Installation
cd $HOME/COSSIM/cCERTI
mkdir build_certi
cd build_certi
cmake -DCMAKE_INSTALL_PREFIX=$HOME/COSSIM/cCERTI/build_certi $HOME/COSSIM/cCERTI

make
make install

cd $HOME/COSSIM/cCERTI/SynchServer
./build.sh

cd $HOME/COSSIM/cCERTI
cp Federation.fed $HOME/COSSIM/cCERTI/build_certi/share/federations

echo "#cCERTI exports" >> ~/.bashrc
echo "export CERTI_HOME=$HOME/COSSIM/cCERTI/build_certi" >> ~/.bashrc
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/COSSIM/cCERTI/build_certi/lib" >> ~/.bashrc
echo "export PATH=$HOME/COSSIM/cCERTI/build_certi:$PATH" >> ~/.bashrc
echo "export PATH=$HOME/COSSIM/cCERTI/build_certi/bin:$PATH" >> ~/.bashrc
echo "export CERTI_SOURCE_DIRECTORY=$HOME/COSSIM/cCERTI" >> ~/.bashrc
echo "export CERTI_BINARY_DIRECTORY=$HOME/COSSIM/cCERTI/build_certi" >> ~/.bashrc
echo "#change CERTI_HOST if you want to use HLA Server (rtig) and SynchServer from another machine" >> ~/.bashrc
echo "export CERTI_HOST=127.0.0.1" >> ~/.bashrc

##cgem5 Installation
cd $HOME/COSSIM/cgem5
source ~/.bashrc
scons build/RISCV/gem5.fast -j4

##Untar kernels and images in $HOME/COSSIM directory
cd $HOME/COSSIM/kernels
cat kernels.tar.xz* | tar xzvf -
tar -xf kernels.tar.xz

echo "#GEM5 exports" >> ~/.bashrc
echo "export GEM5=$HOME/COSSIM/cgem5" >> ~/.bashrc
echo "export M5_PATH=$HOME/COSSIM/kernels" >> ~/.bashrc

##cMcPAT Installation
#cd $HOME/COSSIM/cgem5/McPat/mcpat
#make all
#cd $HOME/COSSIM/cgem5/McPat/Scripts
#chmod +x GEM5ToMcPAT.py
#chmod +x print_energy.py

## cOMNET++ with COSSIM WORKSPACE Installation
## Download OMNeT++ 5.0 from http://omnetpp.org. Make sure you select to download the generic archive, omnetpp-5.0-src.tgz.

##Untar it in the $HOME directory & execute the following commands:
cd $HOME
tar xvfz omnetpp-5.0-src.tgz
cd omnetpp-5.0
export PATH=$PATH:$HOME/omnetpp-5.0/bin
./configure && make

mkdir $HOME/COSSIM/OMNETPP_COSSIM_workspace/OMNET_WORKSPACE/HLANode/simulations

echo "export PATH=$PATH:$HOME/omnetpp-5.0/bin" >> ~/.bashrc
echo "export OMNETWP=$HOME/COSSIM/OMNETPP_COSSIM_workspace/OMNET_WORKSPACE" >> ~/.bashrc
source ~/.bashrc

##Execute OMNET++ and import the COSSIM-OMNET workspace (it contains INET-3.2.4 version)
omnetpp
##Select Browse -> $HOME -> COSSIM -> OMNETPP_COSSIM_workspace -> OMNET_WORKSPACE -> Press “OK”

##Build OMNET_WORKSPACE
o	Select Project -> Clean -> Select “INET” -> Select “Start a build immediately” -> Select “Build only the selected projects” -> Press “OK”
o	Select Project -> Clean -> Select “HLANode” & “test” -> Select “Start a build immediately” -> Select “Build only the selected projects” -> Press “OK”

# Install Riscv qemu on Ubuntu 22.04
cd $HOME
sudo apt-get install ninja-build
sudo apt install libglib2.0-dev libpixman-1-dev
mkdir riscv-ubuntu/
cd riscv-ubuntu/
git clone https://github.com/qemu/qemu
cd qemu/
git checkout 0021c4765a6b83e5b09409b75d50c6caaa6971b9
./configure --target-list=riscv64-softmmu
make -j $(nproc)
make install

# Install OpenSBI on Ubuntu 22.04
sudo apt install qemu-system-misc opensbi u-boot-qemu qemu-utils
sudo apt install gcc-riscv64-linux-gnu g++-riscv64-linux-gnu
