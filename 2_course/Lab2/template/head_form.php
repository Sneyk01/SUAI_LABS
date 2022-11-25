<table border = 0 height = 30 width = 629 align = "center" bgcolor = "FFE4C4"> 
	<tr>
		<td colspan = 3> <h3 align = center> Добавить новую запись </h3> </td>
	</tr>
	
	<form action = "new_post.php" method = "post" enctype = "multipart/form-data">
	
	<tr>
		<td width = 63 rowspan = 3> </td>
		
		<td rowspan = 3  width = 407 align = "center"> 
			<input type = "text" name = "text" placeholder = "Напишите ваш пост! (Максимальный размер картинки - 2 мб)" style = "width:400px; height:42px"> </input>
		</td>
					
		<td width = 159 align = "center"> 
			<button type = "submit" style = "width:115px"> Добавить </button>
		</td> 
	
	</tr>
	
	<tr rowspan = 2>
		<td align = "center"> 
			<input type = "file" name = "img" style = "width:115px"> </input> 
		</td>
	</tr>
	
	</form>
</table>