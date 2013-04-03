Web Control Myro Robot
====

Note:
* When a command looks like `cd` that means you can run in the grey command in the terminal.

To install: 
* First, `cd` to the directory you want to put `webbot` in.
* `apt-get install git apache2 php5`
* (It'll ask you your password, type your ubuntu password, then type Yes when it asks [Y/n] to intall)
* `git clone git://github.com/codejoust/webbot.git` 
* `cd webbot` then run `sudo install.sh`.

To configure the webserver:
* Setup a port forwarding rule in Virtualbox
* Go to Machine >> Settings...
* Go to the Network Tab
* Click "Port Forwarding"
* Click the Green plus icon to the right of the table
* Type in a new table line with the host port being 8080 and guest port being 80.
* Leave everything else blank!
* Hit tab, then click "ok" (if it doesn't work on the first time click "ok" again).
* You're good to go!

To run: 
* On your mac run the below command in the terminal:
* `ifconfig | grep inet | awk '{print "http://" $2 ":8080/robot/"}' | tail -n 1` 
* to get the URL to paste into your browser (or phone).
* `cd` to the directory where you cloned the repo,
* `./bin/runner /dev/ttyS0` (or whatever serial port you're using).


