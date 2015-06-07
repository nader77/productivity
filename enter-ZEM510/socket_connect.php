<?php
 
if(!($sock = socket_create(AF_INET, SOCK_STREAM, 0)))
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
     
    die("Couldn't create socket: [$errorcode] $errormsg \n");
}
 
echo "Socket created \n";
 

//Connect socket to remote server
if(!socket_connect($sock , '10.0.0.201' , 4370))
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
     
    die("Could not connect: [$errorcode] $errormsg \n");
}
 
echo "Connection established \n";
 
// First package.
$message = "\x50\x50\x82\x7d\x08\x00\x00\x00\xe8\x03\x17\xfc\x00\x00\x00\x00";
// $message = "\x50\x50\x82\x7d\x10\x00\x00\x00\xe0\x05\x01\xcd\x45\x2d\x18\x00\x00\x00\x00\x00\xc0\xff\x00\x00";
 
// Second package, get version.
$message2 = "\x50\x50\x82\x7d\x08\x00\x00\x00\x4c\x04\x6d\xce\x45\x2d\x01\x00";

// Get data
// $message = "\x50\x50\x82\x7d\x10\x00\x00\x00\xe0\x05\x01\xcd\x45\x2d\x18\x00\x00\x00\x00\x00\xc0\xff\x00\x00";

//Send the message to the server
if( ! socket_send ( $sock , $message , strlen($message) , 0))
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
     
    die("Could not send data: [$errorcode] $errormsg \n");
}
 
echo "Message send successfully \n";
 
$buf = "";
//Now receive reply from server
if( socket_recv( $sock , $buf , 2045 , MSG_PEEK ) === FALSE)
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
     
    die("Could not receive data: [$errorcode] $errormsg \n");
}
 
//print the received message
var_dump($buf);

//Send the message to the server
if( ! socket_send ( $sock , $message2 , strlen($message2) , 0))
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
     
    die("Could not send data: [$errorcode] $errormsg \n");
}
 
echo "Message send successfully \n";
 
$buf = "";
//Now receive reply from server
if( socket_recv( $sock , $buf , 2045 , MSG_PEEK ) === FALSE)
{
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);
     
    die("Could not receive data: [$errorcode] $errormsg \n");
}
 
//print the received message
var_dump($buf);
