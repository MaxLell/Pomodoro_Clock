#!/bin/sh

# Add the respective folders of the parent directory:
# - App and all of its subfolder
# - Bsp and all of its subfolders
# - Drivers and all of its subfolders, except the files, which are provided
#   by the Microcontroller vendor
echo "Enter Directory to check"

read current_dir

echo " "
echo " -------------------------------------------------"
echo " --------------------- Misra ---------------------"
echo " -------------------------------------------------"
echo " "

for entry in "$current_dir"/*
do
  cppcheck --addon=misra.py "$entry"
done

echo " "
echo " -------------------------------------------------"
echo " --------------------- Lint ----------------------"
echo " -------------------------------------------------"
echo " "

for subfolder in "$current_dir"/*
do
  for file in "$subfolder"/*
  do
    cpplint --filter=-build/header_guard,-legal/copyright "$file"
  done
done