Web Control Myro Robot
====

To install: run `git clone git://github.com/codejoust/webbot.git` in the terminal, then `cd webbot` then run `sudo install.sh`.

To run: go to your mac and type `ifconfig | grep inet | awk '{print "http://" $2 ":8080"}' | tail -n 1` to get the URL to paste into your browser.
  then CD to the directory where you cloned the repo, then run `./bin/runner /dev/ttyS0` (or whatever serial port you're using).




