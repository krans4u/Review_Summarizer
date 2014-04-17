<?php 
$dir = $_POST["path"];
//echo "aas";
//echo "baas";
//print_r($_POST);

if (is_dir($dir)) {
	if ($dh = opendir($dir)) {
		while (($file = readdir($dh)) !== false) {
			if($file != ".." && $file!=".")
			{
				echo $file;
				echo ",";
			}
		}
		closedir($dh);
	}
}
else
{
	echo "isn't dir";
}
?>
