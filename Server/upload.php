<?php
$target_dir = "uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));



// Check if file already exists
if (file_exists($target_file)) {
  echo "File is Overwritten Successfully. \n ";
  unlink($target_file);  
}

// Check file size
if ($_FILES["fileToUpload"]["size"] > 50000) {
    $uploadOk = 0;
    header("Location: size.html");
  echo "Sorry, your file is too large. \n ";
  
}

// Allow certain file formats
if($imageFileType != "hex") {
    $uploadOk = 0;
    header("Location: hex.html");
  echo "Sorry, only HEX files are allowed.  \n ";
  
}

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
  echo "Sorry, your file was not uploaded. \n ";
// if everything is ok, try to upload file
} else {
    
  //flag file handling
   $myfileread = fopen("flag.txt" , "r");
   $data = fread($myfileread, 1);
   fclose($myfileread);

   $myfilewrite = fopen("flag.txt" , "w");
   if($data == 0) {
       fwrite($myfilewrite,'1');
   } else {
       fwrite($myfilewrite,'0');
   }
   fclose($myfilewrite);

  if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
    
    echo "The file ". htmlspecialchars( basename( $_FILES["fileToUpload"]["name"])). " has been uploaded.";
    header("Location: updated.html");
    
  } else {
    echo "Sorry, there was an error uploading your file. \n";
  }
}
?>