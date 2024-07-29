#! /usr/bin/bash

crontab -l > .old
echo "@reboot" >> .new
sudo crontab .new
rm .old .new