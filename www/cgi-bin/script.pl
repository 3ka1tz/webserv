#!/usr/bin/env perl
use strict;
use warnings;

print "Content-Type: text/plain\n\n";

print "Hello from Perl CGI!\n\n";

print "Environment variables:\n";
foreach my $key (sort keys %ENV) {
    print "$key = $ENV{$key}\n";
}

my $method = $ENV{'REQUEST_METHOD'} || "GET";
if ($method eq "POST") {
    print "\nPOST body:\n";
    my $body = do { local $/; <STDIN> };
    print $body;
    print "\n";
}
