<!DOCTYPE html>

<?php
	include "functions.php";
	
	if (isset($_COOKIE["Token"]))
		header("Location: http://localhost/login.php");
?>

<html>
<head>
	<title> SIGN UP </title>
	
</head>

<body>
	
	<table border= "0" bordercolor = "grey" height = 50> </table>
	
	
	<table border= "0" bordercolor = "grey" height = 528 align  = "center" bgcolor = "#D9D9D9"> 
		<tr height = 50> </tr>
		
		<tr align = "center"> <td> <h1> Create new account </h1> </td> </tr>
		
		<tr height = 50> <td> <h4 style = "color: red" align = "center">
			<?php 
				print_message();
			?>
		</td> </h4> </tr>
		
		<form action = "register.php" method = "get">
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
		
			<tr height = 35 align = "center"> 
				<td>
					<input type = "password" name = "c_passw" placeholder = "Confirm password" required> </input>
				</td> 
			</tr>
			
			<tr height = 27> </tr>
		
			<tr align = "center">
				<td> 
					<button type = "submit">	SIGN UP	</button>
				</td>
			</tr>
		</form> 
		
		
		<tr height = 115> </tr> <!-- 100 !-->
		
		<tr height = 30 align = "center">
			<td> <span style = "color: #7d7d7d"> Already have an account? <a href="SIGNIN.php"> Sign in </span> </a> </td>
		</tr>
		
		<tr height = 25> </tr>
	</table>

</body>
</html>