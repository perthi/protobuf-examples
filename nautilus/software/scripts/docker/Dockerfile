FROM ubuntu:18.04
LABEL Description="Ubuntu 18.04 Ferrotech Configuration"
USER root

ENV DEBIAN_FRONTEND noninteractive
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# ENV
env FERROTECH_HOME /root/nautilus
env QT_INCLUDE /usr/include/x86_64-linux-gnu/qt5

# Bare minimum
RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
RUN apt-get update && apt-get install -y --no-install-recommends dialog
RUN apt-get update && apt-get install -y build-essential cmake make g++
RUN apt-get update && apt-get install -y gcovr

# Install robotframework
# RUN apt-get update && apt-get -y install python python-pip
# RUN pip install robotframework

RUN apt-get update && apt-get install -y wget curl unzip xz-utils
RUN apt-get update && apt-get install -y automake autoconf
RUN apt-get update && apt-get install -y pkg-config libtool

# Boost / Protobuf / xml / readline
RUN apt-get update && apt-get install -y libboost-all-dev
RUN apt-get update && apt-get install -y libprotobuf-dev protobuf-compiler python-protobuf
RUN apt-get update && apt-get install -y google-mock libgtest-dev
RUN apt-get update && apt-get install -y libxml2 libxml2-dev
RUN apt-get update && apt-get install -y libreadline7 libreadline-dev

# X11
# RUN apt-get update && apt-get install -y xorg xserver-xorg-legacy xinit xterm
# RUN apt-get update && apt-get install -y libx11-dev

# GIT
RUN apt-get update && apt-get install -y git git-extras

# ARM
# RUN apt-get update && apt-get install -y binutils-arm-linux-gnueabi
# RUN apt-get update && apt-get install -y libc6-armel-cross libc6-dev-armel-cross
# RUN apt-get update && apt-get install -y gcc-arm-linux-gnueabi g++-arm-linux-gnueabi
# RUN apt-get update && apt-get install -y gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf

# ncurses
# RUN apt-get update && apt-get install -y libncurses5-dev libncurses-dev

# QT
RUN apt-get update && apt-get install -y qt5-default
RUN apt-get update && apt-get install -y libqt5charts5-dev
RUN apt-get update && apt-get install -y qtdeclarative5-dev qtquickcontrols2-5-dev
RUN apt-get update && apt-get install -y libqt5gstreamer-dev
# RUN apt-get update && apt-get install -y
# RUN apt-get update && apt-get install -y qtcreator


# etc
# RUN apt-get update && apt-get install -y libgl1-mesa-dev
# RUN apt-get update && apt-get install -y x11vnc xvfb
# RUN apt-get update && apt-get install -y dbus dbus-x11

# ERROR
# RUN apt-get update && apt-get install -y qtquick1-5-dev


# not sure if correct package
# libqt5gstreamer-dev libqtgstreamer-dev

# GStreamer Library fix
RUN ln -s /usr/include/Qt5GStreamer /usr/include/QtGStreamer
RUN ln -s /usr/lib/x86_64-linux-gnu/libgstreamer-1.0.so.0 /usr/lib/x86_64-linux-gnu/libgstreamer-1.0.so
RUN ln -s /usr/lib/x86_64-linux-gnu/libQt5GLib-2.0.so /usr/lib/x86_64-linux-gnu/libQtGLib-2.0.so
RUN ln -s /usr/lib/x86_64-linux-gnu/libQt5GStreamer-1.0.so /usr/lib/x86_64-linux-gnu/libQtGStreamer-1.0.so
RUN ln -s /usr/lib/x86_64-linux-gnu/libQt5GStreamerUi-1.0.so /usr/lib/x86_64-linux-gnu/libQtGStreamerUi-1.0.so

# Qt5 Linking problem. This comments out the error message.
RUN sed -i '1135 s/^/#/' /usr/include/x86_64-linux-gnu/qt5/QtCore/qglobal.h

# Installing GCC-9
RUN apt-get install -y software-properties-common

#RUN add-apt-repository -y ppa:jonathonf/gcc-9
#RUN add-apt-repository -y ppa:jonathonf/gcc-10

RUN apt install -y gcc++-9


RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 10
#RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 20