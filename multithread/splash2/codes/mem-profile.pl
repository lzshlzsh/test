#!/usr/bin/perl
use strict;


my $cnt = 0;
my $sum = 0;

while (<>){
	chomp();
	if (m/^really executing/){
		print("\n$_\n");
		die("error") if (0 != $cnt);
	}elsif (m/^\[\d+\](\d+)$/){
		$cnt++;
		$sum += $1;
		if (8 == $cnt){
			print("$sum ");
			$sum = 0;
			$cnt = 0;
		}
	}
}

print("\n");
