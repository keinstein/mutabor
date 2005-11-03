#!/usr/bin/perl
my $classname;
$parengroup=qr{\(
		   (?:
		      (?> [^()]+ ) # non parenthesized text
		        |
		      (??{ $parengroup; }) # nested parentheses
		   )*
	       \)
	   }x; # regular expression to match parenthesized groups

while (<>) {
    print $_ if /^[^%]/;
    if (/%endclass/) {
	print "struct mutabor_class_${classname} {\n";
	print "    struct mutabor_class_",$classes{$classname}{"parent"},
  	  " _; /**< Parent class */\n" if $classes{$classname}{"parent"};
	for (@{$classes{$classname}{"field"}}){
	    print "    ",$_->{"type"}," ",$_->{"name"},"; ", $_->{"comment"},"\n";
	};
	print "};\n\n";
	print "struct mutabor_virttable_${classname} {\n";
	print "    size_t size;\n",
	      "    char * name;\n",
  	      "    void ** parent;\n";
	for (@{$classes{$classname}{"virtual"}}){
	    print "    ",$_->{"returntype"},
  	      " (*",$_->{"name"},")",
	      $_->{"parameters"},
	      "; ", $_->{"comment"},"\n";
	};
	print "};\n\n";
	print "extern const void * mutabor_object_$classname;\n\n";
	for (@{$classes{$classname}{"function"}}){
	    if ($_->{"class"} eq $classname) {
		print "extern ",$_->{"returntype"},
		" mutabor_cls_",$_->{"class"},"_",$_->{"name"},$_->{"parameters"},";\n";
	    } else {
		print "\n#define mutabor_cls_",$classname,"_",$_->{"name"},
		" mutabor_cls_",$_->{"class"},"_",$_->{"name"},"\n";
	    }
	};
	write_hh();
    }
    switch_data();
}

sub parse_file {
    ($_)=@_;
    print STDERR "Parsing file: $_\n";
    open (my $inputfile,"<$_") or die "Can't open include file $_";
    while (<$inputfile>) {
#	print "Data: $_";
	switch_data();
    }
    print STDERR "    returning...\n";
    close $inputfile;
}

