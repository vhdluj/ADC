#!/usr/bin/perl -w

use threads;
use threads::shared;

my $file   = $ARGV[0];
my $evtNum = $ARGV[1];
my $subId  = $ARGV[2];
my $refCh  = $ARGV[3];
my $endp   = $ARGV[4];



#open(DAT, $file);
#@data = <DAT>;
#close(DAT);

#chomp(@data);

#my $size = scalar(@data);


  my $hldFilePath =  $ARGV[0];
  my @fileList = `ls -tr $hldFilePath/*.root`;

  my $size = scalar(@fileList);



for(my $i = 0; $i < $size; $i++) {
        $fileList[$i] = substr($fileList[$i], 0, - 1);
        print("Analyze file: $fileList[$i]\n");#$data
	system ("root -l -b -q 'process_analyze.c(\"$fileList[$i]\",\".//..//Unpacker2//conf_trb3.xml\",100000 )'");#$data
}

print("\n\n -------------- Done ------------ \n\n");

