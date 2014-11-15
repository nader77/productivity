#!/bin/sh
openssl aes-256-cbc -d -in node.tar.gz.enc | tar xz
