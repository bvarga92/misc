<?php
	include("header.php");
	require_once("db_connect.php");
	$con = db_connect();
	$src = mysqli_real_escape_string($con, $_GET['src']);
	$order = mysqli_real_escape_string($con, $_GET['ord']);
	echo "<h2>Keresés a következőre: $src</h2>";
	$result = mysqli_query($con, "SELECT * FROM part WHERE name LIKE '%$src%' OR description LIKE '%$src%' ORDER BY $order ASC;");
	if(mysqli_affected_rows($con)){
		echo "<br />\n<table>
				<thead>
					<tr>
					<th><a href=\"search.php?src=$src&#38;ord=name\">Név</a></th>
					<th><a href=\"search.php?src=$src&#38;ord=smd\">SMD</a></th>
					<th><a href=\"search.php?src=$src&#38;ord=quantity\">Darabszám</a></th>
					<th><a href=\"search.php?src=$src&#38;ord=description\">Leírás</a></th>				
					</tr>
				</thead>
				<tbody>\n";
		while($row=mysqli_fetch_array($result))	printf("<tr>\n<td>%s</td>\n<td class=\"centered\">%s</td>\n<td class=\"centered\">%d</td>\n<td>%s</td>\n</tr>\n", $row['name'], $row['smd'] ? "&#10004;" : "", $row['quantity'], $row['description']);
		echo "</tbody>\n</table>\n";
		$result=mysqli_query($con,"SELECT SUM(quantity) AS osszes, COUNT(name) as hanyfele FROM part WHERE name LIKE '%$src%' OR description LIKE '%$src%';");
		$row=mysqli_fetch_array($result);
		printf("<p>Összesen %d darab alkatrész (%d különböző típus).</p>", $row['osszes'], $row['hanyfele']);
	}
	else
		echo "<p>Nincs találat!</p>";
	include("footer.php");
?>