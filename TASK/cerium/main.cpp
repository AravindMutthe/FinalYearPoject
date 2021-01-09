#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "core/cerium.hpp"
#include "utils/cliutils.hpp"
#include "external/digestpp/digestpp.hpp"

#include "auth/authentication.hpp"

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

auto main(int argc, char* argv[]) -> int {

    // get the parser
    auto parser = cerium::get_cliparser();
    auto args = parser.parse(argc, argv);

    if (args.count("help")) {
        std::cout << parser.help() << "\n";
        exit(0);
    }

    // authenticate the user

    // cerium::create_user("shadowleaf", "satyajit123");
    cerium::AUTH_CODE status = cerium::authenticate_user();

    // check if authentication failed
    if (status == cerium::AUTH_FAILED) {
        LOG_S(ERROR) << "exiting program";

        exit(EXIT_FAILURE);
    }

    // create a runner
    cerium::Runtime runner(args["working_dir"].as<std::string>());

    if (args["record"].as<bool>()) {
        // create a window
        cv::namedWindow("Live", cv::WINDOW_NORMAL);

        // setup the cameras and output file
        runner.setup_devices(args["cam"].as<int>(), 
                            args["output"].as<std::string>(), 
                            args["timestamp"].as<bool>());

        // process the input and write the output file
        runner.process_and_save(args["channel"].as<int>(), true);

        // close all high-gui windows
        cv::destroyAllWindows();
    }

    if (args["list"].as<bool>())
        runner.show_saved_files();


    return EXIT_SUCCESS;
}
