#!/usr/bin/perl
use strict;

my $tmp_file = ".tmp.$$";
my $tf_handle;
my %shared;
my $line;
my $size;

my $debug = 1;
my ($key, $val);


while (<>){
	print();
	chomp();
	system("bpdump $_ >$tmp_file");	
	
	open ($tf_handle, "<", $tmp_file) or die ("cannot open $tmp_file: $!");

	%shared = (); #clear

	while (($line = <$tf_handle>)){
		if ($line =~ m/.+:(.+):\s*.+\s*.*:(.+):/){
			$shared{$1} = 1 if (! exists($shared{$1}));
			$shared{$2} = 1 if (! exists($shared{$2}));
		}
	}
	close($tf_handle);
	
	$size = keys(%shared);

	print("$size\n");

	if ($debug){
		foreach $key(sort(keys(%shared))){
			print("$key\n");
		}
	}

}
unlink("$tmp_file");

