#!/bin/bash

sudo apt-get install -y  git-extras \
     qt5-default qtcreator \
     libqt5gstreamer-dev \
     libboost-all-dev \
     libreadline-dev \
     libxml2-dev \
     qtdeclarative5-dev


sudo ln -s /usr/include/Qt5GStreamer  /usr/include/QtGStreamer
sudo ln -s /usr/lib/x86_64-linux-gnu/libgstreamer-1.0.so.0 /usr/lib/x86_64-linux-gnu/libgstreamer-1.0.so
sudo ln -s /usr/lib/x86_64-linux-gnu/libQt5GLib-2.0.so /usr/lib/x86_64-linux-gnu/libQtGLib-2.0.so
sudo ln -s /usr/lib/x86_64-linux-gnu/libQt5GStreamer-1.0.so /usr/lib/x86_64-linux-gnu/libQtGStreamer-1.0.so
sudo ln -s /usr/lib/x86_64-linux-gnu/libQt5GStreamerUi-1.0.so /usr/lib/x86_64-linux-gnu/libQtGStreamerUi-1.0.so
sudo apt-get install qtdeclarative5-dev
sudo apt-get install autoconf automake libtool curl make g++ unzip
sudo apt-get install pkg-config
sudo apt-get install qtquick1-5-dev
sudo apt-get install python-protobuf
