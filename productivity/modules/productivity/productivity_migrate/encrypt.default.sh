#!/bin/sh
export passwd="myScretPass"
tar cz csv | \
      openssl enc -aes-256-cbc -pass env:passwd -e > csv.tar.gz.enc
