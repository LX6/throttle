use strict ;
use BerkeleyDB ;

#my $filename = "pbase.db" ;
my $filename = "empx.db" ;

#unlink $filename ;
#my %h ;
#tie %h, 

use Class::Struct;

struct employeeRecord => {
   empid    => '$',
   large    => '$',
   note     => '$',
   xpen     => '$', 
};
=pod
my $empid, $large, @note, $xpen;
my $rec = {
#           empid     => $empid,
           large     => $large,
           note      => [@note],
           xpen      => $xpen,
       };


=cut


#y $rec = employeeRecord->new();
#$rec->empid(1508043600);
#$rec->large(1);
#$rec->note('apapapapapapapapapapapapapapapapapapapa');
#$rec->xpen('3.20');

my $dbh = new BerkeleyDB::Btree(
            -Filename   => $filename,
	    -Flags      => DB_RDONLY,)
  or die "Cannot open $filename: $! $BerkeleyDB::Error\n" ;

=pod
           $db = new BerkeleyDB::Unknown
                       [ -Filename      => "filename", ]
                       [ -Subname       => "sub-database name", ]
                       [ -Flags         => flags,]
                       [ -Property      => flags,]
                       [ -Mode          => number,]
                       [ -Cachesize     => number,]
                       [ -Lorder        => number,]
                       [ -Pagesize      => number,]
                       [ -Env           => $e)nv,]
                       [ -Txn           => $txn,]
                       [ -Encrypt       => { Password => "string",
                                             Flags    => number }, ],

=cut


# Add a key/value pair to the file
#$h{'Wall'} = 'Larry' ;
#$h{'Smith'} = 'John' ;
#$h{'mouse'} = 'mickey' ;
#$h{'duck'}  = 'donald' ;

# Delete
#delete $h{"duck"} ;


# Cycle through the keys printing them in order.
# Note it is not necessary to sort the keys as
# the btree will have kept them in order automatically.

my $cursor = $dbh->db_cursor() ;
my $k; my $v;
my $sum = 0;
while ($cursor->c_get($k, $v, DB_NEXT) == 0) {
#    $v = ~m/^(\d)()()$/;
#    print "Key: ", unpack("L",$k), "Value: ", $v;
#    printf("%d  - ,%s\n", \$rec->empid, \$rec->value[1]);
#    printf( "Key: %s", $k, ", value: %s", $v . "\n");
#    print $v,"\n";
    my ($parr, $large,$note,$xpen) = unpack 'L L Z56 f', $v;
    print $parr," | ",$large," | ", $note," | ", $xpen, "\n"   ;
    $sum += $xpen;
#     print length($v), "\n";
#    print unpack("L*",$k), " ", $larg, " ", $not, " ", $xp,"\n";
    
} 

    print "----------------\n",$sum, "\n"   ;


