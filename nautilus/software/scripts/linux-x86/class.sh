#!/bin/bash
classfilename=$1


classfilename_h=$classfilename.h
classfilename_cpp=$classfilename.cpp


function licence
{
    printf "/***************************************************\n"  >>  $1
    printf "* @copyright Kongsberg Ferrotech                   *\n"  >>  $1
    printf "* @author Per Thomas Hille <pth@embc.no>           *\n"  >>  $1
    printf "*                                                  *\n"  >>  $1
    printf "* SW developed by Embedded Consulting AS           *\n"  >>  $1
    printf "* for Semcon Norge AS                              *\n"  >>  $1
    printf "***************************************************/\n"  >>  $1
}


classname=$classfilename
if [ "$#" -ne 1 ]; then
    echo "usage: $0 [classname]"
    exit 0
fi


if [  -a $classfilename_h ] || [ -a $classfilename_cpp ];then
    echo ERROR, $classfilename_h and $classfilename_cpp allready exist, delelte them or rename the class you want to make
else 
    echo creating new files   $classfilename_h and $classfilename_cpp

    printf "// -*- mode: c++ -*-\n" >  $classfilename_h
    
    printf "#ifndef " >> $classfilename_h
    classguard=${classfilename_h/.h/_H}

    echo $classguard | tr "[:lower:]" "[:upper:]"  >> $classfilename_h
    printf "#define " >> $classfilename_h
    echo $classguard | tr "[:lower:]" "[:upper:]"  >> $classfilename_h

    licence $classfilename_h 
    
    printf "\n" >>$classfilename_h 
    printf "\n\n\n" >>$classfilename_h 
    printf "class " >> $classfilename_h
    printf " $classname\n{\n\t$classname();\n\tvirtual ~$classname();\n};\n\n#endif\n" >> $classfilename_h  

    printf "// -*- mode: c++ -*-\n" >  $classfilename_cpp
    
    licence $classfilename_cpp
    
    printf "#include \"$classfilename_h\"\n\n" >>  $classfilename_cpp
    printf "$classname::$classname()\n{\n\n}\n\n" >> $classfilename_cpp
    printf "$classname::~$classname()\n{\n\n}\n\n" >> $classfilename_cpp

fi

