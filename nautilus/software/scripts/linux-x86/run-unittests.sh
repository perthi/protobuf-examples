#!/bin/bash


# Script that runs unit tests. The script atomatically fetches all unit tests from
# the bin directory. Test unit tests can run with 3 different targets
# - x86  Your local PC
# - fec  The FEC linux board from EMCRAFT (or any other Linux arm board) 
# - qemu The arm emulator running under Linux
#
# Author: Per Thomas Hille, Embedded Consulting AS for Semcon Devotek
# email:  pth@embc.no
#


##testcard=$fec5
##x86_dir=$UCW_HOME/build/x86/bin/
##arm_dir=$UCW_HOME/build/arm/bin/

x86_dir=$FERROTECH_HOME/software/build/x86/bin/
arm_dir=$FERROTECH_HOME/software/build/arm/bin/

rm -f  googletest.log

run_test ()
{
    testname=$2
    testname=${testname/*\//};
    
    case $1 in
        x86)
            echo "Running tests "$testname "for" $1 "cmd =" $2
            $2
            ;;
        qemu)
            echo "Running arm emulation unit test for "$testname "for" $1
            LD_LIBRARY_PATH=$UCW_HOME/build/arm/lib:$UCW_HOME/arm-extras
            qemu-arm $arm_dir/$testname
            ;;
        fec)
            if [ "$#" -ne 3 ]; then
                echo "Illegal number of parameters, for testing on the FEC you must specify the IP address of the board"
                echo "Usage" $0 "[target]  [IP addresss]"
                exit -1
            else
                testcard=$3
            fi
            echo "FEC Running tests "$testname "for" $1 
#            cp $arm_dir/* /home/imx/share
            ssh imx@$testcard  "fec-run-unittests.sh $testname"
            ;;
        *)
            echo "Error, target must be one of: x86, qemu, fec, you have typed " $1
            ;;
    esac
}



check_params()
{
    if [ "$#" -le 0 ]; then
        echo error, tto few parametes "$#"
    else
        if  [ "$1" != "x86" ] && [ "$1" != "fec" ] &&  [ "$1" != "qemu"  ]; then
            usage
        else
            if [ "$1" = "x86" ] ||  [ "$1" = "qemu" ]  ; then
                if [ "$#" -ge 2 ]; then
                    printf "too many parameters expected 1, got %d\n", "$#"
                    usage
                    exit
                fi
            fi
            if [ "$1" = "fec" ] ; then
                if [ "$#" -ne 2 ]; then
                    printf "Wrong number of parameters expeceted 2, got %d\n",  "$#"
                    usage
                    exit
                fi
            fi
        fi
    fi
}



usage()
{
    printf "\n"
    printf "\tUsage: %s [target]\t\t(for target = x86 or qemu-arm) \n", $0
    printf "\t\tOR\n"
    printf "\tUsage: %s [target] [ip_address]\t(for target = fec)\n", $0
    printf "\n"
}


check_params $*

#exit

if [ "$1" = "fec" ]; then
     testcard=$2
     ping -w 2 $testcard
     if [ $? -ne 0 ]; then
         echo "ERROR, unable to contact card with IP address" $testcard ",.aborting test..."
         exit 1
     fi
fi



if [ "$1" = "x86" ]; then
       tests=('/build/x86/bin/*unit-test*')
elif  [ "$1" = "fec" ] ||    [ "$1" = "qemu"  ]; then
    tests=('build/arm/bin/*unit-tests*')
else
    echo "usage: " $0 "[target]  where target is either x86, fec, or qemu" 
fi


tests=$FERROTECH_HOME/software/$tests


for test in $tests; do
  #  echo running tets for $test !! argument  = $1
    run_test $1 $test $2
    
    retVal=$?
    
    if [ $retVal -ne 0 ]; then
        exit $retVal 
    fi
done


rm -f dead_letters.log googletest_logging_file_io.log  invalid_letters.log  lost_letters.log  messages.log  mylogfile.log write_read.xml
rm -rf testdir
rm -f z.xml


exit $retVal

