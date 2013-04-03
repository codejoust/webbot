#!/bin/bash
DIR="$( cd "$( dirname "$0" )" && pwd )"
chmod 777 *.txt 
cd /var/www && ln -s $DIR/html ./robot

