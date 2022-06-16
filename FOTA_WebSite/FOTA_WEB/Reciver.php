<?php
if(isset($_GET['Rx']))
{
	/* open the file in write mode*/
	$myfile=fopen("status.txt","w");
	if($_GET['Rx']=='ok')
	{	
		echo "ok";
		fwrite($myfile,"ok");
			fclose($handle); 
		
	}
	elseif($_GET['Rx']!='ok')
	{
		fwrite($myfile,'  ');
	    echo "no";
	}
	/* Close file*/
	fclose($myfile);
}	
?>
