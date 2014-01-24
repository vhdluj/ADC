#!/usr/bin/perl -w

#my $option = "";#$ARGV[0];
#$option = $ARGV[0];

if($ARGV[0] eq ""){
   print("Usage: perl groupUnpack.pl -l /pathToHldFiles\n       perl groupUnpack.pl -f /fileWithHldFileList\n");
   exit 1;
}

if($ARGV[0] eq "-l")
{
 my $hldFilePath =  $ARGV[1];
 my @fileList = `ls -tr $hldFilePath/*.hld`;

 my $size = scalar(@fileList);

 for(my $i = 0; $i < $size; $i++) {
    print("Unpacking $fileList[$i] [$i of $size]__________________________________________\n");
    system ("root -l -b -q 'unpackProcess.c(\"$fileList[$i]\",\".//..//Unpacker2//conf_trb3.xml\",100000 )'");
 }
 print("\n\n -------------- Done ------------ \n\n");
}#______________________________________________________________________________________________________________________________________
elsif($ARGV[0] eq "-f" )
{
  my $file   = $ARGV[1];

  open(DAT, $file);
  @data = <DAT>;
  close(DAT);

  chomp(@data);

  my $size = scalar(@data);

  for(my $i = 0; $i < $size; $i++) {
          print("Unpacking file: $data[$i]\n");
          system ("root -l -b -q 'unpackProcess.c(\"$data[$i]\",\".//..//Unpacker2//conf_trb3.xml\",100000 )'");
  }

  print("\n\n -------------- Done ------------ \n\n");
}#_______________________________________________________________________________________________________________________________________
else
{
  my $hldFilePath =  $ARGV[0];
  my @fileList = `ls -tr $hldFilePath/*.hld`;

  my $size = scalar(@fileList);

  for(my $i = 0; $i < $size; $i++) {
     $fileList[$i] = substr($fileList[$i], 0, - 1);
     print("Unpacking $fileList[$i] [$i of $size]__________________________________________\n");
     system ("root -l -b -q 'unpackProcess.c(\"$fileList[$i]\",\".//..//Unpacker2//conf_trb3.xml\",100000 )'");
  }
  print("\n\n -------------- Done ------------ \n\n");
}#______________________________________________________________________________________________________________________________________
