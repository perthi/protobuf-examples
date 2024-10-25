// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#define GTEST_BREAK_ON_FAILURE 1

#include <utilities/GDefinitions.h>
#ifdef _WIN32
#include <gtest/gtest.h>
#else
#include <gtest-linux/gtest.h>
#endif
#include  <cmdline/GLogApplication.h>



MAIN_UNITTEST()