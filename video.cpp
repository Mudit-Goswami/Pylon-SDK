    #include <iostream>
    #include <string>
    #include <vector>
    #include <ctime>
    #include <opencv2/opencv.hpp>
    #include <opencv2/core/core.hpp>
    #include <opencv/highgui.h>
    #include <opencv/cv.h>
    #include<fstream>
    #include <pylon/PylonIncludes.h>
    #include<math.h>
    #include <iostream>
    #include <cmath>
    #include <string>
    // OpenCV libraries
    #include <fstream>
    #include <string>
    #include <vector>
    #include <ctime>
    #include <cstdlib>


    // Namespace for using pylon objects.
    using namespace Pylon;

    // Namespace for using GenApi objects
    using namespace GenApi;

    // Namespace for using opencv objects.
    using namespace cv;

    // Namespace for using cout.
    using namespace std;



    int main()
    {
    Pylon::PylonAutoInitTerm autoInitTerm;
     PylonInitialize();
    try
    {
        // Create an instant camera object with the camera device found first.
        CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());
        // Print the model name of the camera.
     cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
        // Create an instant camera object with the camera device found first.
       // CDeviceInfo info;
    //info.SetSerialNumber("21998726");
    //cout << "Creating Camera..." << endl;
    //CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());
    //cout << "Camera Created." << endl;
        // Print the model name of the camera.
        //cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;

        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        camera.MaxNumBuffer = 10;

    // create pylon image format converter and pylon image
    CImageFormatConverter formatConverter;
    formatConverter.OutputPixelFormat= PixelType_BGR8packed;
    CPylonImage pylonImage;

    // Create an OpenCV image
    Mat openCvImage;

        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        camera.StartGrabbing(GrabStrategy_LatestImageOnly);



        // This smart pointer will receive the grab result data.
        CGrabResultPtr ptrGrabResult;
        // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
        camera.RetrieveResult(500, ptrGrabResult, TimeoutHandling_ThrowException);
        int frame_width =  ptrGrabResult->GetWidth();
        int frame_height =  ptrGrabResult->GetHeight();

    VideoWriter video("out.avi",CV_FOURCC('M','J','P','G'),60, Size(frame_width,frame_height),true);
        // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
        // when c_countOfImagesToGrab images have been retrieved.
        while ( camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult(500, ptrGrabResult, TimeoutHandling_ThrowException);


        // Convert the grabbed buffer to pylon imag
        formatConverter.Convert(pylonImage, ptrGrabResult);
        // Create an OpenCV image out of pylon image
        openCvImage= cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

               video.write(openCvImage);
               imshow( "Frame", openCvImage );
               char c = (char)waitKey(1);
               if( c == 27 ) break;
            }
          return 0;
        }
     catch (GenICam::GenericException &e)
     {
         // Error handling.
         cerr << "An exception occurred." << endl
         << e.GetDescription() << endl;
    //            exitCode = 1;
     }

                               //        return exitCode;
                                   PylonTerminate();










    }
