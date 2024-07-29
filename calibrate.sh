#! /usr/bin/bash

curl -O https://github.com/mjbots/moteus/releases/download/0.1-20240617/20240617-moteus-863c597794066fa77c94828c0d2eb49614d5ebb0.elf
sudo moteus_tool --pi3hat-cfg "1=2" -t 2 --flash ../20240617-moteus-863c597794066fa77c94828c0d2eb49614d5ebb0.elf
sudo moteus_tool --pi3hat-cfg "1=2" -t 2 --calibrate