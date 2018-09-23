#include <Windows.h>
#include <opencv2/opencv.hpp>


int toGray(cv::Vec3b color)
{
	return (color[0] + color[1] + color[2]) / 3;
}

int avgColor(cv::Mat& image)
{
	const cv::Size imgSize{ image.size() };

	uint_fast64_t totalColor{ 0 };

	for (int i{ 0 }; i < imgSize.width; i++)
	{
		for (int j{ 0 }; j < imgSize.height; j++)
		{
			totalColor += toGray(image.at<cv::Vec3b>(j, i));
		}
	}
	return totalColor / (imgSize.width*imgSize.height);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	cv::VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	std::clock_t begin{ clock() };
	std::clock_t first_dark{ clock() };
	std::clock_t first_light{ clock() };

	bool dark_phase_done{ false };

	for (;;)
	{
		cv::Mat frame;
		cap >> frame; // get a new frame from camera

		if (avgColor(frame) != 0) first_dark = clock();
		else first_light = clock();

		if (!dark_phase_done && 
			static_cast<double>(clock() - first_dark) / static_cast<double>(CLOCKS_PER_SEC) >= 0.2)
				dark_phase_done = true; //Exits dark phase, enters light phase
		
		if (static_cast<double>(clock() - first_dark) / static_cast<double>(CLOCKS_PER_SEC) >= 1.)
				return 0; //If it is covered for too long it returns false

		if (dark_phase_done &&
			static_cast<double>(clock() - first_light) / static_cast<double>(CLOCKS_PER_SEC) >= 0.5)
			return 1;

		if (static_cast<double>(clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) >= 5.)return 0;
	}
} 