#!/bin/bash

function do_make() {
	for file in $1/*
	do
		if [ -d $file ]
		then
			echo $file
			cd $file
			make clean
			make
			cd $1
		else
			echo $file
		fi
	done 
}

CUR_PATH=${PWD}/sszn
do_make $CUR_PATH
