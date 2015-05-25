#/bin/sh -f

# things to do for travis-ci in the before_install section

if ( test "`uname -s`" = "Darwin" )
then
    #cmake v2.8.12 is installed on the Mac workers now
    #brew update
    #brew install cmake
    echo
else
    #install a newer cmake since at this time Travis only has version 2.8.7
    sudo add-apt-repository --yes ppa:kalakris/cmake
    sudo apt-get update -qq
    sudo apt-get install cmake
fi

sudo apt-get update >/dev/null
sudo apt-get -q install check libprotobuf-c0-dev protobuf-c-compiler

#wget https://github.com/google/protobuf/releases/download/v2.5.0/protobuf-2.5.0.tar.gz
#tar -xvzf protobuf-2.5.0.tar.gz
#cd protobuf-2.5.0
#./configure && sudo make install
#cd ..
