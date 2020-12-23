<!DOCTYPE html>
<html>
<head>
	<link href="style.css" rel="stylesheet" type="text/css" />
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<title>Alkatrész-nyilvántartás</title>
</head>
<body>
<div id="container">
	<div id="header">
		<h1><a href="index.php">Alkatrész-nyilvántartás</a></h1>
		<form action="search.php" method="GET">
			<input id="srctxt" type="text" name="src" value="Keresés..." onfocus="this.value='';" />
			<input type="image" src="search.png" alt="Keresés" />
			<input type="hidden" name="ord" value="name" />
		</form>
	</div>
<?php
	require_once("db_connect.php");
	$con = db_connect();
	$cat = mysqli_real_escape_string($con, $_GET['cat']);
?>
	<div id="navigation">
		<ul>
			<li><a href="lister.php?cat=1&#38;ord=name"<?php if($cat==1) echo " id=\"navigation_selected\""; ?>>ANALÓG IC</a></li>
			<li><a href="lister.php?cat=2&#38;ord=name"<?php if($cat==2) echo " id=\"navigation_selected\""; ?>>DIGITÁLIS IC</a></li>
			<li><a href="lister.php?cat=3&#38;ord=name"<?php if($cat==3) echo " id=\"navigation_selected\""; ?>>BIPOLÁRIS TRANZISZTOR</a></li>
			<li><a href="lister.php?cat=4&#38;ord=name"<?php if($cat==4) echo " id=\"navigation_selected\""; ?>>FET TRANZISZTOR</a></li>
			<li><a href="lister.php?cat=5&#38;ord=name"<?php if($cat==5) echo " id=\"navigation_selected\""; ?>>DIÓDA</a></li>
			<li><a href="lister.php?cat=6&#38;ord=name"<?php if($cat==6) echo " id=\"navigation_selected\""; ?>>STABILIZÁTOR</a></li>
			<li><a href="lister.php?cat=7&#38;ord=name"<?php if($cat==7) echo " id=\"navigation_selected\""; ?>>TIRISZTOR, TRIAK, DIAK</a></li>
		</ul>
	</div>
	<div id="content-container">
		<div id="content">
