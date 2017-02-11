#!/usr/bin/env perl
use strict;
use warnings;

use File::Basename;
my $test_path = dirname(__FILE__);

system( "cat $test_path/wordlist.txt | ./dp_browser > temp.txt" );
my $diff = `diff temp.txt $test_path/wordlist_out.txt`;
chomp( $diff );
if( $diff )
{
    print STDERR $diff;
    unlink( "temp.txt" );
    exit( -1 );
}
print STDERR "***PASSED***\n";
unlink( "temp.txt" );
exit( 0 );
