<?php
	include("header.php");
	require_once("db_connect.php");
	$con = db_connect();
	$cat = mysqli_real_escape_string($con, $_GET['cat']);
	$order = mysqli_real_escape_string($con, $_GET['ord']);
	$result = mysqli_query($con, "SELECT name FROM category WHERE id=$cat;");
	$row = mysqli_fetch_array($result);
	printf("<h2>%s</h2>", $row['name']);
	echo "<br />\n<table>
			<thead>
				<tr>
				<th><a href=\"lister.php?cat=$cat&#38;ord=name\">Név</a></th>
				<th><a href=\"lister.php?cat=$cat&#38;ord=smd\">SMD</a></th>
				<th><a href=\"lister.php?cat=$cat&#38;ord=quantity\">Darabszám</a></th>
				<th><a href=\"lister.php?cat=$cat&#38;ord=description\">Leírás</a></th>				
				</tr>
			</thead>
			<tbody>\n";
	$result = mysqli_query($con,"SELECT * FROM part WHERE category_id=$cat ORDER BY $order ASC;");
	while($row=mysqli_fetch_array($result))	printf("<tr>\n<td>%s</td>\n<td class=\"centered\">%s</td>\n<td class=\"centered\">%d</td>\n<td>%s</td>\n</tr>\n", $row['name'], $row['smd'] ? "&#10004;" : "", $row['quantity'], $row['description']);
	echo "</tbody>\n</table>\n";
	$result = mysqli_query($con, "SELECT SUM(quantity) AS osszes, COUNT(name) as hanyfele FROM part WHERE category_id=$cat;");
	$row = mysqli_fetch_array($result);
	printf("<p>Összesen %d darab alkatrész (%d különböző típus).</p>", $row['osszes'], $row['hanyfele']);
	include("footer.php");
?>