#!/usr/bin/env bash

echo "
deb http://ddebs.ubuntu.com $(lsb_release -cs) main restricted universe multiverse
deb http://ddebs.ubuntu.com $(lsb_release -cs)-updates main restricted universe multiverse
deb http://ddebs.ubuntu.com $(lsb_release -cs)-security main restricted universe multiverse
deb http://ddebs.ubuntu.com $(lsb_release -cs)-proposed main restricted universe multiverse
" | sudo tee /etc/apt/sources.list.d/dbgsyms.list
wget -q http://ddebs.ubuntu.com/dbgsym-release-key.asc -O- | sudo apt-key add -

echo -e "APT::Install-Recommends "0";\nAPT::Install-Suggests "0";" | sudo tee /etc/apt/apt.conf.d/00bloatware

sudo apt-get update
sudo apt-get install synaptic

# synaptic: setup, upgrade && reboot

exit 0

