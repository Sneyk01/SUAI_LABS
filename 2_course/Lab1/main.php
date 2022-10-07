<!DOCTYPE html>

<?php
	include "auth.php";
	include "functions.php";
	include "data_base_functions.php";
	
	$db = open_data("data.json");
	
	$user_name = check_token($db);
	
	if(!(isset($_GET["message"]))) check_time_p($db);
?>

<html>
<head>
	<title> main </title>
</head>

<body>
	<table border= "0" bordercolor = "grey" height = 50> </table>

	<table border = "0" bordercolor = "black" align = "center" height = 528 bgcolor = "#D9D9D9">
		<tr align = "center" height = 156> 
			<td width = "300"> 
				<h2> Hello,
					<?php print($user_name); ?>
					!
				</h2>
			</td>
		</tr>
		
		<tr align = "center" height = 20> <td> <hr color = "black", size = 2 width = 100> </hr> </td> </tr>
		<tr align = "center" height = 25> <td> <h3 style = "color: #4d4d4d"> Change Password </h3> </td> </tr>
		<tr align = "center" height = 55> <td> <?php print_message(); ?> </td> </tr>
		
		<tr align = "center" height = 35>
			<form action = "restorepassword.php" method = "get">
			<input type = "hidden" name = "login" value = "token"> </input>
			<td><input type = "password" name = "npass" placeholder = "Enter new password"> </input></td>
		</tr>
		<tr align = "center" height = 35>
			<td><input type = "password" name = "c_npass" placeholder = "Repeat new password"> </input></td>
		</tr>
		<tr align = "center" height = 35>
			<td><button type = "submit"> Change password </button></td>
		</tr></form>
		
		<tr><td></td></tr>
		
		<tr align = "center" height = 35>
		<td> <form action = "logout.php" method = "get">
				<input type = "hidden" name = "action" value = "del_cookie"> </input>
				<button type = "submit"> Log out </button>
			</form> </td>
		</tr>
	</table>	
		
		
</body>
</html>