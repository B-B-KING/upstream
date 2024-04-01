#include<librealsense2/rs.hpp>
#include<iostream>
#include <zmq.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/core/utility.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<thread>
#include <memory>

using namespace cv;
using namespace std;

#define w 640
#define h 480


void printMatAsDecimal(const cv::Mat& mat) {
    // 检查矩阵是否为空
    if (mat.empty()) {
        std::cerr << "Empty matrix!" << std::endl;
        return;
    }

    // 遍历矩阵的每个像素并将其打印为十进制数字
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            std::cout << static_cast<int>(mat.at<uchar>(i, j)) << " ";
        }
        std::cout << std::endl;
    }
}


void receiveirImages() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.connect("tcp://192.168.91.97:9001");
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    zmq::message_t message;


    while (true) {
        Mat irframe;

        socket.recv(&message);
        size_t message_size = message.size();
        if (message_size == 0) {
            std::cerr << "Received empty message!" << std::endl;
            continue;
        }
        irframe = Mat(cv::Size(640, 480), CV_8UC1, message.data(), cv::Mat::AUTO_STEP);
        // std::cerr << "Received irmessage size : "<< message_size << std::endl;
        // std::cout << "irframe : " << ",  size : "<< irframe.rows*irframe.cols << std::endl;

        // 显示图像
        imshow("right IR Image", irframe); // 右红外灰度影像
        irframe.release();
        if(waitKey(1)>0)//if touch button end stream
        {
            // break;
        }
    }
}


void receiveilImages() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.connect("tcp://192.168.91.97:9000");
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    zmq::message_t message;


    while (true) {
        Mat ilframe;

        socket.recv(&message);
        size_t message_size = message.size();
        if (message_size == 0) {
            std::cerr << "Received empty message!" << std::endl;
            continue;
        }
        ilframe = Mat(cv::Size(640, 480), CV_8UC1, message.data(), cv::Mat::AUTO_STEP);
        // std::cerr << "Received ilmessage size : "<< message_size << std::endl;
        // std::cout << "ilframe : " << ",  size : "<< ilframe.rows*ilframe.cols << std::endl;


        // 显示图像
        imshow("left IR Image", ilframe); // 右红外灰度影像
        ilframe.release();
        if(waitKey(1)>0)//if touch button end stream
        {
            // break;
        }
    }
}

void receivedepImages() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.connect("tcp://192.168.91.97:9002");
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    zmq::message_t message;


    while (true) {
        Mat depframe;

        socket.recv(&message);
        size_t message_size = message.size();
        if (message_size == 0) {
            std::cerr << "Received empty message!" << std::endl;
            continue;
        }
        depframe = Mat(cv::Size(640, 480), CV_8UC3, message.data(), cv::Mat::AUTO_STEP);
        // std::cerr << "Received irmessage size : "<< message_size << std::endl;
        // std::cout << "depframe : " << ",  size : "<< depframe.rows*depframe.cols << std::endl;

        // 显示图像
        imshow("depth IR Image", depframe); // 右红外灰度影像
        depframe.release();
        if(waitKey(1)>0)//if touch button end stream
        {
            // break;
        }
    }
}

void receivergbImages() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.connect("tcp://192.168.91.97:9004");
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    zmq::message_t message;

    while (true) {
        Mat rgbframe;

        socket.recv(&message);
        size_t message_size = message.size();
        if (message_size == 0) {
            std::cerr << "Received empty message!" << std::endl;
            continue;
        }
        rgbframe = Mat(cv::Size(640, 480), CV_8UC3, message.data(), cv::Mat::AUTO_STEP);
        // std::cerr << "Received irmessage size : "<< message_size << std::endl;
        // std::cout << "depframe : " << ",  size : "<< depframe.rows*depframe.cols << std::endl;

        // 显示图像
        imshow("rgb IR Image", rgbframe); // 右红外灰度影像
        rgbframe.release();
        if(waitKey(1)>0)//if touch button end stream
        {
            // break;
        }
    }
}


void receivecenterdist() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.connect("tcp://192.168.91.97:9003");
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    zmq::message_t message;
    float dist = 0.0;

    while (true) {

        socket.recv(&message);
        size_t message_size = message.size();
        if (message_size == 0) {
            std::cerr << "Received empty message!" << std::endl;
            continue;
        }
        memcpy(&dist, message.data(), sizeof(float));
        std::cout << "center dist :" << dist << std::endl;
    }
}


int main() {


    // Create unique_ptr objects to manage threads
    std::unique_ptr<std::thread> threadir(new std::thread([&]{
        receiveirImages();
    }));

    std::unique_ptr<std::thread> threadil(new std::thread([&]{
        receiveilImages();
    }));

    std::unique_ptr<std::thread> threaddep(new std::thread([&]{
        receivedepImages();
    }));

    std::unique_ptr<std::thread> threadrgb(new std::thread([&]{
        receivergbImages();
    }));

    std::unique_ptr<std::thread> threaddist(new std::thread([&]{
        receivecenterdist();
    }));

// When threads are no longer needed, they will be automatically deleted


    while(true)
    {

    }


    return 0;
}
