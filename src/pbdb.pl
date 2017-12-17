use strict ;
use BerkeleyDB ;

my $filename = "empx.db" ;

use Class::Struct;

struct employeeRecord => {
   empid    => '$',
   large    => '$',
   note     => '$',
   xpen     => '$', 
};

my $dbh = new BerkeleyDB::Btree(
            -Filename   => $filename,
#            -Flags      => DB_RDONLY,)
            )
  or die "Cannot open $filename: $! $BerkeleyDB::Error\n" ;


  
  
# Cycle through the keys printing them in order.
# Note it is not necessary to sort the keys as
# the btree will have kept them in order automatically.

my $cursor = $dbh->db_cursor() ;
my $k; my $v;
my $sum = 0; my $summ = 0;
while ($cursor->c_get($k, $v, DB_NEXT) == 0) {
    my ($parr, $large,$note,$xpen) = unpack 'L L Z56 f', $v;
    if ($parr == 1504926002) {
        print $parr," +++++| ",$large," | ", $note," | ", $xpen, " V\n"   ;
        $cursor->c_del()
        or die "$BerkeleyDB::Error\n";;
    } 
    
#    $v = ~m/^(\d)()()$/;
#    print "Key: ", unpack("L",$k), "Value: ", $v;
#    printf("%d  - ,%s\n", \$rec->empid, \$rec->value[1]);
#    printf( "Key: %s", $k, ", value: %s", $v . "\n");
#    print $v,"\n";
    if ((scalar localtime $parr) =~ m/$ARGV[0]/ ) { $summ += $xpen; }
    print $parr," | ",scalar localtime $parr, "|",$large," | ", $note," | ", $xpen, "\n"   ;
    $sum += $xpen;
#     print length($v), "\n";
#    print unpack("L*",$k), " ", $larg, " ", $not, " ", $xp,"\n";
    
} 
$cursor->c_close();

undef $cursor ;

# Delete a key/value pair.
#$dbh->db_del("1509613200") ;

undef $dbh ;

print "----------------\n",$sum, "\n"   ;
print "----------------\n for $ARGV[0]: ",$summ, "\n"   ;


