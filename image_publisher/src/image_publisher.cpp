#include <ros/ros.h> /*Core ROS Packages */
#include <image_transport/image_transport.h> /* Image transport helps to pub and sub to images in ROS */
#include <opencv2/highgui/highgui.hpp> /* OpenCV image function */
#include <cv_bridge/cv_bridge.h> /* CV Bridge function */

int main(int argc, char ** argv)
{

    /* Init a ROS node with name */
    ros::init(argc, argv, "image_publisher");

    /* This object used to communicate with the ROS system */
    ros::NodeHandle nh;
    
    /* Create a image transport object instance */
    image_transport::ImageTransport it(nh);

    /* Publisher object with camera/image topic with buffer size of 1 */
    image_transport::Publisher pub = it.advertise("camera/image", 1);

    /* Image read */
    cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

    /* Convert OpenCV image to ROS sensor Message */
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

    /* Set a frequency to publish a message */
    ros::Rate loop_rate(5);
    
    while (nh.ok()) {
        /* Publish a message */
        pub.publish(msg);

        ros::spinOnce();
        
        loop_rate.sleep();
    }

    return 0;
}
