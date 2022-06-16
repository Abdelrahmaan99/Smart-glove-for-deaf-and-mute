<?php

session_start();
if(isset($_SESSION["username"] )){
?>
<!DOCTYPE html>
<html>
<head>
<title>OTA Programmer</title>
<link rel="icon" href="Logo.png">
<link rel="stylesheet" type="text/css" href="style.css" >
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Raleway:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800&display=swap" rel="stylesheet">
</head>
<body>
   <div class="logo" style="opacity: 0; transition: all 2s;" >
     <img src="2.png" alt="logo">
   </div>
   <span style="color: white;
    margin: 10px;
    padding: 10px 20px;
    background: red;
    border-radius: 14px;
    position: absolute;
    bottom: 10px;
	right : 10px; opacity: 0; transition: all 2s; " class="logout"><a href='./../logout.php' style="
    text-decoration: none;
    color: white;
" ><font face = "Gill sans mt">Log Out</font></a></span>
<style>
.Button1
{
border: 1px solid red;
padding: 10px;
font-size: 17px;
border-radius: 21px;
transition: all 0.5s;
color:white;
background:red;
font-family: 'Raleway', sans-serif;
cursor: pointer;
}

.Button1:hover
{
border: 1px solid red;
color: red;
padding: 10px;
font-size: 17px;
border-radius: 21px;
transition: all 0.5s;
background:white;
font-family: 'Raleway', sans-serif;
}
</style>

<center>
<font face = "Gill sans mt" color = "white"> 
<br>
<br>
<h1 style="opacity: 0;
    transition: all 2s;" class="one" ><font size = 7 color = "red">PROGRAM&nbsp;YOUR&nbsp;MCU&nbsp;WHERE&nbsp;EVER&nbsp;YOU&nbsp;ARE</font></h1>
<h2 style="opacity: 0;
    transition: all 2s;" class="two"> This website was impltemented by <i><font color = "orange">BioNist </font></i> This site is used to send your ".hex" file
<br>to your MCU via ESP8266 WIFI module, and let your Bootloader program it .
<br>Enjoy the OTA Programming</h2>
</font> 
<h1>
<br>
<br>
</h1>
<form action="upload.php" method="POST" enctype="multipart/form-data" style="opacity: 0; transition: all 2s;" class="form">
	<input class="Button1" type="file" name="file" id='file_' style='display: none;'>
	<label for='file_'  style="
    display: inline-block;
    width: auto;
    margin: 0px 20px;
    background: transparent;
    padding: 9px 10px;
    color: white;
    border: 3px solid white;
    border-radius: 22px;
    text-align: left;
	font-family: 'Raleway', sans-serif;
	cursor: pointer;
"> <span style="
    margin-right: 42px;
    background: red;
    padding: 5px 22px;
    border-radius: 13px;
    margin: 5px 6px 5px 0px;
	font-family: 'Raleway', sans-serif;
" >Upload File</span> <span class="file_name">No file chosen</span></label>
	<button class="Button1" type="submit" name="submit">UPLOAD</button>
</form>
</center>
<script src="main.js"></script>

</body>
</html>

<?php

}
else{
header("Location: ./../index.php");
}

?>