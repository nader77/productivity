#!/bin/sh
export passwd="myScretPass"
tar cz node | \
      openssl enc -aes-256-cbc -pass env:passwd -e > node.tar.gz.enc
