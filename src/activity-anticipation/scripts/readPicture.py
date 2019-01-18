import cv2
import os

videoPath = './having_meal_1.mp4'
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
videoWriter = cv2.VideoWriter(videoPath, fourcc, 25, (640, 480))
picture_path = '/home/tan/ros/final_project_ros/human_anticipation_data/CAD_120/person1/Subject1_rgbd_images/having_meal/0510182057'

for i in range(658):
    picture = picture_path + '/RGB_{0}'.format(i+1)+'.png'
    print(picture)
    frame = cv2.imread(picture)
    frame = cv2.resize(frame, (640,480))
    videoWriter.write(frame)



