#!/bin/sh
export passwd="myScretPass"
tar cz csv/salary.csv | \
      openssl enc -aes-256-cbc -pass env:passwd -e > salary.tar.gz.enc
