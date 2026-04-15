#!/usr/bin/php-cgi
<?php

header("Content-Type: text/plain");

echo "Hello from PHP CGI!\n\n";

echo "Environment variables:\n";
foreach ($_SERVER as $key => $value)
    echo "$key = $value\n";

echo "\nPOST body:\n";
$body = file_get_contents("php://input");
echo $body;
