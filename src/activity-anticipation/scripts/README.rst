Firstly ,you should to read wiki.

https://github.com/Jiongyu/activity-anticipation/wiki

Running the file activity_prediction_sharedrnn.py will generate prediciton file(prediction_anticipation_human_579188.pik).

quesstion:
how to choose a activity to show the consquence of it`s prediction?

After generating about the file of the prediction, the file include all the activity prediction, so you could use python-list to get the activity you want.

Every activity are represented by number  in the pik file.

The correspondence between numbers and semantics is shown as follows:

	human-label = {1:'reaching',2:'moving',3:'pouring',4:'eating',5:'drinking',\
								6:'opening',7:'placing',8:'closing',9:'null',10:'cleaning'}

	object_label = {1:'mvable',2:'stationary',3:'reachable',4:'pourable',5:'pourto',\
								6:'containable',7:'drinkable',8:'openable',9:'placeable',10:'closeable',\
								11:'cleanable',12:'cleaner'}

So you could follow the above to get the pik file meaning.

read_pik_file.py is an example to read the pik file.

example :
 After I run the read_pik_file.py, there are some consquence below about the '0510182057'acitvity  which locate in the 9 line about the activity/fold_3/fold3 file. 
 
 
	truth_human:
	
	[9 1 2 5 2 7 1 2 4 2 7 9 1 2 5 2 7]
	
	detect_human
	
	[[9 1 2 5 2 7 2 2 5 2 7 2 7 2 5 2 7]]
	
	anticipation_human
	
	[[ 1  2  5  2  7 11  2  7  1  7  1  7  1  5  2  7 11]]
	
	truth_object
	
	[[ 2  2  2  3  1 12  1  9  2  2]]
	
	detect_object
	
	[[2 2 2 2 2 2 1 9 2 2]]
	
	anticipation_object
	
	[[ 2  2  2  2  2  2  9  2  2 13]]

so,you could change the fold_3 folds and fold3 files to choose the another activity  to get the prediction consquence.



