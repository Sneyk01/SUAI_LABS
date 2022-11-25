<table border = 0 bordercolor = "grey" width = 620  align = "center" bgcolor = "FFEBCD">
			<tr height = 45>
				<td width = 10> </td>
			
				<td width = 45 align = "center"> <h2> <?php echo $i?> </h2> </td>
				
				<td style = "table-layout:fixed; width:420px;"  rowspan = 2 height = 100 bgcolor = "F5F5F5" width = 420> <?php print ($text);?>  </td>
			
				<td width = 45 align = "center" > 
					<form action = "reaction.php?" method = "get">
						<input type = "hidden" name = "reaction" value = "like"> </input>
						<input type = "hidden" name = "id" value = "<?php echo $post_id?>"> </input>
						<input type = "hidden" name = "page" value = "<?php echo $page?>"> </input>
						<input type = "hidden" name = "count" value = "<?php echo $like?>"> </input>
						<button type = "submit"> 👍 &nbsp;<?php echo $like?> </button>
					</form> 
				</td>
			
				<td width = 45 align = "center" > 
					<form action = "reaction.php?" method = "get">
						<input type = "hidden" name = "reaction" value = "fun"> </input>
						<input type = "hidden" name = "id" value = "<?php echo $post_id?>"> </input>
						<input type = "hidden" name = "page" value = "<?php echo $page?>"> </input>
						<input type = "hidden" name = "count" value = "<?php echo $fun?>"> </input>
						<button type = "submit"> 😂 &nbsp;<?php echo $fun?> </button>
					</form> 
				</td>
				
				<td width = 45 align = "center" > 
					<form action = "reaction.php?" method = "get">
						<input type = "hidden" name = "reaction" value = "dislike"> </input>
						<input type = "hidden" name = "id" value = "<?php echo $post_id?>"> </input>
						<input type = "hidden" name = "page" value = "<?php echo $page?>"> </input>
						<input type = "hidden" name = "count" value = "<?php echo $dislike?>"> </input>
						<button type = "submit"> 👎 &nbsp;<?php echo $dislike?> </button>
					</form> 
				</td>
			
				<td width = 10> </td>
		</tr>
		<tr>
			<td width = 10> </td>
			<td> </td>
			<td colspan = 3> 
				<button id="b<?php echo $i?>" onclick="show_comments('<?php echo $i?>')"> Показать комментарии </button>
			</td>
			
			<td width = 10> </td>
		</tr>
		
		<?php
			if ($img_id != "none") {
						
				echo "<tr><td></td><td></td><td>";
				echo "<table class = 'img_t' border = 0>";
								
				echo "<tr>";
			
				echo "<td align = 'center'><img style = 'width:390px;' src = 'img/".$img_id."' alt = 'Тут должно быть изображение'/> </td>";
				//echo "<td><button onclick='show_img('".$img_id."')> Оригинальный размер </button></td>";
							
				echo "</tr>";
				
				echo "</table></td><td></td><td></td><td></td><td></td></tr>";
			}
		?>
		
		<style>
			table.img_t {
				table-layout:fixed; width:100%;
			}
		</style>
		
		</table>