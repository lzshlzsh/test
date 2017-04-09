#!/usr/bin/perl 
use strict;

my %hash;
my $i = 0;
my $key;

while (<>){
	chomp();
	if (!exists($hash{$_})){
		$hash{$_} = $i++;
	}
}

#foreach $key(sort {$hash{$a} <=> $hash{$b}} keys(%hash)){
foreach $key(sort {$a cmp $b} keys(%hash)){
	print("$key => $hash{$key}\n");
}
