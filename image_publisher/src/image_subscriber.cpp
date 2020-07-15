#include <ros/ros.h> /*Core ROS Packages */
#include <image_transport/image_transport.h> /* Image transport helps to pub and sub to images in ROS */
#include <opencv2/highgui/highgui.hpp> /* OpenCV image function */
#include <cv_bridge/cv_bridge.h> /* CV Bridge function */

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        /* Convert ROS Message to OpenCV Mat */
        cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        cv::waitKey(30);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
    /* Init a ROS node with name */
    ros::init(argc, argv, "image_subscriber");

    /* This object used to communicate with the ROS system */
    ros::NodeHandle nh;
    
    cv::namedWindow("view");
    cv::startWindowThread();
    
    /* Create a image transport object instance */
    image_transport::ImageTransport it(nh);

    /* Subscribe to camera/image topic with buffer size of 1 */
    image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);

    ros::spin();
    cv::destroyWindow("view");
    return 0;
}