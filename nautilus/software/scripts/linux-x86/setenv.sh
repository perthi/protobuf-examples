#!/bin/bash

alias f='cd  $FERROTECH_HOME/software'
alias b='cd  $FERROTECH_HOME/software/build/x86/bin'
export PS1="\[\033[36m\]\u\[\033[m\]@\[\033[32m\] \[\033[33;1m\]\w\[\033[m\] (\$(git branch 2>/dev/null | grep '^*' | colrm 1 2)) \$ "

alias m='make x86 -j'

export QT_INCLUDE=/usr/include/x86_64-linux-gnu/qt5/
export QT_DIR=$HOME/Qt/5.12.2/
#export QT_LIBS=$QT_DIR/gcc_64/lib
#export QT_LIBS=/usr/lib/x86_64-linux-gnu/
#export QT_DEBUG_PLUGINS=1

#export FERROTECH_HOME=$HOME/nautilus/
export LD_LIBRARY_PATH=$QT_LIBS:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$FERROTECH_HOME/software/build/x86/lib
