import cPickle
import numpy as np

def main():

	dic_ground_truth_label_human = {1:'reaching',2:'moving',3:'pouring',4:'eating',5:'drinking',\
								6:'opening',7:'placing',8:'closing',9:'null',10:'cleaning'}

	dic_ground_truth_label_object = {1:'mvable',2:'stationary',3:'reachable',4:'pourable',5:'pourto',\
								6:'containable',7:'drinkable',8:'openable',9:'placeable',10:'closeable',\
								11:'cleanable',12:'cleaner'}

	ground_truth_test_data = cPickle.load(open('grount_truth_test_data_579188.pik'))
	ground_truth_label_human = ground_truth_test_data['labels_human']
	ground_truth_label_object = ground_truth_test_data['labels_objects']

	detection_human_data = cPickle.load(open('prediction_detection_human_579188.pik'))
	anticipation_human_data = cPickle.load(open('prediction_anticipation_human_579188.pik'))

	detection_object_data = cPickle.load(open('prediction_detection_object_579188.pik'))
	anticipation_object_data = cPickle.load(open('prediction_anticipation_object_579188.pik'))


	truth_human = ground_truth_label_human[8].T[0]
	detect_human = detection_human_data[8].T
	anticipation_human = anticipation_human_data[8].T
	truth_object = ground_truth_label_object[8].T
	detect_object = detection_object_data[8].T
	anticipation_object = anticipation_object_data[8].T

    print 'truth_human:'
    print truth_human
    print 'detect_human'
    print detect_human
    print 'anticipation_human'
    print anticipation_human
    print 'truth_object'
    print truth_object
    print 'detect_object'
    print detect_object
    print 'anticipation_object'
    print anticipation_object


main()


