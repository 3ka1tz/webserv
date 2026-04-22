#!/usr/bin/php-cgi

<?php
header("Content-Type: text/plain");

echo "Hello from PHP CGI!\n\n";

echo "Environment variables:\n";
foreach (getenv() as $key => $value)
    echo "$key = $value\n";

$method = getenv('REQUEST_METHOD');
if ($method === 'POST') {
    echo "\nPOST body:\n";
    echo file_get_contents("php://input");
}
?>
