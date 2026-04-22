#!/bin/bash

echo "Content-Type: text/plain"
echo

echo "Hello from Bash CGI!"
echo

echo "Environment variables:"
env

if [ "$REQUEST_METHOD" = "POST" ]; then
    echo
    echo "POST body:"
    cat
    echo
fi
