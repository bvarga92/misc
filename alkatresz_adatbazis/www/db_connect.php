<?php
	$server = "db";
	$user = "root";
	$passwd = "12345";
	$database = "parts_db";
	function db_connect(){
		global $server, $user, $passwd, $database;
		error_reporting(0);
		$con = mysqli_connect($server, $user, $passwd, $database) or die("Kapcsolódási hiba: ".mysqli_connect_error());
		mysqli_query($con, "SET NAMES UTF8;");
		return $con;
	}
?>