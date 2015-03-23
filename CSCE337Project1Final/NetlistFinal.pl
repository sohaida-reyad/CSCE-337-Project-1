 use Verilog::Netlist;
 

    # Setup options so files can be found
    use Verilog::Getopt;
    my $opt = new Verilog::Getopt;
    $opt->parameter( "+incdir+verilog",
                     "-y","verilog",
                     );

    # Prepare netlist
    my $nl = new Verilog::Netlist (options => $opt,);
    $path = shift;  #the path is the argument passed when running the script
    my $filename;
    $nl->read_file (filename=>$path);
    #delete the path, just keep the file name without the '/'
    if($path =~ m/\/(.*)/) {
      $filename = $1 ;
    }
    #output file = parsed_ then the file name
    $outputFile = "output/parsed_" . $filename. ".txt";
    open(my $parsedOutput, '>', $outputFile); #open the file

    my %portNames;  #hashmap for portNames -- ports are the inputs and outputs

    @inputs;        #arrays to store the strings declaring the input ports, output ports, wires , inout ports
    @outputs;
    @wires;
    @inouts;
    $inputCount =0;     #counters to count the number of input ports, output ports, wires and inout ports 
    $outputCount =0;
    $wiresCount =0;
    $inoutCount =0;

    foreach my $module ($nl->modules)   #for each module --> but here we have only one module per file
    {
      foreach my $sig ($module->ports_sorted)   #ports _sorted return all the input,output and inout ports
      {
        my $myString ;
        $myString = $sig->name . "\t";          #to print the name of the port
        if($sig->data_type eq "")           
        {
          $myString = $myString . "1" . "\n";       #if the data tybe is null then it is a wire os size 1, else it is a bus
        }
        else 
        {
          $myString = $myString . $sig->data_type . "\n";   #else it is a bus so print the size of the bus 
           #data type is the range if it is a bus
        }
        $portNames{$sig->name} = true;  
        if($sig->direction eq "in") #check the direction of the port and increment the corresponding counter and push the string to the corresponding array
        {   
            $inputCount++;          
            push(@inputs,$myString);
        }
         if ($sig->direction eq "out")
        {
            $outputCount++;
            push(@outputs,$myString);
        }

         if ($sig->direction eq "inout")
        {
            $inoutCount++;
            push (@inouts, $myString);
        }

      }
    

      foreach my $net ($module->nets_sorted) {  #nets retrun all the ports and wires before the beginning of the instantiations of gates
         my $myString = "";
          if($portNames{$net->name} ne "true")
           {  #if it is a wire, print wire before it , do not print ports, they are already printed
            $wiresCount++;
             $myString =  $net->name . "\n"; #print "wire" then the name of the wire
            push(@wires,$myString);
          }
        }
        print $inputCount . "\n";       #print how many input ports, followed by a list of input ports
        print @inputs;
        print $outputCount . "\n";
        print @outputs;
        print $inoutCount ."\n";
        if($inouts ne 0)
        {
            print @inouts;
        }
        print $wiresCount . "\n";
        print @wires;

        print $parsedOutput $inputCount . "\n";     #write the data to the file
        print $parsedOutput @inputs;
        print $parsedOutput $outputCount . "\n";
        print $parsedOutput @outputs;
        print $parsedOutput $inoutCount ."\n";
        if($inouts ne 0)
        {
            print $parsedOutput @inouts;
        }
        print $parsedOutput $wiresCount . "\n";
        print $parsedOutput @wires;
        #print $parsedOutput @nets;
        
        @assigns;       #array to store the assign statements
        $assignCount =0;    #counter to count how many assign statements

        foreach my $assign ($module->statements_sorted) { #print the assign statements .. for each assign statement print assign, then the left hand side then the right hand side
            my $s;
            $s = $assign->lhs . "\t" . $assign->rhs . "\n";
            $assignCount++;
            push(@assigns,$s);
            #print $parsedOutput $assign->keyword . "\t" . $assign->lhs . "\t" . $assign->rhs . "\n";
        }

        print $assignCount. "\n";   #print data on standard output and the file
        print $parsedOutput $assignCount. "\n";
        print @assigns;
        print $parsedOutput @assigns;
      foreach my $cell ($module->cells_sorted) { #for each cell , print its type, name , number of inputs then the inputs and finally the output
        print $cell->submodname . "\t" . $cell->name . "\t";    #print the gate type , name of gate
        print $parsedOutput $cell->submodname . "\t" . $cell->name . "\t";
        my $index =0;
        foreach my $pin ($cell->pins_sorted) {  #count how many pins for the gate, 
          $index++;
        }
        print $index - 1;       #the number of inputs is how many pins -1
        print $parsedOutput $index - 1;     

        foreach my $pin ($cell->pins_sorted) {
           #print "\t" . $pin->name ;
          print "\t" . $pin->netname;           #print the name of the pins sorted (inputs then outputs)
          print $parsedOutput "\t" . $pin->netname;
        }

        print "\n************************************\n";
        print $parsedOutput "\n";   #print endl
      }
      last;
    }
    close($parsedOutput);   #close the file 
   
