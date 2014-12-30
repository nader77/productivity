#!/bin/sh
export passwd="myScretPass"
openssl aes-256-cbc -d -in salary.tar.gz.enc -pass env:passwd | tar xz
