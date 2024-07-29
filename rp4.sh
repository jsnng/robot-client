#! /usr/bin/bash

### This script is for Raspberry Pi on Robot Only . ###

sudo apt-get update
sudo apt-get upgrade --yes

sudo rm -rf /usr/lib/python3.11/EXTERNALLY-MANAGED*

libbcm_host='/lib/aarch64-linux-gnu/libbcm_host.so'
[[ -f $libbcm_host.0 ]] && sudo ln -s $libbcm_host.0 $libbcm_host

# upgrade pip 
sudo pip install --upgrade pip

# installing moteus
sudo pip3 install moteus
sudo pip3 install moteus-pi3hat

# installing tview from moteus
sudo apt-get install --yes python3-pyside2* python3-serial python3-can python3-matplotlib python3-qtconsole
sudo pip3 install asyncqt importlib_metadata pyelftools
sudo pip3 install --no-deps moteus_gui


# initialising this code module

sudo pip3 install --editable .[prod] # installing Module as editable # add [prod] at the end if you are doing it on RP4

git config submodule.src/Client/Shared.url 'git@github.com-shared:WSU-TurtleRabbit/shared.git'
git submodule update --init # initialising submodules

git config submodule.recurse true # this allows git to pull submodules as well
git pull

