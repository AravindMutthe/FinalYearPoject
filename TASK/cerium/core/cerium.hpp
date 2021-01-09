#pragma once

#include <memory>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

namespace fs = std::filesystem;

namespace cerium
{

class Runtime {

private:
    std::unique_ptr<cv::VideoCapture> capture_device;
    std::unique_ptr<cv::VideoWriter> writer;
    fs::path working_dir;

public:
    Runtime(std::string working_dir);

    int setup_devices(int device_id, std::string output_file, bool timestamp);

    int process_and_save(int channel, bool verbose);

    void show_saved_files();

};

} // namespace cerium
