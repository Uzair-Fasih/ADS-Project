The current code works as expected.

The following is still pending:

Verify the following:
> Print(rideNumber) query should be executed in O(log(n)) and Print(rideNumber1,rideNumber2) should 
be executed in O(log(n)+S) where n is the number of active rides and S is the number of triplets 
printed. For this, your search of the RBT should enter only those subtrees that may possibly have a ride 
in the specified range. All other operations should take O(log(n)) time.

Add input_file and output_file logic

Confirm if the output is as expected.