<?php

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