sub switch_data {
#    print "Switch: $_";
    if (/^%include\s+"(.*)"\s*$/) {
	parse_file($1);
    }
    if (/^%class\s+(\w+)/) {
	$classname=$1;
	$classes{$classname}{"field"}=[]; 
	$classes{$classname}{"virtual"}=[];
	$classes{$classname}{"function"}=[];
	print STDERR "Class: $classname\n";
    }
    if (/^%parent\s+(\w+)/) {
	my $tmp=$1;
	if ($classes{$classname}{"parent"}) {
	    die "Two parent classes for class $classname defined" ;
	}
	if (!$classes{$tmp}) { die "Parent class $tmp for class $classname not defiend!"; }
	$classes{$classname}{"parent"}=$tmp;
	@tmp=@{$classes{$classname}{"virtual"}};
	$classes{$classname}{"virtual"}=[];
	for (@{$classes{$classes{$classname}{"parent"}}{"virtual"}}){
	    push @{$classes{$classname}{"virtual"}},{
		returntype => $_->{"returntype"},
		name => $_->{"name"},
		parameters => $_->{"parameters"},
		comment => $_->{"comment"},
		class => $_->{"class"},
	    };
	}
    	for (@tmp) {
	    my $new=$_;
	    my $found=0;
	    for (@{$classes{$classname}{"virtual"}}){
		if (($_->{"name"})eq $new->{"name"}) {
		    die "return type does not match" 
			if not $_->{"returntype"} eq $new->{"returntype"};
		    die "parameters do not match" 
			if not $_->{"parameters"} eq $new->{"parameters"};
		    $_->{"class"}=$new->{"classname"};
		    $_->{"comment"}=$new->{"comment"};
		    $found=1;
		    last;
		}
	    }
	    if (! $found)
	    {
		push @{$classes{$classname}{"virtual"}},$new;
	    }
	    
	}
 	@tmp=@{$classes{$classname}{"function"}};
	$classes{$classname}{"function"}=[];
	for (@{$classes{$classes{$classname}{"parent"}}{"function"}}){
#	    print STDERR "Copying function ",$_->{"name"},"\n";
	    push @{$classes{$classname}{"function"}},{
		returntype => $_->{"returntype"},
		name => $_->{"name"},
		parameters => $_->{"parameters"},
		comment => $_->{"comment"},
		class => $_->{"class"},
	    };
	}
    	for (@tmp) {
	    my $new=$_;
	    my $found=0;
	    for (@{$classes{$classname}{"function"}}){
		if (($_->{"name"})eq $new->{"name"}) {
		    die "return type does not match" 
			if not $_->{"returntype"} eq $new->{"returntype"};
		    die "parameters do not match" 
			if not $_->{"parameters"} eq $new->{"parameters"};
		    $_->{"class"}=$new->{"classname"};
		    $_->{"comment"}=$new->{"comment"};
		    $found=1;
		    last;
		}
	    }
	    if (! $found)
	    {
		push @{$classes{$classname}{"function"}},$new;
	    }
	    
	}
    }
    push @{$classes{$classname}{"field"}},{type => $1, name => $2, comment => $3} 
    if /^%field\s+(\w.*)\s+(\w+)\s*(\/\*.*\*\/)?\s*$/;
#    if (/^%virtual\s+(\w.*)\s+(\w+)\s*(\(.*\))\s*(\/\*.*\*\/)?\s*$/) {
    if (/^%virtual\s+(\w.*)\s+(\w+)\s*($parengroup)\s*(\/\*.*\*\/)?\s*$/) {
	my $tmp=0;
	for (@{$classes{$classname}{"virtual"}}){
	    if (($_->{"name"})eq $2) {
		die "return type does not match" if not $_->{"returntype"} eq $1;
		die "parameters do not match" if not $_->{"parameters"} eq $3;
		$_->{"class"}=$classname;
		$_->{"comment"}=$4;
		$tmp=1;
		last;
	    }
	}
	if (! $tmp)
	{
	    push @{$classes{$classname}{"virtual"}},{
		returntype => $1, 
		name=>$2,
		parameters => $3,
		comment => $4, 
		class => $classname
	    };
	}
    }
    if (/^%function\s+(\w.*)\s+(\w+)\s*($parengroup)\s*(\/\*.*\*\/)?\s*$/) {
	my $tmp=0;
	print STDERR "Funktion: ",$2,"\n";
	for (@{$classes{$classname}{"function"}}){
	    if (($_->{"name"})eq $2) {
		die "return type does not match" if not $_->{"returntype"} eq $1;
		die "parameters do not match" if not $_->{"parameters"} eq $3;
		$_->{"class"}=$classname;
		$_->{"comment"}=$4;
		$tmp=1;
		last;
	    }
	}
#	print STDERR "Function $2: $tmp.\n";
	if (! $tmp)
	{
	    push @{$classes{$classname}{"function"}},{
		returntype => $1, 
		name=>$2,
		parameters => $3,
		comment => $4, 
		class => $classname
	    };
	}
    }
    $classname = "" if /^%endclass/;
}

sub write_hh {
    open outputfile,">$classname.hh" or 
	die "Can't write class definition file for class $classname";

    for (@{$classes{$classname}{"virtual"}}){
	print outputfile $_->{"returntype"},
	  " mutabor_cls_",$_->{"class"},"_",$_->{"name"},$_->{"parameters"},";\n";
    };
    print outputfile "const void * mutabor_object_$classname;\n";
    print outputfile "static struct mutabor_virttable_$classname ",
                     "_mutabor_virttable_$classname = {\n";
    print outputfile "    sizeof(struct mutabor_class_$classname),\n";
    print outputfile "    \"$classname\",\n";
    print outputfile "    ", $classes{$classname}{"parent"}?
	"(void **)&mutabor_object_" . $classes{$classname}{"parent"}:
	"(void **)&mutabor_object_$classname";
    for (@{$classes{$classname}{"virtual"}}){
	print outputfile ",\n    mutabor_cls_",$_->{"class"},"_",$_->{"name"};
    };
    print outputfile "\n};\n";
    print outputfile "const void * mutabor_object_$classname=&_mutabor_virttable_$classname;\n";
    close outputfile;
}
