<!DOCTYPE html>

<?php 
		include "functions.php";
		
		if (isset($_COOKIE["Token"]))
		header("Location: http://localhost/login.php");
?>

<html>
<head>
	<title> restore password </title>
</head>

<body>
	
	<table border= "0" bordercolor = "grey" height = 50> </table>
	
	<table border = "0" bordercolor = "black" align = "center" height = 528 bgcolor = "#D9D9D9">
		<tr height = 50> </tr>
		
		<tr align = "center"> 
			<td width = 300 height = 30> <h1> Restore password </h1> </td>
		</tr>
		
		<tr height = 50 align = "center"> <td> <?php print_message(); ?> </td></tr>
		
		<form action = "restorepassword.php" method = "get">
			
	
			<tr height = 35 align = "center">
				<td><input type = "input" name = "login" placeholder = "Login"> </input></td>
			</tr>
			
			<tr height = 35 align = "center">
			<td><input type = "password" name = "npass" placeholder = "Enter new password"> </input></td>
			</tr>
			
			<tr height = 35 align = "center">
			<td><input type = "password" name = "c_npass" placeholder = "Repeat new password"> </input></td>
			</tr>
			
			<tr height = 35>
				<td width = 200 valign = "top"> &emsp;&emsp;&emsp;&ensp; <input type = "checkbox" required> It is really me :)</input></td>
			</tr>
			
			<tr height = 35> </tr>
			
			<tr height = 35 align = "center">
				<td align = "center"><button type = "submit"> Change password </button></td>
			</tr>
		</form>
		
		<tr height = 50> </tr>
		
		<tr align = "center">
			<td> <span style = "color: #7d7d7d"> <a href = "SIGNIN.php" style="text-decoration: none"> I remembered the password </a> </span> </td>
			</tr>
		<tr height = 25> </tr>
	</table>	
		
		
</body>
</html>