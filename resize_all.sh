#!/bin/bash

WIDTH=800
HEIGHT=600
BORDER_WIDTH=12
BORDER_COLOR=0xFFFFFFFF

for i in *.jpg; do
	echo "Processing file: $i"
	./border $i $WIDTH $HEIGHT $BORDER_WIDTH $BORDER_COLOR
done
