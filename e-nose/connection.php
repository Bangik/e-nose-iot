<?php

$host     = 'localhost';
$user     = 'aldifirm_e-nose';
$password = 'e-nose-lala';
$db       = 'aldifirm_e-nose';


$link = mysqli_connect($host, $user, $password, $db);
if (!$link) {
    die("Connection failed: " . mysqli_connect_error());
}

?>
