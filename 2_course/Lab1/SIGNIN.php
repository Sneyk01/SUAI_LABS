<!DOCTYPE html>

<?php
	include "functions.php";

	if (isset($_COOKIE["Token"]))
		header("Location: http://localhost/main.php");
?>

<html>
<head>
	<title> SIGN IN </title>
</head>

<body>
	
	<table border= "0" bordercolor = "grey" height = 50> </table>
	
	<table border= "0" bordercolor = "grey" align  = "center" height = 528 bgcolor = "#D9D9D9"> 
		<tr height = 50> </tr>
		
		<tr align = "center"> <td> <h1> SIGN IN </h1> </td> </tr>
		
		<tr height = 50> <td> <h4 style = "color: red" align = "center">
		
			<?php 
				print_message();
			?>
					
		</td></h4> </tr>
		
		<form action = "login.php" method = "get">
			<tr height = 35 align = "center"> 
				<td width = "300" >
					<input type = "text" name = "login" placeholder = "Login" required> </input>
				</td> 
			</tr>
			
			<tr height = 35 align = "center"> 
				<td> 
					<input type = "password" name = "passw" placeholder = "Password" required> </input>
				</td> 
			</tr>
			
			<tr height = 35 align = "left" valign = "top">
				<td> <span style = "color: #7d7d7d"> <a href = "restore.php" style="text-decoration: none"> &emsp;&emsp;&emsp;&emsp;&nbsp;Forgot password? </a> </span> </td>
			</tr>
			
			<tr height = 27> </tr>
		
			<tr align = "center">
				<td> 
					<button type = "submit">	SIGN IN	</button>
				</td>
			</tr>
		</form> 	
		
		<tr height = 115> </tr>
		
		<tr height = 30 align = "center">
			<td> <span style = "color: #7d7d7d"> First time on the site? <a href = "SIGNUP.php" style="text-decoration: none"> Sign up </a> </span> </td>
		</tr>
			
		
		<tr height = 25> </tr>
	</table>

</body>
</html>