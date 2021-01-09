#include "cerium.hpp"

#include <memory>
#include <chrono>
#include <filesystem>

#include <opencv2/opencv.hpp>

#define LOGURU_WITH_STREAMS 1
#include "../external/loguru.hpp"
#include "../utils/coreutils.hpp"

namespace fs = std::filesystem;

namespace cerium
{

Runtime::Runtime(std::string working_dir) : working_dir(working_dir) {
    // initialize the video capture
    capture_device = std::make_unique<cv::VideoCapture>();

    // turn off the printing thread info in the output
    loguru::g_preamble_thread = false;

    // turn off the uptime in the output
    loguru::g_preamble_uptime = false;

    // turn off the file_name
    // loguru::g_preamble_file = false;

    fs::create_directory(working_dir);
}

/**
 * Runtime::setup_devices
 * 
 * sets up the capture device and the write device
 * 
 * Args:
 *      device_id: default = 0 opens the default camera
 *      output_file: name of the output file without the extension name
 * Returns:
 *      int: exit_code
 * **/
int Runtime::setup_devices(int device_id = 0, std::string output_file = "output", bool timestamp = true) {

    int api_id = cv::CAP_ANY; // 0 = autodetect default API

    // open the selected camera
    this->capture_device->open(device_id + api_id);

    // check if we succeeded
    if (!this->capture_device->isOpened()) {
        LOG_S(ERROR) << "Unable to open camera" << '\n';
        return -1;
    }

    // Default resolution of the frame is obtained.The default resolution is system dependent. 
    auto S = cv::Size((int) this->capture_device->get(cv::CAP_PROP_FRAME_WIDTH),
                      (int) this->capture_device->get(cv::CAP_PROP_FRAME_HEIGHT));

    // get current timestamp
    auto tstamp = get_timestamp();

    std::string file_name = timestamp ? output_file + "_" + tstamp + ".avi" : output_file + ".avi";

    LOG_S(INFO) << "output file_name : " << file_name;

    cv::String file_location_string = (this->working_dir / file_name).string();

    // had problems with cap's fourcc
    auto writer_fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

    this->writer = std::make_unique<cv::VideoWriter>(file_location_string, writer_fourcc, this->capture_device->get(cv::CAP_PROP_FPS), S);

    return 0;

}

int Runtime::process_and_save(int channel = 2, bool verbose = false) {

    // checks for reader and writer devices
    assert(this->writer != nullptr);
    assert(this->capture_device->isOpened());

    // Default resolution of the frame is obtained.The default resolution is system dependent. 
    auto S = cv::Size((int) this->capture_device->get(cv::CAP_PROP_FRAME_WIDTH),
                      (int) this->capture_device->get(cv::CAP_PROP_FRAME_HEIGHT));

    cv::Mat frame;
    cv::Mat output;

    std::vector<cv::Mat> spl;

    LOG_S(INFO) << "Started Recording, "
                << "Press any key to terminate" << '\n';

    auto start = std::chrono::steady_clock::now();

    while(true) {
        *(this->capture_device) >> frame;

        // check if we have reached end
        if (frame.empty()) {
            LOG_S(ERROR) << "blank frame grabbed" << '\n';
            break;
        }

        // get the selected channel
        cv::split(frame, spl);
        for (auto i = 0 ; i < 3 ; i++) {
            if (i != channel)
                spl[i] = cv::Mat::zeros(S, spl[0].type());
            else
                cv::GaussianBlur(spl[i], spl[i], cv::Size(15, 15), 0, 0, cv::BORDER_DEFAULT);
        }

        cv::merge(spl, output);

        if (verbose) {
            cv::Mat display;
            cv::vconcat(frame, output, display);

            // show live and wait for a key with timeout long enough to show images
            imshow("Live" , display);
        }

        // write to the video file
        *(this->writer) << output;

        if (cv::waitKey(5) >= 0)
            break;

    }

    auto end = std::chrono::steady_clock::now();

    // calculate the recording time
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();


    LOG_S(INFO) << "recorded for " << elapsed << " ms";
    LOG_S(INFO) << "output written in " << this->working_dir;

    // *(this->writer).release();

    return 0;
}

// prints the files saved in working_dir
void Runtime::show_saved_files() {
    LOG_S(INFO) << "saved files in "<< this->working_dir;
    for (const auto &entry : fs::directory_iterator(this->working_dir)) {
        LOG_S(INFO) << entry.path();
    }
}

} // namespace cerium
