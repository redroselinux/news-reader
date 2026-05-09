#!/bin/sh
set -e
version=0.1

if [ ! -e ./news_reader ]; then
    nimble build
fi

rm -rf package
mkdir package
echo "version $version" > package/car
mkdir package/usr
mkdir package/usr/bin
cp ./news_reader package/usr/bin/news-reader
tar -I zstd -cf news-reader.tar.zst package/
