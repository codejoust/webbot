<?php

// don't cache this
header("Cache-Control: no-cache, must-revalidate");
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");


$input_filename = ($_GET['type'] == 'display') ? '../display.txt' : '../output.txt';

$initial_mtime = filemtime($input_filename);

// http://stackoverflow.com/questions/1510141/read-last-line-from-file
function read_last_line($input_filename){
	$cmd = exec("tail -n 1 " . $input_filename);
	echo $cmd;
	flush();
	/*$cmd_ary = explode(':', $cmd);
	$cmd = $cmd_ary[0];
	$cmd .= '(';
	if (count($cmd_ary) > 1){
		$cmd .= '"' . $cmd_ary[1] . '"';
	}
	$cmd .= ');';*/
	
}

$max_times = 10000;

while (filemtime($input_filename) == $initial_mtime){
	usleep(20000);
	clearstatcache();
}

read_last_line($input_filename);