#!/usr/bin/perl -w
use Image::Magick;

my $ifname = shift || "matrix.txt";

open (INFILE, $ifname) or die "Can't open input file";

my $line = <INFILE>;
my @extents = split(/,/, $line);

my $xExt = int($extents[0]);
my $yExt = int($extents[1]);

$size = sprintf("%dx%d", $xExt, $yExt);

my $image = Image::Magick->new(size=>$size);

my $rowc = 1;

while($line = <INFILE>)
{
	chomp $line;
	my @row = split(/,/, $line);
	for (my $i = 0; $i < $xExt; $i++)
	{
		@color = [$row[$i], $row[$i], $row[$i]];
		$image->SetPixel(x=>$i, y=>$rowc, color=>\@color);
	}
	$rowc++;
}
$image->write("matrix.png");
#$image->write(split(/\./, $ifname) . ".png");
