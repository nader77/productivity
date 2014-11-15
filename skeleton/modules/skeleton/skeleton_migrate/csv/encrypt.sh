#!/bin/sh
tar cz node | \
      openssl enc -aes-256-cbc -e > node.tar.gz.enc
