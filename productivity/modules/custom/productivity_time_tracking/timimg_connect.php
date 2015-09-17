#!/usr/local/bin/php -q
<?php
/**
 * Created by PhpStorm.
 * User: brice
 * Date: 3/25/15
 * Time: 4:53 PM
 */

error_reporting(E_ALL);

/* Allow the script to hang around waiting for connections. */
set_time_limit(0);

/* Turn on implicit output flushing so we see what we're getting
 * as it comes in. */
ob_implicit_flush();

$port = 4370;

$host = "10.0.0.201";
$timeout = 15;  //timeout in seconds

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)
or die("Unable to create socket\n");

socket_set_nonblock($socket)
or die("Unable to set nonblock on socket\n");

$time = time();
while (!@socket_connect($socket, $host, $port))
{
  $err = socket_last_error($socket);
  if ($err == 115 || $err == 114)
  {
    if ((time() - $time) >= $timeout)
    {
      socket_close($socket);
      die("Connection timed out.\n");
    }
    sleep(1);
    continue;
  }
  die(socket_strerror($err) . "\n");
}

socket_set_block($this->socket)
or die("Unable to set block on socket\n");
