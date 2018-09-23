#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>

void toClipboard(const std::string &s) {
	OpenClipboard(nullptr);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (hg)
	{
		memcpy(GlobalLock(hg), s.c_str(), s.size());
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT, hg);
		GlobalFree(hg);
	}
	CloseClipboard();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	cv::VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	cv::Mat frame;
	cap >> frame; // get a new frame from camera

	std::time_t time = std::time(0);
	std::tm* now = std::localtime(&time);

	std::string path{ "D:\\Pictures\\Webcam\\" };
	std::string name{ "BAMBOOZLED_" + 
		std::to_string(now->tm_year % 100) +
		std::to_string(now->tm_mon)  +
		std::to_string(now->tm_mday) +
		std::to_string(now->tm_hour) +
		std::to_string(now->tm_min)  +
		std::to_string(now->tm_sec)  +
		".jpg" };

	cv::imwrite(path + name, frame);
	toClipboard(path + name);
	return 0;
}