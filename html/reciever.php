<?php

// don't cache this
header("Cache-Control: no-cache, must-revalidate");
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");


if (!isset($_POST['command'])){
	die('no command');
}


$text = (string)time();
$text .= ",";
$text .= $_POST['command'];
$text .= ",";
if (isset($_POST['args']) && $_POST['args'] != ''){
	$text .= $_POST['args'];
}
$text .= "\n";

/*
if (filesize("../input.txt") != 0){
	echo('Warning: Command overwritten<br/>');
}
*/

if (file_put_contents("../input.txt", $text, FILE_APPEND) !== false){
	echo('ok');
} else {
	echo('err');
}
