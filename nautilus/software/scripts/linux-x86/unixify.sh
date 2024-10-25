#!/bin/bash
#convert all files in all subdirectores to unix style line endings
find . -type f -print0 | xargs -0 dos2unix
