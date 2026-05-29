#!/bin/sh

set -e
version=0.2

echo "Building news-reader package"
echo " => Compiling news-reader $version [Running 'make']"
make >/dev/null
echo " => Creating Car package"
echo "  ==> Installing to staging directory [Running 'make']"
make install DESTDIR=$(pwd)/package >/dev/null
echo "  ==> Creating Car metadata [Running 'echo']"
echo "version $version" > package/car
echo "  ==> Creating final Car package [Running 'tar']"
tar -I zstd -cf news-reader.tar.zst package/
echo "-> [built] news-reader.tar.zst"
echo " => Cleaning up [Running 'rm' and 'make']"
rm -rf package
make clean >/dev/null
