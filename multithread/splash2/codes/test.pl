#!/usr/bin/perl
use strict;

my $size;

print ("$ARGV[0]\n");

my %shared = (
	"a" => 1, 
	"b" => 1, 
	"c" => 1, 
	);
$size = keys(%shared);
print("$size\n");

$size = %shared;
print("$size\n");

$size = scalar(%shared);
print("$size\n");
