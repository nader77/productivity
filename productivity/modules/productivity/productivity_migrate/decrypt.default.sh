#!/bin/sh
export passwd="myScretPass"
openssl aes-256-cbc -d -in csv.tar.gz.enc -pass env:passwd | tar xz
