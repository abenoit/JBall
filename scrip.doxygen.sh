#!/bin/bash

if [ -f ./html/index.html ]
then
  firefox ./html/index.html
else
  echo "La documentation n'a pas été générée"
fi